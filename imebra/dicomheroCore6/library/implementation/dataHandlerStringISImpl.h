/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

/*! \file dataHandlerStringIS.h
    \brief Declaration of the class dataHandlerStringIS.

*/

#if !defined(imebraDataHandlerStringIS_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_)
#define imebraDataHandlerStringIS_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_

#include "dataHandlerStringImpl.h"


namespace dicomhero
{

namespace implementation
{

namespace handlers
{

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief Handles the Dicom type "IS" (integer string)
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class readingDataHandlerStringIS : public readingDataHandlerStringNumbers
{
public:
    readingDataHandlerStringIS(const memory& parseMemory);

    // Overwritten to use getInt32()
    ///////////////////////////////////////////////////////////
    virtual double getDouble(const size_t index) const override;

};

class writingDataHandlerStringIS: public writingDataHandlerStringNumbers
{
public:
    writingDataHandlerStringIS(const std::shared_ptr<buffer> pBuffer);

    // Overwritten to use setInt32()
    ///////////////////////////////////////////////////////////
    virtual void setDouble(const size_t index, const double value) override;

    // Overwritten to use setInt32()
    ///////////////////////////////////////////////////////////
    virtual void setFloat(const size_t index, const float value) override;
};

} // namespace handlers

} // namespace implementation

} // namespace dicomhero

#endif // !defined(imebraDataHandlerStringIS_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_)
