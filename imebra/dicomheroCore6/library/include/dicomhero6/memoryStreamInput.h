/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/


#if !defined(imebraMemoryStreamInput__INCLUDED_)
#define imebraMemoryStreamInput__INCLUDED_

#include <string>
#include "baseStreamInput.h"
#include "definitions.h"

namespace dicomhero
{

class Memory;
class MutableMemory;

///
/// \brief An input stream that reads data from a memory region.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API MemoryStreamInput : public BaseStreamInput
{

public:
    /// \brief Constructor.
    ///
    /// \param memory the memory region from which the stream will read the data
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit MemoryStreamInput(const Memory& memory);

    ///
    /// \brief Copy constructor.
    ///
    /// \param source source MemoryStreamInput object
    ///
    ///////////////////////////////////////////////////////////////////////////////
    MemoryStreamInput(const MemoryStreamInput& source);

    MemoryStreamInput& operator=(const MemoryStreamInput& source) = delete;

    virtual ~MemoryStreamInput();
};

}
#endif // !defined(imebraMemoryStreamInput__INCLUDED_)
