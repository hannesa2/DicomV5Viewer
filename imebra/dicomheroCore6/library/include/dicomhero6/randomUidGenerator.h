/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/


#if !defined(imebraRandomUIDGenerator__INCLUDED_)
#define imebraRandomUIDGenerator__INCLUDED_

#include "baseUidGenerator.h"
#include "definitions.h"

namespace dicomhero
{

///
/// \brief An UID generator that uses a random number to generate unique
///        UIDs.
///
/// The uniqueness of the generated UIDs is guaranteed by the fact that
/// the machine generates a long random number during the UID generator
/// initialization.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API RandomUIDGenerator : public BaseUIDGenerator
{

public:
    /// \brief Constructor.
    ///
    /// \param root the     root UID assigned to the company
    /// \param departmentId department ID (assigned by the company)
    /// \param modelId      model ID (assigned by the department)
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit RandomUIDGenerator(const std::string& root, std::uint32_t departmentId, std::uint32_t modelId);

    ///
    /// \brief Copy constructor.
    ///
    /// \param source source RandomUIDGenerator object
    ///
    ///////////////////////////////////////////////////////////////////////////////
    RandomUIDGenerator(const RandomUIDGenerator& source);

    virtual ~RandomUIDGenerator();

};

}
#endif // !defined(imebraRandomUIDGenerator__INCLUDED_)
