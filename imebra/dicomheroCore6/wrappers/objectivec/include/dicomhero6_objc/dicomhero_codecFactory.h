/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

#if !defined(dicomheroObjcCodecFactory__INCLUDED_)
#define dicomheroObjcCodecFactory__INCLUDED_

#import <Foundation/Foundation.h>

@class DicomheroDataSet;
@class DicomheroStreamReader;
@class DicomheroStreamWriter;


/// \enum DicomheroCodecType
/// \brief Defines the data stream & images codec.
///
///////////////////////////////////////////////////////////////////////////////
typedef NS_ENUM(unsigned short, DicomheroCodecType)
{
    DicomheroCodecTypeDicom = 0, ///< DICOM codec
    DicomheroCodecTypeJpeg  = 1  ///< JPEG codec
};

///
/// \brief The DicomheroCodecFactory class can load or save a DataSet or an Image
///        object using one of the codecs supplied by the Imebra library.
///
///////////////////////////////////////////////////////////////////////////////
@interface DicomheroCodecFactory: NSObject


    /// \brief Parses the content of the input file and returns a DicomheroDataSet
    ///        object representing it.
    ///
    /// If none of the codecs supplied by Imebra is able to decode the file's
    /// content then sets the pError parameter and returns nil.
    ///
    /// \param fileName          the name of the input file
    /// \param pError            pointer to a NSError pointer that will be set
    ///                          in case of error
    /// \return a DicomheroDataSet object representing the input file's content
    ///
    ///////////////////////////////////////////////////////////////////////////////
    +(DicomheroDataSet*)loadFromFile:(NSString*)fileName error:(NSError**)pError;

    /// \brief Parses the content of the input file and returns a DicomheroDataSet
    ///        object representing it.
    ///
    /// If none of the codecs supplied by Imebra is able to decode the file's
    /// content then sets the pError parameter and returns nil.
    ///
    /// \param fileName          the name of the input file
    /// \param maxSizeBufferLoad the maximum size of the tags that are loaded
    ///                          immediately. Tags larger than maxSizeBufferLoad
    ///                          are left on the input stream and loaded only when
    ///                          a DicomheroReadingDataHandler object or a
    ///                          DicomheroWritingDataHandler object reference them.
    /// \param pError            pointer to a NSError pointer that will be set
    ///                          in case of error
    /// \return a DicomheroDataSet object representing the input file's content
    ///
    ///////////////////////////////////////////////////////////////////////////////
    +(DicomheroDataSet*)loadFromFileMaxSize:(NSString*)fileName maxBufferSize:(unsigned int)maxBufferSize error:(NSError**)pError;

    /// \brief Parses the content of the input stream and returns a
    ///        DicomheroDataSet representing it.
    ///
    /// If none of the codecs supplied by Imebra is able to decode the stream's
    /// content then sets the pError parameter and returns nil.
    ///
    /// The read position of the DicomheroStreamReader object is undefined when
    /// this method returns.
    ///
    /// \param pReader           a DicomheroStreamReader object connected to the
    ///                          input stream
    /// \param pError            pointer to a NSError pointer that will be set
    ///                          in case of error
    /// \return an DicomheroDataSet object representing the input stream's content
    ///
    ///////////////////////////////////////////////////////////////////////////////
    +(DicomheroDataSet*)loadFromStream:(DicomheroStreamReader*)pReader error:(NSError**)pError;

    /// \brief Parses the content of the input stream and returns a
    ///        DicomheroDataSet representing it.
    ///
    /// If none of the codecs supplied by Imebra is able to decode the stream's
    /// content then sets the pError parameter and returns nil.
    ///
    /// The read position of the DicomheroStreamReader object is undefined when
    /// this method returns.
    ///
    /// \param pReader           a DicomheroStreamReader object connected to the
    ///                          input stream
    /// \param maxSizeBufferLoad the maximum size of the tags that are loaded
    ///                          immediately. Tags larger than maxSizeBufferLoad
    ///                          are left on the input stream and loaded only when
    ///                          an DicomheroReadingDataHandler or an
    ///                          DicomheroWritingDataHandler object reference sthem.
    /// \param pError            pointer to a NSError pointer that will be set
    ///                          in case of error
    /// \return an DicomheroDataSet object representing the input stream's content
    ///
    ///////////////////////////////////////////////////////////////////////////////
    +(DicomheroDataSet*)loadFromStreamMaxSize:(DicomheroStreamReader*)pReader maxBufferSize:(unsigned int)maxBufferSize error:(NSError**)pError;

    /// \brief Saves the content of a DicomheroDataSet object to a file.
    ///
    /// \param fileName          the name of the output file
    /// \param pDataSet          the DicomheroDataSet object to save
    /// \param codecType         the codec to use to save the DicomheroDataSet
    /// \param pError            pointer to a NSError pointer that will be set
    ///                          in case of error
    ///
    ///////////////////////////////////////////////////////////////////////////////
    +(void)saveToFile:(NSString*)fileName dataSet:(DicomheroDataSet*) pDataSet codecType:(DicomheroCodecType) codecType error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    /// \brief Saves the content of a DicomheroDataSet object to an output stream
    ///        using the requested codec.
    ///
    /// \param pWriter           an DicomheroStreamWriter connected to the output stream
    /// \param pDataSet          the DicomheroDataSet object to save
    /// \param codecType         the codec to use to save the DicomheroDataSet
    /// \param pError            pointer to a NSError pointer that will be set
    ///                          in case of error
    ///
    ///////////////////////////////////////////////////////////////////////////////
    +(void)saveToStream:(DicomheroStreamWriter*)pWriter dataSet:(DicomheroDataSet*)pDataSet codecType:(DicomheroCodecType) codecType error:(NSError**)pError
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

#endif // dicomheroObjcCodecFactory__INCLUDED_


