/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#import "imebra_readingDataHandler.h"
#import <Foundation/Foundation.h>

#if !defined(imebraObjcReadingDataHandlerNumeric__INCLUDED_)
#define imebraObjcReadingDataHandlerNumeric__INCLUDED_

@class ImebraWritingDataHandlerNumeric;
@class ImebraMemory;

///
/// \brief Specialized ImebraReadingDataHandler for numeric data types.
///
/// Includes few methods that allow accessing the raw memory containing the
/// buffer's data.
///
///////////////////////////////////////////////////////////////////////////////
@interface ImebraReadingDataHandlerNumeric: ImebraReadingDataHandler

    /// \brief Return a ReadMemory object referencing the raw buffer's data.
    ///
    /// \param pError set to a NSError derived class in case of error
    /// \return a ReadMemory object referencing the raw buffer's data
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(ImebraMemory*)getMemory: (NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    /// \brief Copies the content of the data handler into another data handler,
    ///        converting the data to the destination handler data type.
    ///
    /// \warning the size of the destination data handler stays unchanged: if
    ///          the destination too small to contain all the data to be copied
    ///          then only a part of the data will be copied.
    ///
    /// \param pError      set to a NSError derived class in case of error
    /// \param destination the destination data handler
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(void)copyTo:(ImebraWritingDataHandlerNumeric*)destination error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    /// \brief Returns the number of bytes occupied by the numbers handled by the
    ///        data handler
    ///
    ///////////////////////////////////////////////////////////////////////////////
    @property (readonly) unsigned int unitSize;

    /// \brief Returns true if the numbers stored in the buffer are signed, false
    ///        otherwise.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    @property (readonly) bool isSigned;

    /// \brief Returns true if the numbers stored in the buffer are floating point
    ///        numbers, false otherwise.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    @property (readonly) bool isFloat;


@end

#endif // !defined(imebraObjcReadingDataHandlerNumeric__INCLUDED_)
