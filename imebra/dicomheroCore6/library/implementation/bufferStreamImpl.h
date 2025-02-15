/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

///////////////////////////////////////////////////////////
//  bufferStream.h
//  Declaration of the Class bufferStream
///////////////////////////////////////////////////////////

#if !defined(imebraBufferStream_DE3F98A9_664E_47c0_A29B_B681F9AEB118__INCLUDED_)
#define imebraBufferStream_DE3F98A9_664E_47c0_A29B_B681F9AEB118__INCLUDED_

#include "memoryStreamImpl.h"
#include "dataHandlerNumericImpl.h"

namespace dicomhero
{

namespace implementation
{

/// \addtogroup group_dataset
///
/// @{

class bufferStreamOutput: public memoryStreamOutput
{
public:
    bufferStreamOutput(std::shared_ptr<handlers::writingDataHandlerRaw> pDataHandler):
      memoryStreamOutput(pDataHandler->getMemory()),
	  m_pDataHandler(pDataHandler){}
protected:

    std::shared_ptr<handlers::writingDataHandlerRaw> m_pDataHandler;
};

/// @}

} // namespace implementation

} // namespace dicomhero

#endif // !defined(imebraBufferStream_DE3F98A9_664E_47c0_A29B_B681F9AEB118__INCLUDED_)
