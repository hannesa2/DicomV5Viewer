package com.imebra.tests;

import com.imebra.*;
import org.junit.BeforeClass;
import org.junit.Test;
import org.junit.Assert;
import java.text.Normalizer;

import java.io.UnsupportedEncodingException;

import static junit.framework.TestCase.assertEquals;

public class ImebraTests {

    @BeforeClass
    public static void SetupTest() throws Exception
    {
        System.loadLibrary("imebrajni");
    }

    @Test
    public void testUnicode()
    {
        byte patientName0Bytes[]= new byte[28];
        patientName0Bytes[0] = 0;
        patientName0Bytes[1] = 0;
        patientName0Bytes[2] = 0x06;
        patientName0Bytes[3] = 0x28;
        patientName0Bytes[4] = 0;
        patientName0Bytes[5] = 0;
        patientName0Bytes[6] = 0x06;
        patientName0Bytes[7] = 0x2a;
        patientName0Bytes[8] = 0;
        patientName0Bytes[9] = 0;
        patientName0Bytes[10] = 0x06;
        patientName0Bytes[11] = 0x2b;
        patientName0Bytes[12] = 0;
        patientName0Bytes[13] = 0;
        patientName0Bytes[14] = 0;
        patientName0Bytes[15] = 0x40;
        patientName0Bytes[16] = 0;
        patientName0Bytes[17] = 0;
        patientName0Bytes[18] = 0;
        patientName0Bytes[19] = 0x41;
        patientName0Bytes[20] = 0;
        patientName0Bytes[21] = 0;
        patientName0Bytes[22] = 0;
        patientName0Bytes[23] = 0x42;
        patientName0Bytes[24] = 0;
        patientName0Bytes[25] = 0;
        patientName0Bytes[26] = 0;
        patientName0Bytes[27] = 0x43;

        String patientName0 = null;
        try {
            patientName0 = new String(patientName0Bytes, "UTF-32BE");

        } catch (UnsupportedEncodingException e) {
            e.printStackTrace();
        }
        String patientName1 = new String("\u0420\u062a\u062b^\u0410\u0628\u062a");

        com.imebra.MutableMemory streamMemory = new com.imebra.MutableMemory();
        {
            StringsList charsetsList = new StringsList();
            charsetsList.add("ISO_IR 6");
            charsetsList.add("ISO 2022 IR 144");
            charsetsList.add("ISO 2022 IR 100");
            charsetsList.add("ISO 2022 IR 126");
            charsetsList.add("ISO 2022 IR 127");

            MutableDataSet testDataSet = new com.imebra.MutableDataSet("1.2.840.10008.1.2.1", charsetsList);

            {
                WritingDataHandler handler = testDataSet.getWritingDataHandler(new TagId(0x10, 0x10), 0);

                handler.setString(0, patientName0);
                handler.setString(1, patientName1);

                handler.delete();
            }

            MemoryStreamOutput writeStream = new MemoryStreamOutput(streamMemory);
            StreamWriter writer = new StreamWriter(writeStream);
            CodecFactory.save(testDataSet, writer, codecType_t.dicom);
        }

        {
            MemoryStreamInput readStream = new MemoryStreamInput(streamMemory);
            StreamReader reader = new StreamReader(readStream);
            DataSet testDataSet = CodecFactory.load(reader);

            Assert.assertEquals(patientName0, testDataSet.getString(new TagId(0x0010, 0x0010), 0));
            Assert.assertEquals(patientName1, testDataSet.getString(new TagId(0x0010, 0x0010), 1));
        }
    }

    @Test
    public void testJapanese()
    {
        byte patientNameBytes[]= new byte[44];
        patientNameBytes[0] = (byte)0xd4;
        patientNameBytes[1] = (byte)0xcf;
        patientNameBytes[2] = (byte)0xc0;
        patientNameBytes[3] = (byte)0xde;
        patientNameBytes[4] = (byte)0x5e;
        patientNameBytes[5] = (byte)0xc0;
        patientNameBytes[6] = (byte)0xdb;
        patientNameBytes[7] = (byte)0xb3;
        patientNameBytes[8] = (byte)0x3d;
        patientNameBytes[9] = (byte)0x1b;
        patientNameBytes[10] = (byte)0x24;
        patientNameBytes[11] = (byte)0x42;
        patientNameBytes[12] = (byte)0x3b;
        patientNameBytes[13] = (byte)0x33;
        patientNameBytes[14] = (byte)0x45;
        patientNameBytes[15] = (byte)0x44;
        patientNameBytes[16] = (byte)0x1b;
        patientNameBytes[17] = (byte)0x28;
        patientNameBytes[18] = (byte)0x4a;
        patientNameBytes[19] = (byte)0x5e;
        patientNameBytes[20] = (byte)0x1b;
        patientNameBytes[21] = (byte)0x24;
        patientNameBytes[22] = (byte)0x42;
        patientNameBytes[23] = (byte)0x42;
        patientNameBytes[24] = (byte)0x40;
        patientNameBytes[25] = (byte)0x4f;
        patientNameBytes[26] = (byte)0x3a;
        patientNameBytes[27] = (byte)0x1b;
        patientNameBytes[28] = (byte)0x28;
        patientNameBytes[29] = (byte)0x4a;
        patientNameBytes[30] = (byte)0x3d;
        patientNameBytes[31] = (byte)0x1b;
        patientNameBytes[32] = (byte)0x24;
        patientNameBytes[33] = (byte)0x42;
        patientNameBytes[34] = (byte)0x24;
        patientNameBytes[35] = (byte)0x64;
        patientNameBytes[36] = (byte)0x24;
        patientNameBytes[37] = (byte)0x5e;
        patientNameBytes[38] = (byte)0x24;
        patientNameBytes[39] = (byte)0x40;
        patientNameBytes[40] = (byte)0x1b;
        patientNameBytes[41] = (byte)0x28;
        patientNameBytes[42] = (byte)0x4a;
        patientNameBytes[43] = (byte)0x5e;

        com.imebra.MutableMemory streamMemory = new com.imebra.MutableMemory();
        {
            StringsList charsetsList = new StringsList();
            charsetsList.add("ISO 2022 IR 13");
            charsetsList.add("ISO 2022 IR 87");

            MutableDataSet testDataSet = new com.imebra.MutableDataSet("1.2.840.10008.1.2.1", charsetsList);

            {
                WritingDataHandlerNumeric handler = testDataSet.getWritingDataHandlerRaw(new TagId(0x10, 0x10), 0);
                handler.assign(patientNameBytes);
                handler.delete();
            }

            MemoryStreamOutput writeStream = new MemoryStreamOutput(streamMemory);
            StreamWriter writer = new StreamWriter(writeStream);
            CodecFactory.save(testDataSet, writer, codecType_t.dicom);
        }

        {
            MemoryStreamInput readStream = new MemoryStreamInput(streamMemory);
            StreamReader reader = new StreamReader(readStream);
            DataSet testDataSet = CodecFactory.load(reader);

            byte patientNameUnicodeBytes[]= new byte[47];
            patientNameUnicodeBytes[0] = (byte)0xef;
            patientNameUnicodeBytes[1] = (byte)0xbe;
            patientNameUnicodeBytes[2] = (byte)0x94;
            patientNameUnicodeBytes[3] = (byte)0xef;
            patientNameUnicodeBytes[4] = (byte)0xbe;
            patientNameUnicodeBytes[5] = (byte)0x8f;
            patientNameUnicodeBytes[6] = (byte)0xef;
            patientNameUnicodeBytes[7] = (byte)0xbe;
            patientNameUnicodeBytes[8] = (byte)0x80;
            patientNameUnicodeBytes[9] = (byte)0xef;
            patientNameUnicodeBytes[10] = (byte)0xbe;
            patientNameUnicodeBytes[11] = (byte)0x9e;
            patientNameUnicodeBytes[12] = (byte)0x5e;
            patientNameUnicodeBytes[13] = (byte)0xef;
            patientNameUnicodeBytes[14] = (byte)0xbe;
            patientNameUnicodeBytes[15] = (byte)0x80;
            patientNameUnicodeBytes[16] = (byte)0xef;
            patientNameUnicodeBytes[17] = (byte)0xbe;
            patientNameUnicodeBytes[18] = (byte)0x9b;
            patientNameUnicodeBytes[19] = (byte)0xef;
            patientNameUnicodeBytes[20] = (byte)0xbd;
            patientNameUnicodeBytes[21] = (byte)0xb3;
            patientNameUnicodeBytes[22] = (byte)0x3d;
            patientNameUnicodeBytes[23] = (byte)0xe5;
            patientNameUnicodeBytes[24] = (byte)0xb1;
            patientNameUnicodeBytes[25] = (byte)0xb1;
            patientNameUnicodeBytes[26] = (byte)0xe7;
            patientNameUnicodeBytes[27] = (byte)0x94;
            patientNameUnicodeBytes[28] = (byte)0xb0;
            patientNameUnicodeBytes[29] = (byte)0x5e;
            patientNameUnicodeBytes[30] = (byte)0xe5;
            patientNameUnicodeBytes[31] = (byte)0xa4;
            patientNameUnicodeBytes[32] = (byte)0xaa;
            patientNameUnicodeBytes[33] = (byte)0xe9;
            patientNameUnicodeBytes[34] = (byte)0x83;
            patientNameUnicodeBytes[35] = (byte)0x8e;
            patientNameUnicodeBytes[36] = (byte)0x3d;
            patientNameUnicodeBytes[37] = (byte)0xe3;
            patientNameUnicodeBytes[38] = (byte)0x82;
            patientNameUnicodeBytes[39] = (byte)0x84;
            patientNameUnicodeBytes[40] = (byte)0xe3;
            patientNameUnicodeBytes[41] = (byte)0x81;
            patientNameUnicodeBytes[42] = (byte)0xbe;
            patientNameUnicodeBytes[43] = (byte)0xe3;
            patientNameUnicodeBytes[44] = (byte)0x81;
            patientNameUnicodeBytes[45] = (byte)0xa0;
            patientNameUnicodeBytes[46] = (byte)0x5e;

            Assert.assertArrayEquals(patientNameUnicodeBytes, testDataSet.getString(new TagId(0x0010, 0x0010), 0).getBytes(java.nio.charset.StandardCharsets.UTF_8));
        }
    }


    public class SCPThread extends Thread
    {
        public void run() {
            try
            {
                PresentationContext context = new PresentationContext("1.2.840.10008.1.1");
                context.addTransferSyntax("1.2.840.10008.1.2");
                PresentationContexts presentationContexts = new PresentationContexts();
                presentationContexts.addPresentationContext(context);

                TCPListener listener = new TCPListener(new TCPPassiveAddress("", "20002"));

                TCPStream stream = listener.waitForConnection();

                AssociationSCP scp = new AssociationSCP("SCP", 1, 1, presentationContexts, new StreamReader(stream.getStreamInput()), new StreamWriter(stream.getStreamOutput()), 0, 10);

                DimseService dimseService = new DimseService(scp);

                CStoreCommand command = dimseService.getCommand().getAsCStoreCommand();

                dimseService.sendCommandOrResponse(new CStoreResponse(command, dimseStatusCode_t.success));

            }
            catch(Exception e)
            {
                System.out.println(e.getMessage());

            }

        }
    }

    @Test
    public void testStorageSCU()
    {
        Thread scpThread = new SCPThread();
        scpThread.start();

        try {
            Thread.sleep(10000);

            TCPStream stream = new TCPStream(new TCPActiveAddress("", "20002"));

            StreamReader readSCU = new StreamReader(stream.getStreamInput());
            StreamWriter writeSCU = new StreamWriter(stream.getStreamOutput());

            PresentationContext context = new PresentationContext("1.2.840.10008.1.1");
            context.addTransferSyntax("1.2.840.10008.1.2");
            PresentationContexts presentationContexts = new PresentationContexts();
            presentationContexts.addPresentationContext(context);

            AssociationSCU scu = new AssociationSCU("SCU", "SCP", 1, 1, presentationContexts, readSCU, writeSCU, 0);

            DimseService dimse = new DimseService(scu);

            MutableDataSet payload = new MutableDataSet ("1.2.840.10008.1.2");
            payload.setString(new TagId(0x0008, 0x0016), "1.1.1.1.1");
            payload.setString(new TagId(0x0008, 0x0018), "1.1.1.1.2");
            payload.setString(new TagId(0x0010, 0x0010), "Test^Patient");
            CStoreCommand storeCommand = new CStoreCommand(
                    "1.2.840.10008.1.1",
                    dimse.getNextCommandID(),
                    dimseCommandPriority_t.medium,
                    payload.getString(new TagId(0x0008, 0x0016), 0),
                    payload.getString(new TagId(0x0008, 0x0018), 0),
                    "Origin",
                    0,
                    payload);
            dimse.sendCommandOrResponse(storeCommand);
            CStoreResponse response = dimse.getCStoreResponse(storeCommand);

            scpThread.join();
        }
        catch(Exception e)
        {
            System.out.println(e.getMessage());

        }

    }


}
