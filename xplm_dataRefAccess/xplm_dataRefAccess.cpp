/**
 * @author:     Christopher Ruwisch
 * @version:    0.3
 * @brief:      Access class for XPlane plugin
 * @date:       2019/11/27
 */

#include "xplm_dataRefAccess.h"
#include "../common/errPrint.h"
/**
 * [Xplm_dataRefAccess::Xplm_dataRefAccess description]
 */
Xplm_dataRefAccess::Xplm_dataRefAccess() {

    // ADDING ELEMENTS TO VECTOR
    _refStorage.reserve(MAXSIZEREFS);
    _isInit = false;
    // CALL DESTRUCTOR IF NOT ENOUGH SPACE IS SET
    if(_refStorage.capacity() != MAXSIZEREFS) {
        print_xplog("Could not reserve enought space");
    }

	initStorage();
}

/**
 * [Xplm_dataRefAccess description]
 */
Xplm_dataRefAccess::~Xplm_dataRefAccess() {
    // DESTRUCTOR TASKS HERE
}


/**
 * [Xplm_dataRefAccess::initStorage description]
 * @return  [description]
 */
bool Xplm_dataRefAccess::initStorage(void) {
    // CHECK IF ALREADY INIT
    if(!_isInit) {

        for(uint32_t i = 0; i < MAXSIZEREFS; ++i) {
            _refStorage[i] = XPLMFindDataRef(xplm_ref[i].refName);
            if(_refStorage[i] == NULL) {
                print_xplog("ID[%04d] ... %s wasn't found\n",i,xplm_ref[i].refName);
            }
        }
        // SET INIT FLAG
        _isInit = true;
    }
    return _isInit;
}

// == READ FUNCTIONS ===========================================================
/**
 * [readData description]
 * @param _num [description]
 * @param data [description]
 */
void Xplm_dataRefAccess::readData(enum xplm_ref_E _num, uint8_t *data) {


    if(data == NULL) {
        return;
    }
    else {
        // To Do errorhandling
        XPLMGetDatab(_refStorage[_num],data,0,getSize(_num));
    }
}

void Xplm_dataRefAccess::readData(enum xplm_ref_E _num,
                                  uint8_t *data,
                                  int offSet,
                                  int nElem)
{
    if(data == NULL) {
        return;
    }
    else {
        XPLMGetDatab(_refStorage[_num],data,offSet,nElem);
    }
}

/**
 * [Xplm_dataRefAccess::readData description]
 * @param _num [description]
 * @param data [description]
 */
void Xplm_dataRefAccess::readData(enum xplm_ref_E _num, int *data) {

    if(data == NULL) {
        return;
    }
    else {
        // To Do errorhandling
        if(getSize(_num) > 1) {
            XPLMGetDatavi(_refStorage[_num],data,0,getSize(_num));
        }
        else {
            *data = XPLMGetDatai(_refStorage[_num]);
        }
    }
}

/**
 * [Xplm_dataRefAccess::readData description]
 * @param _num   [description]
 * @param data   [description]
 * @param offSet [description]
 * @param nElem  [description]
 */
void Xplm_dataRefAccess::readData(enum xplm_ref_E _num,
                                  int *data,
                                  int offSet,
                                  int nElem)
{
    if(data == NULL) {
        return;
    }
    else {
        XPLMGetDatavi(_refStorage[_num],data,offSet,nElem);
    }
}

/**
 * [Xplm_dataRefAccess::readData description]
 * @param _num [description]
 * @param data [description]
 */
void Xplm_dataRefAccess::readData(enum xplm_ref_E _num, float *data) {

    if(data == NULL) {
        return;
    }
    else {
        // To Do errorhandling
        if(getSize(_num) > 1) {
            XPLMGetDatavf(_refStorage[_num],data,0,getSize(_num));
        }
        else {
            *data = XPLMGetDataf(_refStorage[_num]);
        }
    }
}

/**
 * [Xplm_dataRefAccess::readData description]
 * @param _num   [description]
 * @param data   [description]
 * @param offSet [description]
 * @param nElem  [description]
 */
void Xplm_dataRefAccess::readData(enum xplm_ref_E _num,
                                  float *data,
                                  int offSet,
                                  int nElem)
{
    if(data == NULL) {
        return;
    }
    else {
        XPLMGetDatavf(_refStorage[_num],data,offSet,nElem);
    }
}

/**
 * [Xplm_dataRefAccess::readData description]
 * @param _num [description]
 * @param data [description]
 */
void Xplm_dataRefAccess::readData(enum xplm_ref_E _num, double *data) {

    if(data == NULL) {
        return;
    }
    else {
        // To Do errorhandling
        *data = XPLMGetDatad(_refStorage[_num]);
    }
}

// == WRITE FUNCTIONS ==========================================================
/**
 * [Xplm_dataRefAccess::writeData description]
 * @param _num [description]
 * @param data [description]
 */
void Xplm_dataRefAccess::writeData(enum xplm_ref_E _num, uint8_t *data) {

    if(data == NULL) {
        return;
    }
    else {
        // To Do errorhandling
        XPLMSetDatab(_refStorage[_num],data,0,getSize(_num));
    }
}

/**
 * [Xplm_dataRefAccess::writeData description]
 * @param _num   [description]
 * @param data   [description]
 * @param offSet [description]
 * @param nElem  [description]
 */
void Xplm_dataRefAccess::writeData(enum xplm_ref_E _num, uint8_t *data,int offSet, int nElem) {
    if(data == NULL) {
        return;
    }
    else {
        XPLMSetDatab(_refStorage[_num],data,offSet,nElem);
    }
}

/**
 * [Xplm_dataRefAccess::writeData description]
 * @param _num [description]
 * @param data [description]
 * @param off  [description]
 * @param n    [description]
 */
void Xplm_dataRefAccess::writeData(enum xplm_ref_E _num, int *data)
{
	if(data == NULL) {
		return;
	}
	else {
		// To Do errorhandling
		if(getSize(_num) > 1) {
			XPLMSetDatavi(_refStorage[_num], data, 0, getSize(_num));
		}
		else {
			XPLMSetDatai(_refStorage[_num], *data);
		}
	}
}

/**
 * [Xplm_dataRefAccess::writeData description]
 * @param _num   [description]
 * @param data   [description]
 * @param offSet [description]
 * @param nElem  [description]
 */
void Xplm_dataRefAccess::writeData(enum xplm_ref_E _num,
                                   int *data,
                                   int offSet,
                                   int nElem)
{
    if(data == NULL) {
        return;
    }
    else {
        XPLMSetDatavi(_refStorage[_num],data,offSet,nElem);
    }
}

/**
 * [Xplm_dataRefAccess::writeData description]
 * @param _num [description]
 * @param data [description]
 */
void Xplm_dataRefAccess::writeData(enum xplm_ref_E _num, float *data) {

    if(data == NULL) {
        return;
    }
    else {
        // To Do errorhandling
        if(getSize(_num) > 1) {
            XPLMSetDatavf(_refStorage[_num],data,0,getSize(_num));
        }
        else {
            XPLMSetDataf(_refStorage[_num],*data);
        }
    }
}

void Xplm_dataRefAccess::writeData(enum xplm_ref_E _num,
                                   float *data,
                                   int offSet,
                                   int nElem)
{
    if(data == NULL) {
        return;
    }
    else {
        XPLMSetDatavf(_refStorage[_num],data,offSet,nElem);
    }
}

/**
 * [Xplm_dataRefAccess::writeData description]
 * @param _num [description]
 * @param data [description]
 */
void Xplm_dataRefAccess::writeData(enum xplm_ref_E _num, double *data) {

    if(data == NULL) {
        return;
    }
    else {
        // To Do errorhandling
        XPLMSetDatad(_refStorage[_num],*data);
    }
}

/**
 * [Xplm_dataRefAccess::isWritableRef description]
 * @param  _num [description]
 * @return      [description]
 */
bool Xplm_dataRefAccess::isWritableRef(enum xplm_ref_E _num) {
    if(xplm_ref[_num].isWritable) {
        return true;
    }
    return false;
}

/**
 * [Xplm_dataRefAccess::getType description]
 * @param  _num [description]
 * @return      [description]
 */
int Xplm_dataRefAccess::getType(enum xplm_ref_E _num) {
    return xplm_ref[_num].type;
}

/**
 * [Xplm_dataRefAccess::getSize description]
 * @param  _num [description]
 * @return      [description]
 */
int Xplm_dataRefAccess::getSize(enum xplm_ref_E _num) {
    return xplm_ref[_num].size;
}
