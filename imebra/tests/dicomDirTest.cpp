#include <imebra/imebra.h>
#include <gtest/gtest.h>

namespace imebra
{

namespace tests
{

TEST(dicomDirTest, createDicomDir)
{
    MutableDicomDir newDicomDir;

    MutableDicomDirEntry rootRecord = newDicomDir.getNewEntry("PATIENT");

    MutableDataSet rootRecordDataSet(rootRecord.getEntryDataSet());
    rootRecordDataSet.setUnicodeString(TagId(tagId_t::PatientName_0010_0010), L"Surname");
    newDicomDir.setFirstRootEntry(rootRecord);

    MutableDicomDirEntry nextRecord = newDicomDir.getNewEntry("PATIENT");
    MutableDataSet nextRecordDataSet = nextRecord.getEntryDataSet();
    nextRecordDataSet.setUnicodeString(TagId(tagId_t::PatientName_0010_0010), L"Surname 1");
    rootRecord.setNextEntry(nextRecord);

    MutableDicomDirEntry imageRecord = newDicomDir.getNewEntry("IMAGE");
    MutableDataSet imageRecordDataSet = imageRecord.getEntryDataSet();
    imageRecordDataSet.setString(TagId(tagId_t::SOPInstanceUID_0008_0018), "1.2.840.34.56.78999654.235");
    fileParts_t parts;
    parts.push_back("folder");
    parts.push_back("file.dcm");
    imageRecord.setFileParts(parts);

    nextRecord.setFirstChildEntry(imageRecord);

    DataSet dicomDirDataSet = newDicomDir.updateDataSet();

    MutableMemory streamMemory;
    MemoryStreamOutput memStream(streamMemory);
    StreamWriter writer(memStream);
    CodecFactory::save(dicomDirDataSet, writer, codecType_t::dicom);

    MemoryStreamInput inputMemStream(streamMemory);
    StreamReader reader(inputMemStream);
    DataSet readDataSet = CodecFactory::load(reader);

    DicomDir testDicomDir(readDataSet);
    DicomDirEntry testRootRecord = testDicomDir.getFirstRootEntry();
    DataSet testRootRecordDataSet = testRootRecord.getEntryDataSet();
    EXPECT_EQ("PATIENT", testRootRecord.getTypeString());
    EXPECT_EQ(std::wstring(L"Surname"), testRootRecordDataSet.getUnicodeString(TagId(tagId_t::PatientName_0010_0010), 0));

    DicomDirEntry testNextRecord = testRootRecord.getNextEntry();
    DataSet testNextRecordDataSet = testNextRecord.getEntryDataSet();
    EXPECT_EQ("PATIENT", testNextRecord.getTypeString());
    EXPECT_EQ(std::wstring(L"Surname 1"), testNextRecordDataSet.getUnicodeString(TagId(tagId_t::PatientName_0010_0010), 0));
    EXPECT_THROW(testNextRecord.getNextEntry(), DicomDirNoEntryError);

    DicomDirEntry testImageRecord = testNextRecord.getFirstChildEntry();
    DataSet testImageRecordDataSet = testImageRecord.getEntryDataSet();
    EXPECT_EQ("IMAGE", testImageRecord.getTypeString());
    EXPECT_EQ(std::string("1.2.840.34.56.78999654.235"), testImageRecordDataSet.getString(TagId(tagId_t::SOPInstanceUID_0008_0018), 0));
    EXPECT_EQ(std::string("folder"), testImageRecord.getFileParts().at(0));
    EXPECT_EQ(std::string("file.dcm"), testImageRecord.getFileParts().at(1));
    EXPECT_THROW(testImageRecord.getFirstChildEntry(), DicomDirNoEntryError);
}


TEST(dicomDirTest, emptyDicomDir)
{
    MutableDicomDir newDicomDir;

    DataSet dicomDirDataSet = newDicomDir.updateDataSet();

    MutableMemory streamMemory;
    MemoryStreamOutput memStream(streamMemory);
    StreamWriter writer(memStream);
    CodecFactory::save(dicomDirDataSet, writer, codecType_t::dicom);

    MemoryStreamInput inputMemStream(streamMemory);
    StreamReader reader(inputMemStream);
    DataSet readDataSet = CodecFactory::load(reader);

    DicomDir testDicomDir(readDataSet);
    EXPECT_THROW(testDicomDir.getFirstRootEntry(), DicomDirNoEntryError);
}

} // namespace tests

} // namespace imebra
