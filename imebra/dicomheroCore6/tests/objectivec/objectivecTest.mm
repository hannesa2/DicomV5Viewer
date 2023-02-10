#include <gtest/gtest.h>
#include <dicomhero6_objc/dicomhero.h>
#include "../buildImageForTest.h"
#include "../../objectivec/src/dicomhero_strings.h"
#include <thread>



namespace dicomhero
{

namespace tests
{


// Test NSString conversion functions
TEST(objectivec, stringToNSStringTest)
{
    NSString* patient0 = [[NSString alloc] initWithUTF8String:"??\xD0\xA1\xD0\xBC\xD1\x8B\xD1\x81\xD0\xBB\x20\xD0\xB2\xD1\x81\xD0\xB5\xD0\xB9"];
    NSString* patient1 = [[NSString alloc] initWithUTF8String:"\xD0\xA1\xD0\xBC\xD1\x8B\xD1\x81\xD0\xBB\x20\xD0\xB2\xD1\x81\xD0\xB5\xD0\xB9"];

    DicomheroMutableMemory* pStreamMemory = [[DicomheroMutableMemory alloc] init];
    DicomheroTagId* pPatientTag = [[DicomheroTagId alloc] initWithId:DicomheroTagEnumPatientName_0010_0010];

    {

        NSMutableArray* pCharsets = [[NSMutableArray alloc] init];
        [pCharsets addObject: @"ISO_IR 6"];
        [pCharsets addObject: @"ISO 2022 IR 127"];
        [pCharsets addObject: @"ISO 2022 IR 144"];
        [pCharsets addObject: @"ISO 2022 IR 100"];
        [pCharsets addObject: @"ISO 2022 IR 126"];

        DicomheroDataSet* pDataSet = [[DicomheroDataSet alloc] initWithTransferSyntax:@"1.2.840.10008.1.2.1" charsets:pCharsets];

        @autoreleasepool
        {
            NSError* pError = 0;
            DicomheroWritingDataHandler* pHandler = [pDataSet getWritingDataHandler:pPatientTag bufferId:0 error:&pError];

            [pHandler setString:0 newValue:patient0 error:&pError];
            [pHandler setString:1 newValue:patient1 error:&pError];
        }

        @autoreleasepool
        {
            DicomheroMemoryStreamOutput* pWriteStream = [[DicomheroMemoryStreamOutput alloc] initWithMutableMemory:pStreamMemory];
            DicomheroStreamWriter* pWriter = [[DicomheroStreamWriter alloc] initWithOutputStream: pWriteStream];
            NSError* pError = 0;
            [DicomheroCodecFactory saveToStream:pWriter dataSet:pDataSet codecType:DicomheroCodecTypeDicom error:&pError];

        }

        NSArray* pTags = [pDataSet getTags];
        size_t numTags = [pTags count];
        bool bPatientFound(false);
        for(size_t scanTags(0); scanTags != numTags; ++scanTags)
        {
            DicomheroTagId* pTag = [pTags objectAtIndex:scanTags];
            if(pTag.groupId == 0x10 && pTag.tagId == 0x10 && pTag.groupOrder == 0)
            {
                bPatientFound = true;
            }
        }
        EXPECT_TRUE(bPatientFound);

    }

    {
        DicomheroMemoryStreamInput* pReadStream = [[DicomheroMemoryStreamInput alloc] initWithReadMemory:pStreamMemory];

        DicomheroStreamReader* pReader = [[DicomheroStreamReader alloc] initWithInputStream:pReadStream];

        NSError* pError = 0;
        DicomheroDataSet* pTestDataSet = [DicomheroCodecFactory loadFromStream:pReader error:&pError];

        NSString* nsPatientName0 = [pTestDataSet getString:pPatientTag elementNumber:0 error:&pError];
        NSString* nsPatientName1 = [pTestDataSet getString:pPatientTag elementNumber:1 error:&pError];

        EXPECT_TRUE([nsPatientName0 isEqualToString:patient0]);
        EXPECT_TRUE([nsPatientName1 isEqualToString:patient1]);
    }

}


TEST(objectivec, PatientName)
{
    NSString* patient0 = [[NSString alloc] initWithUTF8String:"name^surname"];
    NSString* patient1 = [[NSString alloc] initWithUTF8String:"name1^surname1"];
    NSString* patient2 = [[NSString alloc] initWithUTF8String:"name2^surname2"];
    DicomheroPatientName* pPatientName = [[DicomheroPatientName alloc] initWithAlphabeticRepresentation:patient0 ideographicRepresentation:patient1 phoneticRepresentation:patient2];

    DicomheroDataSet* pDataset = [[DicomheroDataSet alloc] initWithTransferSyntax:@"1.2.840.10008.1.2.1"];
    NSError* pError = 0;
    DicomheroTagId* pTagId = [[DicomheroTagId alloc] initWithGroup:0x10 tag:0x10];
    [pDataset setPatientName:pTagId newValue:pPatientName error:&pError];

    DicomheroPatientName* pCheckPatientName = [pDataset getPatientName:pTagId elementNumber:0 error:&pError];

    NSString* checkPatient0 = [pCheckPatientName valueForKey:@"alphabeticRepresentation"];
    NSString* checkPatient1 = [pCheckPatientName valueForKey:@"ideographicRepresentation"];
    NSString* checkPatient2 = [pCheckPatientName valueForKey:@"phoneticRepresentation"];

    EXPECT_TRUE([checkPatient0 isEqualToString:patient0]);
    EXPECT_TRUE([checkPatient1 isEqualToString:patient1]);
    EXPECT_TRUE([checkPatient2 isEqualToString:patient2]);
}

// Test NSString conversion functions
TEST(objectivec, NSStringToStringTest)
{
    MutableMemory streamMemory;
    {
        charsetsList_t charsets;
        charsets.push_back("ISO_IR 6");
        DataSet testDataSet("1.2.840.10008.1.2.1", charsets);

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
    DataSet testDataSet("1.2.840.10008.1.2");
    testDataSet.setString(TagId(tagId_t::PatientName_0010_0010), "Test^Patient");
    testDataSet.setString(TagId(tagId_t::PatientID_0010_0020), "TestID");
    CodecFactory::save(testDataSet, "testCodecFactory.dcm", codecType_t::dicom);

    NSError* error = nil;
    DicomheroDataSet* pDataSet = [DicomheroCodecFactory loadFromFile:@"testCodecFactory.dcm" error:&error];
    NSString* checkPatientName = [pDataSet getString:[[DicomheroTagId alloc] initWithGroup:0x10 tag:0x10] elementNumber:0 error:&error];
    NSString* checkPatientID = [pDataSet getString:[[DicomheroTagId alloc] initWithGroup:0x10 tag:0x20] elementNumber:0 error:&error];

    EXPECT_EQ(dicomhero::NSStringToString(checkPatientName), "Test^Patient");
    EXPECT_EQ(dicomhero::NSStringToString(checkPatientID), "TestID");
}


// Test NSError on non-existent file
TEST(objectivec, CodecFactoryFailLoad)
{
    NSError* error = nil;
    DicomheroDataSet* pDataSet = [DicomheroCodecFactory loadFromFile:@"fail.dcm" error:&error];
    EXPECT_EQ(pDataSet, nullptr);
    EXPECT_EQ(dicomhero::NSStringToString([error domain]), "imebra");
}


// Initialize and check an image content
TEST(objectivec, image)
{
    DicomheroImage* pImage = [[DicomheroImage alloc] initWithWidth:5 height:5 depth:DicomheroBitDepthU16 colorSpace:@"MONOCHROME2" highBit:15];

    NSError* error = nil;

    @autoreleasepool
    {
        DicomheroWritingDataHandler* writingDataHandler = [pImage getWritingDataHandler:&error];
        for(unsigned int pixel(0); pixel != 25; ++pixel)
        {
            [writingDataHandler setUint32:pixel newValue:pixel error:&error];
        }
    }

    DicomheroDataSet* pDataSet = [[DicomheroDataSet alloc] initWithTransferSyntax:@"1.2.840.10008.1.2"];
    [pDataSet setImage:0 image:pImage quality:DicomheroImageQualityVeryHigh error:&error];

    DicomheroImage* pCheckImage = [pDataSet getImage:0 error:&error];
    DicomheroReadingDataHandlerNumeric* readingDataHandler = [pCheckImage getReadingDataHandler:&error];
    for(unsigned int pixel(0); pixel != 25; ++pixel)
    {
        EXPECT_EQ([readingDataHandler getUint32:pixel error:&error], pixel);
    }
}


// Initialize and check an image content
TEST(objectivec, imageNSData)
{
    DicomheroImage* pImage = [[DicomheroImage alloc] initWithWidth:5 height:5 depth:DicomheroBitDepthU16 colorSpace:@"MONOCHROME2" highBit:15];

    NSError* error = nil;

    @autoreleasepool
    {
        std::uint16_t buffer[25];
        for(std::uint16_t pixel(0); pixel != 25; ++pixel)
        {
            buffer[pixel] = (std::uint16_t)(pixel + 1u);
        }
        NSData* pSource = [[NSData alloc] initWithBytes:buffer length:sizeof(buffer)];
        DicomheroWritingDataHandlerNumeric* writingDataHandler = [pImage getWritingDataHandler:&error];
        [writingDataHandler assign:pSource error:&error];
    }

    DicomheroDataSet* pDataSet = [[DicomheroDataSet alloc] initWithTransferSyntax:@"1.2.840.10008.1.2"];
    [pDataSet setImage:0 image:pImage quality:DicomheroImageQualityVeryHigh error:&error];

    DicomheroImage* pCheckImage = [pDataSet getImage:0 error:&error];
    DicomheroReadingDataHandlerNumeric* readingDataHandler = [pCheckImage getReadingDataHandler:&error];
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

    DicomheroDataSet* pDataSet = [[DicomheroDataSet alloc] initWithTransferSyntax:@"1.2.840.10008.1.2"];

    [pDataSet setString:[[DicomheroTagId alloc] initWithGroup:0x10 tag:0x10] newValue:@"TestPatient" error:&error];
    [pDataSet setAge:[[DicomheroTagId alloc] initWithGroup:0x10 tag:0x1010] newValue:[[DicomheroAge alloc] initWithAge:10 units:DicomheroAgeUnitYears] error:&error];

    [pDataSet setInt32:[[DicomheroTagId alloc] initWithGroup:0x10 tag:0x1011] newValue:10 tagVR:DicomheroTagTypeSL error:&error];
    [pDataSet setUint32:[[DicomheroTagId alloc] initWithGroup:0x10 tag:0x1012] newValue:11 tagVR:DicomheroTagTypeUL error:&error];
    [pDataSet setDouble:[[DicomheroTagId alloc] initWithGroup:0x10 tag:0x1013] newValue:12.0f tagVR:DicomheroTagTypeUL error:&error];

    DicomheroTag* pTag = [pDataSet getTagCreate:[[DicomheroTagId alloc] initWithGroup:0x12 tag:0x12] tagVR:DicomheroTagTypeFD error:&error];

    @autoreleasepool
    {
        DicomheroWritingDataHandlerNumeric* pWriteDouble = [pTag getWritingDataHandlerNumeric:0 error:&error];
        [pWriteDouble setSize:4];
        EXPECT_EQ(4u, pWriteDouble.size);
        [pWriteDouble setDouble:0 newValue:0 error:&error];
        [pWriteDouble setDouble:1 newValue:1 error:&error];
        [pWriteDouble setDouble:2 newValue:2 error:&error];
        [pWriteDouble setDouble:3 newValue:3 error:&error];
    }

    NSString* checkPatient0 = [pDataSet getString:[[DicomheroTagId alloc] initWithGroup:0x10 tag:0x10] elementNumber:0 error:&error];
    DicomheroAge* checkAge = [pDataSet getAge:[[DicomheroTagId alloc] initWithGroup:0x10 tag:0x1010] elementNumber:0 error:&error];

    EXPECT_EQ(error, nil);
    NSString* checkPatient1 = [pDataSet getString:[[DicomheroTagId alloc] initWithGroup:0x10 tag:0x11] elementNumber:0 error:&error];
    EXPECT_EQ(dicomhero::NSStringToString([error domain]), "imebra");
    NSString* checkPatient2 = [pDataSet getString:[[DicomheroTagId alloc] initWithGroup:0x10 tag:0x11] elementNumber:0 defaultValue:@"defaultValue" error:&error];

    EXPECT_EQ(dicomhero::NSStringToString(checkPatient0), "TestPatient");
    EXPECT_EQ(checkPatient1, nil);
    EXPECT_EQ(dicomhero::NSStringToString(checkPatient2), "defaultValue");

    EXPECT_EQ(10u, [checkAge age]);
    EXPECT_EQ(DicomheroAgeUnitYears, [checkAge units]);

    EXPECT_EQ(10, [pDataSet getInt32:[[DicomheroTagId alloc] initWithGroup:0x10 tag:0x1011] elementNumber:0 error:&error]);
    EXPECT_EQ(11u, [pDataSet getUint32:[[DicomheroTagId alloc] initWithGroup:0x10 tag:0x1012] elementNumber:0 error:&error]);
    EXPECT_DOUBLE_EQ(12.0, [pDataSet getDouble:[[DicomheroTagId alloc] initWithGroup:0x10 tag:0x1013] elementNumber:0 error:&error]);
    EXPECT_EQ(12, [pDataSet getInt32:[[DicomheroTagId alloc] initWithGroup:0x10 tag:0x1020] elementNumber:0 defaultValue:12u error:&error]);
    EXPECT_EQ(13u, [pDataSet getUint32:[[DicomheroTagId alloc] initWithGroup:0x10 tag:0x1021] elementNumber:0 defaultValue:13u error:&error]);
    EXPECT_DOUBLE_EQ(14.0, [pDataSet getDouble:[[DicomheroTagId alloc] initWithGroup:0x10 tag:0x1022] elementNumber:0 defaultValue:14.0 error:&error]);

    EXPECT_DOUBLE_EQ(0.0, [pDataSet getDouble:[[DicomheroTagId alloc] initWithGroup:0x12 tag:0x12] elementNumber:0 error:&error]);
    EXPECT_DOUBLE_EQ(1.0, [pDataSet getDouble:[[DicomheroTagId alloc] initWithGroup:0x12 tag:0x12] elementNumber:1 error:&error]);
    EXPECT_DOUBLE_EQ(2.0, [pDataSet getDouble:[[DicomheroTagId alloc] initWithGroup:0x12 tag:0x12] elementNumber:2 error:&error]);
    EXPECT_DOUBLE_EQ(3.0, [pDataSet getDouble:[[DicomheroTagId alloc] initWithGroup:0x12 tag:0x12] elementNumber:3 error:&error]);
}


void listenerThread()
{
    try
    {
        NSError* pError(0);
        DicomheroTCPPassiveAddress* pAddress = [[DicomheroTCPPassiveAddress alloc] initWithNode:@"localhost" service:@"20000" error:&pError];
        DicomheroTCPListener* pListener = [[DicomheroTCPListener alloc] initWithAddress:pAddress error:&pError];

        @autoreleasepool
        {
            DicomheroTCPStream* pStream = [pListener waitForConnection:&pError];

            DicomheroBaseStreamInput* pInput = [pStream getStreamInput];
            DicomheroBaseStreamOutput* pOutput = [pStream getStreamOutput];
            DicomheroStreamReader* pReader = [[DicomheroStreamReader alloc] initWithInputStream:pInput];
            DicomheroStreamWriter* pWriter = [[DicomheroStreamWriter alloc] initWithOutputStream:pOutput];

            DicomheroPresentationContexts* pContexts = [[DicomheroPresentationContexts alloc] init];

            DicomheroPresentationContext* pContext = [[DicomheroPresentationContext alloc] initWithAbstractSyntax:@"1.2.840.10008.1.1"];
            [pContext addTransferSyntax:@"1.2.840.10008.1.2"];

            [pContexts addPresentationContext:pContext];

            DicomheroAssociationSCP* pSCP = [[DicomheroAssociationSCP alloc]
                    initWithThisAET:@"SCP" maxInvokedOperations:1 maxPerformedOperations:1 presentationContexts:pContexts
                         reader:pReader writer:pWriter dimseTimeoutSeconds:30 artimTimeoutSeconds:30 error:&pError];

            DicomheroDimseService* pDimse = [[DicomheroDimseService alloc]initWithAssociation:pSCP];

            for(;;)
            {
                DicomheroDimseCommand* pCommand = (DicomheroDimseCommand*)[pDimse getCommand:&pError];

                if(pError != 0)
                {
                    break;
                }

                DicomheroDimseResponse* pResponse = nil;
                switch([pCommand commandType])
                {
                case DicomheroDimseCommandTypeCStore:
                    pResponse = [[DicomheroCStoreResponse alloc]initWithcommand:(DicomheroCStoreCommand*)pCommand responseCode:DicomheroDimseStatusCodeSuccess];
                    break;
                case DicomheroDimseCommandTypeCGet:
                    pResponse = [[DicomheroCGetResponse alloc]initWithcommand:(DicomheroCGetCommand*)pCommand responseCode:DicomheroDimseStatusCodeSuccess
                                                                           remainingSubOperations:0
                                                                           completedSubOperations:1
                                                                           failedSubOperations:0
                                                                           warningSubOperations:0];
                    break;
                case DicomheroDimseCommandTypeCFind:
                    pResponse = [[DicomheroCFindResponse alloc]initWithcommand:(DicomheroCFindCommand*)pCommand responseCode:DicomheroDimseStatusCodeSuccess];
                    break;
                case DicomheroDimseCommandTypeCMove:
                    pResponse = [[DicomheroCMoveResponse alloc]initWithcommand:(DicomheroCMoveCommand*)pCommand responseCode:DicomheroDimseStatusCodeSuccess
                                                                           remainingSubOperations:0
                                                                           completedSubOperations:1
                                                                           failedSubOperations:0
                                                                           warningSubOperations:0];
                    EXPECT_EQ("DEST", dicomhero::NSStringToString([(DicomheroCMoveCommand*)pCommand getDestinationAET:&pError]));
                    break;
                case DicomheroDimseCommandTypeCEcho:
                    pResponse = [[DicomheroCEchoResponse alloc]initWithcommand:(DicomheroCEchoCommand*)pCommand responseCode:DicomheroDimseStatusCodeSuccess];
                    break;
                case DicomheroDimseCommandTypeCCancel:
                    break;
                case DicomheroDimseCommandTypeNEventReport:
                    pResponse = [[DicomheroNEventReportResponse alloc]initWithcommand:(DicomheroNEventReportCommand*)pCommand responseCode:DicomheroDimseStatusCodeSuccess];
                    break;
                case DicomheroDimseCommandTypeNGet:
                    pResponse = [[DicomheroNGetResponse alloc]initWithcommand:(DicomheroNGetCommand*)pCommand responseCode:DicomheroDimseStatusCodeSuccess];
                    break;
                case DicomheroDimseCommandTypeNSet:
                    pResponse = [[DicomheroNSetResponse alloc]initWithcommand:(DicomheroNSetCommand*)pCommand responseCode:DicomheroDimseStatusCodeSuccess];
                    break;
                case DicomheroDimseCommandTypeNAction:
                    pResponse = [[DicomheroNActionResponse alloc]initWithcommand:(DicomheroNActionCommand*)pCommand responseCode:DicomheroDimseStatusCodeSuccess];
                    break;
                case DicomheroDimseCommandTypeNCreate:
                    pResponse = [[DicomheroNCreateResponse alloc]initWithcommand:(DicomheroNCreateCommand*)pCommand responseCode:DicomheroDimseStatusCodeSuccess];
                    break;
                case DicomheroDimseCommandTypeNDelete:
                    pResponse = [[DicomheroNDeleteResponse alloc]initWithcommand:(DicomheroNDeleteCommand*)pCommand responseCode:DicomheroDimseStatusCodeSuccess];
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
        std::cout << dicomhero::ExceptionsManager::getExceptionTrace();

    }

}


// Send a CStore command to a SCP via TCP
TEST(objectivec, dimse)
{
    std::thread scp(dicomhero::tests::listenerThread);

    try
    {

        std::this_thread::sleep_for(std::chrono::seconds(5));

        NSError* pError(0);
        DicomheroTCPActiveAddress* pAddress = [[DicomheroTCPActiveAddress alloc] initWithNode:@"localhost" service:@"20000" error:&pError];

        @autoreleasepool
        {
            DicomheroTCPStream* pStream = [[DicomheroTCPStream alloc] initWithAddress:pAddress error:&pError];

            DicomheroBaseStreamInput* pInput = [pStream getStreamInput];
            DicomheroBaseStreamOutput* pOutput = [pStream getStreamOutput];
            DicomheroStreamReader* pReader = [[DicomheroStreamReader alloc] initWithInputStream:pInput];
            DicomheroStreamWriter* pWriter = [[DicomheroStreamWriter alloc] initWithOutputStream:pOutput];

            DicomheroPresentationContexts* pContexts = [[DicomheroPresentationContexts alloc] init];

            DicomheroPresentationContext* pContext = [[DicomheroPresentationContext alloc] initWithAbstractSyntax:@"1.2.840.10008.1.1"];
            [pContext addTransferSyntax:@"1.2.840.10008.1.2"];

            [pContexts addPresentationContext:pContext];

            DicomheroAssociationSCU* pSCU = [[DicomheroAssociationSCU alloc]
                    initWithThisAET:@"SCU" otherAET:@"SCP" maxInvokedOperations:1 maxPerformedOperations:1 presentationContexts:pContexts
                         reader:pReader writer:pWriter dimseTimeoutSeconds:30 error:&pError];

            DicomheroDimseService* pDimse = [[DicomheroDimseService alloc]initWithAssociation:pSCU];

            // Send C-STORE
            {
                DicomheroDataSet* pDataSet = [[DicomheroDataSet alloc] initWithTransferSyntax:@"1.2.840.10008.1.2"];

                [pDataSet setString:[[DicomheroTagId alloc] initWithGroup:0x10 tag:0x10] newValue:@"TestPatient" error:&pError];
                [pDataSet setAge:[[DicomheroTagId alloc] initWithGroup:0x10 tag:0x1010] newValue:[[DicomheroAge alloc] initWithAge:10 units:DicomheroAgeUnitYears] error:&pError];

                DicomheroCStoreCommand* pCommand = [[DicomheroCStoreCommand alloc]initWithAbstractSyntax:
                    @"1.2.840.10008.1.1"
                    messageID:[pDimse getNextCommandID]
                    priority:DicomheroDimseCommandPriorityMedium
                    affectedSopClassUid:@"1.2.840.10008.1.1"
                    affectedSopInstanceUid:@"1.2.3.4.5"
                    originatorAET:@"SCU"
                    originatorMessageID:0
                    payload:pDataSet];

                [pDimse sendCommandOrResponse:pCommand error:&pError];
                DicomheroCStoreResponse* pResponse = [pDimse getCStoreResponse:pCommand error:&pError];

                EXPECT_EQ(DicomheroDimseStatusSuccess, pResponse.status);
            }

            // Send C-GET
            {
                DicomheroDataSet* pDataSet = [[DicomheroDataSet alloc] initWithTransferSyntax:@"1.2.840.10008.1.2"];

                [pDataSet setString:[[DicomheroTagId alloc] initWithGroup:0x10 tag:0x10] newValue:@"TestPatient" error:&pError];

                DicomheroCGetCommand* pCommand = [[DicomheroCGetCommand alloc]initWithAbstractSyntax:
                    @"1.2.840.10008.1.1"
                    messageID:[pDimse getNextCommandID]
                    priority:DicomheroDimseCommandPriorityMedium
                    affectedSopClassUid:@"1.2.840.10008.1.1"
                    identifier:pDataSet];

                [pDimse sendCommandOrResponse:pCommand error:&pError];
                DicomheroCGetResponse* pResponse = [pDimse getCGetResponse:pCommand error:&pError];

                EXPECT_EQ(DicomheroDimseStatusSuccess, pResponse.status);
            }

            // Send C-FIND
            {
                DicomheroDataSet* pDataSet = [[DicomheroDataSet alloc] initWithTransferSyntax:@"1.2.840.10008.1.2"];

                [pDataSet setString:[[DicomheroTagId alloc] initWithGroup:0x10 tag:0x10] newValue:@"TestPatient" error:&pError];

                DicomheroCFindCommand* pCommand = [[DicomheroCFindCommand alloc]initWithAbstractSyntax:
                    @"1.2.840.10008.1.1"
                    messageID:[pDimse getNextCommandID]
                    priority:DicomheroDimseCommandPriorityMedium
                    affectedSopClassUid:@"1.2.840.10008.1.1"
                    identifier:pDataSet];

                [pDimse sendCommandOrResponse:pCommand error:&pError];
                DicomheroCFindResponse* pResponse = [pDimse getCFindResponse:pCommand error:&pError];

                EXPECT_EQ(DicomheroDimseStatusSuccess, pResponse.status);
            }

            // Send C-MOVE
            {
                DicomheroDataSet* pDataSet = [[DicomheroDataSet alloc] initWithTransferSyntax:@"1.2.840.10008.1.2"];

                [pDataSet setString:[[DicomheroTagId alloc] initWithGroup:0x10 tag:0x10] newValue:@"TestPatient" error:&pError];

                DicomheroCMoveCommand* pCommand = [[DicomheroCMoveCommand alloc]initWithAbstractSyntax:
                    @"1.2.840.10008.1.1"
                    messageID:[pDimse getNextCommandID]
                    priority:DicomheroDimseCommandPriorityMedium
                    affectedSopClassUid:@"1.2.840.10008.1.1"
                    destinationAET:@"DEST"
                    identifier:pDataSet];

                [pDimse sendCommandOrResponse:pCommand error:&pError];
                DicomheroCMoveResponse* pResponse = [pDimse getCMoveResponse:pCommand error:&pError];

                EXPECT_EQ(DicomheroDimseStatusSuccess, pResponse.status);
            }

            // Send C-ECHO
            {
                DicomheroCEchoCommand* pCommand = [[DicomheroCEchoCommand alloc]initWithAbstractSyntax:
                    @"1.2.840.10008.1.1"
                    messageID:[pDimse getNextCommandID]
                    priority:DicomheroDimseCommandPriorityMedium
                    affectedSopClassUid:@"1.2.840.10008.1.1"];

                [pDimse sendCommandOrResponse:pCommand error:&pError];
                DicomheroCEchoResponse* pResponse = [pDimse getCEchoResponse:pCommand error:&pError];

                EXPECT_EQ(DicomheroDimseStatusSuccess, pResponse.status);
            }

            // Send C-CANCEL
            {
                DicomheroCCancelCommand* pCommand = [[DicomheroCCancelCommand alloc]initWithAbstractSyntax:
                    @"1.2.840.10008.1.1"
                    messageID:[pDimse getNextCommandID]
                    priority:DicomheroDimseCommandPriorityMedium
                    cancelMessageID:1];

                [pDimse sendCommandOrResponse:pCommand error:&pError];
            }

            // Send N-EVENTREPORT
            {
                DicomheroNEventReportCommand* pCommand = [[DicomheroNEventReportCommand alloc]initWithAbstractSyntax:
                    @"1.2.840.10008.1.1"
                    messageID:[pDimse getNextCommandID]
                    affectedSopClassUid:@"1.2.840.10008.1.1"
                    affectedSopInstanceUid:@"1.1.1"
                    eventID:1];

                [pDimse sendCommandOrResponse:pCommand error:&pError];

                DicomheroNEventReportResponse* pResponse = [pDimse getNEventReportResponse:pCommand error:&pError];

                EXPECT_EQ(DicomheroDimseStatusSuccess, pResponse.status);
            }

            // Send N-GET
            {
                NSMutableArray* identifierList = [[NSMutableArray alloc] init];
                [identifierList addObject: [[DicomheroTagId alloc] initWithGroup:0x10 tag:0x10]];
                [identifierList addObject: [[DicomheroTagId alloc] initWithGroup:0x20 tag:0x10]];

                DicomheroNGetCommand* pCommand = [[DicomheroNGetCommand alloc]initWithAbstractSyntax:
                    @"1.2.840.10008.1.1"
                    messageID:[pDimse getNextCommandID]
                    requestedSopClassUid:@"1.2.840.10008.1.1"
                    requestedSopInstanceUid:@"1.1.1"
                    attributeIdentifierList:identifierList];

                [pDimse sendCommandOrResponse:pCommand error:&pError];

                DicomheroNGetResponse* pResponse = [pDimse getNGetResponse:pCommand error:&pError];

                EXPECT_EQ(DicomheroDimseStatusSuccess, pResponse.status);
            }

            // Send N-SET
            {
                DicomheroDataSet* pDataSet = [[DicomheroDataSet alloc] initWithTransferSyntax:@"1.2.840.10008.1.2"];

                [pDataSet setString:[[DicomheroTagId alloc] initWithGroup:0x10 tag:0x10] newValue:@"TestPatient" error:&pError];

                DicomheroNSetCommand* pCommand = [[DicomheroNSetCommand alloc]initWithAbstractSyntax:
                    @"1.2.840.10008.1.1"
                    messageID:[pDimse getNextCommandID]
                    requestedSopClassUid:@"1.2.840.10008.1.1"
                    requestedSopInstanceUid:@"1.1.1"
                    modificationList:pDataSet];

                [pDimse sendCommandOrResponse:pCommand error:&pError];

                DicomheroNSetResponse* pResponse = [pDimse getNSetResponse:pCommand error:&pError];

                EXPECT_EQ(DicomheroDimseStatusSuccess, pResponse.status);
            }

            // Send N-ACTION
            {
                DicomheroDataSet* pDataSet = [[DicomheroDataSet alloc] initWithTransferSyntax:@"1.2.840.10008.1.2"];

                [pDataSet setString:[[DicomheroTagId alloc] initWithGroup:0x10 tag:0x10] newValue:@"TestPatient" error:&pError];

                DicomheroNActionCommand* pCommand = [[DicomheroNActionCommand alloc]initWithAbstractSyntax:
                    @"1.2.840.10008.1.1"
                    messageID:[pDimse getNextCommandID]
                    requestedSopClassUid:@"1.2.840.10008.1.1"
                    requestedSopInstanceUid:@"1.1.1"
                    actionID:10
                    actionInformation:pDataSet];

                [pDimse sendCommandOrResponse:pCommand error:&pError];

                DicomheroNActionResponse* pResponse = [pDimse getNActionResponse:pCommand error:&pError];

                EXPECT_EQ(DicomheroDimseStatusSuccess, pResponse.status);
                EXPECT_EQ(10, pResponse.actionID);
            }

            // Send N-CREATE
            {

                DicomheroDataSet* pDataSet = [[DicomheroDataSet alloc] initWithTransferSyntax:@"1.2.840.10008.1.2"];

                [pDataSet setString:[[DicomheroTagId alloc] initWithGroup:0x10 tag:0x10] newValue:@"TestPatient" error:&pError];

                DicomheroNCreateCommand* pCommand = [[DicomheroNCreateCommand alloc]initWithAbstractSyntax:
                    @"1.2.840.10008.1.1"
                    messageID:[pDimse getNextCommandID]
                    affectedSopClassUid:@"1.2.840.10008.1.1"
                    affectedSopInstanceUid:@"1.1.1"
                    attributeList:pDataSet];

                [pDimse sendCommandOrResponse:pCommand error:&pError];

                DicomheroNCreateResponse* pResponse = [pDimse getNCreateResponse:pCommand error:&pError];

                EXPECT_EQ(DicomheroDimseStatusSuccess, pResponse.status);
            }

            // Send N-DELETE
            {
                DicomheroDataSet* pDataSet = [[DicomheroDataSet alloc] initWithTransferSyntax:@"1.2.840.10008.1.2"];

                [pDataSet setString:[[DicomheroTagId alloc] initWithGroup:0x10 tag:0x10] newValue:@"TestPatient" error:&pError];

                DicomheroNDeleteCommand* pCommand = [[DicomheroNDeleteCommand alloc]initWithAbstractSyntax:
                    @"1.2.840.10008.1.1"
                    messageID:[pDimse getNextCommandID]
                    requestedSopClassUid:@"1.2.840.10008.1.1"
                    requestedSopInstanceUid:@"1.1.1"];

                [pDimse sendCommandOrResponse:pCommand error:&pError];

                DicomheroNDeleteResponse* pResponse = [pDimse getNDeleteResponse:pCommand error:&pError];

                EXPECT_EQ(DicomheroDimseStatusSuccess, pResponse.status);
            }
        } // autoreleasepool
    }
    catch(...)
    {
        std::cout << dicomhero::ExceptionsManager::getExceptionTrace();
    }

    scp.join();

}


// Test interface with dicomdir
TEST(objectivec, createDicomDir)
{
    DicomheroDicomDir* newDicomDir = [[DicomheroDicomDir alloc] init];

    NSError* pError(0);
    DicomheroDicomDirEntry* rootRecord = [newDicomDir getNewEntry:@"PATIENT" error:&pError];

    DicomheroDataSet* rootRecordDataSet = [rootRecord getEntryDataSet];
    [rootRecordDataSet setString:[[DicomheroTagId alloc] initWithGroup:0x10 tag:0x10] newValue:@"Surname" error:&pError];
    [newDicomDir setFirstRootEntry:rootRecord error:&pError];

    DicomheroDicomDirEntry* nextRecord = [newDicomDir getNewEntry:@"PATIENT" error:&pError];
    DicomheroDataSet* nextRecordDataSet = [nextRecord getEntryDataSet];
    [nextRecordDataSet setString:[[DicomheroTagId alloc] initWithGroup:0x10 tag:0x10] newValue:@"Surname 1" error:&pError];
    [rootRecord setNextEntry:nextRecord error:&pError];

    DicomheroDicomDirEntry* imageRecord = [newDicomDir getNewEntry:@"IMAGE" error:&pError];
    DicomheroDataSet* imageRecordDataSet = [imageRecord getEntryDataSet];
    [imageRecordDataSet setString:[[DicomheroTagId alloc] initWithGroup:0x8 tag:0x18] newValue:@"1.2.840.34.56.78999654.235" error:&pError];
    [nextRecord setFirstChildEntry:imageRecord error:&pError];

    NSMutableArray* parts = [[NSMutableArray alloc] init];
    [parts addObject: @"folder"];
    [parts addObject: @"file.dcm"];

    [imageRecord setFileParts:parts error:&pError];

    [nextRecord setFirstChildEntry:imageRecord error:&pError];

    DicomheroDataSet* dicomDirDataSet = [newDicomDir updateDataSet:&pError];

    DicomheroDicomDir* testDicomDir = [[DicomheroDicomDir alloc] initWithDataSet:dicomDirDataSet error:&pError];
    DicomheroDicomDirEntry* testRootRecord = [testDicomDir getFirstRootEntry:&pError];
    DicomheroDataSet* testRootRecordDataSet = [testRootRecord getEntryDataSet];
    EXPECT_EQ("PATIENT", NSStringToString([testRootRecord getTypeString:&pError]));
    EXPECT_EQ("Surname", NSStringToString([testRootRecordDataSet getString:[[DicomheroTagId alloc] initWithGroup:0x10 tag:0x10] elementNumber:0 error:&pError]));

    DicomheroDicomDirEntry* testNextRecord = [testRootRecord getNextEntry];
    DicomheroDataSet* testNextRecordDataSet = [testNextRecord getEntryDataSet];
    EXPECT_EQ("PATIENT", NSStringToString([testNextRecord getTypeString:&pError]));
    EXPECT_EQ("Surname 1", NSStringToString([testNextRecordDataSet getString:[[DicomheroTagId alloc] initWithGroup:0x10 tag:0x10] elementNumber:0 error:&pError]));
    EXPECT_EQ(0, [testNextRecord getNextEntry]);

    DicomheroDicomDirEntry* testImageRecord = [testNextRecord getFirstChildEntry];
    DicomheroDataSet* testImageRecordDataSet = [testImageRecord getEntryDataSet];
    EXPECT_EQ("IMAGE", NSStringToString([testImageRecord getTypeString:&pError]));
    EXPECT_EQ("1.2.840.34.56.78999654.235", NSStringToString([testImageRecordDataSet getString:[[DicomheroTagId alloc] initWithGroup:0x8 tag:0x18] elementNumber:0 error:&pError]));
    EXPECT_EQ("folder", NSStringToString([[testImageRecord getFileParts:&pError] objectAtIndex:0]));
    EXPECT_EQ("file.dcm", NSStringToString([[testImageRecord getFileParts:&pError] objectAtIndex:1]));
    EXPECT_EQ(0, [testImageRecord getFirstChildEntry]);

}


// Test the UID generators
TEST(objectivec, uidGenerators)
{
    DicomheroBaseUIDGenerator* random = [[DicomheroRandomUIDGenerator alloc] initWithRoot:@"1.2.3" departmentId:2 modelId:3];
    DicomheroBaseUIDGenerator* serial = [[DicomheroSerialNumberUIDGenerator alloc] initWithRoot:@"1.2.3" departmentId:4 modelId:3 serialNumber:4];

    NSError* pError(0);
    [DicomheroUIDGeneratorFactory registerUIDGenerator:@"random" generator:random error:&pError];
    [DicomheroUIDGeneratorFactory registerUIDGenerator:@"serial" generator:serial error:&pError];

    std::set<std::string> generatedUids;

    size_t numberOfUIDs(100000);

    for(size_t index(0); index != numberOfUIDs; ++index)
    {
        @autoreleasepool
        {
            std::string uid0 = dicomhero::NSStringToString([random getUID]);
            std::string uid1 = dicomhero::NSStringToString([serial getUID]);

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
    DicomheroDataSet* testDataSet = [[DicomheroDataSet alloc] initWithTransferSyntax:dicomhero::stringToNSString(transferSyntax)];
    DicomheroTag* streamTag = [testDataSet getTagCreate:[[DicomheroTagId alloc] initWithGroup:0x20 tag:0x20] tagVR:DicomheroTagTypeOB error:&pError];
    [streamTag setStream:0 stream:[[DicomheroFileStreamInput alloc] initWithName:dicomhero::stringToNSString(fileName) error:&pError] error:&pError];

    DicomheroMutableMemory* pStreamMemory = [[DicomheroMutableMemory alloc] init];
    @autoreleasepool
    {
        DicomheroMemoryStreamOutput* pWriteStream = [[DicomheroMemoryStreamOutput alloc] initWithMutableMemory:pStreamMemory];
        DicomheroStreamWriter* pWriter = [[DicomheroStreamWriter alloc] initWithOutputStream: pWriteStream];
        NSError* pError = 0;
        [DicomheroCodecFactory saveToStream:pWriter dataSet:testDataSet codecType:DicomheroCodecTypeDicom error:&pError];

    }

    DicomheroMemoryStreamInput* pReadStream = [[DicomheroMemoryStreamInput alloc] initWithReadMemory:pStreamMemory];

    DicomheroStreamReader* pReader = [[DicomheroStreamReader alloc] initWithInputStream:pReadStream];

    DicomheroDataSet* pTestDataSet = [DicomheroCodecFactory loadFromStream:pReader error:&pError];

    unsigned int bufferSize = [[pTestDataSet getTag:[[DicomheroTagId alloc] initWithGroup:0x20 tag:0x20] error:&pError] getBufferSize:0 error:&pError];
    EXPECT_EQ(1024u * 1024u, bufferSize);

}


TEST(objectivec, voilutUnsigned8OptimalVOI)
{
    DicomheroImage* unsigned8 = [[DicomheroImage alloc] initWithWidth:6 height:1 depth:DicomheroBitDepthU8 colorSpace:@"MONOCHROME2" highBit:7];

    NSError* pError(0);

    @autoreleasepool
    {
        DicomheroWritingDataHandler* unsigned8Handler = [unsigned8 getWritingDataHandler:&pError];
        [unsigned8Handler setUint32:0 newValue:10 error:&pError];
        [unsigned8Handler setUint32:1 newValue:0 error:&pError];
        [unsigned8Handler setUint32:2 newValue:20 error:&pError];
        [unsigned8Handler setUint32:3 newValue:30 error:&pError];
        [unsigned8Handler setUint32:4 newValue:40 error:&pError];
        [unsigned8Handler setUint32:5 newValue:50 error:&pError];
    }

    DicomheroVOIDescription* voiDescription = [DicomheroVOILUT getOptimalVOI:unsigned8 inputTopLeftX:0 inputTopLeftY:0 inputWidth:6 inputHeight:1 error:&pError];
    DicomheroVOILUT* voilut = [[DicomheroVOILUT alloc] initWithVOIDescription:voiDescription];

    DicomheroImage* unsigned8Out = [voilut allocateOutputImage:unsigned8 width:6 height:1 error:&pError];
    [voilut runTransform:unsigned8 inputTopLeftX:0 inputTopLeftY:0 inputWidth:6 inputHeight:1 outputImage:unsigned8Out outputTopLeftX:0 outputTopLeftY:0 error:&pError];

    DicomheroReadingDataHandler* unsigned8Handler = [unsigned8Out getReadingDataHandler:&pError];

    EXPECT_LE(51u, [unsigned8Handler getUint32:0 error:&pError]);
    EXPECT_GE(53u, [unsigned8Handler getUint32:0 error:&pError]);

    EXPECT_LE(0u, [unsigned8Handler getUint32:1 error:&pError]);
    EXPECT_GE(1u, [unsigned8Handler getUint32:1 error:&pError]);

    EXPECT_LE(103u, [unsigned8Handler getUint32:2 error:&pError]);
    EXPECT_GE(105u, [unsigned8Handler getUint32:2 error:&pError]);

    EXPECT_LE(155u, [unsigned8Handler getUint32:3 error:&pError]);
    EXPECT_GE(157u, [unsigned8Handler getUint32:3 error:&pError]);

    EXPECT_LE(207u, [unsigned8Handler getUint32:4 error:&pError]);
    EXPECT_GE(209u, [unsigned8Handler getUint32:4 error:&pError]);

    EXPECT_LE(254u, [unsigned8Handler getUint32:5 error:&pError]);
    EXPECT_GE(255u, [unsigned8Handler getUint32:5 error:&pError]);
}


TEST(objectivec, testOverlay)
{
    DicomheroImage* overlayBitmap = [[DicomheroImage alloc] initWithWidth:6 height:1 depth:DicomheroBitDepthU8 colorSpace:@"MONOCHROME2" highBit:1];

    NSError* pError(0);

    @autoreleasepool
    {
        DicomheroWritingDataHandler* unsigned8Handler = [overlayBitmap getWritingDataHandler:&pError];
        [unsigned8Handler setUint32:0 newValue:1 error:&pError];
        [unsigned8Handler setUint32:1 newValue:0 error:&pError];
        [unsigned8Handler setUint32:2 newValue:1 error:&pError];
        [unsigned8Handler setUint32:3 newValue:0 error:&pError];
        [unsigned8Handler setUint32:4 newValue:1 error:&pError];
        [unsigned8Handler setUint32:5 newValue:0 error:&pError];
    }

    DicomheroOverlay* overlay = [[DicomheroOverlay alloc] initWithType:DicomheroOverlayTypeGraphic subType:@"" firstFrame:0 zeroBasedOriginX:0 zeroBasedOriginY:0 label:@"LABEL" description:@"Description"];
    [overlay setImage:0 image:overlayBitmap error:&pError];

    DicomheroDataSet* testDataSet = [[DicomheroDataSet alloc] initWithTransferSyntax:@"1.2.840.10008.1.2.1"];

    [testDataSet setOverlay:0 overlay: overlay error:&pError];

    DicomheroOverlay* checkOverlay = [testDataSet getOverlay:0 error:&pError];

    ASSERT_EQ([checkOverlay getImage:0 error:&pError].width, 6u);

}



// Test DrawBitmap generating a NSImage
#if defined(__APPLE__)

TEST(objectivec, images)
{
    NSError* pError(0);

    unsigned int width = 600;
    unsigned int height = 400;

    DicomheroImage* pBaselineImage = [[DicomheroImage alloc] initWithWidth:width height:height depth:DicomheroBitDepthU8 colorSpace:@"RGB" highBit:7];

    @autoreleasepool
    {
        DicomheroWritingDataHandler* pWritingDataHandler = [pBaselineImage getWritingDataHandler:&pError];

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


    DicomheroTransform* pColorTransform = [DicomheroColorTransformsFactory getTransform:@"RGB" finalColorSpace:@"YBR_FULL" error:&pError];

    DicomheroImage* pYbrImage = [pColorTransform allocateOutputImage:pBaselineImage width:width height:height error:&pError];

    [pColorTransform runTransform:pBaselineImage inputTopLeftX:0 inputTopLeftY:0 inputWidth:width inputHeight:height outputImage:pYbrImage outputTopLeftX:0 outputTopLeftY:0 error:&pError];

    DicomheroDrawBitmap* pDrawBitmap = [[DicomheroDrawBitmap alloc] init];

    NSImage* pNsImage = [pDrawBitmap getDicomheroImage:pYbrImage error:&pError];

    NSData* pImageData = [pNsImage TIFFRepresentation];
    NSBitmapImageRep* pImageRep = [NSBitmapImageRep imageRepWithData:pImageData];
    NSDictionary *pImageProps = [NSDictionary dictionaryWithObject:[NSNumber numberWithFloat:1.0] forKey:NSImageCompressionFactor];
    pImageData = [pImageRep representationUsingType:NSBitmapImageFileTypeJPEG properties:pImageProps];

    DicomheroMutableMemory* pDataMemory = [[DicomheroMutableMemory alloc] initWithData:pImageData];
    DicomheroMemoryStreamInput* pDataStream = [[DicomheroMemoryStreamInput alloc] initWithReadMemory:pDataMemory];
    DicomheroStreamReader* pDataReader = [[DicomheroStreamReader alloc] initWithInputStream:pDataStream];

    DicomheroDataSet* pLoadedDataSet = [DicomheroCodecFactory loadFromStream:pDataReader error:&pError];
    DicomheroImage* pLoadedImage = [pLoadedDataSet getImage:0 error:&pError];

    // Compare the buffers. A little difference is allowed
    double differenceYBR = compareImages(*(dicomhero::Image*)(pYbrImage->m_Image), *(dicomhero::Image*)(pLoadedImage->m_Image));
    ASSERT_LE(differenceYBR, 1);
}

#endif

} // namespace tests

} // namespace dicomhero
