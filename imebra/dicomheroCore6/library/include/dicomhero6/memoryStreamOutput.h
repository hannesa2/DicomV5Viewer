/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/


#if !defined(imebraMemoryStreamOutput__INCLUDED_)
#define imebraMemoryStreamOutput__INCLUDED_

#include <string>
#include "baseStreamOutput.h"
#include "definitions.h"

namespace dicomhero
{

class MutableMemory;

///
/// \brief An output stream that writes data into a memory region.
///
/// When new data is written into the memory then it is resized as necessary.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API MemoryStreamOutput : public BaseStreamOutput
{

public:

    /// \brief Constructor.
    ///
    /// \param memory the memory region into which the stream will write the data
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit MemoryStreamOutput(const MutableMemory& memory);

    ///
    /// \brief Copy constructor.
    ///
    /// \param source source MemoryStreamOutput object
    ///
    ///////////////////////////////////////////////////////////////////////////////
    MemoryStreamOutput(const MemoryStreamOutput& source);

    MemoryStreamOutput& operator=(const MemoryStreamOutput& source) = delete;

    virtual ~MemoryStreamOutput();
};

}
#endif // !defined(imebraMemoryStreamOutput__INCLUDED_)
