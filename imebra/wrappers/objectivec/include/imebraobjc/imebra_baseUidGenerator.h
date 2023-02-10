/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#if !defined(imebraObjcBaseUidGenerator__INCLUDED_)
#define imebraObjcBaseUidGenerator__INCLUDED_

#import <Foundation/Foundation.h>
#import "imebra_macros.h"

///
/// \brief Base class for the DICOM UID generators.
///
///////////////////////////////////////////////////////////////////////////////
@interface ImebraBaseUIDGenerator: NSObject
{
    @public
    define_imebra_object_holder(BaseUIDGenerator);
}

    -(id)initWithImebraBaseUidGenerator:define_imebra_parameter(BaseUIDGenerator);

    -(void)dealloc;

    ///
    /// \brief Generates a new UID.
    ///
    /// \return a new UID.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(NSString*)getUID;

@end


#endif // !defined(imebraObjcBaseUidGenerator__INCLUDED_)
