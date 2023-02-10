/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

#if !defined(dicomheroObjcLut__INCLUDED_)
#define dicomheroObjcLut__INCLUDED_

#import <Foundation/Foundation.h>
#include "dicomhero_macros.h"

@class DicomheroReadingDataHandlerNumeric;

///
/// \brief This class represents Lookup Table.
///
///////////////////////////////////////////////////////////////////////////////
@interface DicomheroLUT : NSObject

{
    @public
    define_dicomhero_object_holder(LUT);
}

    -(id)initWithDicomheroLut:define_dicomhero_parameter(LUT);

    -(void)dealloc;

    /// \brief Return a numeric handler for the memory containing the mapped
    ///        values.
    ///
    /// \return a reading data handler that points to the mapped values
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(DicomheroReadingDataHandlerNumeric*) getReadingDataHandler;

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

#endif // dicomheroObjcLut__INCLUDED_


