#include <imebra/imebra.h>
#include <gtest/gtest.h>
#include <thread>
#include <chrono>
#include <array>
#include <list>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include "testsSettings.h"

#ifndef DISABLE_DCMTK_INTEROPERABILITY_TEST
    #include <dirent.h>
    #include <sys/stat.h>
#endif

namespace imebra
{

namespace tests
{

///////////////////////////////////////////////////////////
//
// A SCP that responds to C-STORE commands
//
///////////////////////////////////////////////////////////
void storeScpThread(
        const std::string& name,
        PresentationContexts& presentationContexts,
        StreamReader& readSCP,
        StreamWriter& writeSCP,
        std::list<CStoreCommand>& receivedCommands)
{
    try
    {
        AssociationSCP scp(name, 1, 1, presentationContexts, readSCP, writeSCP, 0, 10);

        DimseService dimseService(scp);

        CStoreCommand command = dimseService.getCommand().getAsCStoreCommand();
        receivedCommands.push_back(command);

        dimseService.sendCommandOrResponse(CStoreResponse(command, dimseStatusCode_t::success));

    }
    catch(const StreamClosedError&)
    {

    }
}


///////////////////////////////////////////////////////////
//
// Store SCU test
//
// This test sends a DataSet to a SCP which logs all the
// received commands, then checks that the sent dataset
// is in the logged commands.
//
///////////////////////////////////////////////////////////
TEST(dimseTest, storeSCUSCP)
{
    PipeStream toSCU(1024), toSCP(1024);

    StreamReader readSCU(toSCU.getStreamInput());
    StreamWriter writeSCU(toSCP.getStreamOutput());

    StreamReader readSCP(toSCP.getStreamInput());
    StreamWriter writeSCP(toSCU.getStreamOutput());

    PresentationContext context("1.2.840.10008.1.1");
    context.addTransferSyntax("1.2.840.10008.1.2"); // implicit VR little endian
    PresentationContexts presentationContexts;
    presentationContexts.addPresentationContext(context);

    const std::string scpName("SCP");

    std::list<CStoreCommand> receivedCommands;

    std::thread thread(
                imebra::tests::storeScpThread,
                std::ref(scpName),
                std::ref(presentationContexts),
                std::ref(readSCP),
                std::ref(writeSCP),
                std::ref(receivedCommands));

    AssociationSCU scu("SCU", scpName, 1, 1, presentationContexts, readSCU, writeSCU, 0);

    DimseService dimse(scu);

    MutableDataSet payload("1.2.840.10008.1.2");
    payload.setString(TagId(tagId_t::SOPClassUID_0008_0016), "1.1.1.1.1");
    payload.setString(TagId(tagId_t::SOPInstanceUID_0008_0018), "1.1.1.1.2");
    payload.setString(TagId(tagId_t::PatientName_0010_0010), "Test^Patient");
    CStoreCommand storeCommand(
                "1.2.840.10008.1.1",
                dimse.getNextCommandID(),
                dimseCommandPriority_t::medium,
                payload.getString(TagId(tagId_t::SOPClassUID_0008_0016), 0),
                payload.getString(TagId(tagId_t::SOPInstanceUID_0008_0018), 0),
                "Origin",
                15,
                payload);
    dimse.sendCommandOrResponse(storeCommand);
    CStoreResponse response = dimse.getCStoreResponse(storeCommand);

    EXPECT_EQ(1u, receivedCommands.size());
    EXPECT_EQ("Origin", receivedCommands.front().getOriginatorAET());
    EXPECT_EQ("1.1.1.1.2", receivedCommands.front().getAffectedSopInstanceUid());
    EXPECT_EQ("1.1.1.1.1", receivedCommands.front().getAffectedSopClassUid());

    DataSet receivedCommand = receivedCommands.front().getCommandDataSet();
    EXPECT_EQ("Origin", receivedCommand.getString(TagId(tagId_t::MoveOriginatorApplicationEntityTitle_0000_1030), 0));

    DataSet receivedPayload = receivedCommands.front().getPayloadDataSet();
    EXPECT_EQ("Test^Patient", receivedPayload.getString(TagId(tagId_t::PatientName_0010_0010), 0));

    EXPECT_EQ(15, receivedCommands.front().getOriginatorMessageID());

    thread.join();
}




///////////////////////////////////////////////////////////
//
// A SCP that responds to C-GET commands.
// It only accepts "PATIENT" query levels and only
// respond to the patient ID "100"
//
///////////////////////////////////////////////////////////
void getScpThread(
        const std::string& name,
        PresentationContexts& presentationContexts,
        StreamReader& readSCP,
        StreamWriter& writeSCP)
{
    try
    {
        AssociationSCP scp(name, 1, 1, presentationContexts, readSCP, writeSCP, 0, 10);

        DimseService dimseService(scp);

        for(;;)
        {
            CGetCommand command = dimseService.getCommand().getAsCGetCommand();
            DataSet identifier(command.getPayloadDataSet());

            if(identifier.getString(TagId(tagId_t::QueryRetrieveLevel_0008_0052), 0) != "PATIENT" ||
                    identifier.getString(TagId(tagId_t::PatientID_0010_0020), 0) != "100")
            {
                dimseService.sendCommandOrResponse(CGetResponse(command, dimseStatusCode_t::success, 0, 0, 0, 0));
                return;
            }

            // Return a partial response
            dimseService.sendCommandOrResponse(CGetResponse(command, dimseStatusCode_t::pending, 1, 0, 0, 0));

            // Perform a C-STORE on the AE that requested the C-GET
            std::string abstractSyntax(command.getAbstractSyntax());
            MutableDataSet storePayload(dimseService.getTransferSyntax(abstractSyntax));
            storePayload.setString(TagId(tagId_t::PatientID_0010_0020), "100");
            storePayload.setString(TagId(tagId_t::PatientName_0010_0010), "TEST^PATIENT");
            CStoreCommand storeCommand(
                        abstractSyntax,
                        dimseService.getNextCommandID(),
                        dimseCommandPriority_t::medium,
                        command.getAffectedSopClassUid(),
                        "1.2.3.4.5.6",
                        scp.getOtherAET(),
                        command.getID(),
                        storePayload);

            dimseService.sendCommandOrResponse(storeCommand);
            CStoreResponse storeResponse = dimseService.getCStoreResponse(storeCommand);

            // Send the C-GET final response
            if(storeResponse.getStatus() == dimseStatus_t::success)
            {
                dimseService.sendCommandOrResponse(CGetResponse(command, dimseStatusCode_t::success, 0, 1, 0, 0));
            }
            else
            {
                dimseService.sendCommandOrResponse(CGetResponse(command, dimseStatusCode_t::subOperationCompletedWithErrors, 0, 0, 1, 0));
            }
        }
    }
    catch(const StreamClosedError&)
    {

    }
}


///////////////////////////////////////////////////////////
//
// Get SCU test
//
// This test requests a C-GET to a SCP, and wait for the
// SCP C-STORE operation and the C-GET responses.
//
///////////////////////////////////////////////////////////
TEST(dimseTest, getSCUSCP)
{
    PipeStream toSCU(1024), toSCP(1024);

    StreamReader readSCU(toSCU.getStreamInput());
    StreamWriter writeSCU(toSCP.getStreamOutput());

    StreamReader readSCP(toSCP.getStreamInput());
    StreamWriter writeSCP(toSCU.getStreamOutput());

    PresentationContext context("1.2.840.10008.5.1.4.1.2.1.3", true, true);
    context.addTransferSyntax("1.2.840.10008.1.2"); // implicit VR little endian
    PresentationContexts presentationContexts;
    presentationContexts.addPresentationContext(context);

    const std::string scpName("SCP");

    std::thread thread(
                imebra::tests::getScpThread,
                std::ref(scpName),
                std::ref(presentationContexts),
                std::ref(readSCP),
                std::ref(writeSCP));

    AssociationSCU scu("SCU", scpName, 1, 1, presentationContexts, readSCU, writeSCU, 0);
    DimseService dimse(scu);

    MutableDataSet keys(dimse.getTransferSyntax("1.2.840.10008.5.1.4.1.2.1.3"));
    keys.setString(TagId(tagId_t::QueryRetrieveLevel_0008_0052), "PATIENT");
    keys.setString(TagId(tagId_t::PatientID_0010_0020), "100");
    CGetCommand getCommand(
                "1.2.840.10008.5.1.4.1.2.1.3",
                dimse.getNextCommandID(),
                dimseCommandPriority_t::medium,
                "1.1.1.1.1",
                keys);

    dimse.sendCommandOrResponse(getCommand);

    // Wait for incoming c-store
    CStoreCommand storeCommand = dimse.getCommand().getAsCStoreCommand();

    DataSet storeDataSet = storeCommand.getPayloadDataSet();

    std::string patientId(storeDataSet.getString(TagId(tagId_t::PatientID_0010_0020), 0));
    std::string patientName(storeDataSet.getString(TagId(tagId_t::PatientName_0010_0010), 0));

    EXPECT_EQ("100", patientId);
    EXPECT_EQ("TEST^PATIENT", patientName);

    dimse.sendCommandOrResponse(CStoreResponse(storeCommand, dimseStatusCode_t::success));

    CGetResponse response0 = dimse.getCGetResponse(getCommand);
    EXPECT_EQ(dimseStatus_t::pending, response0.getStatus());
    CGetResponse response1 = dimse.getCGetResponse(getCommand);
    EXPECT_EQ(dimseStatus_t::success, response1.getStatus());

    readSCU.terminate();
    readSCP.terminate();
    thread.join();
}


///////////////////////////////////////////////////////////
//
// A SCP that responds to C-MOVE commands.
// It only accepts "PATIENT" query levels and only
// respond to the patient ID "100"
//
///////////////////////////////////////////////////////////
void moveScpThread(
        const std::string& name,
        PresentationContexts& presentationContexts,
        StreamReader& readSCP,
        StreamWriter& writeSCP,
        std::size_t* pReceivedRequests)
{
    try
    {
        AssociationSCP scp(name, 1, 1, presentationContexts, readSCP, writeSCP, 0, 10);

        DimseService dimseService(scp);

        for(;;)
        {
            CMoveCommand command = dimseService.getCommand().getAsCMoveCommand();
            DataSet identifier = command.getPayloadDataSet();

            if(identifier.getString(TagId(tagId_t::QueryRetrieveLevel_0008_0052), 0) != "PATIENT" ||
                    identifier.getString(TagId(tagId_t::PatientID_0010_0020), 0) != "100")
            {
                dimseService.sendCommandOrResponse(CMoveResponse(command, dimseStatusCode_t::success, 0, 0, 0, 0));
                return;
            }

            (*pReceivedRequests)++;

            // Return a partial response
            dimseService.sendCommandOrResponse(CMoveResponse(command, dimseStatusCode_t::pending, 1, 0, 0, 0));

            dimseService.sendCommandOrResponse(CMoveResponse(command, dimseStatusCode_t::success, 0, 1, 0, 0));
        }
    }
    catch(const StreamClosedError&)
    {

    }
}


///////////////////////////////////////////////////////////
//
// Move SCU test
//
// This test requests a C-MOVE to a SCP, and wait for the
// C-MOVE responses.
//
///////////////////////////////////////////////////////////
TEST(dimseTest, moveSCUSCP)
{
    PipeStream toSCU(1024), toSCP(1024);

    StreamReader readSCU(toSCU.getStreamInput());
    StreamWriter writeSCU(toSCP.getStreamOutput());

    StreamReader readSCP(toSCP.getStreamInput());
    StreamWriter writeSCP(toSCU.getStreamOutput());

    PresentationContext context("1.2.840.10008.5.1.4.1.2.1.2");
    context.addTransferSyntax("1.2.840.10008.1.2"); // implicit VR little endian
    PresentationContexts presentationContexts;
    presentationContexts.addPresentationContext(context);

    const std::string scpName("SCP");

    size_t receivedRequests(0);
    std::thread thread(
                imebra::tests::moveScpThread,
                std::ref(scpName),
                std::ref(presentationContexts),
                std::ref(readSCP),
                std::ref(writeSCP),
                &receivedRequests);

    AssociationSCU scu("SCU", scpName, 1, 1, presentationContexts, readSCU, writeSCU, 0);
    DimseService dimse(scu);



    MutableDataSet keys(dimse.getTransferSyntax("1.2.840.10008.5.1.4.1.2.1.2"));
    keys.setString(TagId(tagId_t::QueryRetrieveLevel_0008_0052), "PATIENT");
    keys.setString(TagId(tagId_t::PatientID_0010_0020), "100");
    CMoveCommand getCommand(
                "1.2.840.10008.5.1.4.1.2.1.2",
                dimse.getNextCommandID(),
                dimseCommandPriority_t::medium,
                "1.1.1.1.1",
                "Destination",
                keys);

    dimse.sendCommandOrResponse(getCommand);

    CMoveResponse response0 = dimse.getCMoveResponse(getCommand);
    EXPECT_EQ(dimseStatus_t::pending, response0.getStatus());
    CMoveResponse response1 = dimse.getCMoveResponse(getCommand);
    EXPECT_EQ(dimseStatus_t::success, response1.getStatus());

    readSCU.terminate();
    readSCP.terminate();
    thread.join();

    EXPECT_EQ(1u, receivedRequests);
}


///////////////////////////////////////////////////////////
//
// A SCP that responds to C-FIND commands.
// It returns 2 studies.
//
///////////////////////////////////////////////////////////
void findScpThread(
        const std::string& name,
        PresentationContexts& presentationContexts,
        StreamReader& readSCP,
        StreamWriter& writeSCP)
{
    try
    {
        AssociationSCP scp(name, 1, 1, presentationContexts, readSCP, writeSCP, 0, 10);

        DimseService dimseService(scp);

        for(;;)
        {
            CFindCommand command = dimseService.getCommand().getAsCFindCommand();
            DataSet identifier = command.getPayloadDataSet();

            if(identifier.getString(TagId(tagId_t::QueryRetrieveLevel_0008_0052), 0) != "STUDY" ||
                    identifier.getString(TagId(tagId_t::PatientID_0010_0020), 0) != "100")
            {
                dimseService.sendCommandOrResponse(CFindResponse(command, dimseStatusCode_t::success));
                return;
            }

            MutableDataSet study0(dimseService.getTransferSyntax(command.getAbstractSyntax()));
            study0.setString(TagId(tagId_t::PatientID_0010_0020), "100");
            study0.setString(TagId(tagId_t::StudyID_0020_0010), "110");
            dimseService.sendCommandOrResponse(CFindResponse(command, study0));

            MutableDataSet study1(dimseService.getTransferSyntax(command.getAbstractSyntax()));
            study1.setString(TagId(tagId_t::PatientID_0010_0020), "100");
            study1.setString(TagId(tagId_t::StudyID_0020_0010), "120");
            dimseService.sendCommandOrResponse(CFindResponse(command, study1));

            dimseService.sendCommandOrResponse(CFindResponse(command, dimseStatusCode_t::success));
        }
    }
    catch(const StreamClosedError&)
    {

    }
}


///////////////////////////////////////////////////////////
//
// Find SCU test
//
// This test requests a C-FIND to a SCP, and wait for the
// C-FIND responses.
//
///////////////////////////////////////////////////////////
TEST(dimseTest, findSCUSCP)
{
    PipeStream toSCU(1024), toSCP(1024);

    StreamReader readSCU(toSCU.getStreamInput());
    StreamWriter writeSCU(toSCP.getStreamOutput());

    StreamReader readSCP(toSCP.getStreamInput());
    StreamWriter writeSCP(toSCU.getStreamOutput());

    PresentationContext context("1.2.840.10008.5.1.4.1.2.1.1");
    context.addTransferSyntax("1.2.840.10008.1.2.1"); // explicit VR little endian
    PresentationContexts presentationContexts;
    presentationContexts.addPresentationContext(context);

    const std::string scpName("SCP");

    std::thread thread(
                imebra::tests::findScpThread,
                std::ref(scpName),
                std::ref(presentationContexts),
                std::ref(readSCP),
                std::ref(writeSCP));

    AssociationSCU scu("SCU", scpName, 1, 1, presentationContexts, readSCU, writeSCU, 0);
    DimseService dimse(scu);

    MutableDataSet keys(dimse.getTransferSyntax("1.2.840.10008.5.1.4.1.2.1.1"));
    keys.setString(TagId(tagId_t::QueryRetrieveLevel_0008_0052), "STUDY");
    keys.setString(TagId(tagId_t::PatientID_0010_0020), "100");
    CFindCommand findCommand(
                "1.2.840.10008.5.1.4.1.2.1.1",
                dimse.getNextCommandID(),
                dimseCommandPriority_t::medium,
                "1.1.1.1.1",
                keys);

    dimse.sendCommandOrResponse(findCommand);

    CFindResponse response0 = dimse.getCFindResponse(findCommand);
    EXPECT_EQ(dimseStatus_t::pending, response0.getStatus());
    DataSet dataset0 = response0.getPayloadDataSet();
    EXPECT_EQ("110", dataset0.getString(TagId(tagId_t::StudyID_0020_0010), 0));

    CFindResponse response1 = dimse.getCFindResponse(findCommand);
    EXPECT_EQ(dimseStatus_t::pending, response1.getStatus());
    DataSet dataset1 = response1.getPayloadDataSet();
    EXPECT_EQ("120", dataset1.getString(TagId(tagId_t::StudyID_0020_0010), 0));

    CFindResponse response2 = dimse.getCFindResponse(findCommand);
    EXPECT_EQ(dimseStatus_t::success, response2.getStatus());

    readSCU.terminate();
    readSCP.terminate();
    thread.join();
}





///////////////////////////////////////////////////////////
//
// A SCP that responds to C-ECHO commands.
//
///////////////////////////////////////////////////////////
void echoScpThread(
        const std::string& name,
        PresentationContexts& presentationContexts,
        StreamReader& readSCP,
        StreamWriter& writeSCP)
{
    try
    {
        AssociationSCP scp(name, 1, 1, presentationContexts, readSCP, writeSCP, 0, 10);

        DimseService dimseService(scp);

        for(;;)
        {
            CEchoCommand command = dimseService.getCommand().getAsCEchoCommand();
            dimseService.sendCommandOrResponse(CEchoResponse(command, dimseStatusCode_t::success));
        }
    }
    catch(const StreamClosedError&)
    {

    }
}


///////////////////////////////////////////////////////////
//
// ECHO SCU test
//
// This test requests a C-ECHO to a SCP, and wait for the
// C-ECHO responses.
//
///////////////////////////////////////////////////////////
TEST(dimseTest, echoSCUSCP)
{
    PipeStream toSCU(1024), toSCP(1024);

    StreamReader readSCU(toSCU.getStreamInput());
    StreamWriter writeSCU(toSCP.getStreamOutput());

    StreamReader readSCP(toSCP.getStreamInput());
    StreamWriter writeSCP(toSCU.getStreamOutput());

    PresentationContext context("1.2.840.10008.1.1");
    context.addTransferSyntax("1.2.840.10008.1.2.1"); // explicit VR little endian
    PresentationContexts presentationContexts;
    presentationContexts.addPresentationContext(context);

    const std::string scpName("SCP");

    std::thread thread(
                imebra::tests::echoScpThread,
                std::ref(scpName),
                std::ref(presentationContexts),
                std::ref(readSCP),
                std::ref(writeSCP));

    AssociationSCU scu("SCU", scpName, 1, 1, presentationContexts, readSCU, writeSCU, 0);
    DimseService dimse(scu);

    CEchoCommand echoCommand(
                "1.2.840.10008.1.1",
                dimse.getNextCommandID(),
                dimseCommandPriority_t::medium,
                "1.1.1.1.1");

    dimse.sendCommandOrResponse(echoCommand);

    CEchoResponse response = dimse.getCEchoResponse(echoCommand);
    EXPECT_EQ(dimseStatus_t::success, response.getStatus());
    EXPECT_EQ("1.1.1.1.1", response.getAffectedSopClassUid());

    readSCU.terminate();
    readSCP.terminate();

    thread.join();
}


///////////////////////////////////////////////////////////
//
// A SCP that wait for a cancelation of a C-MOVE command
//
///////////////////////////////////////////////////////////
void cancelScpThread(
        const std::string& name,
        PresentationContexts& presentationContexts,
        StreamReader& readSCP,
        StreamWriter& writeSCP)
{
    try
    {
        AssociationSCP scp(name, 1, 1, presentationContexts, readSCP, writeSCP, 0, 10);

        DimseService dimseService(scp);

        for(;;)
        {
            DimseCommand command = dimseService.getCommand();
            ASSERT_EQ(dimseCommandType_t::cMove, command.getCommandType());
            CMoveCommand moveCommand = command.getAsCMoveCommand();
            CCancelCommand cancel = dimseService.getCommand().getAsCCancelCommand();
            dimseService.getCommand().getAsCCancelCommand();

            if(cancel.getCancelMessageID() == moveCommand.getID())
            {
                dimseService.sendCommandOrResponse(CMoveResponse(moveCommand, dimseStatusCode_t::canceled, 0, 0, 0, 0));
            }
            else
            {
                dimseService.sendCommandOrResponse(CMoveResponse(moveCommand, dimseStatusCode_t::success, 0, 0, 0, 0));
            }
            dimseService.getCommand().getAsCCancelCommand();

        }
    }
    catch(const StreamClosedError&)
    {

    }
}


///////////////////////////////////////////////////////////
//
// CANCEL SCU test
//
// This test requests a C-MOVE and then cancels it.
//
///////////////////////////////////////////////////////////
TEST(dimseTest, cancelSCUSCP)
{
    PipeStream toSCU(1024), toSCP(1024);

    StreamReader readSCU(toSCU.getStreamInput());
    StreamWriter writeSCU(toSCP.getStreamOutput());

    StreamReader readSCP(toSCP.getStreamInput());
    StreamWriter writeSCP(toSCU.getStreamOutput());

    PresentationContext context("1.2.840.10008.5.1.4.1.2.1.2");
    context.addTransferSyntax("1.2.840.10008.1.2"); // implicit VR little endian
    PresentationContexts presentationContexts;
    presentationContexts.addPresentationContext(context);

    const std::string scpName("SCP");

    std::thread thread(
                imebra::tests::cancelScpThread,
                std::ref(scpName),
                std::ref(presentationContexts),
                std::ref(readSCP),
                std::ref(writeSCP));

    AssociationSCU scu("SCU", scpName, 1, 1, presentationContexts, readSCU, writeSCU, 0);
    DimseService dimse(scu);

    MutableDataSet keys(dimse.getTransferSyntax("1.2.840.10008.5.1.4.1.2.1.2"));
    keys.setString(TagId(tagId_t::QueryRetrieveLevel_0008_0052), "PATIENT");
    keys.setString(TagId(tagId_t::PatientID_0010_0020), "100");
    CMoveCommand moveCommand(
                "1.2.840.10008.5.1.4.1.2.1.2",
                dimse.getNextCommandID(),
                dimseCommandPriority_t::medium,
                "1.1.1.1.1",
                "Destination",
                keys);
    dimse.sendCommandOrResponse(moveCommand);

    CCancelCommand cancel("1.2.840.10008.5.1.4.1.2.1.2", dimse.getNextCommandID(), dimseCommandPriority_t::medium, moveCommand.getID());
    dimse.sendCommandOrResponse(cancel);
    CCancelCommand cancel1("1.2.840.10008.5.1.4.1.2.1.2", dimse.getNextCommandID(), dimseCommandPriority_t::medium, moveCommand.getID());
    dimse.sendCommandOrResponse(cancel1);

    std::this_thread::sleep_for(std::chrono::seconds(5));

    CMoveResponse response = dimse.getCMoveResponse(moveCommand);

    EXPECT_EQ(dimseStatus_t::cancel, response.getStatus());

    EXPECT_NO_THROW(dimse.sendCommandOrResponse(cancel));

    readSCU.terminate();
    readSCP.terminate();

    thread.join();
}


///////////////////////////////////////////////////////////
//
// A SCP that wait for a N-EVENT-REPORT command
//
///////////////////////////////////////////////////////////
void neventReportScpThread(
        const std::string& name,
        PresentationContexts& presentationContexts,
        StreamReader& readSCP,
        StreamWriter& writeSCP)
{
    try
    {
        AssociationSCP scp(name, 1, 1, presentationContexts, readSCP, writeSCP, 0, 10);

        DimseService dimseService(scp);

        for(;;)
        {
            NEventReportCommand command = dimseService.getCommand().getAsNEventReportCommand();

            MutableDataSet eventReply(dimseService.getTransferSyntax(command.getAbstractSyntax()));
            DataSet eventData = command.getPayloadDataSet();
            eventReply.setString(TagId(tagId_t::PatientName_0010_0010),
                                 eventData.getString(TagId(tagId_t::PatientName_0010_0010), 0));
            dimseService.sendCommandOrResponse(NEventReportResponse(command, eventReply));
        }
    }
    catch(const StreamClosedError&)
    {

    }
}


///////////////////////////////////////////////////////////
//
// N-EVENT-REPORT SCU test
//
// This test requests a N-EVENT-REPORT
//
///////////////////////////////////////////////////////////
TEST(dimseTest, neventReportSCUSCP)
{
    PipeStream toSCU(1024), toSCP(1024);

    StreamReader readSCU(toSCU.getStreamInput());
    StreamWriter writeSCU(toSCP.getStreamOutput());

    StreamReader readSCP(toSCP.getStreamInput());
    StreamWriter writeSCP(toSCU.getStreamOutput());

    PresentationContext context("1.2.840.10008.5.1.4.34.6.4");
    context.addTransferSyntax("1.2.840.10008.1.2.1"); // explicit VR little endian
    PresentationContexts presentationContexts;
    presentationContexts.addPresentationContext(context);

    const std::string scpName("SCP");

    std::thread thread(
                imebra::tests::neventReportScpThread,
                std::ref(scpName),
                std::ref(presentationContexts),
                std::ref(readSCP),
                std::ref(writeSCP));

    AssociationSCU scu("SCU", scpName, 1, 1, presentationContexts, readSCU, writeSCU, 0);
    DimseService dimse(scu);

    MutableDataSet nevent(dimse.getTransferSyntax("1.2.840.10008.5.1.4.34.6.4"));
    nevent.setString(TagId(tagId_t::PatientName_0010_0010), "EVENT^PATIENT");
    NEventReportCommand eventCommand(
                "1.2.840.10008.5.1.4.34.6.4",
                dimse.getNextCommandID(),
                "1.1.1.1.1",
                "1.1.1.1.1.1.1",
                1,
                nevent);
    dimse.sendCommandOrResponse(eventCommand);

    NEventReportResponse response = dimse.getNEventReportResponse(eventCommand);
    DataSet eventInformation = response.getPayloadDataSet();

    EXPECT_EQ("EVENT^PATIENT", eventInformation.getString(TagId(tagId_t::PatientName_0010_0010), 0));
    EXPECT_EQ(1, response.getEventID());

    readSCU.terminate();
    readSCP.terminate();

    thread.join();
}


///////////////////////////////////////////////////////////
//
// A SCP that wait for a N-GET command
//
///////////////////////////////////////////////////////////
void ngetScpThread(
        const std::string& name,
        PresentationContexts& presentationContexts,
        StreamReader& readSCP,
        StreamWriter& writeSCP)
{
    try
    {
        AssociationSCP scp(name, 1, 1, presentationContexts, readSCP, writeSCP, 0, 10);

        DimseService dimseService(scp);

        for(;;)
        {
            NGetCommand command = dimseService.getCommand().getAsNGetCommand();
            MutableDataSet getReply(dimseService.getTransferSyntax(command.getAbstractSyntax()));

            attributeIdentifierList_t identifierList(command.getAttributeList());
            if(identifierList.size() == 2 &&
                    identifierList[0] == tagId_t::PatientName_0010_0010 &&
                    identifierList[1] == tagId_t::PatientID_0010_0020)
            {
                getReply.setString(TagId(tagId_t::PatientName_0010_0010), "GET^PATIENT");
                getReply.setString(TagId(tagId_t::PatientID_0010_0020), "100");
            }
            dimseService.sendCommandOrResponse(NGetResponse(command, dimseStatusCode_t::success, getReply));
        }
    }
    catch(const StreamClosedError&)
    {

    }
}


///////////////////////////////////////////////////////////
//
// N-GET SCU test
//
// This test requests a N-GET to a SCP
//
///////////////////////////////////////////////////////////
TEST(dimseTest, ngetSCUSCP)
{
    PipeStream toSCU(1024), toSCP(1024);

    StreamReader readSCU(toSCU.getStreamInput());
    StreamWriter writeSCU(toSCP.getStreamOutput());

    StreamReader readSCP(toSCP.getStreamInput());
    StreamWriter writeSCP(toSCU.getStreamOutput());

    PresentationContext context("1.2.840.10008.5.1.4.34.6.4");
    context.addTransferSyntax("1.2.840.10008.1.2.1"); // explicit VR little endian
    PresentationContexts presentationContexts;
    presentationContexts.addPresentationContext(context);

    const std::string scpName("SCP");

    std::thread thread(
                imebra::tests::ngetScpThread,
                std::ref(scpName),
                std::ref(presentationContexts),
                std::ref(readSCP),
                std::ref(writeSCP));

    AssociationSCU scu("SCU", scpName, 1, 1, presentationContexts, readSCU, writeSCU, 0);
    DimseService dimse(scu);

    attributeIdentifierList_t identifierList;
    identifierList.push_back(tagId_t::PatientName_0010_0010);
    identifierList.push_back(tagId_t::PatientID_0010_0020);
    NGetCommand getCommand(
                "1.2.840.10008.5.1.4.34.6.4",
                dimse.getNextCommandID(),
                "1.1.1.1.1",
                "1.1.1.1.1.1.1",
                identifierList);
    dimse.sendCommandOrResponse(getCommand);

    NGetResponse response = dimse.getNGetResponse(getCommand);
    DataSet getIdentifier = response.getPayloadDataSet();

    EXPECT_EQ("GET^PATIENT", getIdentifier.getString(TagId(tagId_t::PatientName_0010_0010), 0));
    EXPECT_EQ("100", getIdentifier.getString(TagId(tagId_t::PatientID_0010_0020), 0));

    readSCU.terminate();
    readSCP.terminate();

    thread.join();
}




///////////////////////////////////////////////////////////
//
// A SCP that wait for a N-SET command
//
///////////////////////////////////////////////////////////
void nsetScpThread(
        const std::string& name,
        PresentationContexts& presentationContexts,
        StreamReader& readSCP,
        StreamWriter& writeSCP)
{
    try
    {
        AssociationSCP scp(name, 1, 1, presentationContexts, readSCP, writeSCP, 0, 10);

        DimseService dimseService(scp);

        for(;;)
        {
            NSetCommand command = dimseService.getCommand().getAsNSetCommand();
            DataSet setDataSet = command.getPayloadDataSet();

            attributeIdentifierList_t identifierList;

            if(setDataSet.getString(TagId(tagId_t::PatientName_0010_0010), 0) == "SET^PATIENT")
            {
                identifierList.push_back(tagId_t::PatientName_0010_0010);
                dimseService.sendCommandOrResponse(NSetResponse(command, identifierList));
            }
            else
            {
                dimseService.sendCommandOrResponse(NSetResponse(command, dimseStatusCode_t::unableToProcess));
            }
        }
    }
    catch(const StreamClosedError&)
    {

    }
}


///////////////////////////////////////////////////////////
//
// N-SET SCU test
//
// This test requests a N-SET to a SCP
//
///////////////////////////////////////////////////////////
TEST(dimseTest, nsetSCUSCP)
{
    PipeStream toSCU(1024), toSCP(1024);

    StreamReader readSCU(toSCU.getStreamInput());
    StreamWriter writeSCU(toSCP.getStreamOutput());

    StreamReader readSCP(toSCP.getStreamInput());
    StreamWriter writeSCP(toSCU.getStreamOutput());

    PresentationContext context("1.2.840.10008.5.1.4.34.6.4");
    context.addTransferSyntax("1.2.840.10008.1.2.1"); // explicit VR little endian
    PresentationContexts presentationContexts;
    presentationContexts.addPresentationContext(context);

    const std::string scpName("SCP");

    std::thread thread(
                imebra::tests::nsetScpThread,
                std::ref(scpName),
                std::ref(presentationContexts),
                std::ref(readSCP),
                std::ref(writeSCP));

    AssociationSCU scu("SCU", scpName, 1, 1, presentationContexts, readSCU, writeSCU, 0);
    DimseService dimse(scu);

    MutableDataSet setDataset(dimse.getTransferSyntax("1.2.840.10008.5.1.4.34.6.4"));
    setDataset.setString(TagId(tagId_t::PatientName_0010_0010), "SET^PATIENT");

    NSetCommand setCommand(
                "1.2.840.10008.5.1.4.34.6.4",
                dimse.getNextCommandID(),
                "1.1.1.1.1",
                "1.1.1.1.1.1.1",
                setDataset);
    dimse.sendCommandOrResponse(setCommand);

    NSetResponse response = dimse.getNSetResponse(setCommand);

    attributeIdentifierList_t identifier(response.getModifiedAttributes());

    ASSERT_EQ(1u, identifier.size());
    EXPECT_EQ(tagId_t::PatientName_0010_0010, identifier[0]);

    readSCU.terminate();
    readSCP.terminate();

    thread.join();
}



///////////////////////////////////////////////////////////
//
// A SCP that wait for a N-ACTION command
//
///////////////////////////////////////////////////////////
void nActionScpThread(
        const std::string& name,
        PresentationContexts& presentationContexts,
        StreamReader& readSCP,
        StreamWriter& writeSCP)
{
    try
    {
        AssociationSCP scp(name, 1, 1, presentationContexts, readSCP, writeSCP, 0, 10);

        DimseService dimseService(scp);

        for(;;)
        {
            NActionCommand command = dimseService.getCommand().getAsNActionCommand();
            DataSet setDataSet = command.getPayloadDataSet();

            if(setDataSet.getString(TagId(tagId_t::PatientName_0010_0010), 0) == "ACTION^PATIENT")
            {
                dimseService.sendCommandOrResponse(NActionResponse(command, setDataSet));
            }
            else
            {
                dimseService.sendCommandOrResponse(NActionResponse(command, dimseStatusCode_t::unableToProcess));
            }
        }
    }
    catch(const StreamClosedError&)
    {

    }
}


///////////////////////////////////////////////////////////
//
// N-ACTION SCU test
//
// This test requests a N-ACTION to a SCP
//
///////////////////////////////////////////////////////////
TEST(dimseTest, nActionSCUSCP)
{
    PipeStream toSCU(1024), toSCP(1024);

    StreamReader readSCU(toSCU.getStreamInput());
    StreamWriter writeSCU(toSCP.getStreamOutput());

    StreamReader readSCP(toSCP.getStreamInput());
    StreamWriter writeSCP(toSCU.getStreamOutput());

    PresentationContext context("1.2.840.10008.5.1.4.34.6.4");
    context.addTransferSyntax("1.2.840.10008.1.2.1"); // explicit VR little endian
    PresentationContexts presentationContexts;
    presentationContexts.addPresentationContext(context);

    const std::string scpName("SCP");

    std::thread thread(
                imebra::tests::nActionScpThread,
                std::ref(scpName),
                std::ref(presentationContexts),
                std::ref(readSCP),
                std::ref(writeSCP));

    AssociationSCU scu("SCU", scpName, 1, 1, presentationContexts, readSCU, writeSCU, 0);
    DimseService dimse(scu);

    MutableDataSet actionDataset(dimse.getTransferSyntax("1.2.840.10008.5.1.4.34.6.4"));
    actionDataset.setString(TagId(tagId_t::PatientName_0010_0010), "ACTION^PATIENT");

    std::uint16_t actionID(101);

    NActionCommand actionCommand(
                "1.2.840.10008.5.1.4.34.6.4",
                dimse.getNextCommandID(),
                "1.1.1.1.1",
                "1.1.1.1.1.1.1",
                actionID,
                actionDataset);
    dimse.sendCommandOrResponse(actionCommand);

    NActionResponse response = dimse.getNActionResponse(actionCommand);
    ASSERT_EQ((std::uint16_t)dimseStatusCode_t::success, response.getStatusCode());
    ASSERT_EQ(actionID, response.getActionID());

    DataSet responseDataSet(response.getPayloadDataSet());
    EXPECT_EQ("ACTION^PATIENT", responseDataSet.getString(TagId(tagId_t::PatientName_0010_0010), 0));

    readSCU.terminate();
    readSCP.terminate();

    thread.join();
}



///////////////////////////////////////////////////////////
//
// A SCP that wait for a N-CREATE command
//
///////////////////////////////////////////////////////////
void nCreateScpThread(
        const std::string& name,
        PresentationContexts& presentationContexts,
        StreamReader& readSCP,
        StreamWriter& writeSCP)
{
    try
    {
        AssociationSCP scp(name, 1, 1, presentationContexts, readSCP, writeSCP, 0, 10);

        DimseService dimseService(scp);

        for(;;)
        {
            NCreateCommand command = dimseService.getCommand().getAsNCreateCommand();
            DataSet createDataSet = command.getPayloadDataSet();

            if(createDataSet.getString(TagId(tagId_t::PatientName_0010_0010), 0) == "CREATE^PATIENT")
            {
                dimseService.sendCommandOrResponse(NCreateResponse(command, createDataSet));
            }
            else
            {
                dimseService.sendCommandOrResponse(NCreateResponse(command, dimseStatusCode_t::outOfResources));
            }
        }
    }
    catch(const StreamClosedError&)
    {

    }
}


///////////////////////////////////////////////////////////
//
// N-CREATE SCU test
//
// This test requests a N-CREATE to a SCP
//
///////////////////////////////////////////////////////////
TEST(dimseTest, nCreateSCUSCP)
{
    PipeStream toSCU(1024), toSCP(1024);

    StreamReader readSCU(toSCU.getStreamInput());
    StreamWriter writeSCU(toSCP.getStreamOutput());

    StreamReader readSCP(toSCP.getStreamInput());
    StreamWriter writeSCP(toSCU.getStreamOutput());

    PresentationContext context("1.2.840.10008.5.1.4.34.6.4");
    context.addTransferSyntax("1.2.840.10008.1.2.1"); // explicit VR little endian
    PresentationContexts presentationContexts;
    presentationContexts.addPresentationContext(context);

    const std::string scpName("SCP");

    std::thread thread(
                imebra::tests::nCreateScpThread,
                std::ref(scpName),
                std::ref(presentationContexts),
                std::ref(readSCP),
                std::ref(writeSCP));

    AssociationSCU scu("SCU", scpName, 1, 1, presentationContexts, readSCU, writeSCU, 0);
    DimseService dimse(scu);

    MutableDataSet createDataset(dimse.getTransferSyntax("1.2.840.10008.5.1.4.34.6.4"));
    createDataset.setString(TagId(tagId_t::PatientName_0010_0010), "CREATE^PATIENT");

    NCreateCommand createCommand(
                "1.2.840.10008.5.1.4.34.6.4",
                dimse.getNextCommandID(),
                "1.1.1.1.1",
                "1.1.1.1.1.1.1",
                createDataset);
    dimse.sendCommandOrResponse(createCommand);

    NCreateResponse response = dimse.getNCreateResponse(createCommand);
    ASSERT_EQ((std::uint16_t)dimseStatusCode_t::success, response.getStatusCode());

    DataSet responseDataSet = response.getPayloadDataSet();
    EXPECT_EQ("CREATE^PATIENT", responseDataSet.getString(TagId(tagId_t::PatientName_0010_0010), 0));

    readSCU.terminate();
    readSCP.terminate();

    thread.join();
}



///////////////////////////////////////////////////////////
//
// A SCP that wait for a N-ACTION command
//
///////////////////////////////////////////////////////////
void nDeleteScpThread(
        const std::string& name,
        PresentationContexts& presentationContexts,
        StreamReader& readSCP,
        StreamWriter& writeSCP)
{
    try
    {
        AssociationSCP scp(name, 1, 1, presentationContexts, readSCP, writeSCP, 0, 10);

        DimseService dimseService(scp);

        for(;;)
        {
            NDeleteCommand command = dimseService.getCommand().getAsNDeleteCommand();
            dimseService.sendCommandOrResponse(NDeleteResponse(command, dimseStatusCode_t::success));
        }
    }
    catch(const StreamClosedError&)
    {

    }
}


///////////////////////////////////////////////////////////
//
// N-ACTION SCU test
//
// This test requests a N-ACTION to a SCP
//
///////////////////////////////////////////////////////////
TEST(dimseTest, nDeleteSCUSCP)
{
    PipeStream toSCU(1024), toSCP(1024);

    StreamReader readSCU(toSCU.getStreamInput());
    StreamWriter writeSCU(toSCP.getStreamOutput());

    StreamReader readSCP(toSCP.getStreamInput());
    StreamWriter writeSCP(toSCU.getStreamOutput());

    PresentationContext context("1.2.840.10008.5.1.4.34.6.4");
    context.addTransferSyntax("1.2.840.10008.1.2.1"); // explicit VR little endian
    PresentationContexts presentationContexts;
    presentationContexts.addPresentationContext(context);

    const std::string scpName("SCP");

    std::thread thread(
                imebra::tests::nDeleteScpThread,
                std::ref(scpName),
                std::ref(presentationContexts),
                std::ref(readSCP),
                std::ref(writeSCP));

    AssociationSCU scu("SCU", scpName, 1, 1, presentationContexts, readSCU, writeSCU, 0);
    DimseService dimse(scu);

    NDeleteCommand deleteCommand(
                "1.2.840.10008.5.1.4.34.6.4",
                dimse.getNextCommandID(),
                "1.1.1.1.1",
                "1.1.1.1.1.1.1");
    dimse.sendCommandOrResponse(deleteCommand);

    NDeleteResponse response = dimse.getNDeleteResponse(deleteCommand);
    ASSERT_EQ("1.1.1.1.1.1.1", response.getAffectedSopInstanceUid());

    readSCU.terminate();
    readSCP.terminate();

    thread.join();
}


///////////////////////////////////////////////////////////
//
// A DIMSE SCP that will timeout after 10 seconds
//
///////////////////////////////////////////////////////////
void timeoutScpThread(
        const std::string& name,
        PresentationContexts& presentationContexts,
        StreamReader& readSCP,
        StreamWriter& writeSCP)
{
    try
    {
        AssociationSCP scp(name, 1, 1, presentationContexts, readSCP, writeSCP, 10, 10);

        DimseService dimseService(scp);

        for(;;)
        {
            dimseService.getCommand();
        }
    }
    catch(const StreamClosedError&)
    {

    }
}


TEST(dimseTest, dimseTimeoutTest)
{
    PipeStream toSCU(1024), toSCP(1024);

    StreamReader readSCU(toSCU.getStreamInput());
    StreamWriter writeSCU(toSCP.getStreamOutput());

    StreamReader readSCP(toSCP.getStreamInput());
    StreamWriter writeSCP(toSCU.getStreamOutput());

    PresentationContext context("1.2.840.10008.5.1.4.34.6.4");
    context.addTransferSyntax("1.2.840.10008.1.2.1"); // explicit VR little endian
    PresentationContexts presentationContexts;
    presentationContexts.addPresentationContext(context);

    const std::string scpName("SCP");

    std::thread thread(
                imebra::tests::timeoutScpThread,
                std::ref(scpName),
                std::ref(presentationContexts),
                std::ref(readSCP),
                std::ref(writeSCP));

    AssociationSCU scu("SCU", scpName, 1, 1, presentationContexts, readSCU, writeSCU, 0);

    try
    {
        scu.getCommand();
        EXPECT_TRUE(false);
    }
    catch(const StreamClosedError&)
    {

    }

#if defined(IMEBRA_LOGGING_LOG4CXX)
    ::tests::settings& settings = ::tests::settings::getSettings();
    if(!settings.get("--testLogFile").empty())
    {
        std::ifstream logFile(settings.get("--testLogFile"));
        std::ostringstream readLog;
        readLog <<  logFile.rdbuf();
        std::string logContent(readLog.str());
        EXPECT_TRUE(logContent.find("StreamClosedError") != std::string::npos);
        EXPECT_TRUE(logContent.find("DIMSE Timeout") != std::string::npos);
    }
#endif

    thread.join();

}








#ifndef DISABLE_DCMTK_INTEROPERABILITY_TEST

///////////////////////////////////////////////////////////
//
// Get all the files in a folder
//
///////////////////////////////////////////////////////////
std::list<std::string> getFilesInDirectory(const std::string &directory)
{
    std::list<std::string> files;

    DIR* dir(opendir(directory.c_str()));
    for(dirent* ent(readdir(dir)); ent != NULL; ent = readdir(dir))
    {
        const std::string fileName(ent->d_name);
        if(fileName[0] == '.')
        {
            continue;
        }
        const std::string fullFileName(directory + "/" + fileName);

        struct stat st;
        if (stat(fullFileName.c_str(), &st) == -1)
        {
            continue;
        }

        if((st.st_mode & S_IFDIR) == 0)
        {
            files.push_back(fullFileName);
        }
    }
    closedir(dir);

    return files;
}



//
// Store SCU interoperability test
//
// This test sends a DataSet to a DCMTK STORE SCP
// and check that the sent payload was received correctly.
//
///////////////////////////////////////////////////////////
TEST(dimseTest, storeSCUInteroperabilityTest)
{
    char* tempDirName = ::tempnam(0, "imebra");
    std::string dirName(tempDirName);
    free(tempDirName);

    mkdir(dirName.c_str(), 0700);

    pid_t pID = fork();
    if (pID == 0)                // child
    {
        execlp("storescp", "storescp", "-v", "+v", "-d", "-od", dirName.c_str(), "30003", 0);
    }
    else if (pID < 0)            // failed to fork
    {
        ASSERT_TRUE(false);
    }

    try
    {
        std::this_thread::sleep_for(std::chrono::seconds(5));

        TCPStream tcpStream(TCPActiveAddress("127.0.0.1", "30003"));

        StreamReader readSCU(tcpStream.getStreamInput());
        StreamWriter writeSCU(tcpStream.getStreamOutput());

        std::string transferSyntax("1.2.840.10008.1.2.1");

        // Presentation context with a valid transfer syntax and an invalid one
        PresentationContext context("1.2.840.10008.1.1");
        context.addTransferSyntax("1"); // dummy transfer syntax
        context.addTransferSyntax(transferSyntax); // implicit VR little endian

        // Presentation context with dummy abstract syntax and valid transfer syntax
        PresentationContext dummy("1"); // dummy abstract syntax
        dummy.addTransferSyntax(transferSyntax); // implicit VR little endian

        // Presentation context with all dummy transfer syntaxes
        PresentationContext dummySyntaxes("1.2.840.10008.5.1.1.27");
        dummySyntaxes.addTransferSyntax("1"); // dummy transfer syntax
        dummySyntaxes.addTransferSyntax("2"); // dummy transfer syntax

        PresentationContexts presentationContexts;
        presentationContexts.addPresentationContext(context);
        presentationContexts.addPresentationContext(dummy);
        presentationContexts.addPresentationContext(dummySyntaxes);

        AssociationSCU scu("SCU", "SCP", 1, 1, presentationContexts, readSCU, writeSCU, 0);

        EXPECT_EQ(transferSyntax, scu.getTransferSyntax("1.2.840.10008.1.1"));
        EXPECT_THROW(scu.getTransferSyntax("1"), AcseNoTransferSyntaxError);
        EXPECT_THROW(scu.getTransferSyntax("1.2.840.10008.5.1.1.27"), AcseNoTransferSyntaxError);

        DimseService dimse(scu);

        MutableDataSet payload(transferSyntax);
        payload.setString(TagId(tagId_t::SOPInstanceUID_0008_0018), "1.1.1.1");
        payload.setString(TagId(tagId_t::SOPClassUID_0008_0016), "1.1.1.1");
        payload.setString(TagId(tagId_t::PatientName_0010_0010),"Patient^Test");
        CStoreCommand command(
                    "1.2.840.10008.1.1",
                    dimse.getNextCommandID(),
                    dimseCommandPriority_t::medium,
                    payload.getString(TagId(tagId_t::SOPClassUID_0008_0016), 0),
                    payload.getString(TagId(tagId_t::SOPInstanceUID_0008_0018), 0),
                    "",
                    0,
                    payload);
        dimse.sendCommandOrResponse(command);
        DimseResponse response = dimse.getCStoreResponse(command);

        ASSERT_EQ(response.getStatus(), dimseStatus_t::success);

        std::list<std::string> files(getFilesInDirectory(dirName));

        ASSERT_EQ(files.size(), 1u);

        DataSet readDataSet = CodecFactory::load(files.front());

        ASSERT_EQ(readDataSet.getString(TagId(tagId_t::PatientName_0010_0010), 0), "Patient^Test");
    }
    catch(...)
    {
        kill(pID, SIGTERM);
        throw;
    }

    kill(pID, SIGTERM);
}


///////////////////////////////////////////////////////////
//
// Executes a DCMTK Store SCU command
//
///////////////////////////////////////////////////////////
void storeScuThread(std::string transferSyntax, std::string sopClassUid, std::string sopInstanceUid)
{
    std::this_thread::sleep_for(std::chrono::seconds(5));

    for(int i= 0; i != 20; ++i){

    char* tempFileName = ::tempnam(0, "dcmimebra");
    std::string fileName(tempFileName);
    free(tempFileName);

    MutableDataSet dataSet(transferSyntax);
    dataSet.setString(TagId(tagId_t::SOPClassUID_0008_0016), sopClassUid);
    dataSet.setString(TagId(tagId_t::SOPInstanceUID_0008_0018), sopInstanceUid);
    dataSet.setString(TagId(tagId_t::PatientName_0010_0010), "Test^Patient");
    CodecFactory::save(dataSet, fileName, codecType_t::dicom);

    std::string command("storescu -d -aet scu -aec SCP 127.0.0.1 30004 ");
    command += fileName;

    system(command.c_str());

    }
}


TEST(dimseTest, storeSCPInteroperabilityTest)
{

    std::string transferSyntax("1.2.840.10008.1.2.1");
    std::string sopClassUid("1.2.840.10008.5.1.4.1.1.1");
    std::string sopInstanceUid("1.1.1.1.1.1");
    std::thread thread(
                imebra::tests::storeScuThread,
                transferSyntax,
                sopClassUid,
                sopInstanceUid);

    TCPListener tcpListener(TCPPassiveAddress("", "30004"));

    for(int i=0; i != 20; ++i ){
    TCPStream tcpStream(tcpListener.waitForConnection());

    StreamReader readSCU(tcpStream.getStreamInput());
    StreamWriter writeSCU(tcpStream.getStreamOutput());

    PresentationContext context(sopClassUid);
    context.addTransferSyntax(transferSyntax);
    PresentationContexts presentationContexts;
    presentationContexts.addPresentationContext(context);

    AssociationSCP scp("SCP", 1, 1, presentationContexts, readSCU, writeSCU, 0, 10);

    DimseService dimse(scp);

    CStoreCommand command = dimse.getCommand().getAsCStoreCommand();
    DataSet payload = command.getPayloadDataSet();

    ASSERT_EQ("Test^Patient", payload.getString(TagId(tagId_t::PatientName_0010_0010), 0));

    dimse.sendCommandOrResponse(CStoreResponse(command, dimseStatusCode_t::success));
}
    thread.join();

}


void moveScuThread()
{
    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::string command("movescu -v -k 0010,0020=\"100\" -P -aet scu -aec SCP -aem SCP1 127.0.0.1 30005");
    system(command.c_str());
}


//
// Move SCU interoperability test
//
// This executes the DCMTK command movescu and check that
// it is interpreted correctly by Imebra
//
///////////////////////////////////////////////////////////
TEST(dimseTest, moveSCPInteroperabilityTest)
{
    std::thread thread(
                imebra::tests::moveScuThread);

    {
        TCPListener tcpListener(TCPPassiveAddress("", "30005"));
        TCPStream tcpStream(tcpListener.waitForConnection());

        StreamReader readSCP(tcpStream.getStreamInput());
        StreamWriter writeSCP(tcpStream.getStreamOutput());

        PresentationContext context("1.2.840.10008.5.1.4.1.2.1.2");
        context.addTransferSyntax("1.2.840.10008.1.2.1"); // explicit VR little endian
        PresentationContexts presentationContexts;
        presentationContexts.addPresentationContext(context);

        AssociationSCP scp("SCP", 1, 1, presentationContexts, readSCP, writeSCP, 0, 10);
        DimseService dimse(scp);

        CMoveCommand move = dimse.getCommand().getAsCMoveCommand();

        EXPECT_EQ("SCP1", move.getDestinationAET());

        DataSet identifier = move.getPayloadDataSet();

        EXPECT_EQ("100", identifier.getString(TagId(tagId_t::PatientID_0010_0020), 0));

        dimse.sendCommandOrResponse(CMoveResponse(move, dimseStatusCode_t::pending, 1, 0, 0, 0));
        dimse.sendCommandOrResponse(CMoveResponse(move, dimseStatusCode_t::success, 0, 1, 0, 0));

        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
    thread.join();
}


//
// Executes a command and returns its output
//
///////////////////////////////////////////////////////////
std::string execute(const char* cmd)
{
    std::array<char, 128> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    if (!pipe) throw std::runtime_error("popen() failed!");
    while (!feof(pipe.get()))
    {
        if(fgets(buffer.data(), 128, pipe.get()) != nullptr)
        {
            result += buffer.data();
        }
    }
    return result;
}


void findScuThread(std::string* pResponse)
{
    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::string command("findscu -v -k 0010,0020=\"100\" -P -aet scu -aec SCP 127.0.0.1 30005 2>&1");
    *pResponse = execute(command.c_str());
}


//
// Find SCU interoperability test
//
// This executes the DCMTK command findscu and check that
// it is interpreted correctly by Imebra
//
///////////////////////////////////////////////////////////
TEST(dimseTest, findSCPInteroperabilityTest)
{
    std::string responseString;
    std::thread thread(imebra::tests::findScuThread, &responseString);

    {
        TCPListener tcpListener(TCPPassiveAddress("", "30005"));
        TCPStream tcpStream(tcpListener.waitForConnection());

        StreamReader readSCP(tcpStream.getStreamInput());
        StreamWriter writeSCP(tcpStream.getStreamOutput());

        PresentationContext context("1.2.840.10008.5.1.4.1.2.1.1");
        context.addTransferSyntax("1.2.840.10008.1.2.1"); // explicit VR little endian
        PresentationContexts presentationContexts;
        presentationContexts.addPresentationContext(context);

        AssociationSCP scp("SCP", 1, 1, presentationContexts, readSCP, writeSCP, 0, 10);
        DimseService dimse(scp);

        CFindCommand find = dimse.getCommand().getAsCFindCommand();

        DataSet identifier = find.getPayloadDataSet();

        EXPECT_EQ("100", identifier.getString(TagId(tagId_t::PatientID_0010_0020), 0));

        MutableDataSet study0(dimse.getTransferSyntax(find.getAbstractSyntax()));
        study0.setString(TagId(tagId_t::PatientID_0010_0020), "100");
        study0.setString(TagId(tagId_t::StudyID_0020_0010), "110");
        dimse.sendCommandOrResponse(CFindResponse(find, study0));

        MutableDataSet study1(dimse.getTransferSyntax(find.getAbstractSyntax()));
        study1.setString(TagId(tagId_t::PatientID_0010_0020), "100");
        study1.setString(TagId(tagId_t::StudyID_0020_0010), "120");
        dimse.sendCommandOrResponse(CFindResponse(find, study1));

        dimse.sendCommandOrResponse(CFindResponse(find, dimseStatusCode_t::success));

        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
    thread.join();

    EXPECT_NE(std::string::npos, responseString.find("110"));
    EXPECT_NE(std::string::npos, responseString.find("120"));
}


#endif // DISABLE_DCMTK_INTEROPERABILITY_TEST



} // namespace tests

} // namespace imebra
