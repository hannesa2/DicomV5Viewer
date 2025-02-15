/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#import "../include/imebraobjc/imebra_codecFactory.h"
#import "../include/imebraobjc/imebra_dataset.h"
#import "../include/imebraobjc/imebra_streamReader.h"
#import "../include/imebraobjc/imebra_streamWriter.h"
#include "imebra_implementation_macros.h"
#include "imebra_nserror.h"
#include "imebra_strings.h"
#include <imebra/codecFactory.h>
#include <imebra/dataSet.h>
#include <imebra/streamReader.h>

@implementation ImebraCodecFactory

+(ImebraDataSet*)loadFromFile:(NSString*) fileName error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START()

    std::unique_ptr<imebra::DataSet> pDataSet(new imebra::DataSet(imebra::CodecFactory::load(imebra::NSStringToString(fileName))));
    return [[ImebraDataSet alloc] initWithImebraDataSet:pDataSet.release()];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil)
}

+(ImebraDataSet*)loadFromFileMaxSize:(NSString*) fileName maxBufferSize:(unsigned int)maxBufferSize error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START()

    std::unique_ptr<imebra::DataSet> pDataSet(new imebra::DataSet(imebra::CodecFactory::load(imebra::NSStringToString(fileName), maxBufferSize)));
    return [[ImebraDataSet alloc] initWithImebraDataSet:pDataSet.release()];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil)
}

+(ImebraDataSet*)loadFromStream:(ImebraStreamReader*)pReader error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    std::unique_ptr<imebra::DataSet> pDataSet(new imebra::DataSet(imebra::CodecFactory::load(*get_other_imebra_object_holder(pReader, StreamReader))));
    return [[ImebraDataSet alloc] initWithImebraDataSet:pDataSet.release()];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

+(ImebraDataSet*)loadFromStreamMaxSize:(ImebraStreamReader*)pReader maxBufferSize:(unsigned int)maxBufferSize error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    std::unique_ptr<imebra::DataSet> pDataSet(new imebra::DataSet(imebra::CodecFactory::load(*get_other_imebra_object_holder(pReader, StreamReader), maxBufferSize)));
    return [[ImebraDataSet alloc] initWithImebraDataSet:pDataSet.release()];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

+(void)saveToFile:(NSString*)fileName dataSet:(ImebraDataSet*)pDataSet codecType:(ImebraCodecType)codecType error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    imebra::CodecFactory::save(*get_other_imebra_object_holder(pDataSet, DataSet), imebra::NSStringToString(fileName), (imebra::codecType_t)codecType);

    OBJC_IMEBRA_FUNCTION_END();
}

+(void)saveToStream:(ImebraStreamWriter*)pWriter dataSet:(ImebraDataSet*)pDataSet codecType:(ImebraCodecType) codecType error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    imebra::CodecFactory::save(*get_other_imebra_object_holder(pDataSet, DataSet), *get_other_imebra_object_holder(pWriter, StreamWriter), (imebra::codecType_t)codecType);

    OBJC_IMEBRA_FUNCTION_END();

}

+(void)setMaximumImageSize:(unsigned int)maximumWidth maxHeight:(unsigned int)maximumHeight
{
    imebra::CodecFactory::setMaximumImageSize((const::uint32_t)maximumWidth, (const::uint32_t)maximumHeight);
}


@end




