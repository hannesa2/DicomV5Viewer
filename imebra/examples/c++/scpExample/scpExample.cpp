/*
 * This application demonstrate a simple DICOM SCP.
 *
 * The application listen for incoming ACSE association and parses
 * DIMSE streams once the association is negotiated.
 * The application can process several concurrent connections.
 *
 * Each connection is processed in a separate thread, and for each
 * received command the header and payload datasets are logged to
 * the standard output.
 */

#include <iostream>
#include <thread>
#include <mutex>
#include <functional>
#include <list>
#include <set>

#include <imebra/imebra.h>

// List of accepted abstract syntaxes
const std::list<std::string> abstractSyntaxes {
    imebra::dicom2018e::uidStoredPrintStorageSOPClass,
    imebra::dicom2018e::uidHardcopyGrayscaleImageStorageSOPClass,
    imebra::dicom2018e::uidHardcopyColorImageStorageSOPClass,
    imebra::dicom2018e::uidComputedRadiographyImageStorage,
    imebra::dicom2018e::uidDigitalXRayImageStorageForPresentation,
    imebra::dicom2018e::uidDigitalXRayImageStorageForProcessing,
    imebra::dicom2018e::uidDigitalMammographyXRayImageStorageForPresentation,
    imebra::dicom2018e::uidDigitalMammographyXRayImageStorageForProcessing,
    imebra::dicom2018e::uidDigitalIntraOralXRayImageStorageForPresentation,
    imebra::dicom2018e::uidDigitalIntraOralXRayImageStorageForProcessing,
    imebra::dicom2018e::uidCTImageStorage,
    imebra::dicom2018e::uidEnhancedCTImageStorage,
    imebra::dicom2018e::uidLegacyConvertedEnhancedCTImageStorage,
    imebra::dicom2018e::uidUltrasoundMultiframeImageStorage,
    imebra::dicom2018e::uidMRImageStorage,
    imebra::dicom2018e::uidEnhancedMRImageStorage,
    imebra::dicom2018e::uidMRSpectroscopyStorage,
    imebra::dicom2018e::uidEnhancedMRColorImageStorage,
    imebra::dicom2018e::uidLegacyConvertedEnhancedMRImageStorage,
    imebra::dicom2018e::uidUltrasoundImageStorage,
    imebra::dicom2018e::uidEnhancedUSVolumeStorage,
    imebra::dicom2018e::uidSecondaryCaptureImageStorage,
    imebra::dicom2018e::uidMultiframeSingleBitSecondaryCaptureImageStorage,
    imebra::dicom2018e::uidMultiframeGrayscaleByteSecondaryCaptureImageStorage,
    imebra::dicom2018e::uidMultiframeGrayscaleWordSecondaryCaptureImageStorage,
    imebra::dicom2018e::uidMultiframeTrueColorSecondaryCaptureImageStorage,
    imebra::dicom2018e::uidStandaloneOverlayStorage,
    imebra::dicom2018e::uidStandaloneCurveStorage,
    imebra::dicom2018e::uidWaveformStorageTrial,
    imebra::dicom2018e::uid12leadECGWaveformStorage,
    imebra::dicom2018e::uidGeneralECGWaveformStorage,
    imebra::dicom2018e::uidAmbulatoryECGWaveformStorage,
    imebra::dicom2018e::uidHemodynamicWaveformStorage,
    imebra::dicom2018e::uidCardiacElectrophysiologyWaveformStorage,
    imebra::dicom2018e::uidBasicVoiceAudioWaveformStorage,
    imebra::dicom2018e::uidGeneralAudioWaveformStorage,
    imebra::dicom2018e::uidArterialPulseWaveformStorage,
    imebra::dicom2018e::uidRespiratoryWaveformStorage,
    imebra::dicom2018e::uidStandaloneModalityLUTStorage,
    imebra::dicom2018e::uidStandaloneVOILUTStorage,
    imebra::dicom2018e::uidGrayscaleSoftcopyPresentationStateStorage,
    imebra::dicom2018e::uidColorSoftcopyPresentationStateStorage,
    imebra::dicom2018e::uidPseudoColorSoftcopyPresentationStateStorage,
    imebra::dicom2018e::uidBlendingSoftcopyPresentationStateStorage,
    imebra::dicom2018e::uidXAXRFGrayscaleSoftcopyPresentationStateStorage,
    imebra::dicom2018e::uidGrayscalePlanarMPRVolumetricPresentationStateStorage,
    imebra::dicom2018e::uidCompositingPlanarMPRVolumetricPresentationStateStorage,
    imebra::dicom2018e::uidAdvancedBlendingPresentationStateStorage,
    imebra::dicom2018e::uidVolumeRenderingVolumetricPresentationStateStorage,
    imebra::dicom2018e::uidSegmentedVolumeRenderingVolumetricPresentationStateStorage,
    imebra::dicom2018e::uidMultipleVolumeRenderingVolumetricPresentationStateStorage,
    imebra::dicom2018e::uidXRayAngiographicImageStorage,
    imebra::dicom2018e::uidEnhancedXAImageStorage,
    imebra::dicom2018e::uidXRayRadiofluoroscopicImageStorage,
    imebra::dicom2018e::uidEnhancedXRFImageStorage,
    imebra::dicom2018e::uidXRayAngiographicBiPlaneImageStorage,
    imebra::dicom2018e::uidXRay3DAngiographicImageStorage,
    imebra::dicom2018e::uidXRay3DCraniofacialImageStorage,
    imebra::dicom2018e::uidBreastTomosynthesisImageStorage,
    imebra::dicom2018e::uidNuclearMedicineImageStorageRetired,
    imebra::dicom2018e::uidNuclearMedicineImageStorage,
    imebra::dicom2018e::uidParametricMapStorage,
    imebra::dicom2018e::uidRawDataStorage,
    imebra::dicom2018e::uidSpatialRegistrationStorage,
    imebra::dicom2018e::uidSpatialFiducialsStorage,
    imebra::dicom2018e::uidDeformableSpatialRegistrationStorage,
    imebra::dicom2018e::uidSegmentationStorage,
    imebra::dicom2018e::uidSurfaceSegmentationStorage,
    imebra::dicom2018e::uidTractographyResultsStorage,
    imebra::dicom2018e::uidRealWorldValueMappingStorage,
    imebra::dicom2018e::uidSurfaceScanMeshStorage,
    imebra::dicom2018e::uidSurfaceScanPointCloudStorage,
    imebra::dicom2018e::uidVLImageStorageTrial,
    imebra::dicom2018e::uidVLMultiframeImageStorageTrial,
    imebra::dicom2018e::uidVLEndoscopicImageStorage,
    imebra::dicom2018e::uidVideoEndoscopicImageStorage,
    imebra::dicom2018e::uidVLMicroscopicImageStorage,
    imebra::dicom2018e::uidVideoMicroscopicImageStorage,
    imebra::dicom2018e::uidVLSlideCoordinatesMicroscopicImageStorage,
    imebra::dicom2018e::uidVLPhotographicImageStorage,
    imebra::dicom2018e::uidVideoPhotographicImageStorage,
    imebra::dicom2018e::uidOphthalmicPhotography8BitImageStorage,
    imebra::dicom2018e::uidOphthalmicPhotography16BitImageStorage,
    imebra::dicom2018e::uidStereometricRelationshipStorage,
    imebra::dicom2018e::uidOphthalmicTomographyImageStorage,
    imebra::dicom2018e::uidTextSRStorageTrial,
    imebra::dicom2018e::uidAudioSRStorageTrial,
    imebra::dicom2018e::uidDetailSRStorageTrial,
    imebra::dicom2018e::uidComprehensiveSRStorageTrial,
    imebra::dicom2018e::uidBasicTextSRStorage,
    imebra::dicom2018e::uidEnhancedSRStorage,
    imebra::dicom2018e::uidComprehensiveSRStorage,
    imebra::dicom2018e::uidComprehensive3DSRStorage,
    imebra::dicom2018e::uidExtensibleSRStorage,
    imebra::dicom2018e::uidProcedureLogStorage,
    imebra::dicom2018e::uidMammographyCADSRStorage,
    imebra::dicom2018e::uidKeyObjectSelectionDocumentStorage,
    imebra::dicom2018e::uidChestCADSRStorage,
    imebra::dicom2018e::uidXRayRadiationDoseSRStorage,
    imebra::dicom2018e::uidRadiopharmaceuticalRadiationDoseSRStorage,
    imebra::dicom2018e::uidColonCADSRStorage,
    imebra::dicom2018e::uidImplantationPlanSRStorage,
    imebra::dicom2018e::uidAcquisitionContextSRStorage,
    imebra::dicom2018e::uidSimplifiedAdultEchoSRStorage,
    imebra::dicom2018e::uidPatientRadiationDoseSRStorage,
    imebra::dicom2018e::uidPlannedImagingAgentAdministrationSRStorage,
    imebra::dicom2018e::uidPerformedImagingAgentAdministrationSRStorage,
    imebra::dicom2018e::uidContentAssessmentResultsStorage,
    imebra::dicom2018e::uidEncapsulatedPDFStorage,
    imebra::dicom2018e::uidEncapsulatedCDAStorage,
    imebra::dicom2018e::uidEncapsulatedSTLStorage,
    imebra::dicom2018e::uidPositronEmissionTomographyImageStorage,
    imebra::dicom2018e::uidLegacyConvertedEnhancedPETImageStorage,
    imebra::dicom2018e::uidStandalonePETCurveStorage,
    imebra::dicom2018e::uidEnhancedPETImageStorage,
    imebra::dicom2018e::uidBasicStructuredDisplayStorage,
    imebra::dicom2018e::uidCTDefinedProcedureProtocolStorage,
    imebra::dicom2018e::uidCTPerformedProcedureProtocolStorage,
    imebra::dicom2018e::uidProtocolApprovalStorage,
    imebra::dicom2018e::uidProtocolApprovalInformationModelFIND,
    imebra::dicom2018e::uidProtocolApprovalInformationModelMOVE,
    imebra::dicom2018e::uidProtocolApprovalInformationModelGET,
    imebra::dicom2018e::uidRTImageStorage,
    imebra::dicom2018e::uidRTDoseStorage,
    imebra::dicom2018e::uidRTStructureSetStorage,
    imebra::dicom2018e::uidRTBeamsTreatmentRecordStorage,
    imebra::dicom2018e::uidRTPlanStorage,
    imebra::dicom2018e::uidRTBrachyTreatmentRecordStorage,
    imebra::dicom2018e::uidRTTreatmentSummaryRecordStorage,
    imebra::dicom2018e::uidRTIonPlanStorage,
    imebra::dicom2018e::uidRTIonBeamsTreatmentRecordStorage,
    imebra::dicom2018e::uidRTPhysicianIntentStorage,
    imebra::dicom2018e::uidRTSegmentAnnotationStorage,
    imebra::dicom2018e::uidDICOSCTImageStorage,
    imebra::dicom2018e::uidDICOSDigitalXRayImageStorageForPresentation,
    imebra::dicom2018e::uidDICOSDigitalXRayImageStorageForProcessing,
    imebra::dicom2018e::uidDICOSThreatDetectionReportStorage,
    imebra::dicom2018e::uidDICOS2DAITStorage,
    imebra::dicom2018e::uidDICOS3DAITStorage,
    imebra::dicom2018e::uidDICOSQuadrupoleResonanceQRStorage,
    imebra::dicom2018e::uidEddyCurrentImageStorage,
    imebra::dicom2018e::uidEddyCurrentMultiframeImageStorage,
    imebra::dicom2018e::uidPatientRootQueryRetrieveInformationModelFIND,
    imebra::dicom2018e::uidPatientRootQueryRetrieveInformationModelMOVE,
    imebra::dicom2018e::uidPatientRootQueryRetrieveInformationModelGET,
    imebra::dicom2018e::uidStudyRootQueryRetrieveInformationModelFIND,
    imebra::dicom2018e::uidStudyRootQueryRetrieveInformationModelMOVE,
    imebra::dicom2018e::uidStudyRootQueryRetrieveInformationModelGET,
    imebra::dicom2018e::uidPatientStudyOnlyQueryRetrieveInformationModelFIND,
    imebra::dicom2018e::uidPatientStudyOnlyQueryRetrieveInformationModelMOVE,
    imebra::dicom2018e::uidPatientStudyOnlyQueryRetrieveInformationModelGET,
    imebra::dicom2018e::uidCompositeInstanceRootRetrieveMOVE,
    imebra::dicom2018e::uidCompositeInstanceRootRetrieveGET,
    imebra::dicom2018e::uidCompositeInstanceRetrieveWithoutBulkDataGET,
    imebra::dicom2018e::uidDefinedProcedureProtocolInformationModelFIND,
    imebra::dicom2018e::uidDefinedProcedureProtocolInformationModelMOVE,
    imebra::dicom2018e::uidDefinedProcedureProtocolInformationModelGET,
    imebra::dicom2018e::uidModalityWorklistInformationModelFIND,
    imebra::dicom2018e::uidGeneralPurposeWorklistInformationModelFIND,
    imebra::dicom2018e::uidRTBeamsDeliveryInstructionStorageTrial,
    imebra::dicom2018e::uidRTBeamsDeliveryInstructionStorage,
    imebra::dicom2018e::uidRTBrachyApplicationSetupDeliveryInstructionStorage,
    imebra::dicom2018e::uidGeneralRelevantPatientInformationQuery,
    imebra::dicom2018e::uidBreastImagingRelevantPatientInformationQuery,
    imebra::dicom2018e::uidCardiacRelevantPatientInformationQuery,
    imebra::dicom2018e::uidColorPaletteStorage,
    imebra::dicom2018e::uidColorPaletteQueryRetrieveInformationModelFIND,
    imebra::dicom2018e::uidColorPaletteQueryRetrieveInformationModelMOVE,
    imebra::dicom2018e::uidColorPaletteQueryRetrieveInformationModelGET,
};

// List of accepted transfer syntaxes
const std::list<std::string> transferSyntaxes
{
    imebra::dicom2018e::uidImplicitVRLittleEndian,
    imebra::dicom2018e::uidExplicitVRLittleEndian,
    imebra::dicom2018e::uidExplicitVRBigEndian,
    imebra::dicom2018e::uidJPEGBaselineProcess1,
    imebra::dicom2018e::uidJPEGExtendedProcess2_4,
    imebra::dicom2018e::uidJPEGExtendedProcess3_5,
    imebra::dicom2018e::uidJPEGSpectralSelectionNonHierarchicalProcess6_8,
    imebra::dicom2018e::uidJPEGSpectralSelectionNonHierarchicalProcess7_9,
    imebra::dicom2018e::uidJPEGFullProgressionNonHierarchicalProcess10_12,
    imebra::dicom2018e::uidJPEGFullProgressionNonHierarchicalProcess11_13,
    imebra::dicom2018e::uidJPEGLosslessNonHierarchicalProcess14,
    imebra::dicom2018e::uidJPEGLosslessNonHierarchicalProcess15,
    imebra::dicom2018e::uidJPEGExtendedHierarchicalProcess16_18,
    imebra::dicom2018e::uidJPEGExtendedHierarchicalProcess17_19,
    imebra::dicom2018e::uidJPEGSpectralSelectionHierarchicalProcess20_22,
    imebra::dicom2018e::uidJPEGSpectralSelectionHierarchicalProcess21_23,
    imebra::dicom2018e::uidJPEGFullProgressionHierarchicalProcess24_26,
    imebra::dicom2018e::uidJPEGFullProgressionHierarchicalProcess25_27,
    imebra::dicom2018e::uidJPEGLosslessHierarchicalProcess28,
    imebra::dicom2018e::uidJPEGLosslessHierarchicalProcess29,
    imebra::dicom2018e::uidJPEGLosslessNonHierarchicalFirstOrderPredictionProcess14SelectionValue1,
    imebra::dicom2018e::uidJPEGLSLosslessImageCompression,
    imebra::dicom2018e::uidJPEGLSLossyNearLosslessImageCompression,
    imebra::dicom2018e::uidJPEG2000ImageCompressionLosslessOnly,
    imebra::dicom2018e::uidJPEG2000ImageCompression,
    imebra::dicom2018e::uidJPEG2000Part2MulticomponentImageCompressionLosslessOnly,
    imebra::dicom2018e::uidJPEG2000Part2MulticomponentImageCompression,
    imebra::dicom2018e::uidJPIPReferenced,
    imebra::dicom2018e::uidJPIPReferencedDeflate,
    imebra::dicom2018e::uidMPEG2MainProfileMainLevel,
    imebra::dicom2018e::uidMPEG2MainProfileHighLevel,
    imebra::dicom2018e::uidMPEG4AVCH264HighProfileLevel41,
    imebra::dicom2018e::uidMPEG4AVCH264BDcompatibleHighProfileLevel41,
    imebra::dicom2018e::uidMPEG4AVCH264HighProfileLevel42For2DVideo,
    imebra::dicom2018e::uidMPEG4AVCH264HighProfileLevel42For3DVideo,
    imebra::dicom2018e::uidMPEG4AVCH264StereoHighProfileLevel42,
    imebra::dicom2018e::uidHEVCH265MainProfileLevel51,
    imebra::dicom2018e::uidHEVCH265Main10ProfileLevel51,
    imebra::dicom2018e::uidRLELossless
};


///
/// \brief Output to the standard output all the tags contained in a dataset
///
/// \param dataset the dataset to output
/// \param prefix  a string to display before each tag (used for indentation
///                in recursive calls of this method)
///
//////////////////////////////////////////////////////////////////////////////////////
void outputDatasetTags(const imebra::DataSet& dataset, const std::wstring& prefix)
{
    // Get all the tags
    imebra::tagsIds_t tags = dataset.getTags();

    // Output all the tags
    for(const imebra::TagId& tagId: tags)
    {
        try
        {
            std::wstring tagName = imebra::DicomDictionary::getUnicodeTagDescription(tagId);
            std::wcout << prefix << L"Tag " << tagId.getGroupId() << L"," << tagId.getTagId() << L" (" << tagName << L")" << std::endl;
        }
        catch(const imebra::DictionaryUnknownTagError&)
        {
            std::wcout << prefix << L"Tag " << tagId.getGroupId() << L"," << tagId.getTagId() << L" (Unknown tag)" << std::endl;
        }

        imebra::Tag tag(dataset.getTag(tagId));

        for(size_t itemId(0); ; ++itemId)
        {
            try
            {
                imebra::DataSet sequence = tag.getSequenceItem(itemId);
                std::wcout << prefix << L"  SEQUENCE " << itemId << std::endl;
                outputDatasetTags(sequence, prefix + L"    ");
            }
            catch(const imebra::MissingDataElementError&)
            {
                break;
            }
        }

        for(size_t bufferId(0); bufferId != tag.getBuffersCount(); ++bufferId)
        {
            imebra::ReadingDataHandler handler = tag.getReadingDataHandler(bufferId);
            if(handler.getDataType() != imebra::tagVR_t::OW && handler.getDataType() != imebra::tagVR_t::OB)
            {
                for(size_t scanHandler(0); scanHandler != handler.getSize(); ++scanHandler)
                {
                    std::wcout << prefix << L"  buffer " << bufferId << L", position "<< scanHandler << ":" << handler.getUnicodeString(scanHandler) << std::endl;
                }
            }
            else
            {
                std::wcout << prefix << L"  Not shown: size " << handler.getSize() << " elements" << std::endl;
            }

        }
    }
}


///
/// \brief Calls outputDatasetTags to display both the command dataset and the
///        payload dataset.
///
/// \param title   title to display before the datasets
/// \param command DIMSE command containing the command and payload datasets
///
//////////////////////////////////////////////////////////////////////////////////////
void outputCommandTags(const std::string& title, const imebra::DimseCommand& command)
{
    if(!title.empty())
    {
        std::wcout << std::endl;
        std::wcout << std::endl;
        std::wcout << title.c_str() << std::endl;
        std::wcout << std::wstring(title.size(), L'*') << std::endl;
        std::wcout << std::endl;
    }

    try
    {
        // Get the header dataset
        imebra::DataSet header = command.getCommandDataSet();
        std::wcout << std::endl;
        std::wcout << L"    HEADER:" << std::endl;
        std::wcout << L"    -------" << std::endl;
        outputDatasetTags(header, L"    ");

        // Get the payload dataset
        imebra::DataSet payload = command.getPayloadDataSet();
        std::wcout << std::endl;
        std::wcout << L"    PAYLOAD:" << std::endl;
        std::wcout << L"    --------" << std::endl;
        outputDatasetTags(payload, L"    ");
    }
    catch (const imebra::MissingItemError&)
    {
        // We arrive here if the payload we request above does not exist.
    }
}


// When an association is created then its address is inserted
// in the set below, when it is destroyed it is removed from the set.
// When the app must terminate then we abort all the active associations.
static std::set<imebra::AssociationBase*> activeAssociations;
static std::mutex lockActiveAssociations; // Lock the access to the associations set.

///
/// \brief When a DIMSE connection is received then this method is executed in a
///        separate thread and continues until the connection is closed, either
///        on the remote or on the local side.
///
/// \param tcpStream the tcp stream for the TCP connection
/// \param aet       the SCP aet to communicate during the ACSE negotiation
///
//////////////////////////////////////////////////////////////////////////////////////
void processDimseCommands(imebra::TCPStream tcpStream, std::string aet)
{
    try
    {
        // tcpStream represents the connected socket. Allocate a stream reader and a writer
        // to read and write on the connected socket
        imebra::StreamReader readSCU(tcpStream.getStreamInput());
        imebra::StreamWriter writeSCU(tcpStream.getStreamOutput());

        // Specify which presentation contexts we accept (declared on the top of this file)
        imebra::PresentationContexts presentationContexts;
        for(const std::string& abstractSyntax: abstractSyntaxes)
        {
            imebra::PresentationContext context(abstractSyntax);
            for(const std::string& transferSyntax: transferSyntaxes)
            {
                context.addTransferSyntax(transferSyntax);
            }
            presentationContexts.addPresentationContext(context);
        }

        // The AssociationSCP constructor will negotiate the assocation
        imebra::AssociationSCP scp(aet, 1, 1, presentationContexts, readSCU, writeSCU, 0, 10);

        {
            std::lock_guard<std::mutex> lock(lockActiveAssociations);
            activeAssociations.insert(&scp);
        }

        try
        {
            // Receive commands via the dimse service, which uses the scp association
            imebra::DimseService dimse(scp);

            // Receive commands until the association is closed
            for(;;)
            {
                // Blocks until a command is received, throws EOF when the connection
                // is closed.
                imebra::DimseCommand command(dimse.getCommand());

                // Act accordingly to the type of the received command
                switch(command.getCommandType())
                {
                case imebra::dimseCommandType_t::cStore:
                    // Received a CSTORE command
                    ////////////////////////////
                    {
                        outputCommandTags("**** Received CSTORE command from " + scp.getOtherAET(), command);

                        imebra::CStoreCommand cstore = command.getAsCStoreCommand(); // Convert to cstore to retrieve cstore-specific data
                        dimse.sendCommandOrResponse(imebra::CStoreResponse(cstore, imebra::dimseStatusCode_t::success));
                    }
                    break;
                case imebra::dimseCommandType_t::cGet:
                    // Received a CGET command
                    ////////////////////////////
                    {
                        outputCommandTags("**** Received CGET command from " + scp.getOtherAET(), command);

                        imebra::CGetCommand cget = command.getAsCGetCommand(); // Convert to cget to retrieve cget-specific data

                        // Respond with an error
                        dimse.sendCommandOrResponse(imebra::CGetResponse(cget, imebra::dimseStatusCode_t::unappropriateActionForInstance, 0, 0, 0, 0));
                    }
                    break;

                case imebra::dimseCommandType_t::cFind:
                    // Received a CFIND command
                    ////////////////////////////
                    {
                        outputCommandTags("**** Received CFIND command from " + scp.getOtherAET(), command);

                        imebra::CFindCommand cfind = command.getAsCFindCommand(); // Convert to cfind to retrieve cfind-specific data

                        // CFIND processing example
                        //-------------------------
                        const imebra::DataSet payload = cfind.getPayloadDataSet();

                        // Find the root of the query
                        std::string abstractSyntax = cfind.getAbstractSyntax();
                        if(abstractSyntax == imebra::dicom2018e::uidPatientRootQueryRetrieveInformationModelFIND)
                        {
                            // Patient root
                            // ....
                        }
                        else if(abstractSyntax == imebra::dicom2018e::uidStudyRootQueryRetrieveInformationModelFIND)
                        {
                            // Study root
                            // ....
                        }

                        // Find out what we should retrieve (e.g. "PATIENT", "STUDY")
                        std::string queryLevel = payload.getString(imebra::TagId(imebra::tagId_t::QueryRetrieveLevel_0008_0052), 0);

                        // Find out the query parameters
                        std::string patientId = payload.getString(imebra::TagId(imebra::tagId_t::PatientID_0010_0020), 0, "");
                        std::string patientIdIssuer = payload.getString(imebra::TagId(imebra::tagId_t::IssuerOfPatientID_0010_0021), 0, "");
                        std::string patientName = payload.getString(imebra::TagId(imebra::tagId_t::PatientName_0010_0010), 0, "");

                        // Search the database for results
                        // .....

                        // For each result:
                            imebra::charsetsList_t charsets;
                            charsets.push_back("ISO_IR 192");
                            imebra::MutableDataSet responseDataSet(scp.getTransferSyntax(abstractSyntax), charsets);

                            responseDataSet.setString(imebra::TagId(imebra::tagId_t::QueryRetrieveLevel_0008_0052), queryLevel);

                            //...Set the key attributes for the found record
                            responseDataSet.setString(imebra::TagId(imebra::tagId_t::PatientID_0010_0020), "FoundPatientId");
                            //...
                            responseDataSet.setString(imebra::TagId(imebra::tagId_t::RetrieveAETitle_0008_0054), "AET where the file can be retrieved with c-get or c-move");
                            responseDataSet.setString(imebra::TagId(imebra::tagId_t::SOPInstanceUID_0008_0018), "SOP.INSTANCE.FOUND.RECORD");

                            // Send the response
                            imebra::CFindResponse response(cfind, responseDataSet);
                            dimse.sendCommandOrResponse(response);

                        // At the end, send the final confirmation for c-find
                        imebra::CFindResponse finalResponse(cfind, imebra::dimseStatusCode_t::success);
                        dimse.sendCommandOrResponse(finalResponse);

                    }
                    break;
                case imebra::dimseCommandType_t::cMove:
                    // Received a CMOVE command
                    ////////////////////////////
                    {
                        outputCommandTags("**** Received CMOVE command from " + scp.getOtherAET(), command);

                        imebra::CMoveCommand cmove = command.getAsCMoveCommand(); // Convert to cmove to retrieve cmove-specific data

                        // Respond with an error
                        dimse.sendCommandOrResponse(imebra::CMoveResponse(cmove, imebra::dimseStatusCode_t::unappropriateActionForInstance, 0, 0, 0, 0));
                    }
                    break;
                case imebra::dimseCommandType_t::cCancel:
                    // Received a CMOVE command
                    ////////////////////////////
                    {
                        outputCommandTags("**** Received CCANCEL command from " + scp.getOtherAET(), command);
                    }
                    break;
                case imebra::dimseCommandType_t::cEcho:
                    // Received a CECHO command
                    ////////////////////////////
                    {
                        outputCommandTags("**** Received CECHO command from " + scp.getOtherAET(), command);

                        imebra::CEchoCommand cecho = command.getAsCEchoCommand(); // Convert to cmove to retrieve cecho-specific data

                        // Respond with an error
                        dimse.sendCommandOrResponse(imebra::CEchoResponse(cecho, imebra::dimseStatusCode_t::success));
                    }
                    break;
                case imebra::dimseCommandType_t::nEventReport:
                    // Received a NEVENTREPORT command
                    ///////////////////////////////////
                    {
                        outputCommandTags("**** Received NEVENTREPORT command from " + scp.getOtherAET(), command);

                        imebra::NEventReportCommand neventreport = command.getAsNEventReportCommand(); // Convert to neventreport to retrieve neventreport-specific data

                        // Respond with an error
                        dimse.sendCommandOrResponse(imebra::NEventReportResponse(neventreport, imebra::dimseStatusCode_t::unappropriateActionForInstance));
                    }
                    break;
                case imebra::dimseCommandType_t::nGet:
                    // Received a NGET command
                    ///////////////////////////////////
                    {
                        outputCommandTags("**** Received NGET command from " + scp.getOtherAET(), command);

                        imebra::NGetCommand nget = command.getAsNGetCommand(); // Convert to nget to retrieve nget-specific data

                        // Respond with an error
                        dimse.sendCommandOrResponse(imebra::NGetResponse(nget, imebra::dimseStatusCode_t::unappropriateActionForInstance));
                    }
                    break;
                case imebra::dimseCommandType_t::nSet:
                    // Received a NSET command
                    ///////////////////////////////////
                    {
                        outputCommandTags("**** Received NSET command from " + scp.getOtherAET(), command);

                        imebra::NSetCommand nset = command.getAsNSetCommand(); // Convert to nset to retrieve nset-specific data

                        // Respond with an error
                        dimse.sendCommandOrResponse(imebra::NSetResponse(nset, imebra::dimseStatusCode_t::unappropriateActionForInstance));
                    }
                    break;
                case imebra::dimseCommandType_t::nAction:
                    // Received a NACTION command
                    ///////////////////////////////////
                    {
                        outputCommandTags("**** Received NACTION command from " + scp.getOtherAET(), command);

                        imebra::NActionCommand naction = command.getAsNActionCommand(); // Convert to naction to retrieve naction-specific data

                        // Respond with an error
                        dimse.sendCommandOrResponse(imebra::NActionResponse(naction, imebra::dimseStatusCode_t::unappropriateActionForInstance));
                    }
                    break;
                case imebra::dimseCommandType_t::nCreate:
                    // Received a NCREATE command
                    ///////////////////////////////////
                    {
                        outputCommandTags("**** Received NCREATE command from " + scp.getOtherAET(), command);

                        imebra::NCreateCommand ncreate = command.getAsNCreateCommand(); // Convert to ncreate to retrieve ncreate-specific data

                        // Respond with an error
                        dimse.sendCommandOrResponse(imebra::NCreateResponse(ncreate, imebra::dimseStatusCode_t::unappropriateActionForInstance));
                    }
                    break;
                case imebra::dimseCommandType_t::nDelete:
                    // Received a NDELETE command
                    ///////////////////////////////////
                    {
                        outputCommandTags("**** Received NDELETE command from " + scp.getOtherAET(), command);

                        imebra::NDeleteCommand ndelete = command.getAsNDeleteCommand(); // Convert to ndelete to retrieve ndelete-specific data

                        // Respond with an error
                        dimse.sendCommandOrResponse(imebra::NDeleteResponse(ndelete, imebra::dimseStatusCode_t::unappropriateActionForInstance));
                    }
                    break;
                default:
                    std::wcout << L"Wrong command received" << std::endl;
                }
            }
        }
        catch(const imebra::StreamEOFError&)
        {
            // The association has been closed during the association
        }
        catch(const std::exception& e)
        {
            std::wcout << e.what() << std::endl;
        }

        {
            std::lock_guard<std::mutex> lock(lockActiveAssociations);
            activeAssociations.erase(&scp);
        }

    }
    catch(const imebra::StreamEOFError&)
    {
        // The association has been closed
    }
    catch(const std::exception& e)
    {
        std::wcout << e.what() << std::endl;
    }
}


///
/// \brief main
///
/// \param argc number of arguments
/// \param argv arguments
/// \return 0
///
//////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
    std::wcout << L"scpExample" << std::endl;

    try
    {
        // Check the number of received arguments
        if(argc < 3)
        {
            std::wcout << L"Usage: scpExample port AET" << std::endl;
            return 1;
        }

        // Create a listening socket bound to the port in the first argument
        imebra::TCPPassiveAddress listeningAddress("", argv[1]);
        imebra::TCPListener listenForConnections(listeningAddress);

        // Get the AET (second argument)
        std::string aet(argv[2]);

        // Listen in a lambda execute in another thread
        std::thread listeningThread(
                    [&]()
        {
            try
            {
                for(;;)
                {
                    // Blocks until the TCPListener is terminated (throws EOF) or until a connection arrives
                    imebra::TCPStream newTCPStream = listenForConnections.waitForConnection();

                    // Launch a thread that processes the dimse commands on the new connection
                    std::thread processDimseCommandsThread(processDimseCommands, newTCPStream, aet);

                    // We detach the thread so we can forget about it.
                    processDimseCommandsThread.detach();
                }
            }
            catch (const imebra::StreamEOFError&)
            {
            }
            catch (const std::exception& e)
            {
                // An error occurred. Print it out.
                std::wcout << e.what() << std::endl;
            }

            // Abort all open associations
            {
                std::lock_guard<std::mutex> lock(lockActiveAssociations);
                for(imebra::AssociationBase* pAssociation: activeAssociations)
                {
                    pAssociation->abort();
                }
            }

        });

        std::wcout << "SCP is listening on port " << argv[1] << " with AET " << argv[2] << std::endl;
        std::wcout << "Press ENTER to exit..." << argv[1] << std::endl;

        getchar();

        // Terminate the listening socket: will cause the listening thread to exit
        listenForConnections.terminate();
        listeningThread.join();

        return 0;

    }
    catch(const std::exception& e)
    {
        std::wcout << std::endl << "Error: " << std::endl << e.what() << std::endl;
        return 1;
    }
}

