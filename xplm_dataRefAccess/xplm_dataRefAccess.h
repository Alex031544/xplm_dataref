/**
 * @author:     Christopher Ruwisch, Alexander Behrens
 * @version:    1.0
 * @brief:      Access class for XPlane plugin
 * @date:       2020/11/27
 */

#ifndef XPLM_DATAREFACCESS_H_INCLUDED
#define XPLM_DATAREFACCESS_H_INCLUDED

// standard includes
#include <cstdint>
#include <vector>
// XPLANE SDK includes
#include "XPLM/XPLMDataAccess.h"

#include "xplm_dataRef.h"


/** @brief: Xplm_dataRefAccess Class
 *
 * Reserving space + R/W of Variables via ENUM
 */
class Xplm_dataRefAccess
{
public:
    /** @brief Constructor
     */
    Xplm_dataRefAccess ();

    /** @brief Destructor
     */
    ~Xplm_dataRefAccess ();

    /** @brief initialise datarefs (singleton)
     *
     * @return true if successful otherwise false
     */
    bool initStorage (void);

    /** @brief Read data of type uint8_t from XPlane internal memory
     *
     * @param ref   Dataref key
     * @param data  store the data to the buffer pointed to by data
     */
    void readData (enum xplm_ref_e ref, uint8_t *data);

    /** @brief Read data of type uint8_t[] from XPlane internal memory
     *
     * @param ref     Dataref key
     * @param data    store the data to the buffer pointed to by data
     * @param offSet  offset where to begin copying data from source array
     * @param nElem   number of elements to copy beginning from the offset
     */
    void readData (enum xplm_ref_e ref, uint8_t *data, int offSet, int nElem);

    /** @brief Read data of type int from XPlane internal memory
     *
     * @param ref   Dataref key
     * @param data  store the data to the buffer pointed to by data
     */
    void readData (enum xplm_ref_e ref, int *data);

    /** @brief Read data of type int[] from XPlane internal memory
     *
     * @param ref     Dataref key
     * @param data    store the data to the buffer pointed to by data
     * @param offSet  offset where to begin copying data from source array
     * @param nElem   number of elements to copy beginning from the offset
     */
    void readData (enum xplm_ref_e ref, int *data, int offSet, int nElem);

    /** @brief Read data of type float from XPlane internal memory
     *
     * @param ref   Dataref key
     * @param data  store the data to the buffer pointed to by data
     */
    void readData (enum xplm_ref_e ref, float *data);

    /** @brief Read data of type float[] from XPlane internal memory
     *
     * @param ref     Dataref key
     * @param data    store the data to the buffer pointed to by data
     * @param offSet  offset where to begin copying data from source array
     * @param nElem   number of elements to copy beginning from the offset
     */
    void readData (enum xplm_ref_e ref, float *data, int offSet, int nElem);

    /** @brief Read data of type double from XPlane internal memory
     *
     * @param ref   Dataref key
     * @param data  store the data to the buffer pointed to by data
     */
    void readData (enum xplm_ref_e ref, double *data);

    /** @brief Write data of type uint8_t to the XPlane internal memory
     *
     * @param ref   Dataref key
     * @param data  take the data from the buffer pointed to by data
     */
    void writeData (enum xplm_ref_e ref, uint8_t *data);

    /** @brief Write data of type uint8_t[] to the XPlane internal memory
     *
     * @param ref     Dataref key
     * @param data    take the data from the buffer pointed to by data
     * @param offSet  offset where to begin copying data to the source array
     * @param nElem   number of elements to copy beginning from the offset
     */
    void writeData (enum xplm_ref_e ref, uint8_t *data, int offSet, int nElem);

    /** @brief Write data of type int to the XPlane internal memory
     *
     * @param ref   Dataref key
     * @param data  take the data from the buffer pointed to by data
     */
    void writeData (enum xplm_ref_e ref, int *data);

    /** @brief Write data of type int[] to the XPlane internal memory
     *
     * @param ref     Dataref key
     * @param data    take the data from the buffer pointed to by data
     * @param offSet  offset where to begin copying data to the source array
     * @param nElem   number of elements to copy beginning from the offset
     */
    void writeData (enum xplm_ref_e ref, int *data, int offSet, int nElem);

    /** @brief Write data of type float to the XPlane internal memory
     *
     * @param ref   Dataref key
     * @param data  take the data from the buffer pointed to by data
     */
    void writeData (enum xplm_ref_e ref, float *data);

    /** @brief Write data of type float[] to the XPlane internal memory
     *
     * @param ref     Dataref key
     * @param data    take the data from the buffer pointed to by data
     * @param offSet  offset where to begin copying data to the source array
     * @param nElem   number of elements to copy beginning from the offset
     */
    void writeData (enum xplm_ref_e ref, float *data, int offSet, int nElem);

    /** @brief Write data of type double to the XPlane internal memory
     *
     * @param ref   Dataref key
     * @param data  take the data from the buffer pointed to by data
     */
    void writeData (enum xplm_ref_e ref, double *data);

    /** @brief Informs if the field of XPlane memory is writable or not
     * 
     * @param ref   Dataref key
     * @return      true if writeable or false otherwise
     */
    bool isWritableRef (enum xplm_ref_e ref);

    /** @brief Informs about the data type a field of XPlane memory have
     * 
     * @param ref   Dataref key
     * @return      The datatype represented by enum type xplm_types_t
     */
    xplm_types_t getType (enum xplm_ref_e ref);

    /** @brief Informs about the data size a field of XPlane memory have
     * 
     * @param ref   Dataref key
     * @return      The size of the field. A size greater than 1 indicates an array.
     */
    int getSize (enum xplm_ref_e ref);

private:
    /** @brief a vector containing all pointers to the fields in the XPlane memory */
    std::vector <XPLMDataRef> _refStorage;

    /** @brief keeps the information if the datarefs are already initialised */
    bool _isInit;
};


#endif // XPLM_DATAREFACCESS_H_INCLUDED
