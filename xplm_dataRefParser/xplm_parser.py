# == XPLANE PLUGIN DATAREF PARSING TO CPP HEADER ===============================
# @author:  Christopher Ruwisch
# @date:    19/11/2019
# @version: 0.0
# @brief:   Parser for datareferences from XPLANE SDK to build a plugin for
#           different applications
# ==============================================================================

from parseData import *
# == START SCRIPT ==============================================================

pathToRefFile   = ""
referenceFile   = "DataRefs.txt"
headerFile      = "xplm_dataRef.h"

# == READING DATAREFERENCE FILE ===============================================
with open(pathToRefFile + referenceFile,"r") as refFile:
    refDataContent = refFile.readlines()

# == PREPROCESS DATA ==========================================================

header  = refDataContent[0]
rawData = refDataContent[2:]
rawDataSize = len(rawData)

dataRef = []
for idx in range(rawDataSize):
    dataRef.append(preProcessDataRef(rawData[idx]))


maxSizeString = max(len(element.ref) for element in dataRef) + 1

# == FILE CREATION ============================================================
with open(headerFile,"w+") as wFile:
    _hName = "_" + (headerFile.replace(".","_")).upper()
    wFile.writelines("#ifndef " + _hName + "\n")
    wFile.writelines("#define " + _hName + "\n\n")

    wFile.writelines("// == DEFINES =================================================================\n")
    wFile.writelines("#define MAXSIZESTRING\t" + str(maxSizeString) + "\n")
    wFile.writelines("#define MAXSIZEREFS\t\t" + str(rawDataSize) + "\n\n")

    wFile.writelines("// == TYPEDEFS ================================================================\n")

    # Typedef Struct xplm_dRef_t(START) - VARIABLE
    wFile.writelines("typedef struct {\n")
    # Structelements
    wFile.writelines("\tchar refName[MAXSIZESTRING];\n")
    wFile.writelines("\tint type;\t\t // 0 - BYTE | 1 - INT | 2 - FLOAT | 3 - DOUBLE | 4 - UNKNOWN\n")
    wFile.writelines("\tint size;\t\t // NUMBER OF ELEMENT\n")
    wFile.writelines("\tint isWrite;\t // 1 - YES | 0 - NO //\n")
    # Typedef Struct (END)
    wFile.writelines("} xplm_ref_t;\n\n")
    wFile.writelines("// HINT: Array in this File \"xplm_ref[MAXSIZEREFS]\"\n\n")

    wFile.writelines("// == ENUMERATION =============================================================\n")
    # Data access enums (START)
    wFile.writelines("enum xplm_ref {\n")
    # Data access enums
    for element in dataRef:
        wFile.writelines("\tXPLM_" + (element.var).upper() + ",\n")
    # Data access enums (END)
    wFile.writelines("};\n\n")

    wFile.writelines("// == REFERENCES ==============================================================\n")
    # Const struct xplm_ref_t (START)
    wFile.writelines("const xplm_ref_t xplm_ref[MAXSIZEREFS] = {\n")
    for element in dataRef:
        wFile.writelines("\t{" + "\"" + element.ref +"\",")
        wFile.writelines(" " + str(element.type) + ", " + str(element.size) + ", " + str(element.isWrite))
        wFile.writelines("},\n")

    # Const struct xplm_ref_t (END)
    wFile.writelines("};\n")

    wFile.writelines("#endif //" + _hName + "\n")











