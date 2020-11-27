/**
 * @author:     Christopher Ruwisch, Alexander Behrens
 * @version:    1.0
 * @brief:      Access class for XPlane plugin
 * @date:       2020/11/27
 */

#include "xplm_dataRefAccess.h"
#include "common/errPrint.h"


Xplm_dataRefAccess::Xplm_dataRefAccess ()
{
    // ADDING ELEMENTS TO VECTOR
    _refStorage.reserve(MAXSIZEREFS);
    _isInit = false;
    // CALL DESTRUCTOR IF NOT ENOUGH SPACE IS SET
    if (_refStorage.capacity() != MAXSIZEREFS) {
        print_xplog("Could not reserve enought space");
    }

    initStorage();
}


Xplm_dataRefAccess::~Xplm_dataRefAccess ()
{
}


bool
Xplm_dataRefAccess::initStorage (void)
{
    // CHECK IF ALREADY INIT
    if (!_isInit) {

        for (uint32_t i = 0; i < MAXSIZEREFS; ++i) {
            _refStorage[i] = XPLMFindDataRef(xplm_ref[i].refName);
            if (_refStorage[i] == NULL) {
                print_xplog("ID[%04d] ... %s wasn't found\n", i, xplm_ref[i].refName);
            }
        }
        // SET INIT FLAG
        _isInit = true;
    }
    return _isInit;
}


void
Xplm_dataRefAccess::readData (enum xplm_ref_e ref, uint8_t *data)
{
    if (data == NULL) {
        return;
    }
    else {
        // ToDo errorhandling
        XPLMGetDatab(_refStorage[ref], data, 0, getSize(ref));
    }
}


void
Xplm_dataRefAccess::readData (enum xplm_ref_e ref,
                              uint8_t *data,
                              int offSet,
                              int nElem)
{
    if (data == NULL) {
        return;
    }
    else {
        XPLMGetDatab(_refStorage[ref], data, offSet, nElem);
    }
}


void
Xplm_dataRefAccess::readData (enum xplm_ref_e ref, int *data)
{
    if (data == NULL) {
        return;
    }
    else {
        // ToDo errorhandling
        if (getSize(ref) > 1) {
            XPLMGetDatavi(_refStorage[ref], data, 0, getSize(ref));
        }
        else {
            *data = XPLMGetDatai(_refStorage[ref]);
        }
    }
}


void
Xplm_dataRefAccess::readData (enum xplm_ref_e ref,
                              int *data,
                              int offSet,
                              int nElem)
{
    if (data == NULL) {
        return;
    }
    else {
        XPLMGetDatavi(_refStorage[ref], data, offSet, nElem);
    }
}


void
Xplm_dataRefAccess::readData (enum xplm_ref_e ref, float *data)
{

    if (data == NULL) {
        return;
    }
    else {
        // ToDo errorhandling
        if (getSize(ref) > 1) {
            XPLMGetDatavf(_refStorage[ref], data, 0, getSize(ref));
        }
        else {
            *data = XPLMGetDataf(_refStorage[ref]);
        }
    }
}


void
Xplm_dataRefAccess::readData (enum xplm_ref_e ref,
                              float *data,
                              int offSet,
                              int nElem)
{
    if (data == NULL) {
        return;
    }
    else {
        XPLMGetDatavf(_refStorage[ref], data, offSet, nElem);
    }
}


void
Xplm_dataRefAccess::readData (enum xplm_ref_e ref, double *data)
{
    if (data == NULL) {
        return;
    }
    else {
        // ToDo errorhandling
        *data = XPLMGetDatad(_refStorage[ref]);
    }
}


void
Xplm_dataRefAccess::writeData (enum xplm_ref_e ref, uint8_t *data)
{
    if (data == NULL) {
        return;
    }
    else {
        // ToDo errorhandling
        XPLMSetDatab(_refStorage[ref], data, 0, getSize(ref));
    }
}


void
Xplm_dataRefAccess::writeData (enum xplm_ref_e ref, uint8_t *data, int offSet, int nElem)
{
    if (data == NULL) {
        return;
    }
    else {
        XPLMSetDatab(_refStorage[ref], data, offSet, nElem);
    }
}


void
Xplm_dataRefAccess::writeData (enum xplm_ref_e ref, int *data)
{
    if (data == NULL) {
        return;
    }
    else {
        // ToDo errorhandling
        if (getSize(ref) > 1) {
            XPLMSetDatavi(_refStorage[ref], data, 0, getSize(ref));
        }
        else {
            XPLMSetDatai(_refStorage[ref], *data);
        }
    }
}


void
Xplm_dataRefAccess::writeData (enum xplm_ref_e ref,
                               int *data,
                               int offSet,
                               int nElem)
{
    if (data == NULL) {
        return;
    }
    else {
        XPLMSetDatavi(_refStorage[ref], data, offSet, nElem);
    }
}


void
Xplm_dataRefAccess::writeData (enum xplm_ref_e ref, float *data)
{
    if (data == NULL) {
        return;
    }
    else {
        // ToDo errorhandling
        if (getSize(ref) > 1) {
            XPLMSetDatavf(_refStorage[ref], data, 0, getSize(ref));
        }
        else {
            XPLMSetDataf(_refStorage[ref], *data);
        }
    }
}


void
Xplm_dataRefAccess::writeData (enum xplm_ref_e ref,
                               float *data,
                               int offSet,
                               int nElem)
{
    if (data == NULL) {
        return;
    }
    else {
        XPLMSetDatavf(_refStorage[ref], data, offSet, nElem);
    }
}


void
Xplm_dataRefAccess::writeData (enum xplm_ref_e ref, double *data)
{
    if (data == NULL) {
        return;
    }
    else {
        // ToDo errorhandling
        XPLMSetDatad(_refStorage[ref], *data);
    }
}


bool
Xplm_dataRefAccess::isWritableRef (enum xplm_ref_e ref)
{
    if (xplm_ref[ref].isWritable) {
        return true;
    }
    return false;
}


xplm_types_t
Xplm_dataRefAccess::getType (enum xplm_ref_e ref)
{
    return xplm_ref[ref].type;
}


int
Xplm_dataRefAccess::getSize (enum xplm_ref_e ref)
{
    return xplm_ref[ref].size;
}
