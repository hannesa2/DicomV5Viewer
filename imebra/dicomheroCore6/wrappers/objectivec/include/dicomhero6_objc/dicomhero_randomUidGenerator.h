/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

#if !defined(dicomheroObjcRandomUidGenerator__INCLUDED_)
#define dicomheroObjcRandomUidGenerator__INCLUDED_

#import <Foundation/Foundation.h>
#import "dicomhero_baseUidGenerator.h"
#include "dicomhero_macros.h"

///
/// \brief An UID generator that uses a random number to generate unique
///        UIDs.
///
/// The uniqueness of the generated UIDs is guaranteed by the fact that
/// the machine generates a long random number during the UID generator
/// initialization.
///
///////////////////////////////////////////////////////////////////////////////
@interface DicomheroRandomUIDGenerator: DicomheroBaseUIDGenerator

    /// \brief Constructor.
    ///
    /// \param root the     root UID assigned to the company
    /// \param departmentId department ID (assigned by the company)
    /// \param modelId      model ID (assigned by the department)
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(id)initWithRoot:(NSString*)root departmentId:(unsigned int)departmentId modelId:(unsigned int)modelId;

@end

#endif // dicomheroObjcRandomUidGenerator__INCLUDED_
