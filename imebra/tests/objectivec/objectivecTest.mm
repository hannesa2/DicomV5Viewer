#include <gtest/gtest.h>
#include <imebra/imebra.h>
#include <imebraobjc/imebra.h>
#include "../buildImageForTest.h"
#include "../../objectivec/src/imebra_strings.h"
#include <thread>



namespace imebra
{

namespace tests
{


// Test NSString conversion functions
TEST(objectivec, stringToNSStringTest)
{
    NSString* patient0 = [[NSString alloc] initWithUTF8String:"??\xD0\xA1\xD0\xBC\xD1\x8B\xD1\x81\xD0\xBB\x20\xD0\xB2\xD1\x81\xD0\xB5\xD0\xB9"];
    NSString* patient1 = [[NSString alloc] initWithUTF8String:"\xD0\xA1\xD0\xBC\xD1\x8B\xD1\x81\xD0\xBB\x20\xD0\xB2\xD1\x81\xD0\xB5\xD0\xB9"];

    ImebraMutableMemory* pStreamMemory = [[ImebraMutableMemory alloc] init];
    ImebraTagId* pPatientTag = [[ImebraTagId alloc] initWithId:ImebraTagEnumPatientName_0010_0010];

    {

        NSMutableArray* pCharsets = [[NSMutableArray alloc] init];
        [pCharsets addObject: @"ISO_IR 6"];
        [pCharsets addObject: @"ISO 2022 IR 127"];
        [pCharsets addObject: @"ISO 2022 IR 144"];
        [pCharsets addObject: @"ISO 2022 IR 100"];
        [pCharsets addObject: @"ISO 2022 IR 126"];
        
        ImebraMutableDataSet* pDataSet = [[ImebraMutableDataSet alloc] initWithTransferSyntax:@"1.2.840.10008.1.2.1" charsets:pCharsets];

        @autoreleasepool
        {
            NSError* pError = 0;
            ImebraWritingDataHandler* pHandler = [pDataSet getWritingDataHandler:pPatientTag bufferId:0 error:&pError];

            [pHandler setString:0 newValue:patient0 error:&pError];
            [pHandler setString:1 newValue:patient1 error:&pError];
        }

        @autoreleasepool
        {
            ImebraMemoryStreamOutput* pWriteStream = [[ImebraMemoryStreamOutput alloc] initWithMutableMemory:pStreamMemory];
            ImebraStreamWriter* pWriter = [[ImebraStreamWriter alloc] initWithOutputStream: pWriteStream];
            NSError* pError = 0;
            [ImebraCodecFactory saveToStream:pWriter dataSet:pDataSet codecType:ImebraCodecTypeDicom error:&pError];

        }

        NSArray* pTags = [pDataSet getTags];
        size_t numTags = [pTags count];
        bool bPatientFound(false);
        for(size_t scanTags(0); scanTags != numTags; ++scanTags)
        {
            ImebraTagId* pTag = [pTags objectAtIndex:scanTags];
            if(pTag.groupId == 0x10 && pTag.tagId == 0x10 && pTag.groupOrder == 0)
            {
                bPatientFound = true;
            }
        }
        EXPECT_TRUE(bPatientFound);

    }

    {
        ImebraMemoryStreamInput* pReadStream = [[ImebraMemoryStreamInput alloc] initWithReadMemory:pStreamMemory];

        ImebraStreamReader* pReader = [[ImebraStreamReader alloc] initWithInputStream:pReadStream];

        NSError* pError = 0;
        ImebraDataSet* pTestDataSet = [ImebraCodecFactory loadFromStream:pReader error:&pError];

        NSString* nsPatientName0 = [pTestDataSet getString:pPatientTag elementNumber:0 error:&pError];
        NSString* nsPatientName1 = [pTestDataSet getString:pPatientTag elementNumber:1 error:&pError];

        EXPECT_TRUE([nsPatientName0 isEqualToString:patient0]);
        EXPECT_TRUE([nsPatientName1 isEqualToString:patient1]);
    }

}


// Test NSString conversion functions
TEST(objectivec, NSStringToStringTest)
{
    MutableMemory streamMemory;
    {
        charsetsList_t charsets;
        charsets.push_back("ISO_IR 6");
        MutableDataSet testDataSet("1.2.840.10008.1.2.1", charsets);

        {
            WritingDataHandler handler(testDataSet.getWritingDataHandler(TagId(0x10, 0x10), 0));

            handler.setString(0, NSStringToString(@"Test 1"));
            handler.setString(1, NSStringToString(@"Test 2"));
        }

        MemoryStreamOutput writeStream(streamMemory);
        StreamWriter writer(writeStream);
        CodecFactory::save(testDataSet, writer, codecType_t::dicom);
    }

    {
        MemoryStreamInput readStream(streamMemory);
        StreamReader reader(readStream);
        DataSet testDataSet(CodecFactory::load(reader));

        std::string patientName0(testDataSet.getString(TagId(0x0010, 0x0010), 0));
        std::string patientName1(testDataSet.getString(TagId(0x0010, 0x0010), 1));

        EXPECT_EQ("Test 1", patientName0);
        EXPECT_EQ("Test 2", patientName1);

    }
}


// Test the codec factory (save and reload a dataset)
TEST(objectivec, CodecFactory)
{
    MutableDataSet testDataSet("1.2.840.10008.1.2");
    testDataSet.setString(TagId(tagId_t::PatientName_0010_0010), "Test^Patient");
    testDataSet.setString(TagId(tagId_t::PatientID_0010_0020), "TestID");
    CodecFactory::save(testDataSet, "testCodecFactory.dcm", codecType_t::dicom);

    NSError* error = nil;
    ImebraDataSet* pDataSet = [ImebraCodecFactory loadFromFile:@"testCodecFactory.dcm" error:&error];
    NSString* checkPatientName = [pDataSet getString:[[ImebraTagId alloc] initWithGroup:0x10 tag:0x10] elementNumber:0 error:&error];
    NSString* checkPatientID = [pDataSet getString:[[ImebraTagId alloc] initWithGroup:0x10 tag:0x20] elementNumber:0 error:&error];

    EXPECT_EQ(imebra::NSStringToString(checkPatientName), "Test^Patient");
    EXPECT_EQ(imebra::NSStringToString(checkPatientID), "TestID");
}


// Test NSError on non-existent file
TEST(objectivec, CodecFactoryFailLoad)
{
    NSError* error = nil;
    ImebraDataSet* pDataSet = [ImebraCodecFactory loadFromFile:@"fail.dcm" error:&error];
    EXPECT_EQ(pDataSet, nullptr);
    EXPECT_EQ(imebra::NSStringToString([error domain]), "imebra");
}


// Initialize and check an image content
TEST(objectivec, image)
{
    ImebraMutableImage* pImage = [[ImebraMutableImage alloc] initWithWidth:5 height:5 depth:ImebraBitDepthU16 colorSpace:@"MONOCHROME2" highBit:15];

    NSError* error = nil;

    @autoreleasepool
    {
        ImebraWritingDataHandler* writingDataHandler = [pImage getWritingDataHandler:&error];
        for(unsigned int pixel(0); pixel != 25; ++pixel)
        {
            [writingDataHandler setUint32:pixel newValue:pixel error:&error];
        }
    }

    ImebraMutableDataSet* pDataSet = [[ImebraMutableDataSet alloc] initWithTransferSyntax:@"1.2.840.10008.1.2"];
    [pDataSet setImage:0 image:pImage quality:ImebraImageQualityVeryHigh error:&error];

    ImebraImage* pCheckImage = [pDataSet getImage:0 error:&error];
    ImebraReadingDataHandlerNumeric* readingDataHandler = [pCheckImage getReadingDataHandler:&error];
    for(unsigned int pixel(0); pixel != 25; ++pixel)
    {
        EXPECT_EQ([readingDataHandler getUint32:pixel error:&error], pixel);
    }
}


// Initialize and check an image content
TEST(objectivec, imageNSData)
{
    ImebraMutableImage* pImage = [[ImebraMutableImage alloc] initWithWidth:5 height:5 depth:ImebraBitDepthU16 colorSpace:@"MONOCHROME2" highBit:15];

    NSError* error = nil;

    @autoreleasepool
    {
        std::uint16_t buffer[25];
        for(std::uint16_t pixel(0); pixel != 25; ++pixel)
        {
            buffer[pixel] = (std::uint16_t)(pixel + 1u);
        }
        NSData* pSource = [[NSData alloc] initWithBytes:buffer length:sizeof(buffer)];
        ImebraWritingDataHandlerNumeric* writingDataHandler = [pImage getWritingDataHandler:&error];
        [writingDataHandler assign:pSource error:&error];
    }

    ImebraMutableDataSet* pDataSet = [[ImebraMutableDataSet alloc] initWithTransferSyntax:@"1.2.840.10008.1.2"];
    [pDataSet setImage:0 image:pImage quality:ImebraImageQualityVeryHigh error:&error];

    ImebraImage* pCheckImage = [pDataSet getImage:0 error:&error];
    ImebraReadingDataHandlerNumeric* readingDataHandler = [pCheckImage getReadingDataHandler:&error];
    NSData* pData = [readingDataHandler getMemory:&error].data;
    for(unsigned int pixel(0); pixel != 25; ++pixel)
    {
        EXPECT_EQ(pixel + 1, ((std::uint16_t*)(pData.bytes))[pixel]);
    }
}



// Set different dataset tags
TEST(objectivec, datasetValues)
{
    NSError* error = nil;

    ImebraMutableDataSet* pDataSet = [[ImebraMutableDataSet alloc] initWithTransferSyntax:@"1.2.840.10008.1.2"];

    [pDataSet setString:[[ImebraTagId alloc] initWithGroup:0x10 tag:0x10] newValue:@"TestPatient" error:&error];
    [pDataSet setAge:[[ImebraTagId alloc] initWithGroup:0x10 tag:0x1010] newValue:[[ImebraAge alloc] initWithAge:10 units:ImebraAgeUnitYears] error:&error];

    [pDataSet setInt32:[[ImebraTagId alloc] initWithGroup:0x10 tag:0x1011] newValue:10 tagVR:ImebraTagTypeSL error:&error];
    [pDataSet setUint32:[[ImebraTagId alloc] initWithGroup:0x10 tag:0x1012] newValue:11 tagVR:ImebraTagTypeUL error:&error];
    [pDataSet setDouble:[[ImebraTagId alloc] initWithGroup:0x10 tag:0x1013] newValue:12.0f tagVR:ImebraTagTypeUL error:&error];

    ImebraMutableTag* pTag = [pDataSet getTagCreate:[[ImebraTagId alloc] initWithGroup:0x12 tag:0x12] tagVR:ImebraTagTypeFD error:&error];

    @autoreleasepool
    {
        ImebraWritingDataHandlerNumeric* pWriteDouble = [pTag getWritingDataHandlerNumeric:0 error:&error];
        [pWriteDouble setSize:4];
        EXPECT_EQ(4u, pWriteDouble.size);
        [pWriteDouble setDouble:0 newValue:0 error:&error];
        [pWriteDouble setDouble:1 newValue:1 error:&error];
        [pWriteDouble setDouble:2 newValue:2 error:&error];
        [pWriteDouble setDouble:3 newValue:3 error:&error];
    }

    NSString* checkPatient0 = [pDataSet getString:[[ImebraTagId alloc] initWithGroup:0x10 tag:0x10] elementNumber:0 error:&error];
    ImebraAge* checkAge = [pDataSet getAge:[[ImebraTagId alloc] initWithGroup:0x10 tag:0x1010] elementNumber:0 error:&error];

    EXPECT_EQ(error, nil);
    NSString* checkPatient1 = [pDataSet getString:[[ImebraTagId alloc] initWithGroup:0x10 tag:0x11] elementNumber:0 error:&error];
    EXPECT_EQ(imebra::NSStringToString([error domain]), "imebra");
    NSString* checkPatient2 = [pDataSet getString:[[ImebraTagId alloc] initWithGroup:0x10 tag:0x11] elementNumber:0 defaultValue:@"defaultValue" error:&error];

    EXPECT_EQ(imebra::NSStringToString(checkPatient0), "TestPatient");
    EXPECT_EQ(checkPatient1, nil);
    EXPECT_EQ(imebra::NSStringToString(checkPatient2), "defaultValue");

    EXPECT_EQ(10u, [checkAge age]);
    EXPECT_EQ(ImebraAgeUnitYears, [checkAge units]);

    EXPECT_EQ(10, [pDataSet getInt32:[[ImebraTagId alloc] initWithGroup:0x10 tag:0x1011] elementNumber:0 error:&error]);
    EXPECT_EQ(11u, [pDataSet getUint32:[[ImebraTagId alloc] initWithGroup:0x10 tag:0x1012] elementNumber:0 error:&error]);
    EXPECT_DOUBLE_EQ(12.0, [pDataSet getDouble:[[ImebraTagId alloc] initWithGroup:0x10 tag:0x1013] elementNumber:0 error:&error]);
    EXPECT_EQ(12, [pDataSet getInt32:[[ImebraTagId alloc] initWithGroup:0x10 tag:0x1020] elementNumber:0 defaultValue:12u error:&error]);
    EXPECT_EQ(13u, [pDataSet getUint32:[[ImebraTagId alloc] initWithGroup:0x10 tag:0x1021] elementNumber:0 defaultValue:13u error:&error]);
    EXPECT_DOUBLE_EQ(14.0, [pDataSet getDouble:[[ImebraTagId alloc] initWithGroup:0x10 tag:0x1022] elementNumber:0 defaultValue:14.0 error:&error]);

    EXPECT_DOUBLE_EQ(0.0, [pDataSet getDouble:[[ImebraTagId alloc] initWithGroup:0x12 tag:0x12] elementNumber:0 error:&error]);
    EXPECT_DOUBLE_EQ(1.0, [pDataSet getDouble:[[ImebraTagId alloc] initWithGroup:0x12 tag:0x12] elementNumber:1 error:&error]);
    EXPECT_DOUBLE_EQ(2.0, [pDataSet getDouble:[[ImebraTagId alloc] initWithGroup:0x12 tag:0x12] elementNumber:2 error:&error]);
    EXPECT_DOUBLE_EQ(3.0, [pDataSet getDouble:[[ImebraTagId alloc] initWithGroup:0x12 tag:0x12] elementNumber:3 error:&error]);
}


void listenerThread()
{
    try
    {
        NSError* pError(0);
        ImebraTCPPassiveAddress* pAddress = [[ImebraTCPPassiveAddress alloc] initWithNode:@"localhost" service:@"20000" error:&pError];
        ImebraTCPListener* pListener = [[ImebraTCPListener alloc] initWithAddress:pAddress error:&pError];

        @autoreleasepool
        {
            ImebraTCPStream* pStream = [pListener waitForConnection:&pError];

            ImebraBaseStreamInput* pInput = [pStream getStreamInput];
            ImebraBaseStreamOutput* pOutput = [pStream getStreamOutput];
            ImebraStreamReader* pReader = [[ImebraStreamReader alloc] initWithInputStream:pInput];
            ImebraStreamWriter* pWriter = [[ImebraStreamWriter alloc] initWithOutputStream:pOutput];

            ImebraPresentationContexts* pContexts = [[ImebraPresentationContexts alloc] init];

            ImebraPresentationContext* pContext = [[ImebraPresentationContext alloc] initWithAbstractSyntax:@"1.2.840.10008.1.1"];
            [pContext addTransferSyntax:@"1.2.840.10008.1.2"];

            [pContexts addPresentationContext:pContext];

            ImebraAssociationSCP* pSCP = [[ImebraAssociationSCP alloc]
                    initWithThisAET:@"SCP" maxInvokedOperations:1 maxPerformedOperations:1 presentationContexts:pContexts
                         reader:pReader writer:pWriter dimseTimeoutSeconds:30 artimTimeoutSeconds:30 error:&pError];

            ImebraDimseService* pDimse = [[ImebraDimseService alloc]initWithAssociation:pSCP];

            for(;;)
            {
                ImebraDimseCommand* pCommand = (ImebraDimseCommand*)[pDimse getCommand:&pError];

                if(pError != 0)
                {
                    break;
                }

                ImebraDimseResponse* pResponse = nil;
                switch([pCommand commandType])
                {
                case ImebraDimseCommandTypeCStore:
                    pResponse = [[ImebraCStoreResponse alloc]initWithcommand:(ImebraCStoreCommand*)pCommand responseCode:ImebraDimseStatusCodeSuccess];
                    break;
                case ImebraDimseCommandTypeCGet:
                    pResponse = [[ImebraCGetResponse alloc]initWithcommand:(ImebraCGetCommand*)pCommand responseCode:ImebraDimseStatusCodeSuccess
                                                                           remainingSubOperations:0
                                                                           completedSubOperations:1
                                                                           failedSubOperations:0
                                                                           warningSubOperations:0];
                    break;
                case ImebraDimseCommandTypeCFind:
                    pResponse = [[ImebraCFindResponse alloc]initWithcommand:(ImebraCFindCommand*)pCommand responseCode:ImebraDimseStatusCodeSuccess];
                    break;
                case ImebraDimseCommandTypeCMove:
                    pResponse = [[ImebraCMoveResponse alloc]initWithcommand:(ImebraCMoveCommand*)pCommand responseCode:ImebraDimseStatusCodeSuccess
                                                                           remainingSubOperations:0
                                                                           completedSubOperations:1
                                                                           failedSubOperations:0
                                                                           warningSubOperations:0];
                    EXPECT_EQ("DEST", imebra::NSStringToString([(ImebraCMoveCommand*)pCommand getDestinationAET:&pError]));
                    break;
                case ImebraDimseCommandTypeCEcho:
                    pResponse = [[ImebraCEchoResponse alloc]initWithcommand:(ImebraCEchoCommand*)pCommand responseCode:ImebraDimseStatusCodeSuccess];
                    break;
                case ImebraDimseCommandTypeCCancel:
                    break;
                case ImebraDimseCommandTypeNEventReport:
                    pResponse = [[ImebraNEventReportResponse alloc]initWithcommand:(ImebraNEventReportCommand*)pCommand responseCode:ImebraDimseStatusCodeSuccess];
                    break;
                case ImebraDimseCommandTypeNGet:
                    pResponse = [[ImebraNGetResponse alloc]initWithcommand:(ImebraNGetCommand*)pCommand responseCode:ImebraDimseStatusCodeSuccess];
                    break;
                case ImebraDimseCommandTypeNSet:
                    pResponse = [[ImebraNSetResponse alloc]initWithcommand:(ImebraNSetCommand*)pCommand responseCode:ImebraDimseStatusCodeSuccess];
                    break;
                case ImebraDimseCommandTypeNAction:
                    pResponse = [[ImebraNActionResponse alloc]initWithcommand:(ImebraNActionCommand*)pCommand responseCode:ImebraDimseStatusCodeSuccess];
                    break;
                case ImebraDimseCommandTypeNCreate:
                    pResponse = [[ImebraNCreateResponse alloc]initWithcommand:(ImebraNCreateCommand*)pCommand responseCode:ImebraDimseStatusCodeSuccess];
                    break;
                case ImebraDimseCommandTypeNDelete:
                    pResponse = [[ImebraNDeleteResponse alloc]initWithcommand:(ImebraNDeleteCommand*)pCommand responseCode:ImebraDimseStatusCodeSuccess];
                    break;
                }

                if(pResponse != nil)
                {
                    [pDimse sendCommandOrResponse:pResponse error:&pError];
                }

            } // for loop

        } // autoreleasepool

    }
    catch(const std::runtime_error&e)
    {
        std::cout << imebra::ExceptionsManager::getExceptionTrace();

    }

}


// Send a CStore command to a SCP via TCP
TEST(objectivec, dimse)
{
    std::thread scp(imebra::tests::listenerThread);

    try
    {

        std::this_thread::sleep_for(std::chrono::seconds(5));

        NSError* pError(0);
        ImebraTCPActiveAddress* pAddress = [[ImebraTCPActiveAddress alloc] initWithNode:@"localhost" service:@"20000" error:&pError];

        @autoreleasepool
        {
            ImebraTCPStream* pStream = [[ImebraTCPStream alloc] initWithAddress:pAddress error:&pError];

            ImebraBaseStreamInput* pInput = [pStream getStreamInput];
            ImebraBaseStreamOutput* pOutput = [pStream getStreamOutput];
            ImebraStreamReader* pReader = [[ImebraStreamReader alloc] initWithInputStream:pInput];
            ImebraStreamWriter* pWriter = [[ImebraStreamWriter alloc] initWithOutputStream:pOutput];

            ImebraPresentationContexts* pContexts = [[ImebraPresentationContexts alloc] init];

            ImebraPresentationContext* pContext = [[ImebraPresentationContext alloc] initWithAbstractSyntax:@"1.2.840.10008.1.1"];
            [pContext addTransferSyntax:@"1.2.840.10008.1.2"];

            [pContexts addPresentationContext:pContext];

            ImebraAssociationSCU* pSCU = [[ImebraAssociationSCU alloc]
                    initWithThisAET:@"SCU" otherAET:@"SCP" maxInvokedOperations:1 maxPerformedOperations:1 presentationContexts:pContexts
                         reader:pReader writer:pWriter dimseTimeoutSeconds:30 error:&pError];

            ImebraDimseService* pDimse = [[ImebraDimseService alloc]initWithAssociation:pSCU];

            // Send C-STORE
            {
                ImebraMutableDataSet* pDataSet = [[ImebraMutableDataSet alloc] initWithTransferSyntax:@"1.2.840.10008.1.2"];

                [pDataSet setString:[[ImebraTagId alloc] initWithGroup:0x10 tag:0x10] newValue:@"TestPatient" error:&pError];
                [pDataSet setAge:[[ImebraTagId alloc] initWithGroup:0x10 tag:0x1010] newValue:[[ImebraAge alloc] initWithAge:10 units:ImebraAgeUnitYears] error:&pError];

                ImebraCStoreCommand* pCommand = [[ImebraCStoreCommand alloc]initWithAbstractSyntax:
                    @"1.2.840.10008.1.1"
                    messageID:[pDimse getNextCommandID]
                    priority:ImebraDimseCommandPriorityMedium
                    affectedSopClassUid:@"1.2.840.10008.1.1"
                    affectedSopInstanceUid:@"1.2.3.4.5"
                    originatorAET:@"SCU"
                    originatorMessageID:0
                    payload:pDataSet];

                [pDimse sendCommandOrResponse:pCommand error:&pError];
                ImebraCStoreResponse* pResponse = [pDimse getCStoreResponse:pCommand error:&pError];

                EXPECT_EQ(ImebraDimseStatusSuccess, pResponse.status);
            }

            // Send C-GET
            {
                ImebraMutableDataSet* pDataSet = [[ImebraMutableDataSet alloc] initWithTransferSyntax:@"1.2.840.10008.1.2"];

                [pDataSet setString:[[ImebraTagId alloc] initWithGroup:0x10 tag:0x10] newValue:@"TestPatient" error:&pError];

                ImebraCGetCommand* pCommand = [[ImebraCGetCommand alloc]initWithAbstractSyntax:
                    @"1.2.840.10008.1.1"
                    messageID:[pDimse getNextCommandID]
                    priority:ImebraDimseCommandPriorityMedium
                    affectedSopClassUid:@"1.2.840.10008.1.1"
                    identifier:pDataSet];

                [pDimse sendCommandOrResponse:pCommand error:&pError];
                ImebraCGetResponse* pResponse = [pDimse getCGetResponse:pCommand error:&pError];

                EXPECT_EQ(ImebraDimseStatusSuccess, pResponse.status);
            }

            // Send C-FIND
            {
                ImebraMutableDataSet* pDataSet = [[ImebraMutableDataSet alloc] initWithTransferSyntax:@"1.2.840.10008.1.2"];

                [pDataSet setString:[[ImebraTagId alloc] initWithGroup:0x10 tag:0x10] newValue:@"TestPatient" error:&pError];

                ImebraCFindCommand* pCommand = [[ImebraCFindCommand alloc]initWithAbstractSyntax:
                    @"1.2.840.10008.1.1"
                    messageID:[pDimse getNextCommandID]
                    priority:ImebraDimseCommandPriorityMedium
                    affectedSopClassUid:@"1.2.840.10008.1.1"
                    identifier:pDataSet];

                [pDimse sendCommandOrResponse:pCommand error:&pError];
                ImebraCFindResponse* pResponse = [pDimse getCFindResponse:pCommand error:&pError];

                EXPECT_EQ(ImebraDimseStatusSuccess, pResponse.status);
            }

            // Send C-MOVE
            {
                ImebraMutableDataSet* pDataSet = [[ImebraMutableDataSet alloc] initWithTransferSyntax:@"1.2.840.10008.1.2"];

                [pDataSet setString:[[ImebraTagId alloc] initWithGroup:0x10 tag:0x10] newValue:@"TestPatient" error:&pError];

                ImebraCMoveCommand* pCommand = [[ImebraCMoveCommand alloc]initWithAbstractSyntax:
                    @"1.2.840.10008.1.1"
                    messageID:[pDimse getNextCommandID]
                    priority:ImebraDimseCommandPriorityMedium
                    affectedSopClassUid:@"1.2.840.10008.1.1"
                    destinationAET:@"DEST"
                    identifier:pDataSet];

                [pDimse sendCommandOrResponse:pCommand error:&pError];
                ImebraCMoveResponse* pResponse = [pDimse getCMoveResponse:pCommand error:&pError];

                EXPECT_EQ(ImebraDimseStatusSuccess, pResponse.status);
            }

            // Send C-ECHO
            {
                ImebraCEchoCommand* pCommand = [[ImebraCEchoCommand alloc]initWithAbstractSyntax:
                    @"1.2.840.10008.1.1"
                    messageID:[pDimse getNextCommandID]
                    priority:ImebraDimseCommandPriorityMedium
                    affectedSopClassUid:@"1.2.840.10008.1.1"];

                [pDimse sendCommandOrResponse:pCommand error:&pError];
                ImebraCEchoResponse* pResponse = [pDimse getCEchoResponse:pCommand error:&pError];

                EXPECT_EQ(ImebraDimseStatusSuccess, pResponse.status);
            }

            // Send C-CANCEL
            {
                ImebraCCancelCommand* pCommand = [[ImebraCCancelCommand alloc]initWithAbstractSyntax:
                    @"1.2.840.10008.1.1"
                    messageID:[pDimse getNextCommandID]
                    priority:ImebraDimseCommandPriorityMedium
                    cancelMessageID:1];

                [pDimse sendCommandOrResponse:pCommand error:&pError];
            }

            // Send N-EVENTREPORT
            {
                ImebraNEventReportCommand* pCommand = [[ImebraNEventReportCommand alloc]initWithAbstractSyntax:
                    @"1.2.840.10008.1.1"
                    messageID:[pDimse getNextCommandID]
                    affectedSopClassUid:@"1.2.840.10008.1.1"
                    affectedSopInstanceUid:@"1.1.1"
                    eventID:1];

                [pDimse sendCommandOrResponse:pCommand error:&pError];

                ImebraNEventReportResponse* pResponse = [pDimse getNEventReportResponse:pCommand error:&pError];

                EXPECT_EQ(ImebraDimseStatusSuccess, pResponse.status);
            }

            // Send N-GET
            {
                NSMutableArray* identifierList = [[NSMutableArray alloc] init];
                [identifierList addObject: [[ImebraTagId alloc] initWithGroup:0x10 tag:0x10]];
                [identifierList addObject: [[ImebraTagId alloc] initWithGroup:0x20 tag:0x10]];

                ImebraNGetCommand* pCommand = [[ImebraNGetCommand alloc]initWithAbstractSyntax:
                    @"1.2.840.10008.1.1"
                    messageID:[pDimse getNextCommandID]
                    requestedSopClassUid:@"1.2.840.10008.1.1"
                    requestedSopInstanceUid:@"1.1.1"
                    attributeIdentifierList:identifierList];

                [pDimse sendCommandOrResponse:pCommand error:&pError];

                ImebraNGetResponse* pResponse = [pDimse getNGetResponse:pCommand error:&pError];

                EXPECT_EQ(ImebraDimseStatusSuccess, pResponse.status);
            }

            // Send N-SET
            {
                ImebraMutableDataSet* pDataSet = [[ImebraMutableDataSet alloc] initWithTransferSyntax:@"1.2.840.10008.1.2"];

                [pDataSet setString:[[ImebraTagId alloc] initWithGroup:0x10 tag:0x10] newValue:@"TestPatient" error:&pError];

                ImebraNSetCommand* pCommand = [[ImebraNSetCommand alloc]initWithAbstractSyntax:
                    @"1.2.840.10008.1.1"
                    messageID:[pDimse getNextCommandID]
                    requestedSopClassUid:@"1.2.840.10008.1.1"
                    requestedSopInstanceUid:@"1.1.1"
                    modificationList:pDataSet];

                [pDimse sendCommandOrResponse:pCommand error:&pError];

                ImebraNSetResponse* pResponse = [pDimse getNSetResponse:pCommand error:&pError];

                EXPECT_EQ(ImebraDimseStatusSuccess, pResponse.status);
            }

            // Send N-ACTION
            {
                ImebraMutableDataSet* pDataSet = [[ImebraMutableDataSet alloc] initWithTransferSyntax:@"1.2.840.10008.1.2"];

                [pDataSet setString:[[ImebraTagId alloc] initWithGroup:0x10 tag:0x10] newValue:@"TestPatient" error:&pError];

                ImebraNActionCommand* pCommand = [[ImebraNActionCommand alloc]initWithAbstractSyntax:
                    @"1.2.840.10008.1.1"
                    messageID:[pDimse getNextCommandID]
                    requestedSopClassUid:@"1.2.840.10008.1.1"
                    requestedSopInstanceUid:@"1.1.1"
                    actionID:10
                    actionInformation:pDataSet];

                [pDimse sendCommandOrResponse:pCommand error:&pError];

                ImebraNActionResponse* pResponse = [pDimse getNActionResponse:pCommand error:&pError];

                EXPECT_EQ(ImebraDimseStatusSuccess, pResponse.status);
                EXPECT_EQ(10, pResponse.actionID);
            }

            // Send N-CREATE
            {

                ImebraMutableDataSet* pDataSet = [[ImebraMutableDataSet alloc] initWithTransferSyntax:@"1.2.840.10008.1.2"];

                [pDataSet setString:[[ImebraTagId alloc] initWithGroup:0x10 tag:0x10] newValue:@"TestPatient" error:&pError];

                ImebraNCreateCommand* pCommand = [[ImebraNCreateCommand alloc]initWithAbstractSyntax:
                    @"1.2.840.10008.1.1"
                    messageID:[pDimse getNextCommandID]
                    affectedSopClassUid:@"1.2.840.10008.1.1"
                    affectedSopInstanceUid:@"1.1.1"
                    attributeList:pDataSet];

                [pDimse sendCommandOrResponse:pCommand error:&pError];

                ImebraNCreateResponse* pResponse = [pDimse getNCreateResponse:pCommand error:&pError];

                EXPECT_EQ(ImebraDimseStatusSuccess, pResponse.status);
            }

            // Send N-DELETE
            {
                ImebraMutableDataSet* pDataSet = [[ImebraMutableDataSet alloc] initWithTransferSyntax:@"1.2.840.10008.1.2"];

                [pDataSet setString:[[ImebraTagId alloc] initWithGroup:0x10 tag:0x10] newValue:@"TestPatient" error:&pError];

                ImebraNDeleteCommand* pCommand = [[ImebraNDeleteCommand alloc]initWithAbstractSyntax:
                    @"1.2.840.10008.1.1"
                    messageID:[pDimse getNextCommandID]
                    requestedSopClassUid:@"1.2.840.10008.1.1"
                    requestedSopInstanceUid:@"1.1.1"];

                [pDimse sendCommandOrResponse:pCommand error:&pError];

                ImebraNDeleteResponse* pResponse = [pDimse getNDeleteResponse:pCommand error:&pError];

                EXPECT_EQ(ImebraDimseStatusSuccess, pResponse.status);
            }
        } // autoreleasepool
    }
    catch(...)
    {
        std::cout << imebra::ExceptionsManager::getExceptionTrace();
    }

    scp.join();

}


// Test interface with dicomdir
TEST(objectivec, createDicomDir)
{
    ImebraMutableDicomDir* newDicomDir = [[ImebraMutableDicomDir alloc] init];

    NSError* pError(0);
    ImebraMutableDicomDirEntry* rootRecord = [newDicomDir getNewEntry:@"PATIENT" error:&pError];

    ImebraMutableDataSet* rootRecordDataSet = [rootRecord getEntryDataSet];
    [rootRecordDataSet setString:[[ImebraTagId alloc] initWithGroup:0x10 tag:0x10] newValue:@"Surname" error:&pError];
    [newDicomDir setFirstRootEntry:rootRecord error:&pError];

    ImebraMutableDicomDirEntry* nextRecord = [newDicomDir getNewEntry:@"PATIENT" error:&pError];
    ImebraMutableDataSet* nextRecordDataSet = [nextRecord getEntryDataSet];
    [nextRecordDataSet setString:[[ImebraTagId alloc] initWithGroup:0x10 tag:0x10] newValue:@"Surname 1" error:&pError];
    [rootRecord setNextEntry:nextRecord error:&pError];

    ImebraMutableDicomDirEntry* imageRecord = [newDicomDir getNewEntry:@"IMAGE" error:&pError];
    ImebraMutableDataSet* imageRecordDataSet = [imageRecord getEntryDataSet];
    [imageRecordDataSet setString:[[ImebraTagId alloc] initWithGroup:0x8 tag:0x18] newValue:@"1.2.840.34.56.78999654.235" error:&pError];
    [nextRecord setFirstChildEntry:imageRecord error:&pError];

    NSMutableArray* parts = [[NSMutableArray alloc] init];
    [parts addObject: @"folder"];
    [parts addObject: @"file.dcm"];

    [imageRecord setFileParts:parts error:&pError];

    [nextRecord setFirstChildEntry:imageRecord error:&pError];

    ImebraDataSet* dicomDirDataSet = [newDicomDir updateDataSet:&pError];

    ImebraDicomDir* testDicomDir = [[ImebraDicomDir alloc] initWithDataSet:dicomDirDataSet error:&pError];
    ImebraDicomDirEntry* testRootRecord = [testDicomDir getFirstRootEntry:&pError];
    ImebraDataSet* testRootRecordDataSet = [testRootRecord getEntryDataSet];
    EXPECT_EQ("PATIENT", NSStringToString([testRootRecord getTypeString:&pError]));
    EXPECT_EQ("Surname", NSStringToString([testRootRecordDataSet getString:[[ImebraTagId alloc] initWithGroup:0x10 tag:0x10] elementNumber:0 error:&pError]));

    ImebraDicomDirEntry* testNextRecord = [testRootRecord getNextEntry];
    ImebraDataSet* testNextRecordDataSet = [testNextRecord getEntryDataSet];
    EXPECT_EQ("PATIENT", NSStringToString([testNextRecord getTypeString:&pError]));
    EXPECT_EQ("Surname 1", NSStringToString([testNextRecordDataSet getString:[[ImebraTagId alloc] initWithGroup:0x10 tag:0x10] elementNumber:0 error:&pError]));
    EXPECT_EQ(0, [testNextRecord getNextEntry]);

    ImebraDicomDirEntry* testImageRecord = [testNextRecord getFirstChildEntry];
    ImebraDataSet* testImageRecordDataSet = [testImageRecord getEntryDataSet];
    EXPECT_EQ("IMAGE", NSStringToString([testImageRecord getTypeString:&pError]));
    EXPECT_EQ("1.2.840.34.56.78999654.235", NSStringToString([testImageRecordDataSet getString:[[ImebraTagId alloc] initWithGroup:0x8 tag:0x18] elementNumber:0 error:&pError]));
    EXPECT_EQ("folder", NSStringToString([[testImageRecord getFileParts:&pError] objectAtIndex:0]));
    EXPECT_EQ("file.dcm", NSStringToString([[testImageRecord getFileParts:&pError] objectAtIndex:1]));
    EXPECT_EQ(0, [testImageRecord getFirstChildEntry]);

}


// Test the UID generators
TEST(objectivec, uidGenerators)
{
    ImebraBaseUIDGenerator* random = [[ImebraRandomUIDGenerator alloc] initWithRoot:@"1.2.3" departmentId:2 modelId:3];
    ImebraBaseUIDGenerator* serial = [[ImebraSerialNumberUIDGenerator alloc] initWithRoot:@"1.2.3" departmentId:4 modelId:3 serialNumber:4];

    NSError* pError(0);
    [ImebraUIDGeneratorFactory registerUIDGenerator:@"random" generator:random error:&pError];
    [ImebraUIDGeneratorFactory registerUIDGenerator:@"serial" generator:serial error:&pError];

    std::set<std::string> generatedUids;

    size_t numberOfUIDs(100000);

    for(size_t index(0); index != numberOfUIDs; ++index)
    {
        @autoreleasepool
        {
            std::string uid0 = imebra::NSStringToString([random getUID]);
            std::string uid1 = imebra::NSStringToString([serial getUID]);

            ASSERT_TRUE(uid0.find("1.2.3.2.3.") == 0);
            ASSERT_TRUE(uid1.find("1.2.3.4.3.4.") == 0);

            ASSERT_TRUE(generatedUids.find(uid0) == generatedUids.end());
            ASSERT_TRUE(generatedUids.find(uid1) == generatedUids.end());

            generatedUids.insert(uid0);
            generatedUids.insert(uid1);
        }
    }

    ASSERT_EQ(numberOfUIDs * 2, generatedUids.size());
}


TEST(objectivec, testExternalStream)
{
    // Save a file
    char* tempFileName = ::tempnam(0, "dcmimebra");
    std::string fileName(tempFileName);
    free(tempFileName);

    @autoreleasepool
    {
        FileStreamOutput writeFile(fileName);
        char buffer[1024];
        for(size_t resetBuffer(0); resetBuffer != sizeof(buffer); ++resetBuffer)
        {
            buffer[resetBuffer] = (char)(resetBuffer & 0xffu);
        }

        StreamWriter writer(writeFile);

        for(size_t writeKb(0); writeKb != 1024; ++writeKb)
        {
            writer.write(buffer, sizeof(buffer));
        }
    }

    std::string transferSyntax("1.2.840.10008.1.2.1");

    NSError* pError(0);
    ImebraMutableDataSet* testDataSet = [[ImebraMutableDataSet alloc] initWithTransferSyntax:imebra::stringToNSString(transferSyntax)];
    ImebraMutableTag* streamTag = [testDataSet getTagCreate:[[ImebraTagId alloc] initWithGroup:0x20 tag:0x20] tagVR:ImebraTagTypeOB error:&pError];
    [streamTag setStream:0 stream:[[ImebraFileStreamInput alloc] initWithName:imebra::stringToNSString(fileName) error:&pError] error:&pError];

    ImebraMutableMemory* pStreamMemory = [[ImebraMutableMemory alloc] init];
    @autoreleasepool
    {
        ImebraMemoryStreamOutput* pWriteStream = [[ImebraMemoryStreamOutput alloc] initWithMutableMemory:pStreamMemory];
        ImebraStreamWriter* pWriter = [[ImebraStreamWriter alloc] initWithOutputStream: pWriteStream];
        NSError* pError = 0;
        [ImebraCodecFactory saveToStream:pWriter dataSet:testDataSet codecType:ImebraCodecTypeDicom error:&pError];

    }

    ImebraMemoryStreamInput* pReadStream = [[ImebraMemoryStreamInput alloc] initWithReadMemory:pStreamMemory];

    ImebraStreamReader* pReader = [[ImebraStreamReader alloc] initWithInputStream:pReadStream];

    ImebraDataSet* pTestDataSet = [ImebraCodecFactory loadFromStream:pReader error:&pError];

    unsigned int bufferSize = [[pTestDataSet getTag:[[ImebraTagId alloc] initWithGroup:0x20 tag:0x20] error:&pError] getBufferSize:0 error:&pError];
    EXPECT_EQ(1024u * 1024u, bufferSize);

}


TEST(objectivec, voilutUnsigned8OptimalVOI)
{
    ImebraMutableImage* unsigned8 = [[ImebraMutableImage alloc] initWithWidth:6 height:1 depth:ImebraBitDepthU8 colorSpace:@"MONOCHROME2" highBit:7];

    NSError* pError(0);

    @autoreleasepool
    {
        ImebraWritingDataHandler* unsigned8Handler = [unsigned8 getWritingDataHandler:&pError];
        [unsigned8Handler setUint32:0 newValue:10 error:&pError];
        [unsigned8Handler setUint32:1 newValue:0 error:&pError];
        [unsigned8Handler setUint32:2 newValue:20 error:&pError];
        [unsigned8Handler setUint32:3 newValue:30 error:&pError];
        [unsigned8Handler setUint32:4 newValue:40 error:&pError];
        [unsigned8Handler setUint32:5 newValue:50 error:&pError];
    }

    ImebraVOIDescription* voiDescription = [ImebraVOILUT getOptimalVOI:unsigned8 inputTopLeftX:0 inputTopLeftY:0 inputWidth:6 inputHeight:1 error:&pError];
    ImebraVOILUT* voilut = [[ImebraVOILUT alloc] initWithVOIDescription:voiDescription];

    ImebraMutableImage* unsigned8Out = [voilut allocateOutputImage:unsigned8 width:6 height:1 error:&pError];
    [voilut runTransform:unsigned8 inputTopLeftX:0 inputTopLeftY:0 inputWidth:6 inputHeight:1 outputImage:unsigned8Out outputTopLeftX:0 outputTopLeftY:0 error:&pError];

    ImebraReadingDataHandler* unsigned8Handler = [unsigned8Out getReadingDataHandler:&pError];

    ASSERT_EQ(51u, [unsigned8Handler getUint32:0 error:&pError]);
    ASSERT_EQ(0u, [unsigned8Handler getUint32:1 error:&pError]);
    ASSERT_EQ(102u, [unsigned8Handler getUint32:2 error:&pError]);
    ASSERT_EQ(153u, [unsigned8Handler getUint32:3 error:&pError]);
    ASSERT_EQ(204u, [unsigned8Handler getUint32:4 error:&pError]);
    ASSERT_EQ(255u, [unsigned8Handler getUint32:5 error:&pError]);
}


TEST(objectivec, testOverlay)
{
    ImebraMutableImage* overlayBitmap = [[ImebraMutableImage alloc] initWithWidth:6 height:1 depth:ImebraBitDepthU8 colorSpace:@"MONOCHROME2" highBit:1];

    NSError* pError(0);

    @autoreleasepool
    {
        ImebraWritingDataHandler* unsigned8Handler = [overlayBitmap getWritingDataHandler:&pError];
        [unsigned8Handler setUint32:0 newValue:1 error:&pError];
        [unsigned8Handler setUint32:1 newValue:0 error:&pError];
        [unsigned8Handler setUint32:2 newValue:1 error:&pError];
        [unsigned8Handler setUint32:3 newValue:0 error:&pError];
        [unsigned8Handler setUint32:4 newValue:1 error:&pError];
        [unsigned8Handler setUint32:5 newValue:0 error:&pError];
    }

    ImebraMutableOverlay* overlay = [[ImebraMutableOverlay alloc] initWithType:ImebraOverlayTypeGraphic subType:@"" firstFrame:0 zeroBasedOriginX:0 zeroBasedOriginY:0 label:@"LABEL" description:@"Description"];
    [overlay setImage:0 image:overlayBitmap error:&pError];

    ImebraMutableDataSet* testDataSet = [[ImebraMutableDataSet alloc] initWithTransferSyntax:@"1.2.840.10008.1.2.1"];

    [testDataSet setOverlay:0 overlay: overlay error:&pError];

    ImebraOverlay* checkOverlay = [testDataSet getOverlay:0 error:&pError];

    ASSERT_EQ([checkOverlay getImage:0 error:&pError].width, 6);

}



// Test DrawBitmap generating a NSImage
#if defined(__APPLE__)

TEST(objectivec, images)
{
    NSError* pError(0);

    unsigned int width = 600;
    unsigned int height = 400;

    ImebraMutableImage* pBaselineImage = [[ImebraMutableImage alloc] initWithWidth:width height:height depth:ImebraBitDepthU8 colorSpace:@"RGB" highBit:7];

    @autoreleasepool
    {
        ImebraWritingDataHandler* pWritingDataHandler = [pBaselineImage getWritingDataHandler:&pError];

        unsigned int index(0);
        for(unsigned int y(0); y != height; ++y)
        {
            for(unsigned int x(0); x != width; ++x)
            {
                unsigned int r = x < 100 ? 10: 100;
                unsigned int g = x < 200 ? 40: 200;
                unsigned int b = x < 300 ? 100: 4;
                [pWritingDataHandler setUint32:index++ newValue:r error:&pError];
                [pWritingDataHandler setUint32:index++ newValue:g error:&pError];
                [pWritingDataHandler setUint32:index++ newValue:b error:&pError];

            }
        }
    }


    ImebraTransform* pColorTransform = [ImebraColorTransformsFactory getTransform:@"RGB" finalColorSpace:@"YBR_FULL" error:&pError];

    ImebraMutableImage* pYbrImage = [pColorTransform allocateOutputImage:pBaselineImage width:width height:height error:&pError];

    [pColorTransform runTransform:pBaselineImage inputTopLeftX:0 inputTopLeftY:0 inputWidth:width inputHeight:height outputImage:pYbrImage outputTopLeftX:0 outputTopLeftY:0 error:&pError];

    ImebraDrawBitmap* pDrawBitmap = [[ImebraDrawBitmap alloc] init];

    NSImage* pNsImage = [pDrawBitmap getImebraImage:pYbrImage error:&pError];

    NSData* pImageData = [pNsImage TIFFRepresentation];
    NSBitmapImageRep* pImageRep = [NSBitmapImageRep imageRepWithData:pImageData];
    NSDictionary *pImageProps = [NSDictionary dictionaryWithObject:[NSNumber numberWithFloat:1.0] forKey:NSImageCompressionFactor];
    pImageData = [pImageRep representationUsingType:NSBitmapImageFileTypeJPEG properties:pImageProps];

    ImebraMutableMemory* pDataMemory = [[ImebraMutableMemory alloc] initWithData:pImageData];
    ImebraMemoryStreamInput* pDataStream = [[ImebraMemoryStreamInput alloc] initWithReadMemory:pDataMemory];
    ImebraStreamReader* pDataReader = [[ImebraStreamReader alloc] initWithInputStream:pDataStream];

    ImebraDataSet* pLoadedDataSet = [ImebraCodecFactory loadFromStream:pDataReader error:&pError];
    ImebraImage* pLoadedImage = [pLoadedDataSet getImage:0 error:&pError];

    // Compare the buffers. A little difference is allowed
    double differenceYBR = compareImages(*(imebra::Image*)(pYbrImage->m_Image), *(imebra::Image*)(pLoadedImage->m_Image));
    ASSERT_LE(differenceYBR, 1);
}

#endif

} // namespace tests

} // namespace imebra
