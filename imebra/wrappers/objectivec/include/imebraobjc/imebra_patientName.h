/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#if !defined(imebraObjcPatientName__INCLUDED_)
#define imebraObjcPatientName__INCLUDED_

#import <Foundation/Foundation.h>
#include "imebra_macros.h"


@interface ImebraPatientName: NSObject

{
    @public
    define_imebra_object_holder(PatientName);
}

    -(void)dealloc;

    -(id)initWithImebraPatientName:define_imebra_parameter(PatientName);

    /// \brief Constructor.
    ///
    /// Initialize the PatientName structure with the specified values.
    ///
    /// \param alphabeticRepresentation  The alphabetic representation of the
    ///                                  patient name
    /// \param ideographicRepresentation The ideographic representation of the
    ///                                  patient name. Can be left empty
    /// \param phoneticRepresentation    The phonetic representation of the
    ///                                  patient name. Can be left empty
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(id)initWithAlphabeticRepresentation:(NSString*)alphabeticRepresentation
                        ideographicRepresentation:(NSString*)ideographicRepresentation
                        phoneticRepresentation:(NSString*)phoneticRepresentation;

    @property (readonly) NSString* alphabeticRepresentation;         ///< The alphabetic representation of the Patient Name
    @property (readonly) NSString* ideographicRepresentation;        ///< The ideographic representation of the Patient Name
    @property (readonly) NSString* phoneticRepresentation;           ///< The phonetic representation of the Patient Name

@end

#endif // imebraObjcPatientName__INCLUDED_
