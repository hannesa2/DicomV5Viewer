/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

#if !defined(dicomheroObjcBaseUidGenerator__INCLUDED_)
#define dicomheroObjcBaseUidGenerator__INCLUDED_

#import <Foundation/Foundation.h>
#import "dicomhero_macros.h"

///
/// \brief Base class for the DICOM UID generators.
///
///////////////////////////////////////////////////////////////////////////////
@interface DicomheroBaseUIDGenerator: NSObject
{
    @public
    define_dicomhero_object_holder(BaseUIDGenerator);
}

    -(id)initWithDicomheroBaseUidGenerator:define_dicomhero_parameter(BaseUIDGenerator);

    -(void)dealloc;

    ///
    /// \brief Generates a new UID.
    ///
    /// \return a new UID.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(NSString*)getUID;

@end


#endif // !defined(dicomheroObjcBaseUidGenerator__INCLUDED_)
