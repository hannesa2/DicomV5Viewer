/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#include "../include/dicomhero6_objc/dicomhero_dicomDir.h"
#include "../include/dicomhero6_objc/dicomhero_dataset.h"
#include "dicomhero_implementation_macros.h"
#include "dicomhero_strings.h"
#include "dicomhero_nserror.h"
#include <dicomhero6/dicomDirEntry.h>
#include <dicomhero6/dicomDir.h>
#include <dicomhero6/dataSet.h>

@implementation DicomheroDicomDirEntry

-(id)initWithDicomheroDicomDirEntry:define_dicomhero_parameter(DicomDirEntry)
{
    reset_dicomhero_object_holder(DicomDirEntry);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(DicomDirEntry, get_dicomhero_parameter(DicomDirEntry));
    }
    else
    {
        delete get_dicomhero_parameter(DicomDirEntry);
    }
    return self;
}

-(void)dealloc
{
    delete_dicomhero_object_holder(DicomDirEntry);
}

-(DicomheroDataSet*)getEntryDataSet
{
    return [[DicomheroDataSet alloc] initWithDicomheroDataSet:new dicomhero::DataSet(get_dicomhero_object_holder(DicomDirEntry)->getEntryDataSet())];
}

-(DicomheroDicomDirEntry*)getNextEntry
{
    if(!get_dicomhero_object_holder(DicomDirEntry)->hasNextEntry())
    {
        return nil;
    }
    return [[DicomheroDicomDirEntry alloc] initWithDicomheroDicomDirEntry:new dicomhero::DicomDirEntry(get_dicomhero_object_holder(DicomDirEntry)->getNextEntry())];
}

-(DicomheroDicomDirEntry*)getFirstChildEntry
{
    if(!get_dicomhero_object_holder(DicomDirEntry)->hasChildren())
    {
        return nil;
    }
    return [[DicomheroDicomDirEntry alloc] initWithDicomheroDicomDirEntry:new dicomhero::DicomDirEntry(get_dicomhero_object_holder(DicomDirEntry)->getFirstChildEntry())];
}

-(NSArray*)getFileParts:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    NSMutableArray* pFileParts = [[NSMutableArray alloc] init];

    dicomhero::fileParts_t fileParts = get_dicomhero_object_holder(DicomDirEntry)->getFileParts();
    for(const std::string& part: fileParts)
    {
        [pFileParts addObject: dicomhero::stringToNSString(part)];
    }

    return pFileParts;

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

-(NSString*)getTypeString:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return dicomhero::stringToNSString(get_dicomhero_object_holder(DicomDirEntry)->getTypeString());

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

-(void)setNextEntry:(DicomheroDicomDirEntry*)pNextEntry error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    get_dicomhero_object_holder(DicomDirEntry)->setNextEntry(*get_other_dicomhero_object_holder(pNextEntry, DicomDirEntry));

    OBJC_DICOMHERO_FUNCTION_END();
}

-(void)setFirstChildEntry:(DicomheroDicomDirEntry*)pFirstChildEntry error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    get_dicomhero_object_holder(DicomDirEntry)->setFirstChildEntry(*get_other_dicomhero_object_holder(pFirstChildEntry, DicomDirEntry));

    OBJC_DICOMHERO_FUNCTION_END();
}

-(void)setFileParts:(NSArray*)pFileParts error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    dicomhero::fileParts_t fileParts;

    size_t partsCount = [pFileParts count];
    for(size_t scanParts(0); scanParts != partsCount; ++scanParts)
    {
        fileParts.push_back(dicomhero::NSStringToString([pFileParts objectAtIndex:scanParts]));
    }

    get_dicomhero_object_holder(DicomDirEntry)->setFileParts(fileParts);

    OBJC_DICOMHERO_FUNCTION_END();
}

@end



@implementation DicomheroDicomDir

-(id)initWithDicomheroDicomDir:define_dicomhero_parameter(DicomDir)
{
    reset_dicomhero_object_holder(DicomDir);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(DicomDir, get_dicomhero_parameter(DicomDir));
    }
    return self;
}

-(id)initWithDataSet:(DicomheroDataSet*)pDataSet error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    reset_dicomhero_object_holder(DicomDir);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(DicomDir, new dicomhero::DicomDir(*get_other_dicomhero_object_holder(pDataSet, DataSet)));
    }
    return self;

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

-(void)dealloc
{
    delete_dicomhero_object_holder(DicomDir);
}

-(DicomheroDicomDirEntry*)getFirstRootEntry:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return [[DicomheroDicomDirEntry alloc] initWithDicomheroDicomDirEntry:new dicomhero::DicomDirEntry(get_dicomhero_object_holder(DicomDir)->getFirstRootEntry())];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

-(id)init
{
    reset_dicomhero_object_holder(DicomDir);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(DicomDir, new dicomhero::DicomDir());
    }
    return self;
}

-(DicomheroDicomDirEntry*)getNewEntry:(NSString*)recordType error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return [[DicomheroDicomDirEntry alloc] initWithDicomheroDicomDirEntry:new dicomhero::DicomDirEntry(get_dicomhero_object_holder(DicomDir)->getNewEntry(dicomhero::NSStringToString(recordType)))];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

-(void)setFirstRootEntry:(DicomheroDicomDirEntry*)firstEntryRecord error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    get_dicomhero_object_holder(DicomDir)->setFirstRootEntry(*get_other_dicomhero_object_holder(firstEntryRecord, DicomDirEntry));

    OBJC_DICOMHERO_FUNCTION_END();
}

-(DicomheroDataSet*)updateDataSet:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return [[DicomheroDataSet alloc] initWithDicomheroDataSet:new dicomhero::DataSet(get_dicomhero_object_holder(DicomDir)->updateDataSet())];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

@end
