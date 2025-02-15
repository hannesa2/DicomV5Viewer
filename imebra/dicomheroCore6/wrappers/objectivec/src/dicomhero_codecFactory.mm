/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#import "../include/dicomhero6_objc/dicomhero_codecFactory.h"
#import "../include/dicomhero6_objc/dicomhero_dataset.h"
#import "../include/dicomhero6_objc/dicomhero_streamReader.h"
#import "../include/dicomhero6_objc/dicomhero_streamWriter.h"
#include "dicomhero_implementation_macros.h"
#include "dicomhero_nserror.h"
#include "dicomhero_strings.h"
#include <dicomhero6/codecFactory.h>
#include <dicomhero6/dataSet.h>
#include <dicomhero6/streamReader.h>

@implementation DicomheroCodecFactory

+(DicomheroDataSet*)loadFromFile:(NSString*) fileName error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START()

    std::unique_ptr<dicomhero::DataSet> pDataSet(new dicomhero::DataSet(dicomhero::CodecFactory::load(dicomhero::NSStringToString(fileName))));
    return [[DicomheroDataSet alloc] initWithDicomheroDataSet:pDataSet.release()];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil)
}

+(DicomheroDataSet*)loadFromFileMaxSize:(NSString*) fileName maxBufferSize:(unsigned int)maxBufferSize error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START()

    std::unique_ptr<dicomhero::DataSet> pDataSet(new dicomhero::DataSet(dicomhero::CodecFactory::load(dicomhero::NSStringToString(fileName), maxBufferSize)));
    return [[DicomheroDataSet alloc] initWithDicomheroDataSet:pDataSet.release()];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil)
}

+(DicomheroDataSet*)loadFromStream:(DicomheroStreamReader*)pReader error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    std::unique_ptr<dicomhero::DataSet> pDataSet(new dicomhero::DataSet(dicomhero::CodecFactory::load(*get_other_dicomhero_object_holder(pReader, StreamReader))));
    return [[DicomheroDataSet alloc] initWithDicomheroDataSet:pDataSet.release()];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

+(DicomheroDataSet*)loadFromStreamMaxSize:(DicomheroStreamReader*)pReader maxBufferSize:(unsigned int)maxBufferSize error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    std::unique_ptr<dicomhero::DataSet> pDataSet(new dicomhero::DataSet(dicomhero::CodecFactory::load(*get_other_dicomhero_object_holder(pReader, StreamReader), maxBufferSize)));
    return [[DicomheroDataSet alloc] initWithDicomheroDataSet:pDataSet.release()];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

+(void)saveToFile:(NSString*)fileName dataSet:(DicomheroDataSet*)pDataSet codecType:(DicomheroCodecType)codecType error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    dicomhero::CodecFactory::save(*get_other_dicomhero_object_holder(pDataSet, DataSet), dicomhero::NSStringToString(fileName), (dicomhero::codecType_t)codecType);

    OBJC_DICOMHERO_FUNCTION_END();
}

+(void)saveToStream:(DicomheroStreamWriter*)pWriter dataSet:(DicomheroDataSet*)pDataSet codecType:(DicomheroCodecType) codecType error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    dicomhero::CodecFactory::save(*get_other_dicomhero_object_holder(pDataSet, DataSet), *get_other_dicomhero_object_holder(pWriter, StreamWriter), (dicomhero::codecType_t)codecType);

    OBJC_DICOMHERO_FUNCTION_END();

}

+(void)setMaximumImageSize:(unsigned int)maximumWidth maxHeight:(unsigned int)maximumHeight
{
    dicomhero::CodecFactory::setMaximumImageSize((const::uint32_t)maximumWidth, (const::uint32_t)maximumHeight);
}


@end




