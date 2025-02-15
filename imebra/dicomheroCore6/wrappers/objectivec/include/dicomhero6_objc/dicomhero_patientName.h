/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

#if !defined(dicomheroObjcPatientName__INCLUDED_)
#define dicomheroObjcPatientName__INCLUDED_

#import <Foundation/Foundation.h>
#include "dicomhero_macros.h"


@interface DicomheroPatientName: NSObject

{
    @public
    define_dicomhero_object_holder(PatientName);
}

    -(void)dealloc;

    -(id)initWithDicomheroPatientName:define_dicomhero_parameter(PatientName);

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

#endif // dicomheroObjcPatientName__INCLUDED_
