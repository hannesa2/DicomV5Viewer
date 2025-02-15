from imebra.imebra import *
import array
import unittest

class TestDataSet(unittest.TestCase):

    # Test DataSet.setString
    #-----------------------
    def test_string(self):

        dataset = MutableDataSet()

        patientName = 'Test patient'
        dataset.setString(TagId(tagId_t_PatientName_0010_0010), patientName)

        self.assertEqual(patientName, dataset.getString(TagId(tagId_t_PatientName_0010_0010), 0))

    # Test DataSet.setImage
    #----------------------
    def test_set_image(self):

        dataset = MutableDataSet()

        image = MutableImage(300, 100, bitDepth_t_depthU16, "RGB", 15)


        handler = image.getWritingDataHandler()
        for y in range(0, 100):
            for x in range(0, 300):

                handler.setUnsignedLong((y * 300 + x) * 3, y)
                handler.setUnsignedLong((y * 300 + x) * 3 + 1, x)
                handler.setUnsignedLong((y * 300 + x) * 3 + 2, x+1)

        handler = None

        dataset.setImage(0, image, imageQuality_t_high)

        CodecFactory.save(dataset, "test.dcm", codecType_t_dicom)

        loadedDataSet = CodecFactory.load("test.dcm", 2048)

        loadedImage = loadedDataSet.getImage(0)

        readingHandler = loadedImage.getReadingDataHandler()

        intArray = array.array('H', [0] * readingHandler.getSize())
        readingHandler.data(intArray)

        for y in range(0, 100):
            for x in range(0, 300):

                self.assertEqual(intArray[(y * 300 + x) * 3], y)
                self.assertEqual(intArray[(y * 300 + x) * 3 + 1], x)
                self.assertEqual(intArray[(y * 300 + x) * 3 + 2], x+1)


class TestMemoryStream(unittest.TestCase):

    # Test Save/Load
    #---------------
    def test_image(self):

        dataset = MutableDataSet()

        patientName = 'Test patient'
        dataset.setString(TagId(tagId_t_PatientName_0010_0010), patientName)

        streamMemory = MutableMemory()

        streamOutput = MemoryStreamOutput(streamMemory)

        streamWriter = StreamWriter(streamOutput)

        CodecFactory.save(dataset, streamWriter, codecType_t_dicom)

        streamWriter = None
        streamOutput = None

        streamInput = MemoryStreamInput(streamMemory)

        streamReader = StreamReader(streamInput)

        loadedDataSet = CodecFactory.load(streamReader)

        self.assertEqual(patientName, loadedDataSet.getString(TagId(tagId_t_PatientName_0010_0010), 0))




if __name__ == '__main__':
    unittest.main()

