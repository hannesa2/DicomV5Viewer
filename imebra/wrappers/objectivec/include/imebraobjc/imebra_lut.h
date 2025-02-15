/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#if !defined(imebraObjcLut__INCLUDED_)
#define imebraObjcLut__INCLUDED_

#import <Foundation/Foundation.h>
#include "imebra_macros.h"

@class ImebraReadingDataHandlerNumeric;

///
/// \brief This class represents Lookup Table.
///
///////////////////////////////////////////////////////////////////////////////
@interface ImebraLUT : NSObject

{
    @public
    define_imebra_object_holder(LUT);
}

    -(id)initWithImebraLut:define_imebra_parameter(LUT);

    -(void)dealloc;

    /// \brief Return a numeric handler for the memory containing the mapped
    ///        values.
    ///
    /// \return a reading data handler that points to the mapped values
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(ImebraReadingDataHandlerNumeric*) getReadingDataHandler;

    /// \brief Return the mapped value for a specific index
    ///
    /// \param index a LUT index
    /// \return the mapped value for the requested index
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(unsigned int)getMappedValue:(int)index;

    /// \brief Returns the LUT's description.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    @property (readonly) NSString* description;

    /// \brief Return the number of bits used to store a LUT value.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    @property (readonly) unsigned int bits;

    /// \brief Return the lut's size (the number of stored values).
    ///
    ///////////////////////////////////////////////////////////////////////////////
    @property (readonly) unsigned int size;

    /// \brief Return the first LUT index that has a mapped value
    ///
    ///////////////////////////////////////////////////////////////////////////////
    @property (readonly) int firstMappedValue;

@end

#endif // imebraObjcLut__INCLUDED_


