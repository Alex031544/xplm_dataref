# XPLM_DATAREF - Repository

__Repository Description__  
This repository is used to provide functions for creation of a *headerfile* with a description of all available data-references for the __XPLANE 11 API__. This repository contains two folders:
- __xplm_dataRefAccess__ - *xplm_dataRefAccess.cpp/.h* which provide read/write functionality to desired data-references provided by *xplm_dataRef.h*
- __xplm_dataRefParser__ - Python parser from *DataRef.txt* to *xplm_dataRef.h*


*( Dataref.txt can be found within the XPlane installation folder: <path_to_XPlane11>/Resources/plugins )*.

## __xplm_dataRefParser__  
Run xplm_parser.py by (DataRefs.txt has to be in the same folder):
```
...$ python3 xplm_parser.py
```
This parser generates xplm_dataRef.h - The outputfilename can be changed in xplm_parser.py by changing the *headerFile*-Name. If the *DataRefs.txt*-File is not included in the same directory, provide the path in xplm_parser.py with *pathToRefFile*.  

  __ATTENTION: If the *headerFile*-Name is changed, you have to change this Name in xplm_dataRefAccess.h also.__

The references are provides as enums as the _xplm_ref_E_-Type. The associated _const xplm_ref_t xplm_ref[...]_-struct contains four Elements:
1. __char refName[...]__ - String of the associated data-reference
2. __int type__ - Datatype: 0 - BYTE | 1 - INT | 2 - FLOAT | 3 - DOUBLE | 4- UNKNOWN
3. __int size__ - Number of Elements of this type
4. __int isWritable__ - Provides information if data-reference is writable (1 - YES | 0 - NO)
## __xplm_dataRefAccess__
In this folder, xplm_dataRefAccess.cpp/.h provide funcitonality to read/write to the data-references from xplm_dataRef.h. Herein are several read/write functions for every datatype.

The constructor of this .cpp-class reserves memory by a vector for all references.  
__ATTENTION: Do not resize the vector - enumerations and xplm_ref will cannot be assigned correctly if resizing the vector to save memory__  


The references will be loaded by `initStorage`-method. For read and write functionality, use the methods `readData` and `writeData`. These methods are overloaded. Use the correct datatypes:
0. __BYTE__ - *uint8_t*
1. __INT__ - *int*
2. __FLOAT__ - *float*
3. __DOUBLE__ - *double*

For full access, use methods with two arguments:
```
readData(enum xplm_ref_E _num, <desired type> *data)
writeData(enum xplm_ref_E _num, <desired type> *data)
```
These methods deliver all data to the datapointer. Check with `getSize()`-method for datasize.

For partial access, use following methods:
```
readData(enum xplm_ref_E _num, <desired type> *data, int offSet, int nElem);
writeData(enum xplm_ref_E _num, <desired type> *data, int offSet, int nElem);

```
__ATTENTION: There is actually no check for leaving elementsize by offset. Be aware of this situation__
