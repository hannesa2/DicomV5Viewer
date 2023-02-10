Tutorial
========

Include files
-------------

In C++ you have to include the file imebra/imebra.h:

.. code-block:: c++

    include <imebra/imebra.h>

In Java, everything is in the package imebra:

.. code-block:: java

    import com.imebra.*;

In Java, before using any Imebra class you have to load the native code contained in the jar:

.. code-block:: java
    
    System.loadLibrary("imebra_lib")
    

Loading files
-------------

Imebra can read DICOM files and Jpeg files.

Both the DICOM and the Jpeg codes generate an in-memory DICOM structure represented by the :cpp:class:`imebra::DataSet` class
(also the Jpeg codec produces a DICOM structure containing an embedded JPEG file).

Imebra chooses the correct codec automatically according to the stream's content.

To create an :cpp:class:`imebra::DataSet` from a stream use the class :cpp:class:`imebra::CodecFactory`.

In C++:

.. code-block:: c++

    imebra::DataSet loadedDataSet(imebra::CodecFactory::load("DicomFile.dcm"));


In Java:

.. code-block:: java

    com.imebra.DataSet loadedDataSet = com.imebra.CodecFactory.load("DicomFile.dcm");


The previous code loads the file DicomFile.dcm.

Imebra can perform a "lazy loading", which leaves the data on the input stream and loads it into memory
only when necessary; large tags that are not needed are loaded only when necessary and then discarded from memory 
until they are needed once again.

This allows processing large DICOM files by loading large tags only when they are needed and is completely transparent
to the client application.

To enable the "lazy loading", specify the maximum size of the tags that must be loaded immediately. The following line
leaves all the tags bigger than 2048 bytes on the stream and loads them only when needed:

Lazy loading in C++:

.. code-block:: c++

    // Load tags in memory only if their size is equal or smaller than 2048 bytes
    imebra::DataSet loadedDataSet(imebra::CodecFactory::load("DicomFile.dcm", 2048));


in Java

.. code-block:: java

    // Load tags in memory only if their size is equal or smaller than 2048 bytes
    com.imebra.DataSet loadedDataSet = com.imebra.CodecFactory.load("DicomFile.dcm", 2048);
    

Reading the tag's values
------------------------

Once the DataSet has been loaded your application can retrieve the tags stored in it.

Tags' values are converted automatically between different data types unless the conversion would cause a loss
of the value (e.g. the conversion of the string "10" to the number 10 succeeds, but the conversion of the string "Hello" to a number
fails).

In order to retrieve a tag's value, use one of the following methods

- :cpp:member:`imebra::DataSet::getSignedLong`
- :cpp:member:`imebra::DataSet::getUnsignedLong`
- :cpp:member:`imebra::DataSet::getDouble`
- :cpp:member:`imebra::DataSet::getString`
- :cpp:member:`imebra::DataSet::getUnicodeString` (C++ only)
- :cpp:member:`imebra::DataSet::getPatientName`
- :cpp:member:`imebra::DataSet::getUnicodePatientName` (C++ only)
- :cpp:member:`imebra::DataSet::getAge`
- :cpp:member:`imebra::DataSet::getDate`

Alternatively, you can retrieve a :cpp:class:`imebra::ReadingDataHandler` (via :cpp:member:`imebra::DataSet::getReadingDataHandler`) and 
call the methods it offers to read the tag's values.

If you are reading a tag containing numeric values then you can retrieve the Tag's :cpp:class:`imebra::ReadingNumericDataHandler`
(via :cpp:member:`imebra::DataSet::getReadingDataHandlerNumeric`) which exposes the raw memory that stores the actual data: in some cases
this allow for faster information processing.

In order to identify the tag to read you must use the class :cpp:class:`imebra::TagId` which takes as parameters the group ID and the tag ID or
an :cpp:enum:`imebra::tagId_t` enumeration.

This is how you retrieve the patient's name from the DataSet in C++:

.. code-block:: c++

    imebra::UnicodePatientName patientName = loadedDataSet.getUnicodePatientName(imebra::TagId(imebra::tagId_t::PatientName_0010_0010), 0);

    // A patient's name contains 3 values, representing different interpretations of the same name
    // (alphabetic representation, ideographic representation and phonetic representation).
    std::wstring patientNameCharacter = patientName.getAlphabeticRepresentation();
    std::wstring patientNameIdeographic = patientName.getIdeographicRepresentation();

and in Java:

.. code-block:: java

    com.imebra.PatientName patientName = loadedDataSet.getPatientName(new com.imebra.TagId(0x10, 0x10), 0);

    // A patient's name contains 3 values, representing different interpretations of the same name
    // (alphabetic representation, ideographic representation and phonetic representation).
    String patientNameCharacter = patientName.getAlphabeticRepresentation();
    String patientNameIdeographic = patientName.getIdeographicRepresentation();


Note that the previous code will throw one of the exceptions derived from :cpp:class:`imebra::MissingDataElementError`
if the desidered patient name component is not present in the :cpp:class:`imebra::DataSet` (in Golang a panic is raised).

You can specify a return value that is returned when the value is not present in order to avoid throwing an exception when
a tag's value cannot be found in the DataSet :

.. code-block:: c++

    imebra::UnicodePatientName patientName = loadedDataSet.getUnicodePatientName(imebra::TagId(imebra::tagId_t::PatientName_0010_0010), 0, imebra::UnicodePatientName(L"", L"", L""));

in Java:

.. code-block:: java

    com.imebra.PatientName patientName = loadedDataSet.getPatientName(new com.imebra.TagId(0x10, 0x10), 0, new com.imebra.PatientName("", "", ""));


Retrieving an image
-------------------

Imebra exposes two methods to retrieve images from a :cpp:class:`imebra::DataSet`:

- :cpp:member:`imebra::DataSet::getImage`
- :cpp:member:`imebra::DataSet::getImageApplyModalityTransform`

The second method applies to the image the :cpp:member:`imebra::DataSet::ModalityVOILUT` transform automatically if present
and is the reccommended method.

The retrieved image will have the color space & bits per channel as defined in the DataSet.

To retrieve an image in C++:

.. code-block:: c++

    // Retrieve the first image (index = 0)
    imebra::Image image(loadedDataSet.getImageApplyModalityTransform(0));

    // Get the color space
    std::string colorSpace = image.getColorSpace();

    // Get the size in pixels
    std::uint32_t width = image.getWidth();
    std::uint32_t height = image.getHeight();


To retrieve an image in Java:

.. code-block:: java

    // Retrieve the first image (index = 0)
    com.imebra.Image image = loadedDataSet.getImageApplyModalityTransform(0);

    // Get the color space
    String colorSpace = image.getColorSpace();

    // Get the size in pixels
    long width = image.getWidth();
    long height = image.getHeight();


In order to access the image's pixels you can obtain a :cpp:class:`imebra::ReadingDataHandlerNumeric` and then
access the individual pixels via :cpp:member:`imebra::ReadingDataHandler::getSignedLong` or 
:cpp:member:`imebra::ReadingDataHandler::getUnsignedLong`. For faster processing you could also access
the raw memory containing the pixels.

This is how you scan all the pixels in C++, the slow way

.. code-block:: c++

    // let's assume that we already have the image's size in the variables width and height
    // (see previous code snippet)

    // Retrieve the data handler
    imebra::ReadingDataHandlerNumeric dataHandler(image.getReadingDataHandler());

    for(std::uint32 scanY(0); scanY != height; ++scanY)
    {
        for(std::uint32 scanX(0); scanX != width; ++scanX)
        {
            // For monochrome images
            std::int32_t luminance = dataHandler.getSignedLong(scanY * width + scanX);

            // For RGB images
            std::int32_t r = dataHandler.getSignedLong((scanY * width + scanX) * 3);
            std::int32_t g = dataHandler.getSignedLong((scanY * width + scanX) * 3 + 1);
            std::int32_t b = dataHandler.getSignedLong((scanY * width + scanX) * 3 + 2);
        }
    }


How to access the pixels in Java:

.. code-block:: java

    // let's assume that we already have the image's size in the variables width and height
    // (see previous code snippet)

    // Retrieve the data handler
    com.imebra.ReadingDataHandlerNumeric dataHandler = image->getReadingDataHandler();

    for(long scanY = 0; scanY != height; scanY++)
    {
        for(long scanX = 0; scanX != width; scanX++)
        {
            // For monochrome images
            int luminance = dataHandler.getSignedLong(scanY * width + scanX);

            // For RGB images
            int r = dataHandler.getSignedLong((scanY * width + scanX) * 3);
            int g = dataHandler.getSignedLong((scanY * width + scanX) * 3 + 1);
            int b = dataHandler.getSignedLong((scanY * width + scanX) * 3 + 2);
        }
    }


In order to make things faster you can retrieve the memory containing the data in raw format from the :cpp:class:`imebra::ReadingDataHandlerNumeric`
object:

.. code-block:: c++

    // Retrieve the data handler
    imebra::ReadingDataHandlerNumeric dataHandler(image.getReadingDataHandler());

    // Get the memory pointer and the size (in bytes)
    size_t dataLength;
    const char* data = dataHandler.data(&dataLength);

    // Get the number of bytes per each value (1, 2, or 4 for images)
    size_t bytesPerValue = dataHandler.getUnitSize(); 

    // Are the values signed?
    bool bIsSigned = dataHandler.isSigned();

    // Do something with the pixels...A template function would come handy


Displaying an image
-------------------

An image may have to undergo several transformations before it can be displayed on a computer (or mobile) screen.
Usually, the computer monitor accepts 8 bit per channel RGB (or RGBA) images, while images retrieved from a DataSet
may have more than 8 bits per channel (up to 32) and may have a different color space (for instance MONOCHROME1, MONOCHROME2,
YBR_FULL, etc).

While the necessary transforms are performed automatically by the :cpp:class:`imebra::DrawBitmap` class, some 
transformations must still be performed by the client application.

In particular, the :cpp:class:`imebra::DrawBitmap` class takes care of:

- converting the color space
- shifting the channels values to 8 bit

The client application must take care of applying the :cpp:class:`imebra::ModalityVOILUT` transform (but this is easily done
by calling :cpp:member:`imebra::DataSet::getImageApplyModalityTransform` instead of :cpp:member:`imebra::DataSet::getImage`)
and the :cpp:member:`imebra::VOILUT` transform.

The :cpp:member:`imebra::VOILUT` can be applied only to monochromatic images and changes the image's contrast to enhance
different portions of the image (for instance just the bones or the tissue).

Usually, the dataSet contains a few tags that store some pre-defined VOILUT settings for the image: the client application should apply
those values to the VOILUT transform.
The pre-defined settings come as pairs of center/width values or as Lookup Tables stored in the DICOM sequence 0028,3010.

To retrieve the pairs center/width use the method :cpp:member:`imebra::DataSet::getVOIs`, while to retrieve the LUTs use
the method :cpp:member:`imebra::DataSet::getLUT`.

in C++

.. code-block:: c++

    // The transforms chain will contain all the transform that we want to 
    // apply to the image before displaying it
    imebra::TransformsChain chain;

    if(imebra::ColorTransformsFactory::isMonochrome(image.getColorSpace()))
    {
        // Allocate a VOILUT transform. If the DataSet does not contain any pre-defined
        //  settings then we will find the optimal ones.
        std::shared_ptr<imebra::VOILUT> pVoilutTransform;

        // Retrieve the VOIs (center/width pairs)
        imebra::vois_t vois = loadedDataSet.getVOIs();

        // Retrieve the LUTs
        std::list<imebra::LUT> luts;
        for(size_t scanLUTs(0); ; ++scanLUTs)
        {
            try
            {
                luts.push_back(loadedDataSet.getLUT(imebra::TagId(imebra::tagId_t::VOILUTSequence_0028_3010), scanLUTs));
            }
            catch(const imebra::MissingDataElementError&)
            {
                break;
            }
        }

        if(!vois.empty())
        {
            pVoilutTransform.reset(new imebra::VOILUT(vois[0]));
        }
        else if(!luts.empty())
        {
            pVoilutTransform.reset(new imebra::VOILUT(luts.front()));
        }
        else
        {
            pVoilutTransform.reset(new imebra::VOILUT(imebra::VOILUT::getOptimalVOI(image, 0, 0, width, height)));
        }
        
        chain.addTransform(*pVoilutTransform);        
    }

    // If the image is monochromatic then now chain contains the VOILUT transform


in Java

.. code-block:: java

    // The transforms chain will contain all the transform that we want to 
    // apply to the image before displaying it
    com.imebra.TransformsChain chain = new com.imebra.TransformsChain();

    if(com.imebra.ColorTransformsFactory.isMonochrome(image.getColorSpace()))
    {
        // Allocate a VOILUT transform. If the DataSet does not contain any pre-defined
        //  settings then we will find the optimal ones.
        com.imebra.VOILUT voilutTransform = new com.imebra.VOILUT();

        // Retrieve the VOIs (center/width pairs)
        com.imebra.vois_t vois = loadedDataSet.getVOIs();

        // Retrieve the LUTs
        List<com.imebra.LUT> luts = new ArrayList<com.imebra.LUT>();
        for(long scanLUTs = 0; ; scanLUTs++)
        {
            try
            {
                luts.add(loadedDataSet.getLUT(new com.imebra.TagId(0x0028,0x3010), scanLUTs));
            }
            catch(Exception e)
            {
                break;
            }
        }

        if(!vois.isEmpty())
        {
            voilutTransform = new com.imebra.VOILUT(vois.get(0));
        }
        else if(!luts.isEmpty())
        {
            voilutTransform = new com.imebra.VOILUT(luts.get(0));
        }
        else
        {
            voilutTransform = new com.imebra.VOILUT(com.imebra.getOptimalVOI(image, 0, 0, width, height));
        }
        
        chain.add(voilutTransform);        
    }



Now we can display the image. We use :cpp:class:`imebra::DrawBitmap` to obtain an RGB image
ready to be displayed.

In C++

.. code-block:: c++

    // We create a DrawBitmap that always apply the chain transform before getting the RGB image
    imebra::DrawBitmap draw(chain);

    // Ask for the size of the buffer (in bytes)
    size_t requestedBufferSize = draw.getBitmap(image, imebra::drawBitmapType_t::drawBitmapRGBA, 4, 0, 0);
    
    // Now we allocate the buffer and then ask DrawBitmap to fill it
    std::string buffer(requestedBufferSize, char(0));
    draw.getBitmap(image, imebra::drawBitmapType_t::drawBitmapRGBA, 4, &(buffer.at(0)), requestedBufferSize);

On OS-X or iOS you can use the provided method :cpp:func:`imebra::getImebraImage` to obtain a NSImage or an UIImage:

.. code-block:: c++

    // We create a DrawBitmap that always apply the chain transform before getting the RGB image
    imebra::DrawBitmap draw(chain);

    // Get an NSImage (or UIImage on iOS)
    NSImage* nsImage = getImebraImage(*ybrImage, draw);


In Java

.. code-block:: java

    // We create a DrawBitmap that always apply the chain transform before getting the RGB image
    com.imebra.DrawBitmap draw = new com.imebra.DrawBitmap(chain);

    // Ask for the size of the buffer (in bytes)
    long requestedBufferSize = draw.getBitmap(image, imebra::drawBitmapType_t::drawBitmapRGBA, 4, new byte[0]);
    
    byte buffer[] = new byte[(int)requestedBufferSize]; // Ideally you want to reuse this in subsequent calls to getBitmap()
    ByteBuffer byteBuffer = ByteBuffer.wrap(buffer);

    // Now fill the buffer with the image data and create a bitmap from it
    drawBitmap.getBitmap(image, drawBitmapType_t.drawBitmapRGBA, 4, buffer);
    Bitmap renderBitmap = Bitmap.createBitmap((int)image.getWidth(), (int)image.getHeight(), Bitmap.Config.ARGB_8888);
    renderBitmap.copyPixelsFromBuffer(byteBuffer);

    // The Bitmap can be assigned to an ImageView on Android


Creating an empty DataSet
-------------------------

When creating an empty :cpp:class:`imebra::DataSet` you have to specify the transfer syntax that will be used to encode it.
The transfer syntax specifies also how the embedded images are compressed.

The accepted transfer syntaxes are:

- "1.2.840.10008.1.2" (Implicit VR little endian)
- "1.2.840.10008.1.2.1" (Explicit VR little endian)
- "1.2.840.10008.1.2.2" (Explicit VR big endian)
- "1.2.840.10008.1.2.5" (RLE compression)
- "1.2.840.10008.1.2.4.50" (Jpeg baseline 8 bit lossy)
- "1.2.840.10008.1.2.4.51" (Jpeg extended 12 bit lossy)
- "1.2.840.10008.1.2.4.57" (Jpeg lossless NH)
- "1.2.840.10008.1.2.4.70" (Jpeg lossless NH first order prediction)

To create an empty DataSet in C++:

.. code-block:: c++

    // We specify the transfer syntax and the charset
    imebra::MutableDataSet dataSet("1.2.840.10008.1.2.1", "ISO 2022 IR 6");


In Java:

.. code-block:: java

    // We specify the transfer syntax and the charset
    com.imebra.MutableDataSet dataSet = new com.imebra.MutableDataSet("1.2.840.10008.1.2.1", "ISO 2022 IR 6");



Modifying the dataset's content
-------------------------------

You can set the tags values by calling the setters on the DataSet or by retrieving a WritingDataHandler for
a specific tag.

WritingDataHandler objects allow modifying several tag's buffers, while the DataSet setters allow setting only
the element 0 of the first tag's buffer.

The available DataSet setters are:

Once the DataSet has been loaded your application can retrieve the tags stored in it.

In order to write a tag's value, use one of the following methods

- :cpp:member:`imebra::MutableDataSet::setSignedLong`
- :cpp:member:`imebra::MutableDataSet::setUnsignedLong`
- :cpp:member:`imebra::MutableDataSet::setDouble`
- :cpp:member:`imebra::MutableDataSet::setString`
- :cpp:member:`imebra::MutableDataSet::setUnicodeString` (C++ only)
- :cpp:member:`imebra::MutableDataSet::setpatientName`
- :cpp:member:`imebra::MutableDataSet::setUnicodePatientName` (C++ only)
- :cpp:member:`imebra::MutableDataSet::setAge`
- :cpp:member:`imebra::MutableDataSet::setDate`

The WritingDataHandler and WritingDataHandlerNumeric classes contain the same setters but allow to access all the tags' elements, not just
the first one.

This is how you set the patient's name using the DataSet setter:

In C++:

.. code-block:: c++

    dataSet.setUnicodePatientName(TagId(imebra::tagId_t::PatientName_0010_0010), UnicodePatientName(L"Patient^Name", "", ""));

In Java:

.. code-block:: java

    dataSet.setString(new com.imebra.TagId(0x10, 0x10), new PatientName("Patient^Name", "", ""));


Embedding images into the dataSet
---------------------------------

When an image is stored in the dataSet then it is compressed according to the dataSet's transfer syntax.

in C++

.. code-block:: c++

    // Create a 300 by 200 pixel image, 15 bits per color channel, RGB
    imebra::MutableImage image(300, 200, imebra::bitDepth_t::depthU16, "RGB", 15);
    
    {
        WritingDataHandlerNumeric dataHandler(image.getWritingDataHandler());

        // Set all the pixels to red
        for(std::uint32_t scanY(0); scanY != 200; ++scanY)
        {
            for(std::uint32_t scanX(0); scanX != 300; ++scanX)
            {
                dataHandler.setUnsignedLong((scanY * 300 + scanX) * 3, 65535);
                dataHandler.setUnsignedLong((scanY * 300 + scanX) * 3 + 1, 0);
                dataHandler.setUnsignedLong((scanY * 300 + scanX) * 3 + 2, 0);
            }
        }

        // dataHandler will go out of scope and will commit the data into the image
    }

    dataSet.setImage(0, image);

in Java

.. code-block:: java

    // Create a 300 by 200 pixel image, 15 bits per color channel, RGB
    com.imebra.MutableImage image = new com.imebra.MutableImage(300, 200, com.imebra.bitDepth_t.depthU16, "RGB", 15);
    
    {
        WritingDataHandlerNumeric dataHandler = image.getWritingDataHandler();

        // Set all the pixels to red
        for(long scanY = 0; scanY != 200; scanY++)
        {
            for(long scanX =0; scanX != 300; scanX++)
            {
                dataHandler.setUnsignedLong((scanY * 300 + scanX) * 3, 65535);
                dataHandler.setUnsignedLong((scanY * 300 + scanX) * 3 + 1, 0);
                dataHandler.setUnsignedLong((scanY * 300 + scanX) * 3 + 2, 0);
            }
        }

        // Force the commit, don't wait for the garbage collector
        dataHandler.delete();
    }

    dataSet.setImage(0, image);


Saving a DataSet
----------------

A DataSet can be saved using the CodecFactory:

in C++

.. code-block:: c++

    imebra::CodecFactory::save(dataSet, "dicomFile.dcm", imebra::codecType_t::dicom);

in Java

.. code-block:: java

    com.imebra.CodecFactory.save(dataSet, "dicomFile.dcm", com.imebra.codecType_t.dicom);


Sending a DICOM command through an SCU
--------------------------------------

A SCU (Service User) acts as a client in a DICOM association (negotiated connection between 2 peers).

A DICOM association uses a TCP connection to send and receive data.

The DIMSE service (see :cpp:class:`imebra::DimseService`) communicates via an association, represented
either by an AssociationSCU (see :cpp:class:`imebra::AssociationSCU`) or by an AssociationSCP (see :cpp:class:`imebra::AssociationSCP`).

The AssociationSCU usually is the client of a DICOM service, but occasionally can act as an SCP if the SCP role for an abstractSyntax has been
negotiated: this is useful to receive data via C-GET commands, where the SCP sends the requested data to the SCU via a separate C-STORE command.

The following code sends a C-STORE command to an SCP: the C-STORE command instruct the SCP to take a DICOM DataSet. In the example
we prepare the separate DataSet (see :cpp:class:`imebra::DataSet`) and we initialize it with the transfer syntax that we negotiated
in the association.

We then send the command and wait for a response:

.. code-block:: c++

    // Allocate a TCP stream that connects to the DICOM SCP
    imebra::TCPStream tcpStream(TCPActiveAddress("scpHost.company.com", "104"));

    // Allocate a stream reader and a writer that use the TCP stream.
    // If you need a more complex stream (e.g. a stream that uses your
    // own services to send and receive data) then use a Pipe
    imebra::StreamReader readSCU(tcpStream.getInputStream());
    imebra::StreamWriter writeSCU(tcpStream.getOutputStream());

    // Add all the abstract syntaxes and the supported transfer
    // syntaxes for each abstract syntax (the pair abstract/transfer syntax is
    // called "presentation context")
    imebra::PresentationContext context("1.2.840.10008.5.1.4.1.1.4.1"); // Enhanced MR Image Storage
    context.addTransferSyntax("1.2.840.10008.1.2.1"); // Explicit VR little endian
    imebra::PresentationContexts presentationContexts;
    presentationContexts.addPresentationContext(context);

    // The AssociationSCU constructor will negotiate a connection through
    // the readSCU and writeSCU stream reader and writer
    imebra::AssociationSCU scu("SCU", "SCP", 1, 1, presentationContexts, readSCU, writeSCU, 0);

    // The DIMSE service will use the negotiated association to send and receive
    // DICOM commands
    imebra::DimseService dimse(scu);

    // Let's prepare a dataset to store on the SCP
    imebra::MutableDataSet payload(dimse.getTransferSyntax("1.2.840.10008.5.1.4.1.1.4.1")); // We will use the negotiated transfer syntax
    payload.setString(TagId(tagId_t::SOPInstanceUID_0008_0018), "1.1.1.1");
    payload.setString(TagId(tagId_t::SOPClassUID_0008_0016), "1.2.840.10008.5.1.4.1.1.4.1");
    payload.setString(TagId(tagId_t::PatientName_0010_0010),"Patient^Test");
    
    //
    // Fill appropriately all the DataSet tag
    //

    imebra::CStoreCommand command(
                "1.2.840.10008.5.1.4.1.1.4.1", //< one of the negotiated abstract syntaxes
                dimse.getNextCommandID(),
                dimseCommandPriority_t::medium,
                payload.getString(TagId(tagId_t::SOPClassUID_0008_0016), 0),
                payload.getString(TagId(tagId_t::SOPInstanceUID_0008_0018), 0),
                "",
                0,
                payload);
    dimse.sendCommandOrResponse(command);
    imebra::DimseResponse response(dimse.getCStoreResponse(command));

    if(response.getStatus() == imebra::dimseStatus_t::success)
    {
        // SUCCESS!
    }


Implementign a DICOM SCP
------------------------

A DICOM SCP listen for incoming connection and then communicate with the connected peer through a negotiated
DICOM association.

In this example we use the :cpp:class:`imebra::TCPListener` to wait for incoming connections and then negotiate
the association via a AssociationSCP (see :cpp:class:`imebra::AssociationSCP`).

A :cpp:class:`imebra::DimseService` will be used on top of the :cpp:class:`imebra::AssociationSCP` in order to
receive commands and send the responses.

.. code-block:: c++

    // Bind the port 104 to a listening socket
    imebra::TCPListener tcpListener(TCPPassiveAddress("", "104"));
    
    // Wait until a connection arrives or terminate() is called on the tcpListener
    imebra::TCPStream tcpStream(tcpListener.waitForConnection());

    // tcpStream now represents the connected socket. Allocate a stream reader and a writer
    // to read and write on the connected socket
    imebra::StreamReader readSCU(tcpStream.getInputStream());
    imebra::StreamWriter writeSCU(tcpStream.getOutputStream());

    // Specify which presentation contexts we accept
    imebra::PresentationContext context(sopClassUid);
    context.addTransferSyntax(transferSyntax);
    imebra::PresentationContexts presentationContexts;
    presentationContexts.addPresentationContext(context);

    // The AssociationSCP constructor will negotiate the assocation
    imebra::AssociationSCP scp("SCP", 1, 1, presentationContexts, readSCU, writeSCU, 0, 10);

    // Receive commands via the dimse service
    imebra::DimseService dimse(scp);

    try
    {
        // Receive commands until the association is closed
        for(;;)
        {
            // We assume we are going to receive a C-Store. Normally you should check the command type
            // (using DimseCommand::getCommandType()) and then cast to the proper class.
            imebra::CStoreCommand command(dimse.getCommand().getAsCStoreCommand());

            // The store command has a payload. We can do something with it, or we can
            // use the methods in CStoreCommand to get other data sent by the peer
            imebra::DataSet payload = command.getPayloadDataSet();

            // Do something with the payload

            // Send a response
            dimse.sendCommandOrResponse(CStoreResponse(command, dimseStatusCode_t::success));
        }
    }
    catch(const StreamEOFError&)
    {
        // The association has been closed
    }



