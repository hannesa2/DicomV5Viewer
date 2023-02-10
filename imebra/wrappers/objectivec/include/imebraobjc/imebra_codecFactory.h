/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#if !defined(imebraObjcCodecFactory__INCLUDED_)
#define imebraObjcCodecFactory__INCLUDED_

#import <Foundation/Foundation.h>

@class ImebraDataSet;
@class ImebraStreamReader;
@class ImebraStreamWriter;


/// \enum ImebraCodecType
/// \brief Defines the data stream & images codec.
///
///////////////////////////////////////////////////////////////////////////////
typedef NS_ENUM(unsigned short, ImebraCodecType)
{
    ImebraCodecTypeDicom = 0, ///< DICOM codec
    ImebraCodecTypeJpeg  = 1  ///< JPEG codec
};

///
/// \brief The ImebraCodecFactory class can load or save a DataSet or an Image
///        object using one of the codecs supplied by the Imebra library.
///
///////////////////////////////////////////////////////////////////////////////
@interface ImebraCodecFactory: NSObject


    /// \brief Parses the content of the input file and returns a ImebraDataSet
    ///        object representing it.
    ///
    /// If none of the codecs supplied by Imebra is able to decode the file's
    /// content then sets the pError parameter and returns nil.
    ///
    /// \param fileName          the name of the input file
    /// \param pError            pointer to a NSError pointer that will be set
    ///                          in case of error
    /// \return a ImebraDataSet object representing the input file's content
    ///
    ///////////////////////////////////////////////////////////////////////////////
    +(ImebraDataSet*)loadFromFile:(NSString*)fileName error:(NSError**)pError;

    /// \brief Parses the content of the input file and returns a ImebraDataSet
    ///        object representing it.
    ///
    /// If none of the codecs supplied by Imebra is able to decode the file's
    /// content then sets the pError parameter and returns nil.
    ///
    /// \param fileName          the name of the input file
    /// \param maxSizeBufferLoad the maximum size of the tags that are loaded
    ///                          immediately. Tags larger than maxSizeBufferLoad
    ///                          are left on the input stream and loaded only when
    ///                          a ImebraReadingDataHandler object or a
    ///                          ImebraWritingDataHandler object reference them.
    /// \param pError            pointer to a NSError pointer that will be set
    ///                          in case of error
    /// \return a ImebraDataSet object representing the input file's content
    ///
    ///////////////////////////////////////////////////////////////////////////////
    +(ImebraDataSet*)loadFromFileMaxSize:(NSString*)fileName maxBufferSize:(unsigned int)maxBufferSize error:(NSError**)pError;

    /// \brief Parses the content of the input stream and returns a
    ///        ImebraDataSet representing it.
    ///
    /// If none of the codecs supplied by Imebra is able to decode the stream's
    /// content then sets the pError parameter and returns nil.
    ///
    /// The read position of the ImebraStreamReader object is undefined when
    /// this method returns.
    ///
    /// \param pReader           a ImebraStreamReader object connected to the
    ///                          input stream
    /// \param pError            pointer to a NSError pointer that will be set
    ///                          in case of error
    /// \return an ImebraDataSet object representing the input stream's content
    ///
    ///////////////////////////////////////////////////////////////////////////////
    +(ImebraDataSet*)loadFromStream:(ImebraStreamReader*)pReader error:(NSError**)pError;

    /// \brief Parses the content of the input stream and returns a
    ///        ImebraDataSet representing it.
    ///
    /// If none of the codecs supplied by Imebra is able to decode the stream's
    /// content then sets the pError parameter and returns nil.
    ///
    /// The read position of the ImebraStreamReader object is undefined when
    /// this method returns.
    ///
    /// \param pReader           a ImebraStreamReader object connected to the
    ///                          input stream
    /// \param maxSizeBufferLoad the maximum size of the tags that are loaded
    ///                          immediately. Tags larger than maxSizeBufferLoad
    ///                          are left on the input stream and loaded only when
    ///                          an ImebraReadingDataHandler or an
    ///                          ImebraWritingDataHandler object reference sthem.
    /// \param pError            pointer to a NSError pointer that will be set
    ///                          in case of error
    /// \return an ImebraDataSet object representing the input stream's content
    ///
    ///////////////////////////////////////////////////////////////////////////////
    +(ImebraDataSet*)loadFromStreamMaxSize:(ImebraStreamReader*)pReader maxBufferSize:(unsigned int)maxBufferSize error:(NSError**)pError;

    /// \brief Saves the content of a ImebraDataSet object to a file.
    ///
    /// \param fileName          the name of the output file
    /// \param pDataSet          the ImebraDataSet object to save
    /// \param codecType         the codec to use to save the ImebraDataSet
    /// \param pError            pointer to a NSError pointer that will be set
    ///                          in case of error
    ///
    ///////////////////////////////////////////////////////////////////////////////
    +(void)saveToFile:(NSString*)fileName dataSet:(ImebraDataSet*) pDataSet codecType:(ImebraCodecType) codecType error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    /// \brief Saves the content of a ImebraDataSet object to an output stream
    ///        using the requested codec.
    ///
    /// \param pWriter           an ImebraStreamWriter connected to the output stream
    /// \param pDataSet          the ImebraDataSet object to save
    /// \param codecType         the codec to use to save the ImebraDataSet
    /// \param pError            pointer to a NSError pointer that will be set
    ///                          in case of error
    ///
    ///////////////////////////////////////////////////////////////////////////////
    +(void)saveToStream:(ImebraStreamWriter*)pWriter dataSet:(ImebraDataSet*)pDataSet codecType:(ImebraCodecType) codecType error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    /// \brief Set the maximum image's width & height accepted by Imebra.
    ///
    /// By default both the maximum width and height are set to 4096 pixels.
    ///
    /// \param maximumWidth      the maximum image's width accepted by Imebra
    /// \param maximumHeight     the maximum image's height accepted by Imebra
    ///
    ///////////////////////////////////////////////////////////////////////////////
    +(void)setMaximumImageSize:(unsigned int)maximumWidth maxHeight:(unsigned int)maximumHeight;

@end

#endif // imebraObjcCodecFactory__INCLUDED_


