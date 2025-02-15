/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#include "dicomhero_implementation_macros.h"

#import <Foundation/Foundation.h>
#import "../include/dicomhero6_objc/dicomhero_acse.h"
#include "dicomhero_nserror.h"
#include <dicomhero6/acse.h>
#include <dicomhero6/dataSet.h>
#include <dicomhero6/streamReader.h>
#include <dicomhero6/streamWriter.h>
#include "dicomhero_strings.h"

////////////////////////////////////////////////////////
//
// DicomheroPresentationContext
//
////////////////////////////////////////////////////////

@implementation DicomheroPresentationContext

-(id)initWithAbstractSyntax:(NSString*)abstractSyntax
{
    reset_dicomhero_object_holder(PresentationContext);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(PresentationContext, new dicomhero::PresentationContext(dicomhero::NSStringToString(abstractSyntax)));
    }
    return self;
}

-(id)initWithAbstractSyntax:(NSString*)abstractSyntax scuRole:(BOOL)bSCURole scpRole:(BOOL)bSCPRole
{
    reset_dicomhero_object_holder(PresentationContext);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(PresentationContext, new dicomhero::PresentationContext(dicomhero::NSStringToString(abstractSyntax), bSCURole != 0, bSCPRole != 0));
    }
    return self;
}

-(void)dealloc
{
    delete_dicomhero_object_holder(PresentationContext);
}

-(void)addTransferSyntax:(NSString*)transferSyntax
{
    get_dicomhero_object_holder(PresentationContext)->addTransferSyntax(dicomhero::NSStringToString(transferSyntax));
}

@end


@implementation DicomheroPresentationContexts

-(id)init
{
    reset_dicomhero_object_holder(PresentationContexts);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(PresentationContexts, new dicomhero::PresentationContexts());
    }
    return self;

}

-(void)dealloc
{
    delete_dicomhero_object_holder(PresentationContexts);
}

-(void)addPresentationContext:(DicomheroPresentationContext*)pPresentationContext
{
    get_dicomhero_object_holder(PresentationContexts)->addPresentationContext(*get_other_dicomhero_object_holder(pPresentationContext, PresentationContext));
}

@end


@implementation DicomheroAssociationMessage: NSObject

-(id)initWithDicomheroAssociationMessage:define_dicomhero_parameter(AssociationMessage)
{
    reset_dicomhero_object_holder(AssociationMessage);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(AssociationMessage, new dicomhero::AssociationMessage(*get_dicomhero_parameter(AssociationMessage)));
    }
    else
    {
        delete get_dicomhero_parameter(AssociationMessage);
    }
    return self;
}

-(id)initWithAbstractSyntax:(NSString*)abstractSyntax
{
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(AssociationMessage, new dicomhero::AssociationMessage(dicomhero::NSStringToString(abstractSyntax)));
    }
    return self;
}

-(void)dealloc
{
    delete_dicomhero_object_holder(AssociationMessage);
}

-(void)addDataSet:(DicomheroDataSet*)pDataSet error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    get_dicomhero_object_holder(AssociationMessage)->addDataSet(*get_other_dicomhero_object_holder(pDataSet, DataSet));

    OBJC_DICOMHERO_FUNCTION_END();
}

-(NSString*)abstractSyntax
{
    return dicomhero::stringToNSString(get_dicomhero_object_holder(AssociationMessage)->getAbstractSyntax());
}

-(DicomheroDataSet*)getCommand:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return [[DicomheroDataSet alloc] initWithDicomheroDataSet:(new dicomhero::DataSet(get_dicomhero_object_holder(AssociationMessage)->getCommand()))];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

-(DicomheroDataSet*)getPayload:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return [[DicomheroDataSet alloc] initWithDicomheroDataSet:(new dicomhero::DataSet(get_dicomhero_object_holder(AssociationMessage)->getPayload()))];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

-(BOOL)hasPayload
{
    return get_dicomhero_object_holder(AssociationMessage)->hasPayload();
}

@end


@implementation DicomheroAssociationBase

-(void)dealloc
{
    delete_dicomhero_object_holder(AssociationBase);
}

-(DicomheroAssociationMessage*)getCommand:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return [[DicomheroAssociationMessage alloc] initWithDicomheroAssociationMessage:(new dicomhero::AssociationMessage(get_dicomhero_object_holder( AssociationBase)->getCommand()))];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

-(DicomheroAssociationMessage*)getResponse:(unsigned int) messageId error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();
    return [[DicomheroAssociationMessage alloc] initWithDicomheroAssociationMessage:(new dicomhero::AssociationMessage(get_dicomhero_object_holder(AssociationBase)->getResponse((std::uint16_t)messageId)))];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

-(void)sendMessage:(DicomheroAssociationMessage*)pMessage error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    get_dicomhero_object_holder(AssociationBase)->sendMessage(*(get_other_dicomhero_object_holder(pMessage, AssociationMessage)));

    OBJC_DICOMHERO_FUNCTION_END();
}

-(void)release:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    get_dicomhero_object_holder(AssociationBase)->release();

    OBJC_DICOMHERO_FUNCTION_END();
}

-(void)abort:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    get_dicomhero_object_holder(AssociationBase)->abort();

    OBJC_DICOMHERO_FUNCTION_END();
}

-(NSString*)getTransferSyntax:(NSString*)abstractSyntax error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return dicomhero::stringToNSString(get_dicomhero_object_holder(AssociationBase)->getTransferSyntax(dicomhero::NSStringToString(abstractSyntax)));

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

-(NSString*)thisAET
{
    return dicomhero::stringToNSString(get_dicomhero_object_holder(AssociationBase)->getThisAET());
}

-(NSString*)otherAET
{
    return dicomhero::stringToNSString(get_dicomhero_object_holder(AssociationBase)->getOtherAET());
}

@end


@implementation DicomheroAssociationSCU

-(id)initWithThisAET:(NSString*)thisAET otherAET:(NSString*)otherAET
    maxInvokedOperations:(unsigned int)invokedOperations
    maxPerformedOperations:(unsigned int)performedOperations
    presentationContexts:(DicomheroPresentationContexts*)presentationContexts
    reader:(DicomheroStreamReader*)pInput
    writer:(DicomheroStreamWriter*)pOutput
    dimseTimeoutSeconds:(unsigned int)dimseTimeoutSeconds error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    reset_dicomhero_object_holder(AssociationBase);

    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(AssociationBase,
                    new dicomhero::AssociationSCU(
                                     dicomhero::NSStringToString(thisAET),
                                     dicomhero::NSStringToString(otherAET),
                                     invokedOperations,
                                     performedOperations,
                                     *get_other_dicomhero_object_holder(presentationContexts, PresentationContexts),
                                     *get_other_dicomhero_object_holder(pInput, StreamReader),
                                     *get_other_dicomhero_object_holder(pOutput, StreamWriter),
                                     dimseTimeoutSeconds));
    }
    return self;

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

@end


@implementation DicomheroAssociationSCP

-(id)initWithThisAET:(NSString*)thisAET
    maxInvokedOperations:(unsigned int)invokedOperations
    maxPerformedOperations:(unsigned int)performedOperations
    presentationContexts:(DicomheroPresentationContexts*)presentationContexts
    reader:(DicomheroStreamReader*)pInput
    writer:(DicomheroStreamWriter*)pOutput
    dimseTimeoutSeconds:(unsigned int)dimseTimeoutSeconds
    artimTimeoutSeconds:(unsigned int)artimTimeoutSeconds error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    reset_dicomhero_object_holder(AssociationBase);

    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(AssociationBase,
                    new dicomhero::AssociationSCP(
                                     dicomhero::NSStringToString(thisAET),
                                     invokedOperations,
                                     performedOperations,
                                     *get_other_dicomhero_object_holder(presentationContexts, PresentationContexts),
                                     *get_other_dicomhero_object_holder(pInput, StreamReader),
                                     *get_other_dicomhero_object_holder(pOutput, StreamWriter),
                                     dimseTimeoutSeconds,
                                     artimTimeoutSeconds));
    }
    return self;

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

@end


