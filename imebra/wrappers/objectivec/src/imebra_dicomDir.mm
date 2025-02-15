/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#include "../include/imebraobjc/imebra_dicomDir.h"
#include "../include/imebraobjc/imebra_dataset.h"
#include "imebra_implementation_macros.h"
#include "imebra_strings.h"
#include "imebra_nserror.h"
#include <imebra/dicomDirEntry.h>
#include <imebra/dicomDir.h>
#include <imebra/dataSet.h>

@implementation ImebraDicomDirEntry

-(id)initWithImebraDicomDirEntry:define_imebra_parameter(DicomDirEntry)
{
    reset_imebra_object_holder(DicomDirEntry);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(DicomDirEntry, get_imebra_parameter(DicomDirEntry));
    }
    else
    {
        delete get_imebra_parameter(DicomDirEntry);
    }
    return self;
}

-(void)dealloc
{
    delete_imebra_object_holder(DicomDirEntry);
}

-(ImebraDataSet*)getEntryDataSet
{
    return [[ImebraDataSet alloc] initWithImebraDataSet:new imebra::DataSet(get_imebra_object_holder(DicomDirEntry)->getEntryDataSet())];
}

-(ImebraDicomDirEntry*)getNextEntry
{
    if(!get_imebra_object_holder(DicomDirEntry)->hasNextEntry())
    {
        return nil;
    }
    return [[ImebraDicomDirEntry alloc] initWithImebraDicomDirEntry:new imebra::DicomDirEntry(get_imebra_object_holder(DicomDirEntry)->getNextEntry())];
}

-(ImebraDicomDirEntry*)getFirstChildEntry
{
    if(!get_imebra_object_holder(DicomDirEntry)->hasChildren())
    {
        return nil;
    }
    return [[ImebraDicomDirEntry alloc] initWithImebraDicomDirEntry:new imebra::DicomDirEntry(get_imebra_object_holder(DicomDirEntry)->getFirstChildEntry())];
}

-(NSArray*)getFileParts:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    NSMutableArray* pFileParts = [[NSMutableArray alloc] init];

    imebra::fileParts_t fileParts = get_imebra_object_holder(DicomDirEntry)->getFileParts();
    for(const std::string& part: fileParts)
    {
        [pFileParts addObject: imebra::stringToNSString(part)];
    }

    return pFileParts;

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

-(NSString*)getTypeString:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return imebra::stringToNSString(get_imebra_object_holder(DicomDirEntry)->getTypeString());

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

@end


@implementation ImebraMutableDicomDirEntry

-(ImebraMutableDataSet*)getEntryDataSet
{
    return [[ImebraMutableDataSet alloc] initWithImebraDataSet:new imebra::MutableDataSet(((imebra::MutableDicomDirEntry*)get_imebra_object_holder(DicomDirEntry))->getEntryDataSet())];
}

-(void)setNextEntry:(ImebraDicomDirEntry*)pNextEntry error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    ((imebra::MutableDicomDirEntry*)get_imebra_object_holder(DicomDirEntry))->setNextEntry(*get_other_imebra_object_holder(pNextEntry, DicomDirEntry));

    OBJC_IMEBRA_FUNCTION_END();
}

-(void)setFirstChildEntry:(ImebraDicomDirEntry*)pFirstChildEntry error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    ((imebra::MutableDicomDirEntry*)get_imebra_object_holder(DicomDirEntry))->setFirstChildEntry(*get_other_imebra_object_holder(pFirstChildEntry, DicomDirEntry));

    OBJC_IMEBRA_FUNCTION_END();
}

-(void)setFileParts:(NSArray*)pFileParts error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    imebra::fileParts_t fileParts;

    size_t partsCount = [pFileParts count];
    for(size_t scanParts(0); scanParts != partsCount; ++scanParts)
    {
        fileParts.push_back(imebra::NSStringToString([pFileParts objectAtIndex:scanParts]));
    }

    ((imebra::MutableDicomDirEntry*)get_imebra_object_holder(DicomDirEntry))->setFileParts(fileParts);

    OBJC_IMEBRA_FUNCTION_END();
}

@end



@implementation ImebraDicomDir

-(id)initWithImebraDicomDir:define_imebra_parameter(DicomDir)
{
    reset_imebra_object_holder(DicomDir);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(DicomDir, get_imebra_parameter(DicomDir));
    }
    return self;
}

-(id)initWithDataSet:(ImebraDataSet*)pDataSet error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    reset_imebra_object_holder(DicomDir);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(DicomDir, new imebra::DicomDir(*get_other_imebra_object_holder(pDataSet, DataSet)));
    }
    return self;

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

-(void)dealloc
{
    delete_imebra_object_holder(DicomDir);
}

-(ImebraDicomDirEntry*)getFirstRootEntry:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return [[ImebraDicomDirEntry alloc] initWithImebraDicomDirEntry:new imebra::DicomDirEntry(get_imebra_object_holder(DicomDir)->getFirstRootEntry())];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}


@end


@implementation ImebraMutableDicomDir

-(id)init
{
    reset_imebra_object_holder(DicomDir);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(DicomDir, new imebra::MutableDicomDir());
    }
    return self;
}

-(ImebraMutableDicomDirEntry*)getNewEntry:(NSString*)recordType error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return [[ImebraMutableDicomDirEntry alloc] initWithImebraDicomDirEntry:new imebra::MutableDicomDirEntry(((imebra::MutableDicomDir*)get_imebra_object_holder(DicomDir))->getNewEntry(imebra::NSStringToString(recordType)))];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

-(void)setFirstRootEntry:(ImebraDicomDirEntry*)firstEntryRecord error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    ((imebra::MutableDicomDir*)get_imebra_object_holder(DicomDir))->setFirstRootEntry(*get_other_imebra_object_holder(firstEntryRecord, DicomDirEntry));

    OBJC_IMEBRA_FUNCTION_END();
}

-(ImebraDataSet*)updateDataSet:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return [[ImebraDataSet alloc] initWithImebraDataSet:new imebra::DataSet(((imebra::MutableDicomDir*)get_imebra_object_holder(DicomDir))->updateDataSet())];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

@end
