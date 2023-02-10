/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

#if !defined(dicomheroObjcWritingDataHandlerNumeric__INCLUDED_)
#define dicomheroObjcWritingDataHandlerNumeric__INCLUDED_

#import "dicomhero_writingDataHandler.h"
#import <Foundation/Foundation.h>

@class DicomheroReadingDataHandlerNumeric;
@class DicomheroMutableMemory;


///
/// \brief Specialized dicomheroWritingDataHandler for numeric data types.
///
/// Includes few methods that allow accessing the raw memory containing the
/// buffer's data.
///
///////////////////////////////////////////////////////////////////////////////
@interface DicomheroWritingDataHandlerNumeric: DicomheroWritingDataHandler

    /// \brief Return a DicomheroMutableMemory object referencing the raw buffer's
    ///        data.
    ///
    /// \param pError set to a NSError derived class in case of error
    /// \return a DicomheroMutableMemory object referencing the raw buffer's data
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(DicomheroMutableMemory*)getMemory:(NSError**)pError;

    /// \brief Copy the content of the specified buffer into the content managed
    ///        by data handler.
    ///
    /// \param pSource    a pointer to the source memory buffer
    /// \param pError     set to a NSError derived class in case of error
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(void)assign:(NSData*)pSource error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    /// \brief Copies data from another data handler, converting the data type
    ///        if necessary.
    ///
    /// The data handler is resized to the same size of the source data handler.
    ///
    /// \param pSource the data handler from which the data must be copied
    /// \param pError  set to a NSError derived class in case of error
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(void)copyFrom:(DicomheroReadingDataHandlerNumeric*)pSource error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    /// \brief Returns the number of bytes occupied by each number handled by the
    ///        data handler.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    @property (readonly) unsigned int unitSize;

    /// \brief Returns true if the numbers handled by the data handler are signed,
    ///        false otherwise.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    @property (readonly) bool isSigned;

    /// \brief Returns true if the numbers stored in the buffer are floating point
    ///        numbers, false otherwise.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    @property (readonly) bool isFloat;

@end

#endif // !defined(dicomheroObjcWritingDataHandlerNumeric__INCLUDED_)
