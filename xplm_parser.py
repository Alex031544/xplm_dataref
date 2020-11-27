# == XPLANE PLUGIN DATAREF PARSING TO CPP HEADER ===============================
# @author:  Christopher Ruwisch, Alexander Behrens
# @date:    27/11/2020
# @version: 1.0
# @brief:   Parser for datareferences from XPLANE SDK to build a plugin for
#           different applications
# ==============================================================================
import re
import sys
from functools import reduce
from string import Template


class DataRef:
    def __init__(self, path: str = '',
                 data_type: str = 'XPLM_UNKNOWN',
                 data_dim: int = 1,
                 writeable: str = 'XPLM_WRITABLE',
                 unit: str = None,
                 brief: str = None,
                 description: str = ''):
        self.path = path
        self.path_len = len(path)
        self.data_type = data_type
        self.data_dim = data_dim
        self.writeable = writeable
        self.unit = unit
        self.brief = brief
        self.description = description

    def set_path(self, path: str):
        self.path = path
        self.path_len = len(path)


def parse_line(line):
    if line.startswith('sim/'):
        line = line.strip()

        # first section contains the path
        finding = re.match(r'sim[\w/\[\]]+\t+', line)
        dref = DataRef(path=finding.group().strip())
        line = line[finding.end():]

        # second section contains the data type and its dimension
        finding = re.match(r'[\w/\[\]]+\t+', line)
        line = line[finding.end():]
        if "byte" in finding.group():
            dref.data_type = 'XPLM_BYTE'
        elif "int" in finding.group():
            dref.data_type = 'XPLM_INT'
        elif "float" in finding.group():
            dref.data_type = 'XPLM_FLOAT'
        elif "double" in finding.group():
            dref.data_type = 'XPLM_DOUBLE'
        else:
            dref.data_type = 'XPLM_UNKNOWN'

        dim = re.search(r'(?<=\[)\d+(?=])', finding.group())
        if dim:
            dref.data_dim = int(dim.group())

        # third section contains the write-ability (overwrite default if not)
        finding = re.match(r'[ny]\t*', line)
        line = line[finding.end():]

        if 'n' in finding.group():
            dref.writeable = 'XPLM_NONWRITABLE'

        if len(line) == 0:
            return dref

        # fourth section contains the unit - may not exist
        def get_unit(line):
            finding = re.match(r'\[[\s+\-\w.]*]', line)
            if finding:
                dref.unit = re.sub(r'(?<=\d)\s*-\s*(?=\d)', '', finding.group())
                return line[finding.end():].lstrip()

            finding = re.match(r'[ ,+\-\w./]*(?=\t)', line)
            if finding:
                dref.unit = finding.group()
                return line[finding.end():].lstrip()

            return line

        # fifth section contains the description - may not exist
        dref.description = get_unit(line)

        return dref

    return None


def xplm_parser(dataref_file):
    replacements = dict()

    with open(dataref_file) as f:
        dataRefs = f.readlines()

    # extract the version number from the first line of the file and split it to major and minor (last two digits)
    replacements['DREV_VERSION'] = dataRefs[0].split(' ')[1][:-2] + '.' + dataRefs[0].split(' ')[1][-2:]

    # extract the issue date from the first line of the file
    replacements['DREV_ISSUEDATE_Y'] = dataRefs[0].split(' ')[-1].strip()
    replacements['DREV_ISSUEDATE_M'] = dataRefs[0].split(' ')[-4]
    replacements['DREV_ISSUEDATE_D'] = dataRefs[0].split(' ')[-3]

    # parse rest of the file beginning from the third line
    dataRefs = list(map(parse_line, dataRefs[2:]))

    lengths = list(map(lambda d: d.path_len, dataRefs))
    replacements['MAXSIZESTRING'] = reduce(lambda l1, l2: l1 if l1 > l2 else l2, lengths)

    replacements['MAXSIZEREFS'] = len(dataRefs)

    replacements['XPLM_ENUMS'] = '\n'.join(list(map(lambda d: '    /** @brief {descr}\n'
                                                              '     * \n'
                                                              '     * unit: {unit}\n'
                                                              '     * size: {size}\n'
                                                              '     * is writeable: {wr}\n'
                                                              '     * path: {path}\n'
                                                              '     */\n'
                                                              '    XPLM_{enum},\n'
                                                    .format(enum=d.path.replace('/', '_')
                                                                       .replace('[', '_')
                                                                       .replace(']', '')
                                                                       .upper(),
                                                            descr=d.description,
                                                            unit=d.unit,
                                                            size=d.data_dim,
                                                            wr='yes' if d.writeable == 'XPLM_WRITABLE' else 'no',
                                                            path=d.path
                                                            ), dataRefs))).rstrip()

    replacements['XPLM_REFS'] = '\n'.join(list(map(lambda d: '    {\"%s\", %s, %d, %s},' % (
        d.path, d.data_type, d.data_dim, d.writeable), dataRefs)))

    # fixes
    replacements['XPLM_ENUMS'] = re.sub(r'(?<=path: sim/flightmodel/position/q\n'
                                        r'     \*/\n'
                                        r'    )XPLM_SIM_FLIGHTMODEL_POSITION_Q(?=,)',
                                        'XPLM_SIM_FLIGHTMODEL_POSITION_QUAT',
                                        replacements['XPLM_ENUMS'])


    with open('xplm_dataRef.h.template') as f:
        xplm_dataRef_template = Template(f.read())

    print('Write resulting header file to xplm_dataRefAccess/xplm_dataRef.h')
    with open('xplm_dataRefAccess/xplm_dataRef.h', mode='w', encoding='utf-8', newline='\n') as f:
        f.write(xplm_dataRef_template.substitute(replacements))


if __name__ == '__main__':
    dataref_file = 'datarefs/DataRefs.txt.1135'

    if len(sys.argv) > 1:
        dataref_file = sys.argv[1]
    else:
        print('No DataRef.txt specified. Use default one.')

    print('Translate %s' % dataref_file)
    xplm_parser(dataref_file)
