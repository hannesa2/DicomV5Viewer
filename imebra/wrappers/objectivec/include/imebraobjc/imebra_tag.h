/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#if !defined(imebraObjcTag__INCLUDED_)
#define imebraObjcTag__INCLUDED_

#import <Foundation/Foundation.h>
#import "imebra_dataset.h"

#include "imebra_macros.h"

@class ImebraReadingDataHandler;
@class ImebraWritingDataHandler;
@class ImebraReadingDataHandlerNumeric;
@class ImebraWritingDataHandlerNumeric;
@class ImebraStreamWriter;
@class ImebraStreamReader;
@class ImebraDataSet;
@class ImebraFileStreamInput;

///
/// \brief This class represents a DICOM tag.
///
///////////////////////////////////////////////////////////////////////////////
@interface ImebraTag: NSObject

{
    @public
    define_imebra_object_holder(Tag);
}

    -(id)initWithImebraTag:define_imebra_parameter(Tag);

    -(void)dealloc;

    /// \brief Returns the number of buffers in the tag.
    ///
    /// \return the number of buffers in the tag
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(unsigned int) getBuffersCount;

    /// \brief Returns true if the specified buffer exists, otherwise it returns
    ///        false.
    ///
    /// \param bufferId the zero-based buffer's id the
    ///                 function has to check for
    /// \return true if the buffer exists, false otherwise
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(BOOL) bufferExists:(unsigned int) bufferId;

    /// \brief Returns the size of a buffer, in bytes.
    ///
    /// If the buffer doesn't exist then set pError to ImebraMissingBufferError.
    ///
    /// \param bufferId the zero-based buffer's id the
    ///                 function has to check for
    /// \param pError   set to a NSError derived class in case of error
    /// \return the buffer's size in bytes
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(unsigned int) getBufferSize:(unsigned int) bufferId error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    /// \brief Retrieve a ImebraReadingDataHandler object connected to a specific
    ///        buffer.
    ///
    /// If the buffer doesn't exist then set pError to ImebraMissingBufferError.
    ///
    /// \param bufferId the buffer to connect to the ReadingDataHandler object.
    ///                 The first buffer has an Id = 0
    /// \param pError   set to a NSError derived class in case of error
    /// \return a ImebraReadingDataHandler object connected to the requested buffer
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(ImebraReadingDataHandler*) getReadingDataHandler:(unsigned int) bufferId error:(NSError**)pError;

    /// \brief Retrieve a ImebraReadingDataHandlerNumeric object connected to the
    ///        Tag's numeric buffer.
    ///
    /// If the tag's VR is not a numeric type then throws std::bad_cast.
    ///
    /// If the tag does not contain the specified buffer then set pError to
    ///  ImebraMissingBufferError.
    ///
    /// \param bufferId the buffer to connect to the ImebraReadingDataHandler
    ///                 object.
    ///                 The first buffer has an Id = 0
    /// \param pError   set to a NSError derived class in case of error
    /// \return a ImebraReadingDataHandlerNumeric object connected to the Tag's buffer
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(ImebraReadingDataHandlerNumeric*) getReadingDataHandlerNumeric:(unsigned int) bufferId error:(NSError**)pError;

    /// \brief Retrieve a ReadingDataHandlerNumeric object connected to the
    ///        Tag's raw data buffer (8 bit unsigned integers).
    ///
    /// If the tag's VR is not a numeric type then throws std::bad_cast.
    ///
    /// If the specified Tag does not contain the specified buffer then
    ///  throws MissingBufferError.
    ///
    /// \param bufferId the buffer to connect to the ReadingDataHandler object.
    ///                 The first buffer has an Id = 0
    /// \param pError   set to a NSError derived class in case of error
    /// \return a ReadingDataHandlerNumeric object connected to the Tag's buffer
    ///         (raw content represented by 8 bit unsigned integers)
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(ImebraReadingDataHandlerNumeric*) getReadingDataHandlerRaw:(unsigned int) bufferId error:(NSError**)pError;

    /// \brief Get a StreamReader connected to a buffer's data.
    ///
    /// \param bufferId   the id of the buffer for which the StreamReader is
    ///                    required. This parameter is usually 0
    /// \param pError   set to a NSError derived class in case of error
    /// \return           the streamReader connected to the buffer's data.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(ImebraStreamReader*) getStreamReader:(unsigned int) bufferId error:(NSError**)pError;

    /// \brief Retrieve an embedded DataSet.
    ///
    /// Sequence tags (VR=SQ) store embedded dicom structures.
    ///
    /// \param dataSetId  the ID of the sequence item to retrieve. Several sequence
    ///                   items can be embedded in one tag.
    /// \param pError   set to a NSError derived class in case of error
    /// \return           the sequence DataSet
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(ImebraDataSet*) getSequenceItem:(unsigned int) dataSetId error:(NSError**)pError;

    /// \brief Check for the existance of a sequence item.
    ///
    /// \param dataSetId the ID of the sequence item to check for
    /// \return true if the sequence item exists, false otherwise
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(BOOL)sequenceItemExists:(unsigned int) dataSetId;

    /// \brief Get the tag's data type.
    ///
    /// @return the tag's data type
    ///
    ///////////////////////////////////////////////////////////////////////////////
    @property (readonly) ImebraTagType dataType;

@end



///
/// \brief This class represents a DICOM tag.
///
///////////////////////////////////////////////////////////////////////////////
@interface ImebraMutableTag: ImebraTag

    -(id)initWithImebraMutableTag:define_imebra_parameter(MutableTag);

    /// \brief Retrieve a ImebraWritingDataHandler object connected to a specific
    ///        tag's buffer.
    ///
    /// If the specified buffer does not exist then it creates a new buffer.
    ///
    /// \param bufferId the position where the new buffer has to be stored into the
    ///                 tag. The first buffer position is 0
    /// \param pError   set to a NSError derived class in case of error
    /// \return a ImebraWritingDataHandler object connected to a new tag's buffer
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(ImebraWritingDataHandler*) getWritingDataHandler:(unsigned int) bufferId error:(NSError**)pError;

    /// \brief Retrieve a WritingDataHandlerNumeric object connected to the
    ///        Tag's buffer.
    ///
    /// If the tag's VR is not a numeric type then throws std::bad_cast.
    ///
    /// The returned WritingDataHandlerNumeric is connected to a new buffer which
    /// is updated and stored into the tag when WritingDataHandlerNumeric is
    /// destroyed.
    ///
    /// \param bufferId the position where the new buffer has to be stored in the
    ///                 tag. The first buffer position is 0
    /// \param pError   set to a NSError derived class in case of error
    /// \return a WritingDataHandlerNumeric object connected to a new Tag's buffer
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(ImebraWritingDataHandlerNumeric*) getWritingDataHandlerNumeric:(unsigned int) bufferId error:(NSError**)pError;

    /// \brief Retrieve a WritingDataHandlerNumeric object connected to the
    ///        Tag's raw data buffer (8 bit unsigned integers).
    ///
    /// If the tag's VR is not a numeric type then throws std::bad_cast.
    ///
    /// The returned WritingDataHandlerNumeric is connected to a new buffer which
    /// is updated and stored into the tag when WritingDataHandlerNumeric is
    /// destroyed.
    ///
    /// \param bufferId the position where the new buffer has to be stored in the
    ///                 tag. The first buffer position is 0
    /// \param pError   set to a NSError derived class in case of error
    /// \return a WritingDataHandlerNumeric object connected to a new Tag's buffer
    ///         (the buffer contains raw data of 8 bit integers)
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(ImebraWritingDataHandlerNumeric*) getWritingDataHandlerRaw:(unsigned int) bufferId error:(NSError**)pError;

    /// \brief Get a StreamWriter connected to a buffer's data.
    ///
    /// \param bufferId   the id of the buffer for which the StreamWriter is
    ///                    required. This parameter is usually 0
    /// \param pError   set to a NSError derived class in case of error
    /// \return           the StreamWriter connected to the buffer's data.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(ImebraStreamWriter*) getStreamWriter:(unsigned int) bufferId error:(NSError**)pError;

    /// \brief Append a sequence item into the Tag.
    ///
    /// Several sequence items can be nested one inside each other.
    /// When a sequence item is embedded into a Tag, then the tag will have a
    /// sequence VR (VR = SQ).
    ///
    /// \param pError     set to a NSError derived class in case of error
    /// \return a MutableDataSet representing the added sequence item
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(ImebraMutableDataSet*) appendSequenceItem:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    /// \brief Set the tag's content to the content of a file.
    ///
    /// The tag will just keep a reference to the file content.
    ///
    /// This is useful when embedding large objects into a dataset (e.g. a MPEG
    /// file acquired by the device).
    ///
    /// \param bufferId    the id of the buffer to which the content is added
    /// \param streamInput the file into which the tag's content is stored
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(void) setStream:(unsigned int)bufferId stream:(ImebraFileStreamInput*)pStream error:(NSError**)pError;



@end

#endif // !defined(imebraObjcTag__INCLUDED_)
