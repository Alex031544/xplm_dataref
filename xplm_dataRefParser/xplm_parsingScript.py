# =============================================================================
#   @brief: xPlane DataRef Parser for plugin
#   @author: Christopher Ruwisch
#
# =============================================================================

# == IMPORTS ==================================================================
import re


# == CONSTANTS ================================================================
readFile = "dataRef.txt"
writeFile = "headerTry.h"
# == FILEHANDLING =============================================================

# OPENING WRITEFILE
with open(writeFile,"w+") as dataRefHeader:
    headername = "_" + (writeFile.replace(".","_")).upper()
    dataRefHeader.writelines("#ifndef " + headername + "\n")
    dataRefHeader.writelines("#define " + headername + "\n")

    # OPENING CLOSEFILE
    with open(readFile,"r") as dataRefFile:

        # READING FILE
        for line in dataRefFile:


            if line.startswith("2"):

                header = line



            elif line.startswith("sim/"):


                # GET LINE
                ref         = line.split("\t")

                # VARNAME
                rName       = ref[0].replace("/","_")

                # TYPE AND LENGTH
                Type       = (ref[1].replace("]","[")).split("[",2)

                # CHECK FOR SIZE
                if(len(Type) > 1):
                    rLen = Type[1]
                else:
                    rLen = 1

                # CHECK FOR DATATYPES
                # - byte = 0
                # - int  = 1
                # - float = 2
                # - double = 3
                # - unknown = 4

                if(Type[0] == "byte"):
                    rType = 0

                elif(Type[0] == "int"):
                    rType = 1

                elif(Type[0] == "float"):
                    rType = 2

                elif(Type[0] == "double"):
                    rType = 3

                else:
                    rType = 4

                # CHECK FOR WRITABLE
                if(ref[2] == "y"):
                    rIsWrite    = 1
                else:
                    rIsWrite    = 0

                print(rName + " | " + str(rType) + " " + str(rLen) + " " + str(rIsWrite))

            # EMPTY LINES
            else:
                continue









    # == PARSING INSTRUCTIONS =====================================================

    dataRefHeader.writelines("#endif //" + headername + "\n")