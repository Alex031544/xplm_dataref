import collections

def preProcessDataRef(line):
    if line.startswith("sim/"):

        # GET LINE
        ref     = line.split("\t")
        ref[0]  = ref[0].replace("position/elevation","position/altitude")
        # VARNAME
        rName   = ref[0].replace("/", "_")

        # TYPE AND LENGTH
        type    = (ref[1].replace("]","[")).split("[",2)

        # CHECK FOR SIZE
        if(len(type) > 1):
            rLen = type[1]
        else:
            rLen = 1

        # CHECK FOR DATATYPES
        # - byte    = 0
        # - int     = 1
        # - float   = 2
        # - double  = 3
        # - unknown = 4

        if(type[0] == "byte"):
            rType = 0
        elif(type[0] == "int"):
            rType = 1
        elif(type[0] == "float"):
            rType = 2
        elif(type[0] == "double"):
            rType = 3
        else:
            rType = 4

        if(ref[2] == "y"):
            rIsWrite = 1
        else:
            rIsWrite = 0

        processedData = collections.namedtuple('dataref',['ref','var','type','size','isWrite'])
        return processedData(ref[0],rName,rType,rLen,rIsWrite)


