#include <imebra/imebra.h>
#include <gtest/gtest.h>
#include <thread>
#include <memory>
#include <vector>
#include <fstream>
#include <sstream>
#include "testsSettings.h"

namespace imebra
{

namespace tests
{

void scpThread(
        const std::string& name,
        PresentationContexts& presentationContexts,
        StreamReader& readSCP, StreamWriter& writeSCP,
        const std::vector<std::string>& scpAbstractSyntaxes,
        const std::vector<std::string>& scpThrowAbstractSyntaxes)
{
    try
    {
        AssociationSCP scp(name, 1, 1, presentationContexts, readSCP, writeSCP, 0, 10);

        // First send commands for the presentation contexts in which
        // the SCU can act also as SCP
        std::uint16_t messageId(0);
        for(const std::string& abstractSyntax: scpAbstractSyntaxes)
        {
            std::vector<std::string> transferSyntaxes = scp.getTransferSyntaxes(abstractSyntax);
            for(const std::string& transferSyntax: transferSyntaxes)
            {
                // Send a C-Store command
                MutableAssociationMessage command(abstractSyntax);
                MutableDataSet dataset0(transferSyntax);
                dataset0.setUint32(TagId(tagId_t::CommandField_0000_0100), 0x1, tagVR_t::US);
                dataset0.setUint32(TagId(tagId_t::MessageID_0000_0110), messageId, tagVR_t::US);
                dataset0.setString(TagId(tagId_t::StudyInstanceUID_0020_000D), "1.2.3.4.5");
                dataset0.setUint32(TagId(tagId_t::CommandDataSetType_0000_0800), 0x101);
                command.addDataSet(dataset0);
                scp.sendMessage(command);
                scp.getResponse(messageId);
                messageId++;
            }
        }

        // First send commands for the presentation contexts in which
        // the SCU can act also as SCP
        for(const std::string& abstractSyntax: scpThrowAbstractSyntaxes)
        {
            std::vector<std::string> transferSyntaxes = scp.getTransferSyntaxes(abstractSyntax);
            for(const std::string& transferSyntax: transferSyntaxes)
            {
                // Send a C-Store command
                MutableAssociationMessage command(abstractSyntax);
                MutableDataSet dataset0(transferSyntax);
                dataset0.setUint32(TagId(tagId_t::CommandField_0000_0100), 0x1, tagVR_t::US);
                dataset0.setUint32(TagId(tagId_t::MessageID_0000_0110), messageId++, tagVR_t::US);
                dataset0.setString(TagId(tagId_t::StudyInstanceUID_0020_000D), "1.2.3.4.5");
                dataset0.setUint32(TagId(tagId_t::CommandDataSetType_0000_0800), 0x101);
                command.addDataSet(dataset0);
                EXPECT_THROW(scp.sendMessage(command), AcseWrongRoleError);
            }
        }

        for(;;)
        {
            AssociationMessage command = scp.getCommand();
            DataSet commandDataSet = command.getCommand();

            // First send a response with a wrong ID: it should throw
            {
                MutableDataSet responseDataSet;
                responseDataSet.setUint32(TagId(tagId_t::CommandField_0000_0100), 0x8001, tagVR_t::US);
                responseDataSet.setUint32(TagId(tagId_t::MessageIDBeingRespondedTo_0000_0120), 0xffff, tagVR_t::US);
                responseDataSet.setString(TagId(tagId_t::StudyInstanceUID_0020_000D), commandDataSet.getString(TagId(tagId_t::StudyInstanceUID_0020_000D), 0, ""));
                responseDataSet.setString(TagId(tagId_t::SeriesInstanceUID_0020_000E), "1.2.3.4.5");
                responseDataSet.setUint32(TagId(tagId_t::Status_0000_0900), 0x0000);
                MutableAssociationMessage response(command.getAbstractSyntax());
                response.addDataSet(responseDataSet);
                EXPECT_THROW(scp.sendMessage(response), AcseWrongResponseIdError);
            }

            // Now send the real response
            {
                MutableDataSet responseDataSet;
                responseDataSet.setUint32(TagId(tagId_t::CommandField_0000_0100), 0x8001, tagVR_t::US);
                std::uint32_t responseId(commandDataSet.getUint32(TagId(tagId_t::MessageID_0000_0110), 0));
                responseDataSet.setUint32(TagId(tagId_t::MessageIDBeingRespondedTo_0000_0120), responseId, tagVR_t::US);
                responseDataSet.setString(TagId(tagId_t::StudyInstanceUID_0020_000D), commandDataSet.getString(TagId(tagId_t::StudyInstanceUID_0020_000D), 0, ""));
                responseDataSet.setString(TagId(tagId_t::SeriesInstanceUID_0020_000E), "1.2.3.4.5");
                responseDataSet.setUint32(TagId(tagId_t::CommandDataSetType_0000_0800), command.hasPayload() ? 0 : 0x0101);
                responseDataSet.setUint32(TagId(tagId_t::Status_0000_0900), 0x0000);

                MutableAssociationMessage response(command.getAbstractSyntax());
                response.addDataSet(responseDataSet);

                if(command.hasPayload())
                {
                    DataSet payload = command.getPayload();
                    response.addDataSet(payload);
                }

                scp.sendMessage(response);

            }
        }
    }
    catch(const StreamClosedError&)
    {

    }
}


void scpThreadMultipleOperations(const std::string& name, PresentationContexts& presentationContexts, StreamReader& readSCP, StreamWriter& writeSCP, std::uint32_t maxPerformed)
{
    try
    {
        AssociationSCP scp(name, 1, maxPerformed, presentationContexts, readSCP, writeSCP, 0, 10);

        for(;;)
        {
            AssociationMessage command = scp.getCommand();

            {
                MutableDataSet responseDataSet;
                responseDataSet.setUint32(TagId(tagId_t::CommandField_0000_0100), 0x8001, tagVR_t::US);
                std::uint32_t messageId(command.getCommand().getUint32(TagId(tagId_t::MessageID_0000_0110), 0));
                responseDataSet.setUint32(TagId(tagId_t::MessageIDBeingRespondedTo_0000_0120), messageId, tagVR_t::US);
                responseDataSet.setString(TagId(tagId_t::SeriesInstanceUID_0020_000E), "1.2.3.4.5");
                responseDataSet.setUint32(TagId(tagId_t::CommandDataSetType_0000_0800), command.hasPayload() ? 0 : 0x0101);
                responseDataSet.setUint32(TagId(tagId_t::Status_0000_0900), 0x0000);

                MutableAssociationMessage response(command.getAbstractSyntax());
                response.addDataSet(responseDataSet);

                if(command.hasPayload())
                {
                    DataSet payload = command.getPayload();
                    response.addDataSet(payload);
                }

                scp.sendMessage(response);
            }
        }
    }
    catch(const StreamClosedError&)
    {

    }
}


void scpThreadRejectCalledAET(const std::string& name, PresentationContexts& presentationContexts, StreamReader& readSCP, StreamWriter& writeSCP)
{
    try
    {
        AssociationSCP scp(name, 1, 1, presentationContexts, readSCP, writeSCP, 0, 10);

        for(;;)
        {
            scp.getCommand();
        }
    }
    catch(const AcseSCUCalledAETNotRecognizedError&)
    {
    }
}


void scpThreadDontAnswer(const std::string& name, PresentationContexts& presentationContexts, StreamReader& readSCP, StreamWriter& writeSCP)
{
    try
    {
        AssociationSCP scp(name, 1, 1, presentationContexts, readSCP, writeSCP, 0, 10);

        for(;;)
        {
            scp.getCommand();
        }
    }
    catch(const StreamClosedError&)
    {

    }
}



//
// Negotiate one transfer syntax
//
///////////////////////////////////////////////////////////
TEST(acseTest, negotiationOneTransferSyntax)
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

    std::vector<std::string> scpAbstractSyntaxes;
    std::thread scp(imebra::tests::scpThread, std::ref(scpName), std::ref(presentationContexts), std::ref(readSCP), std::ref(writeSCP), std::ref(scpAbstractSyntaxes), std::ref(scpAbstractSyntaxes));

    AssociationSCU scu("SCU", scpName, 1, 1, presentationContexts, readSCU, writeSCU, 0);

    MutableAssociationMessage command("1.2.840.10008.1.1");
    MutableDataSet dataset0;
    dataset0.setUint32(TagId(tagId_t::CommandField_0000_0100), 0x1, tagVR_t::US);
    dataset0.setUint32(TagId(tagId_t::MessageID_0000_0110), 0x1, tagVR_t::US);
    dataset0.setString(TagId(tagId_t::StudyInstanceUID_0020_000D), "1.2.3.4");
    dataset0.setUint32(TagId(tagId_t::CommandDataSetType_0000_0800), 0x101);
    command.addDataSet(dataset0);
    scu.sendMessage(command);

    AssociationMessage response = scu.getResponse(1);
    DataSet responseDataSet = response.getCommand();
    EXPECT_EQ("1.2.3.4", responseDataSet.getString(TagId(tagId_t::StudyInstanceUID_0020_000D), 0));
    EXPECT_EQ("1.2.3.4.5", responseDataSet.getString(TagId(tagId_t::SeriesInstanceUID_0020_000E), 0));
    EXPECT_EQ("1.2.840.10008.1.2",responseDataSet.getString(TagId(tagId_t::TransferSyntaxUID_0002_0010), 0));

    scu.release();

    scp.join();
}


TEST(acseTest, scpScuRole)
{
    PipeStream toSCU(1024), toSCP(1024);

    StreamReader readSCU(toSCU.getStreamInput());
    StreamWriter writeSCU(toSCP.getStreamOutput());

    StreamReader readSCP(toSCP.getStreamInput());
    StreamWriter writeSCP(toSCU.getStreamOutput());

    PresentationContext context0(uidVerificationSOPClass_1_2_840_10008_1_1, false, true);
    context0.addTransferSyntax(uidImplicitVRLittleEndian_1_2_840_10008_1_2);
    context0.addTransferSyntax(uidExplicitVRBigEndian_1_2_840_10008_1_2_2);

    PresentationContext context1(uidVerificationSOPClass_1_2_840_10008_1_1);
    context1.addTransferSyntax(uidExplicitVRLittleEndian_1_2_840_10008_1_2_1);

    PresentationContext context2(uidHardcopyGrayscaleImageStorageSOPClass_1_2_840_10008_5_1_1_29);
    context2.addTransferSyntax(uidExplicitVRLittleEndian_1_2_840_10008_1_2_1);

    PresentationContext context3(uidHardcopyColorImageStorageSOPClass_1_2_840_10008_5_1_1_30, false, true);
    context3.addTransferSyntax(uidExplicitVRLittleEndian_1_2_840_10008_1_2_1);

    PresentationContexts presentationContexts;
    presentationContexts.addPresentationContext(context0);
    presentationContexts.addPresentationContext(context1);
    presentationContexts.addPresentationContext(context2);
    presentationContexts.addPresentationContext(context3);


    std::vector<std::string> scpAbstractSyntaxes;
    scpAbstractSyntaxes.push_back(uidVerificationSOPClass_1_2_840_10008_1_1);
    scpAbstractSyntaxes.push_back(uidHardcopyColorImageStorageSOPClass_1_2_840_10008_5_1_1_30);

    std::vector<std::string> scpThrowAbstractSyntaxes;
    scpThrowAbstractSyntaxes.push_back(uidHardcopyGrayscaleImageStorageSOPClass_1_2_840_10008_5_1_1_29);

    const std::string scpName("SCP");
    std::thread scp(imebra::tests::scpThread, std::ref(scpName), std::ref(presentationContexts), std::ref(readSCP), std::ref(writeSCP), std::ref(scpAbstractSyntaxes), std::ref(scpThrowAbstractSyntaxes));

    {
        AssociationSCU scu("SCU", scpName, 1, 1, presentationContexts, readSCU, writeSCU, 0);

        // Reply to the 2 commands sent by the SCU
        for(const std::string& abstractSyntax: scpAbstractSyntaxes)
        {
            for(const std::string& transferSyntax: scu.getTransferSyntaxes(abstractSyntax))
            {
                std::cout << "Waiting for command with abstract syntax " << abstractSyntax << " and transfer syntax " << transferSyntax << std::endl;
                AssociationMessage command = scu.getCommand();
                MutableDataSet responseDataSet;
                responseDataSet.setUint32(TagId(tagId_t::CommandField_0000_0100), 0x8001, tagVR_t::US);
                std::uint32_t messageId(command.getCommand().getUint32(TagId(tagId_t::MessageID_0000_0110), 0));
                responseDataSet.setUint32(TagId(tagId_t::MessageIDBeingRespondedTo_0000_0120), messageId, tagVR_t::US);
                responseDataSet.setString(TagId(tagId_t::SeriesInstanceUID_0020_000E), "1.2.3.4.5");
                responseDataSet.setUint32(TagId(tagId_t::CommandDataSetType_0000_0800), 0x0101);
                responseDataSet.setUint32(TagId(tagId_t::Status_0000_0900), 0x0000);
                MutableAssociationMessage response(abstractSyntax);
                response.addDataSet(responseDataSet);
                scu.sendMessage(response);
            }
        }

        // We can only receive uidHardcopyColorImageStorageSOPClass
        {
            MutableAssociationMessage command(uidHardcopyColorImageStorageSOPClass_1_2_840_10008_5_1_1_30);
            MutableDataSet dataset0;
            dataset0.setUint32(TagId(tagId_t::CommandField_0000_0100), 0x1, tagVR_t::US);
            dataset0.setUint32(TagId(tagId_t::MessageID_0000_0110), 0x1, tagVR_t::US);
            dataset0.setString(TagId(tagId_t::StudyInstanceUID_0020_000D), "1.2.3.4");
            dataset0.setUint32(TagId(tagId_t::CommandDataSetType_0000_0800), 0x101);
            command.addDataSet(dataset0);
            EXPECT_THROW(scu.sendMessage(command), AcseWrongRoleError);
        }

        // We can transmit uidVerificationSOPClass_1_2_840_10008_1_1
        // because one of the presentation contexts declared it as SCU
        {
            MutableAssociationMessage command(uidVerificationSOPClass_1_2_840_10008_1_1);
            MutableDataSet dataset0;
            dataset0.setUint32(TagId(tagId_t::CommandField_0000_0100), 0x1, tagVR_t::US);
            dataset0.setUint32(TagId(tagId_t::MessageID_0000_0110), 0x2, tagVR_t::US);
            dataset0.setString(TagId(tagId_t::StudyInstanceUID_0020_000D), "1.2.3.4");
            dataset0.setUint32(TagId(tagId_t::CommandDataSetType_0000_0800), 0);
            command.addDataSet(dataset0);
            MutableDataSet dataset1(uidExplicitVRLittleEndian_1_2_840_10008_1_2_1);
            dataset1.setString(TagId(tagId_t::PatientName_0010_0010), "Test");
            command.addDataSet(dataset1);
            scu.sendMessage(command);

            AssociationMessage response = scu.getResponse(0x2);

        }

        scu.release();
    }
    scp.join();
}


TEST(acseTest, negotiationMultipleTransferSyntaxes)
{
    PipeStream toSCU(1024), toSCP(1024);

    StreamReader readSCU(toSCU.getStreamInput());
    StreamWriter writeSCU(toSCP.getStreamOutput());

    StreamReader readSCP(toSCP.getStreamInput());
    StreamWriter writeSCP(toSCU.getStreamOutput());

    PresentationContext context("1.2.840.10008.1.1");
    context.addTransferSyntax("1.2.840.10008.1.2"); // implicit VR little endian
    context.addTransferSyntax("1.2.840.10008.1.2.1"); // explicit VR little endian
    PresentationContexts presentationContexts;
    presentationContexts.addPresentationContext(context);

    const std::string scpName("SCP");

    std::vector<std::string> scpAbstractSyntaxes;
    std::thread scp(imebra::tests::scpThread, std::ref(scpName), std::ref(presentationContexts), std::ref(readSCP), std::ref(writeSCP), std::ref(scpAbstractSyntaxes), std::ref(scpAbstractSyntaxes));

    AssociationSCU scu("SCU", scpName, 1, 1, presentationContexts, readSCU, writeSCU, 0);

    MutableAssociationMessage command("1.2.840.10008.1.1");
    MutableDataSet dataset0;
    dataset0.setUint32(TagId(tagId_t::CommandField_0000_0100), 0x1, tagVR_t::US);
    dataset0.setUint32(TagId(tagId_t::MessageID_0000_0110), 0x1, tagVR_t::US);
    dataset0.setString(TagId(tagId_t::StudyInstanceUID_0020_000D), "1.2.3.4");
    dataset0.setUint32(TagId(tagId_t::CommandDataSetType_0000_0800), 0x101);
    command.addDataSet(dataset0);
    scu.sendMessage(command);

    AssociationMessage response = scu.getResponse(1);
    DataSet responseDataSet = response.getCommand();
    EXPECT_EQ("1.2.3.4", responseDataSet.getString(TagId(tagId_t::StudyInstanceUID_0020_000D), 0));
    EXPECT_EQ("1.2.3.4.5", responseDataSet.getString(TagId(tagId_t::SeriesInstanceUID_0020_000E), 0));
    EXPECT_EQ("1.2.840.10008.1.2",responseDataSet.getString(TagId(tagId_t::TransferSyntaxUID_0002_0010), 0));

    scu.release();

    scp.join();
}


TEST(acseTest, negotiationPartialMatchTransferSyntaxes)
{
    PipeStream toSCU(1024), toSCP(1024);

    StreamReader readSCU(toSCU.getStreamInput());
    StreamWriter writeSCU(toSCP.getStreamOutput());

    StreamReader readSCP(toSCP.getStreamInput());
    StreamWriter writeSCP(toSCU.getStreamOutput());

    PresentationContext scuContext0("1.2.840.10008.1.1");
    scuContext0.addTransferSyntax("1.2.840.10008.1.2"); // implicit VR little endian
    scuContext0.addTransferSyntax("1.2.840.10008.1.2.1"); // explicit VR little endian

    PresentationContext scuContext1("1.2.840.10008.1.1.1.1.1.1.1.1"); // This will be rejected
    scuContext1.addTransferSyntax("1.2.840.10008.1.2"); // implicit VR little endian
    scuContext1.addTransferSyntax("1.2.840.10008.1.2.1"); // explicit VR little endian

    PresentationContexts scuPresentationContexts;
    scuPresentationContexts.addPresentationContext(scuContext0);
    scuPresentationContexts.addPresentationContext(scuContext1);

    PresentationContext scpContext("1.2.840.10008.1.1");
    scpContext.addTransferSyntax("1.2.840.10008.1.2.1"); // explicit VR little endian

    PresentationContexts scpPresentationContexts;
    scpPresentationContexts.addPresentationContext(scpContext);

    const std::string scpName("SCP");

    std::vector<std::string> scpAbstractSyntaxes;
    std::thread scp(imebra::tests::scpThread, std::ref(scpName), std::ref(scpPresentationContexts), std::ref(readSCP), std::ref(writeSCP), std::ref(scpAbstractSyntaxes), std::ref(scpAbstractSyntaxes));

    AssociationSCU scu("SCU", scpName, 1, 1, scuPresentationContexts, readSCU, writeSCU, 0);

    EXPECT_EQ("1.2.840.10008.1.2.1", scu.getTransferSyntax("1.2.840.10008.1.1"));
    EXPECT_THROW(scu.getTransferSyntax("1.2.840.10008.1.1.1.1.1.1.1.1"), AcseNoTransferSyntaxError);
    EXPECT_THROW(scu.getTransferSyntax("1"), AcsePresentationContextNotRequestedError);

    MutableAssociationMessage command("1.2.840.10008.1.1");
    MutableDataSet dataset0;
    dataset0.setUint32(TagId(tagId_t::CommandField_0000_0100), 0x1, tagVR_t::US);
    dataset0.setUint32(TagId(tagId_t::MessageID_0000_0110), 0x1, tagVR_t::US);
    dataset0.setString(TagId(tagId_t::StudyInstanceUID_0020_000D), "1.2.3.4");
    dataset0.setUint32(TagId(tagId_t::CommandDataSetType_0000_0800), 0x101);

    command.addDataSet(dataset0);
    scu.sendMessage(command);

    AssociationMessage response = scu.getResponse(1);
    DataSet responseDataSet = response.getCommand();
    EXPECT_EQ("1.2.840.10008.1.1", response.getAbstractSyntax());
    EXPECT_EQ("1.2.3.4", responseDataSet.getString(TagId(tagId_t::StudyInstanceUID_0020_000D), 0));
    EXPECT_EQ("1.2.3.4.5", responseDataSet.getString(TagId(tagId_t::SeriesInstanceUID_0020_000E), 0));
    EXPECT_EQ("1.2.840.10008.1.2.1",responseDataSet.getString(TagId(tagId_t::TransferSyntaxUID_0002_0010), 0));

    scu.release();

    scp.join();
}


/**
 * @brief Test that the SCP can accept all the transfer syntax even
 *        if the SCU spread them on different presentation contexts
 *        with the same abstract syntax.
 */
TEST(acseTest, negotiationPartialMatchSameAbstractSyntax)
{
    PipeStream toSCU(1024), toSCP(1024);

    StreamReader readSCU(toSCU.getStreamInput());
    StreamWriter writeSCU(toSCP.getStreamOutput());

    StreamReader readSCP(toSCP.getStreamInput());
    StreamWriter writeSCP(toSCU.getStreamOutput());

    PresentationContext scuContext0("1.2.840.10008.1.1");
    scuContext0.addTransferSyntax("1.2.840.10008.1.2"); // implicit VR little endian
    scuContext0.addTransferSyntax("1.2.840.10008.1.2.1"); // explicit VR little endian

    PresentationContext scuContext1("1.2.840.10008.1.1");
    scuContext1.addTransferSyntax("1.2.840.10008.1.2.4.50"); // jpeg baseline

    PresentationContext scuContext2("1.2.840.10008.1.1.1.1.1.1.1.1"); // This will be rejected
    scuContext2.addTransferSyntax("1.2.840.10008.1.2"); // implicit VR little endian
    scuContext2.addTransferSyntax("1.2.840.10008.1.2.1"); // explicit VR little endian

    PresentationContexts scuPresentationContexts;
    scuPresentationContexts.addPresentationContext(scuContext0);
    scuPresentationContexts.addPresentationContext(scuContext1);
    scuPresentationContexts.addPresentationContext(scuContext2);

    PresentationContext scpContext("1.2.840.10008.1.1");
    scpContext.addTransferSyntax("1.2.840.10008.1.2.1"); // explicit VR little endian
    scpContext.addTransferSyntax("1.2.840.10008.1.2.4.50"); // jpeg baseline

    PresentationContexts scpPresentationContexts;
    scpPresentationContexts.addPresentationContext(scpContext);

    const std::string scpName("SCP");

    std::vector<std::string> scpAbstractSyntaxes;
    std::thread scp(imebra::tests::scpThread, std::ref(scpName), std::ref(scpPresentationContexts), std::ref(readSCP), std::ref(writeSCP), std::ref(scpAbstractSyntaxes), std::ref(scpAbstractSyntaxes));

    AssociationSCU scu("SCU", scpName, 1, 1, scuPresentationContexts, readSCU, writeSCU, 0);

    std::vector<std::string> acceptedTransferSyntaxes(scu.getTransferSyntaxes("1.2.840.10008.1.1"));
    EXPECT_EQ(2u, acceptedTransferSyntaxes.size());

    EXPECT_EQ("1.2.840.10008.1.2.1", scu.getTransferSyntax("1.2.840.10008.1.1"));
    EXPECT_THROW(scu.getTransferSyntax("1.2.840.10008.1.1.1.1.1.1.1.1"), AcseNoTransferSyntaxError);
    EXPECT_THROW(scu.getTransferSyntax("1"), AcsePresentationContextNotRequestedError);

    {
        MutableAssociationMessage command("1.2.840.10008.1.1");
        MutableDataSet dataset0;
        dataset0.setUint32(TagId(tagId_t::CommandField_0000_0100), 0x1, tagVR_t::US);
        dataset0.setUint32(TagId(tagId_t::MessageID_0000_0110), 0x1, tagVR_t::US);
        dataset0.setString(TagId(tagId_t::StudyInstanceUID_0020_000D), "1.2.3.4");
        dataset0.setUint32(TagId(tagId_t::CommandDataSetType_0000_0800), 0x101);

        command.addDataSet(dataset0);
        scu.sendMessage(command);

        AssociationMessage response = scu.getResponse(1);
        DataSet responseDataSet = response.getCommand();
        EXPECT_EQ("1.2.840.10008.1.1", response.getAbstractSyntax());
        EXPECT_EQ("1.2.3.4", responseDataSet.getString(TagId(tagId_t::StudyInstanceUID_0020_000D), 0));
        EXPECT_EQ("1.2.3.4.5", responseDataSet.getString(TagId(tagId_t::SeriesInstanceUID_0020_000E), 0));
        EXPECT_EQ("1.2.840.10008.1.2.1",responseDataSet.getString(TagId(tagId_t::TransferSyntaxUID_0002_0010), 0));
    }

    {
        MutableAssociationMessage command("1.2.840.10008.1.1");
        MutableDataSet dataset0("1.2.840.10008.1.2.4.50");
        dataset0.setUint32(TagId(tagId_t::CommandField_0000_0100), 0x1, tagVR_t::US);
        dataset0.setUint32(TagId(tagId_t::MessageID_0000_0110), 0x1, tagVR_t::US);
        dataset0.setString(TagId(tagId_t::StudyInstanceUID_0020_000D), "1.2.3.4");
        dataset0.setUint32(TagId(tagId_t::CommandDataSetType_0000_0800), 0x101);

        command.addDataSet(dataset0);
        scu.sendMessage(command);

        AssociationMessage response = scu.getResponse(1);
        DataSet responseDataSet = response.getCommand();
        EXPECT_EQ("1.2.840.10008.1.1", response.getAbstractSyntax());
        EXPECT_EQ("1.2.3.4", responseDataSet.getString(TagId(tagId_t::StudyInstanceUID_0020_000D), 0));
        EXPECT_EQ("1.2.3.4.5", responseDataSet.getString(TagId(tagId_t::SeriesInstanceUID_0020_000E), 0));
        EXPECT_EQ("1.2.840.10008.1.2.1",responseDataSet.getString(TagId(tagId_t::TransferSyntaxUID_0002_0010), 0));
    }

    scu.release();

    scp.join();
}



TEST(acseTest, sendPayload)
{
    PipeStream toSCU(1024), toSCP(1024);

    StreamReader readSCU(toSCU.getStreamInput());
    StreamWriter writeSCU(toSCP.getStreamOutput());

    StreamReader readSCP(toSCP.getStreamInput());
    StreamWriter writeSCP(toSCU.getStreamOutput());

    PresentationContext scuContext("1.2.840.10008.1.1");
    scuContext.addTransferSyntax("1.2.840.10008.1.2"); // implicit VR little endian
    scuContext.addTransferSyntax("1.2.840.10008.1.2.1"); // explicit VR little endian
    PresentationContexts scuPresentationContexts;
    scuPresentationContexts.addPresentationContext(scuContext);

    PresentationContext scpContext("1.2.840.10008.1.1");
    scpContext.addTransferSyntax("1.2.840.10008.1.2.1"); // explicit VR little endian
    PresentationContexts scpPresentationContexts;
    scpPresentationContexts.addPresentationContext(scpContext);

    const std::string scpName("SCP");

    const size_t maxPayloadSize(128000);

    std::vector<std::string> scpAbstractSyntaxes;
    std::thread scp(imebra::tests::scpThread, std::ref(scpName), std::ref(scpPresentationContexts), std::ref(readSCP), std::ref(writeSCP), std::ref(scpAbstractSyntaxes), std::ref(scpAbstractSyntaxes));

    try{

    {
        AssociationSCU scu("SCU", scpName, 1, 1, scuPresentationContexts, readSCU, writeSCU, 0);

        for(size_t payloadSize(1); payloadSize < maxPayloadSize; payloadSize += 128)
        {
            MutableAssociationMessage command("1.2.840.10008.1.1");

            MutableDataSet dataset0;
            dataset0.setUint32(TagId(tagId_t::CommandField_0000_0100), 0x1, tagVR_t::US);
            dataset0.setUint32(TagId(tagId_t::MessageID_0000_0110), 0x1, tagVR_t::US);
            dataset0.setUint32(TagId(tagId_t::CommandDataSetType_0000_0800), 0);

            command.addDataSet(dataset0);

            MutableDataSet payload(scu.getTransferSyntax("1.2.840.10008.1.1"));
            {
                WritingDataHandlerNumeric writing = payload.getWritingDataHandlerRaw(TagId(tagId_t::PixelData_7FE0_0010), 0, tagVR_t::OB);
                writing.setSize(payloadSize);
                size_t dummy;
                char* payloadData(writing.data(&dummy));
                for(size_t fillPayload(0); fillPayload != payloadSize; ++fillPayload)
                {
                    payloadData[fillPayload] = (char)(fillPayload & 0x7f);
                }
            }
            command.addDataSet(payload);

            scu.sendMessage(command);

            AssociationMessage response = scu.getResponse(1);
            DataSet responsePayload = response.getPayload();

            EXPECT_EQ("1.2.840.10008.1.1", response.getAbstractSyntax());
            {
                ReadingDataHandlerNumeric reading = responsePayload.getReadingDataHandlerRaw(TagId(tagId_t::PixelData_7FE0_0010), 0);
                size_t dummy;
                const char* payloadData(reading.data(&dummy));
                for(size_t fillPayload(0); fillPayload != payloadSize; ++fillPayload)
                {
                    EXPECT_EQ(payloadData[fillPayload], (char)(fillPayload & 0x7f));
                }
                EXPECT_EQ(reading.getSize(), (payloadSize + 1) & 0xfffffffe);
            }
        }
        scu.release();
    }

    }
    catch(std::runtime_error& e)
    {
        std::cout << e.what() << std::endl;
    }


    scp.join();
}


void scuThread(AssociationSCU& scu, std::uint16_t firstMessageId, size_t numberOfMessages)
{
    const size_t payloadSize(100);

    for(std::uint16_t messageNumber(0); messageNumber != numberOfMessages; ++messageNumber)
    {
        MutableAssociationMessage command("1.2.840.10008.1.1");

        MutableDataSet dataset0;
        dataset0.setUint32(TagId(tagId_t::CommandField_0000_0100), 0x1, tagVR_t::US);
        dataset0.setUint32(TagId(tagId_t::MessageID_0000_0110), (std::uint16_t)(firstMessageId + messageNumber), tagVR_t::US);
        dataset0.setUint32(TagId(tagId_t::CommandDataSetType_0000_0800), 0);

        command.addDataSet(dataset0);

        MutableDataSet payload("1.2.840.10008.1.2.1");
        {
            WritingDataHandlerNumeric writing(payload.getWritingDataHandlerRaw(TagId(tagId_t::PixelData_7FE0_0010), 0, tagVR_t::OB));
            writing.setSize(payloadSize);
            size_t dummy;
            char* payloadData(writing.data(&dummy));
            for(size_t fillPayload(0); fillPayload != payloadSize; ++fillPayload)
            {
                payloadData[fillPayload] = (char)((fillPayload + firstMessageId) & 0x7f);
            }
        }
        command.addDataSet(payload);

        scu.sendMessage(command);

        AssociationMessage response = scu.getResponse((std::uint16_t)(firstMessageId + messageNumber));
        DataSet responsePayload = response.getPayload();

        EXPECT_EQ("1.2.840.10008.1.1", response.getAbstractSyntax());
        {
            ReadingDataHandlerNumeric reading(responsePayload.getReadingDataHandlerRaw(TagId(tagId_t::PixelData_7FE0_0010), 0));
            size_t dummy;
            const char* payloadData(reading.data(&dummy));
            for(size_t fillPayload(0); fillPayload != payloadSize; ++fillPayload)
            {
                EXPECT_EQ(payloadData[fillPayload], (char)((fillPayload + firstMessageId) & 0x7f));
            }
            EXPECT_EQ(reading.getSize(), (payloadSize + 1) & 0xfffffffe);
        }
    }
}


TEST(acseTest, overlappingOperations)
{
    PipeStream toSCU(1024), toSCP(1024);

    StreamReader readSCU(toSCU.getStreamInput());
    StreamWriter writeSCU(toSCP.getStreamOutput());

    StreamReader readSCP(toSCP.getStreamInput());
    StreamWriter writeSCP(toSCU.getStreamOutput());

    PresentationContext scuContext("1.2.840.10008.1.1");
    scuContext.addTransferSyntax("1.2.840.10008.1.2"); // implicit VR little endian
    scuContext.addTransferSyntax("1.2.840.10008.1.2.1"); // explicit VR little endian
    PresentationContexts scuPresentationContexts;
    scuPresentationContexts.addPresentationContext(scuContext);

    PresentationContext scpContext("1.2.840.10008.1.1");
    scpContext.addTransferSyntax("1.2.840.10008.1.2.1"); // explicit VR little endian
    PresentationContexts scpPresentationContexts;
    scpPresentationContexts.addPresentationContext(scpContext);

    const std::string scpName("SCP");

    const std::uint32_t maxInvoked(10u);
    const size_t numMessages(1000u);

    std::thread scp(imebra::tests::scpThreadMultipleOperations, std::ref(scpName), std::ref(scpPresentationContexts), std::ref(readSCP), std::ref(writeSCP), maxInvoked);

    {
        AssociationSCU scu("SCU", scpName, maxInvoked, 1u, scuPresentationContexts, readSCU, writeSCU, 0);

        std::vector<std::shared_ptr<std::thread> > scuThreads;

        for(std::uint16_t launchThreads(0); launchThreads != maxInvoked; ++launchThreads)
        {
            scuThreads.push_back(std::make_shared<std::thread>(imebra::tests::scuThread, std::ref(scu), static_cast<std::uint16_t>(launchThreads * numMessages), numMessages));
        }

        for(size_t launchThreads(0); launchThreads != maxInvoked; ++launchThreads)
        {
            scuThreads[launchThreads]->join();
        }

        scu.release();
    }

    scp.join();
}


TEST(acseTest, negotiationMultiplePresentationContexts)
{
    PipeStream toSCU(1024), toSCP(1024);

    StreamReader readSCU(toSCU.getStreamInput());
    StreamWriter writeSCU(toSCP.getStreamOutput());

    StreamReader readSCP(toSCP.getStreamInput());
    StreamWriter writeSCP(toSCU.getStreamOutput());

    PresentationContext scuContext0("1.2.840.10008.1.1");
    scuContext0.addTransferSyntax("1.2.840.10008.1.2"); // implicit VR little endian
    scuContext0.addTransferSyntax("1.2.840.10008.1.2.1"); // explicit VR little endian
    PresentationContext scuContext1("1.2.840.10008.1.1.2");
    scuContext1.addTransferSyntax("1.2.840.10008.1.2"); // implicit VR little endian
    scuContext1.addTransferSyntax("1.2.840.10008.1.2.1"); // explicit VR little endian

    PresentationContexts scuPresentationContexts;
    scuPresentationContexts.addPresentationContext(scuContext0);
    scuPresentationContexts.addPresentationContext(scuContext1);

    PresentationContext scpContext0("1.2.840.10008.1.1");
    scpContext0.addTransferSyntax("1.2.840.10008.1.2.1"); // explicit VR little endian
    PresentationContext scpContext1("1.2.840.10008.1.1.2");
    scpContext1.addTransferSyntax("1.2.840.10008.1.2"); // implicit VR little endian

    PresentationContexts scpPresentationContexts;
    scpPresentationContexts.addPresentationContext(scpContext0);
    scpPresentationContexts.addPresentationContext(scpContext1);

    const std::string scpName("SCP");

    std::vector<std::string> scpAbstractSyntaxes;
    std::thread scp(imebra::tests::scpThread, std::ref(scpName), std::ref(scpPresentationContexts), std::ref(readSCP), std::ref(writeSCP), std::ref(scpAbstractSyntaxes), std::ref(scpAbstractSyntaxes));

    AssociationSCU scu("SCU", scpName, 1, 1, scuPresentationContexts, readSCU, writeSCU, 0);

    {
        MutableAssociationMessage command("1.2.840.10008.1.1");
        MutableDataSet dataset0;
        dataset0.setUint32(TagId(tagId_t::CommandField_0000_0100), 0x1, tagVR_t::US);
        dataset0.setUint32(TagId(tagId_t::MessageID_0000_0110), 0x1, tagVR_t::US);
        dataset0.setString(TagId(tagId_t::StudyInstanceUID_0020_000D), "1.2.3.4");
        dataset0.setUint32(TagId(tagId_t::CommandDataSetType_0000_0800), 0x101);

        command.addDataSet(dataset0);
        scu.sendMessage(command);

        AssociationMessage response = scu.getResponse(1);
        DataSet responseDataSet(response.getCommand());
        EXPECT_EQ("1.2.840.10008.1.1", response.getAbstractSyntax());
        EXPECT_EQ("1.2.3.4", responseDataSet.getString(TagId(tagId_t::StudyInstanceUID_0020_000D), 0));
        EXPECT_EQ("1.2.3.4.5", responseDataSet.getString(TagId(tagId_t::SeriesInstanceUID_0020_000E), 0));
        EXPECT_EQ("1.2.840.10008.1.2.1",responseDataSet.getString(TagId(tagId_t::TransferSyntaxUID_0002_0010), 0));
    }

    {
        MutableAssociationMessage command("1.2.840.10008.1.1.2");
        MutableDataSet dataset0;
        dataset0.setUint32(TagId(tagId_t::CommandField_0000_0100), 0x1, tagVR_t::US);
        dataset0.setUint32(TagId(tagId_t::MessageID_0000_0110), 0x1, tagVR_t::US);
        dataset0.setString(TagId(tagId_t::StudyInstanceUID_0020_000D), "1.2.3.4");
        dataset0.setUint32(TagId(tagId_t::CommandDataSetType_0000_0800), 0x101);

        command.addDataSet(dataset0);
        scu.sendMessage(command);

        AssociationMessage response = scu.getResponse(1);
        DataSet responseDataSet = response.getCommand();
        EXPECT_EQ("1.2.840.10008.1.1.2", response.getAbstractSyntax());
        EXPECT_EQ("1.2.3.4", responseDataSet.getString(TagId(tagId_t::StudyInstanceUID_0020_000D), 0));
        EXPECT_EQ("1.2.3.4.5", responseDataSet.getString(TagId(tagId_t::SeriesInstanceUID_0020_000E), 0));
        EXPECT_EQ("1.2.840.10008.1.2",responseDataSet.getString(TagId(tagId_t::TransferSyntaxUID_0002_0010), 0));
    }

    scu.release();

    scp.join();

#if defined(IMEBRA_LOGGING_LOG4CXX)
    ::tests::settings& settings = ::tests::settings::getSettings();
    if(!settings.get("--testLogFile").empty())
    {
        std::ifstream logFile(settings.get("--testLogFile"));
        std::ostringstream readLog;
        readLog <<  logFile.rdbuf();
        std::string logContent(readLog.str());
        EXPECT_TRUE(logContent.find("Presentation context ID = 1") != std::string::npos);
        EXPECT_TRUE(logContent.find("Presentation context ID = 3") != std::string::npos);
        EXPECT_TRUE(logContent.find("Presentation context ID = 2") == std::string::npos);
    }
#endif

}


TEST(acseTest, negotiationNoTransferSyntax)
{
    PipeStream toSCU(1024), toSCP(1024);

    StreamReader readSCU(toSCU.getStreamInput());
    StreamWriter writeSCU(toSCP.getStreamOutput());

    StreamReader readSCP(toSCP.getStreamInput());
    StreamWriter writeSCP(toSCU.getStreamOutput());

    PresentationContext scuContext0("1.2.840.10008.1.1");
    scuContext0.addTransferSyntax("1.2.840.10008.1.2"); // implicit VR little endian
    scuContext0.addTransferSyntax("1.2.840.10008.1.2.1"); // explicit VR little endian
    PresentationContext scuContext1("1.2.840.10008.1.1.2");
    scuContext1.addTransferSyntax("1.2.840.10008.1.2"); // implicit VR little endian

    PresentationContexts scuPresentationContexts;
    scuPresentationContexts.addPresentationContext(scuContext0);
    scuPresentationContexts.addPresentationContext(scuContext1);

    PresentationContext scpContext0("1.2.840.10008.1.1");
    scpContext0.addTransferSyntax("1.2.840.10008.1.2.1"); // explicit VR little endian
    PresentationContext scpContext1("1.2.840.10008.1.1.2");
    scpContext1.addTransferSyntax("1.2.840.10008.1.2.1"); // explicit VR little endian

    PresentationContexts scpPresentationContexts;
    scpPresentationContexts.addPresentationContext(scpContext0);
    scpPresentationContexts.addPresentationContext(scpContext1);

    const std::string scpName("SCP");

    std::vector<std::string> scpAbstractSyntaxes;
    std::thread scp(imebra::tests::scpThread, std::ref(scpName), std::ref(scpPresentationContexts), std::ref(readSCP), std::ref(writeSCP), std::ref(scpAbstractSyntaxes), std::ref(scpAbstractSyntaxes));

    AssociationSCU scu("SCU", scpName, 1, 1, scuPresentationContexts, readSCU, writeSCU, 0);

    {
        MutableAssociationMessage command("1.2.840.10008.1.1");
        MutableDataSet dataset0;
        dataset0.setUint32(TagId(tagId_t::CommandField_0000_0100), 0x1, tagVR_t::US);
        dataset0.setUint32(TagId(tagId_t::MessageID_0000_0110), 0x1, tagVR_t::US);
        dataset0.setString(TagId(tagId_t::StudyInstanceUID_0020_000D), "1.2.3.4");
        dataset0.setUint32(TagId(tagId_t::CommandDataSetType_0000_0800), 0x101);

        command.addDataSet(dataset0);
        scu.sendMessage(command);

        AssociationMessage response = scu.getResponse(1);
        DataSet responseDataSet = response.getCommand();
        EXPECT_EQ("1.2.840.10008.1.1", response.getAbstractSyntax());
        EXPECT_EQ("1.2.3.4", responseDataSet.getString(TagId(tagId_t::StudyInstanceUID_0020_000D), 0));
        EXPECT_EQ("1.2.3.4.5", responseDataSet.getString(TagId(tagId_t::SeriesInstanceUID_0020_000E), 0));
        EXPECT_EQ("1.2.840.10008.1.2.1",responseDataSet.getString(TagId(tagId_t::TransferSyntaxUID_0002_0010), 0));
    }

    {
        // This should fail (no transfer syntax)
        MutableAssociationMessage command("1.2.840.10008.1.1.2");
        MutableDataSet dataset0;
        dataset0.setUint32(TagId(tagId_t::CommandField_0000_0100), 0x1, tagVR_t::US);
        dataset0.setUint32(TagId(tagId_t::MessageID_0000_0110), 0x1, tagVR_t::US);
        dataset0.setString(TagId(tagId_t::StudyInstanceUID_0020_000D), "1.2.3.4");
        dataset0.setUint32(TagId(tagId_t::CommandDataSetType_0000_0800), 0x101);
        command.addDataSet(dataset0);

        EXPECT_THROW(scu.sendMessage(command), AcseNoTransferSyntaxError);

    }

    {
        MutableAssociationMessage command("1.2.840.10008.1.1");
        MutableDataSet dataset0;
        dataset0.setUint32(TagId(tagId_t::CommandField_0000_0100), 0x1, tagVR_t::US);
        dataset0.setUint32(TagId(tagId_t::MessageID_0000_0110), 0x1, tagVR_t::US);
        dataset0.setString(TagId(tagId_t::StudyInstanceUID_0020_000D), "1.2.3.4.7");
        dataset0.setUint32(TagId(tagId_t::CommandDataSetType_0000_0800), 0x101);

        command.addDataSet(dataset0);
        scu.sendMessage(command);

        AssociationMessage response = scu.getResponse(1);
        DataSet responseDataSet = response.getCommand();
        EXPECT_EQ("1.2.840.10008.1.1", response.getAbstractSyntax());
        EXPECT_EQ("1.2.3.4.7", responseDataSet.getString(TagId(tagId_t::StudyInstanceUID_0020_000D), 0));
        EXPECT_EQ("1.2.3.4.5", responseDataSet.getString(TagId(tagId_t::SeriesInstanceUID_0020_000E), 0));
        EXPECT_EQ("1.2.840.10008.1.2.1",responseDataSet.getString(TagId(tagId_t::TransferSyntaxUID_0002_0010), 0));
    }

    scu.release();

    scp.join();
}


TEST(acseTest, negotiationNoPresentationContext)
{
    PipeStream toSCU(1024), toSCP(1024);

    StreamReader readSCU(toSCU.getStreamInput());
    StreamWriter writeSCU(toSCP.getStreamOutput());

    StreamReader readSCP(toSCP.getStreamInput());
    StreamWriter writeSCP(toSCU.getStreamOutput());

    PresentationContext scuContext0("1.2.840.10008.1.1");
    scuContext0.addTransferSyntax("1.2.840.10008.1.2"); // implicit VR little endian
    scuContext0.addTransferSyntax("1.2.840.10008.1.2.1"); // explicit VR little endian
    PresentationContext scuContext1("1.2.840.10008.1.1.2");
    scuContext1.addTransferSyntax("1.2.840.10008.1.2"); // implicit VR little endian

    PresentationContexts scuPresentationContexts;
    scuPresentationContexts.addPresentationContext(scuContext0);
    scuPresentationContexts.addPresentationContext(scuContext1);

    PresentationContext scpContext0("1.2.840.10008.1.1");
    scpContext0.addTransferSyntax("1.2.840.10008.1.2.1"); // explicit VR little endian

    PresentationContexts scpPresentationContexts;
    scpPresentationContexts.addPresentationContext(scpContext0);

    const std::string scpName("SCP");

    std::vector<std::string> scpAbstractSyntaxes;
    std::thread scp(imebra::tests::scpThread, std::ref(scpName), std::ref(scpPresentationContexts), std::ref(readSCP), std::ref(writeSCP), std::ref(scpAbstractSyntaxes), std::ref(scpAbstractSyntaxes));

    AssociationSCU scu("SCU", scpName, 1, 1, scuPresentationContexts, readSCU, writeSCU, 0);

    {
        MutableAssociationMessage command("1.2.840.10008.1.1");
        MutableDataSet dataset0;
        dataset0.setUint32(TagId(tagId_t::CommandField_0000_0100), 0x1, tagVR_t::US);
        dataset0.setUint32(TagId(tagId_t::MessageID_0000_0110), 0x1, tagVR_t::US);
        dataset0.setString(TagId(tagId_t::StudyInstanceUID_0020_000D), "1.2.3.4");
        dataset0.setUint32(TagId(tagId_t::CommandDataSetType_0000_0800), 0x101);

        command.addDataSet(dataset0);
        scu.sendMessage(command);

        AssociationMessage response = scu.getResponse(1);
        DataSet responseDataSet = response.getCommand();
        EXPECT_EQ("1.2.840.10008.1.1", response.getAbstractSyntax());
        EXPECT_EQ("1.2.3.4", responseDataSet.getString(TagId(tagId_t::StudyInstanceUID_0020_000D), 0));
        EXPECT_EQ("1.2.3.4.5", responseDataSet.getString(TagId(tagId_t::SeriesInstanceUID_0020_000E), 0));
        EXPECT_EQ("1.2.840.10008.1.2.1",responseDataSet.getString(TagId(tagId_t::TransferSyntaxUID_0002_0010), 0));
    }

    {
        // This should fail (no presentation context in scp)
        MutableAssociationMessage command("1.2.840.10008.1.1.2");
        MutableDataSet dataset0;
        dataset0.setUint32(TagId(tagId_t::CommandField_0000_0100), 0x1, tagVR_t::US);
        dataset0.setUint32(TagId(tagId_t::MessageID_0000_0110), 0x1, tagVR_t::US);
        dataset0.setString(TagId(tagId_t::StudyInstanceUID_0020_000D), "1.2.3.4");
        dataset0.setUint32(TagId(tagId_t::CommandDataSetType_0000_0800), 0x101);

        command.addDataSet(dataset0);
        EXPECT_THROW(scu.sendMessage(command), AcseNoTransferSyntaxError);

    }

    {
        // This should fail (no presentation context in scu)
        MutableAssociationMessage command("1.2.840.10008.1.1.3");
        MutableDataSet dataset0;
        dataset0.setUint32(TagId(tagId_t::CommandField_0000_0100), 0x1, tagVR_t::US);
        dataset0.setUint32(TagId(tagId_t::MessageID_0000_0110), 0x1, tagVR_t::US);
        dataset0.setString(TagId(tagId_t::StudyInstanceUID_0020_000D), "1.2.3.4");
        dataset0.setUint32(TagId(tagId_t::CommandDataSetType_0000_0800), 0x101);

        command.addDataSet(dataset0);
        EXPECT_THROW(scu.sendMessage(command), AcsePresentationContextNotRequestedError);

    }

    {
        MutableAssociationMessage command("1.2.840.10008.1.1");
        MutableDataSet dataset0;
        dataset0.setUint32(TagId(tagId_t::CommandField_0000_0100), 0x1, tagVR_t::US);
        dataset0.setUint32(TagId(tagId_t::MessageID_0000_0110), 0x1, tagVR_t::US);
        dataset0.setString(TagId(tagId_t::StudyInstanceUID_0020_000D), "1.2.3.4.7");
        dataset0.setUint32(TagId(tagId_t::CommandDataSetType_0000_0800), 0x101);

        command.addDataSet(dataset0);
        scu.sendMessage(command);

        AssociationMessage response = scu.getResponse(1);
        DataSet responseDataSet = response.getCommand();
        EXPECT_EQ("1.2.840.10008.1.1", response.getAbstractSyntax());
        EXPECT_EQ("1.2.3.4.7", responseDataSet.getString(TagId(tagId_t::StudyInstanceUID_0020_000D), 0));
        EXPECT_EQ("1.2.3.4.5", responseDataSet.getString(TagId(tagId_t::SeriesInstanceUID_0020_000E), 0));
        EXPECT_EQ("1.2.840.10008.1.2.1",responseDataSet.getString(TagId(tagId_t::TransferSyntaxUID_0002_0010), 0));
    }

    scu.release();

    scp.join();
}

TEST(acseTest, rejectAssociationName)
{
    PipeStream toSCU(1024), toSCP(1024);

    StreamReader readSCU(toSCU.getStreamInput());
    StreamWriter writeSCU(toSCP.getStreamOutput());

    StreamReader readSCP(toSCP.getStreamInput());
    StreamWriter writeSCP(toSCU.getStreamOutput());

    PresentationContext scuContext0("1.2.840.10008.1.1");
    scuContext0.addTransferSyntax("1.2.840.10008.1.2"); // implicit VR little endian
    scuContext0.addTransferSyntax("1.2.840.10008.1.2.1"); // explicit VR little endian
    PresentationContext scuContext1("1.2.840.10008.1.1.2");
    scuContext1.addTransferSyntax("1.2.840.10008.1.2"); // implicit VR little endian

    PresentationContexts scuPresentationContexts;
    scuPresentationContexts.addPresentationContext(scuContext0);
    scuPresentationContexts.addPresentationContext(scuContext1);

    PresentationContext scpContext0("1.2.840.10008.1.1");
    scpContext0.addTransferSyntax("1.2.840.10008.1.2.1"); // explicit VR little endian

    PresentationContexts scpPresentationContexts;
    scpPresentationContexts.addPresentationContext(scpContext0);

    const std::string scpName("SCP");

    std::thread scp(imebra::tests::scpThreadRejectCalledAET, std::ref(scpName), std::ref(scpPresentationContexts), std::ref(readSCP), std::ref(writeSCP));

    EXPECT_THROW(AssociationSCU scu("SCU", scpName + "wrong", 1, 1, scuPresentationContexts, readSCU, writeSCU, 0), imebra::AcseSCUCalledAETNotRecognizedError);

    scp.join();
}


TEST(acseTest, invokeTooManyOperations)
{
    PipeStream toSCU(1024), toSCP(1024);

    StreamReader readSCU(toSCU.getStreamInput());
    StreamWriter writeSCU(toSCP.getStreamOutput());

    StreamReader readSCP(toSCP.getStreamInput());
    StreamWriter writeSCP(toSCU.getStreamOutput());

    PresentationContext scuContext0("1.2.840.10008.1.1");
    scuContext0.addTransferSyntax("1.2.840.10008.1.2"); // implicit VR little endian
    scuContext0.addTransferSyntax("1.2.840.10008.1.2.1"); // explicit VR little endian
    PresentationContext scuContext1("1.2.840.10008.1.1.2");
    scuContext1.addTransferSyntax("1.2.840.10008.1.2"); // implicit VR little endian

    PresentationContexts scuPresentationContexts;
    scuPresentationContexts.addPresentationContext(scuContext0);
    scuPresentationContexts.addPresentationContext(scuContext1);

    PresentationContext scpContext0("1.2.840.10008.1.1");
    scpContext0.addTransferSyntax("1.2.840.10008.1.2.1"); // explicit VR little endian

    PresentationContexts scpPresentationContexts;
    scpPresentationContexts.addPresentationContext(scpContext0);

    const std::string scpName("SCP");

    std::thread scp(imebra::tests::scpThreadDontAnswer, std::ref(scpName), std::ref(scpPresentationContexts), std::ref(readSCP), std::ref(writeSCP));

    {
        AssociationSCU scu("SCU", scpName, 1, 1, scuPresentationContexts, readSCU, writeSCU, 0);

        {
            MutableAssociationMessage command("1.2.840.10008.1.1");
            MutableDataSet dataset0;
            dataset0.setUint32(TagId(tagId_t::CommandField_0000_0100), 0x1, tagVR_t::US);
            dataset0.setUint32(TagId(tagId_t::MessageID_0000_0110), 0x1, tagVR_t::US);
            dataset0.setString(TagId(tagId_t::StudyInstanceUID_0020_000D), "1.2.3.4.7");
            dataset0.setUint32(TagId(tagId_t::CommandDataSetType_0000_0800), 0x101);

            command.addDataSet(dataset0);
            scu.sendMessage(command);
        }

        {
            MutableAssociationMessage command("1.2.840.10008.1.1");
            MutableDataSet dataset0;
            dataset0.setUint32(TagId(tagId_t::CommandField_0000_0100), 0x1, tagVR_t::US);
            dataset0.setUint32(TagId(tagId_t::MessageID_0000_0110), 0x2, tagVR_t::US);
            dataset0.setString(TagId(tagId_t::StudyInstanceUID_0020_000D), "1.2.3.4.7");
            dataset0.setUint32(TagId(tagId_t::CommandDataSetType_0000_0800), 0x101);

            command.addDataSet(dataset0);
            EXPECT_THROW(scu.sendMessage(command), AcseTooManyOperationsInvokedError);
        }

        {
            MutableAssociationMessage command("1.2.840.10008.1.1");
            MutableDataSet dataset0;
            dataset0.setUint32(TagId(tagId_t::CommandField_0000_0100), 0x1, tagVR_t::US);
            dataset0.setUint32(TagId(tagId_t::MessageID_0000_0110), 0x1, tagVR_t::US);
            dataset0.setString(TagId(tagId_t::StudyInstanceUID_0020_000D), "1.2.3.4.7");
            dataset0.setUint32(TagId(tagId_t::CommandDataSetType_0000_0800), 0x101);

            command.addDataSet(dataset0);
            EXPECT_THROW(scu.sendMessage(command), AcseWrongCommandIdError);
        }

        scu.release();
    }

    scp.join();
}


TEST(acseTest, artimTest)
{
    PipeStream toSCU(1024), toSCP(1024);

    StreamReader readSCP(toSCP.getStreamInput());
    StreamWriter writeSCP(toSCU.getStreamOutput());

    PresentationContext scuContext("1.2.840.10008.1.1");
    scuContext.addTransferSyntax("1.2.840.10008.1.2"); // implicit VR little endian

    PresentationContexts presentationContexts;
    presentationContexts.addPresentationContext(scuContext);

    const std::string scpName("SCP");

    try
    {
        AssociationSCP scp("SCP", 1, 1, presentationContexts, readSCP, writeSCP, 0, 10);
        EXPECT_TRUE(false);
    }
    catch(const StreamClosedError&)
    {

    }

}


} // namespace tests

} // namespace imebra
