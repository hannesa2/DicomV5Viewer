/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement 
 that your application must also be GPL), you may purchase a commercial 
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

/*! \file dataHandlerStringUR.h
    \brief Declaration of the class dataHandlerStringUR.

*/

#if !defined(imebraDataHandlerStringUR_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_)
#define imebraDataHandlerStringUR_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_

#include "dataHandlerStringImpl.h"
#include <map>
#include <string>


namespace dicomhero
{

namespace implementation
{

namespace handlers
{


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief Handles the Dicom data type "UR" (universal
///         resource identifier)
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class readingDataHandlerStringUR : public readingDataHandlerString
{
public:
    readingDataHandlerStringUR(const memory& parseMemory);
};

class writingDataHandlerStringUR: public writingDataHandlerString
{
public:
    writingDataHandlerStringUR(const std::shared_ptr<buffer>& pBuffer);
};

} // namespace handlers

} // namespace implementation

} // namespace dicomhero

#endif // !defined(imebraDataHandlerStringUR_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_)
