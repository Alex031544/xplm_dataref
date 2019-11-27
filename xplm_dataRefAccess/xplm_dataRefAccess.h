/**
 * @author:     Christopher Ruwisch
 * @version:    0.2
 * @brief:      Access class for XPlane plugin
 * @date:       2019/11/22
 */

#ifndef _XPLM_DATAREFACCESS_H
#define _XPLM_DATAREFACCESS_H

// == SYSTEM INCLUDES
#include <cstdint>
#include <vector>
// == XPLANE SDK INCLUDES
#include "XPLM/XPLMDataAccess.h"

// == OWN INCLUDES
#include "xplm_dataRef.h"


// == CLASS DEFINITIONS

/**
 * Xplm_dataRefAccess Class
 * @brief: Reserving space + R/W of Variables via ENUM
 */
class Xplm_dataRefAccess
{
public:
    // == CONSTRUCTOR / DESTRUCTOR ==
    Xplm_dataRefAccess();
    ~Xplm_dataRefAccess();

    // == PUBLIC ATTRIBUTES ==

    // == PUBLIC METHODS ==
    bool initStorage(void);

	// GETTING DATA
	void readData(enum xplm_ref_E _num, uint8_t *data);
    void readData(enum xplm_ref_E _num, uint8_t *data, int offSet, int nElem);
	void readData(enum xplm_ref_E _num, int *data);
    void readData(enum xplm_ref_E _num, int *data, int offSet, int nElem);
	void readData(enum xplm_ref_E _num, float *data);
    void readData(enum xplm_ref_E _num, float *data, int offSet, int nElem);
	void readData(enum xplm_ref_E _num, double *data);

	// SETTING DATA
	void writeData(enum xplm_ref_E _num, uint8_t *data);
    void writeData(enum xplm_ref_E _num, uint8_t *data, int offSet, int nElem);
	void writeData(enum xplm_ref_E _num, int *data);
    void writeData(enum xplm_ref_E _num, int *data, int offSet, int nElem);
	void writeData(enum xplm_ref_E _num, float *data);
    void writeData(enum xplm_ref_E _num, float *data, int offSet, int nElem);
	void writeData(enum xplm_ref_E _num, double *data);

private:
    // == PRIVATE ATTRIBUTES ==
    std::vector<XPLMDataRef>    _refStorage;
    bool                        _isInit;

    // == PRIVATE METHODS ==
    bool isWritableRef(enum xplm_ref_E _num);
    int getType(enum xplm_ref_E _num);
    int getSize(enum xplm_ref_E _num);

};


#endif // _XPLM_DATAREFACCESS_H
