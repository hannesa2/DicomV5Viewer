/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

#if !defined(dicomheroObjcFileStreamInput__INCLUDED_)
#define dicomheroObjcFileStreamInput__INCLUDED_

#import <Foundation/Foundation.h>
#import "dicomhero_baseStreamInput.h"

///
/// \brief Represents an input file stream.
///
///////////////////////////////////////////////////////////////////////////////
@interface DicomheroFileStreamInput: DicomheroBaseStreamInput

    /// \brief Initializer.
    ///
    /// \param fileName the path to the file to open in read mode
    /// \param pError   set to a NSError derived class in case of error
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(id)initWithName:(NSString*)fileName error:(NSError**)pError;

@end

#endif // dicomheroObjcFileStreamInput__INCLUDED_


