/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#if !defined(imebraObjcVOIDescription__INCLUDED_)
#define imebraObjcVOIDescription__INCLUDED_

#import <Foundation/Foundation.h>
#include "imebra_macros.h"

/// \enum ImebraDicomVOIFunction
/// \brief Specifies the function applied by the ImebraVOILUT transform.
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
@interface ImebraVOIDescription: NSObject

{
    @public
    define_imebra_object_holder(VOIDescription);
}

    -(id)initWithImebraVOIDescription:define_imebra_parameter(VOIDescription);

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

#endif // imebraObjcVOIDescription__INCLUDED_
