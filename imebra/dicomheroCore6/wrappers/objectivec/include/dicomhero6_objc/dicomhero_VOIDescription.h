/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

#if !defined(dicomheroObjcVOIDescription__INCLUDED_)
#define dicomheroObjcVOIDescription__INCLUDED_

#import <Foundation/Foundation.h>
#include "dicomhero_macros.h"

/// \enum ImebraDicomVOIFunction
/// \brief Specifies the function applied by the DicomheroVOILUT transform.
///
///////////////////////////////////////////////////////////////////////////////
typedef NS_ENUM(int, ImebraDicomVOIFunction)
{
    ImebraDicomVOIFunctionLinear = 0,      ///< Correspond to the DICOM VOI function "LINEAR"
    ImebraDicomVOIFunctionLinearExact = 1, ///< Correspond to the DICOM VOI function "LINEAR_EXACT"
    ImebraDicomVOIFunctionSigmoid = 2      ///< Correspond to the DICOM VOI function "SIGMOID"
};

///
/// \brief Specifies an age, in days, weeks, months or years.
///
///////////////////////////////////////////////////////////////////////////////
@interface DicomheroVOIDescription: NSObject

{
    @public
    define_dicomhero_object_holder(VOIDescription);
}

    -(id)initWithDicomheroVOIDescription:define_dicomhero_parameter(VOIDescription);

    -(void)dealloc;


    /// \brief Constructor.
    ///
    /// \param center       the VOI window's center
    /// \param width        the VOI windoe's width
    /// \param function     the function to use when applying the center/width
    /// \param description  the VOI description (unicode)
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(id)initWithCenter:(double)center width:(double)width function:(ImebraDicomVOIFunction)function description:(NSString*)description;

    @property (readonly) double center;                      ///< The VOI window center.
    @property (readonly) double width;                       ///< The VOI window width.
    @property (readonly) ImebraDicomVOIFunction function;    ///< The VOI function.
    @property (readonly) NSString* description;              ///< The VOI description.


@end

#endif // dicomheroObjcVOIDescription__INCLUDED_
