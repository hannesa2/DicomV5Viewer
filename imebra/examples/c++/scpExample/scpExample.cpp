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

#include <dicomhero6/dicomhero.h>

// List of accepted abstract syntaxes
const std::list<std::string> abstractSyntaxes {
    dicomhero::dicom2018e::uidStoredPrintStorageSOPClass,
    dicomhero::dicom2018e::uidHardcopyGrayscaleImageStorageSOPClass,
    dicomhero::dicom2018e::uidHardcopyColorImageStorageSOPClass,
    dicomhero::dicom2018e::uidComputedRadiographyImageStorage,
    dicomhero::dicom2018e::uidDigitalXRayImageStorageForPresentation,
    dicomhero::dicom2018e::uidDigitalXRayImageStorageForProcessing,
    dicomhero::dicom2018e::uidDigitalMammographyXRayImageStorageForPresentation,
    dicomhero::dicom2018e::uidDigitalMammographyXRayImageStorageForProcessing,
    dicomhero::dicom2018e::uidDigitalIntraOralXRayImageStorageForPresentation,
    dicomhero::dicom2018e::uidDigitalIntraOralXRayImageStorageForProcessing,
    dicomhero::dicom2018e::uidCTImageStorage,
    dicomhero::dicom2018e::uidEnhancedCTImageStorage,
    dicomhero::dicom2018e::uidLegacyConvertedEnhancedCTImageStorage,
    dicomhero::dicom2018e::uidUltrasoundMultiframeImageStorage,
    dicomhero::dicom2018e::uidMRImageStorage,
    dicomhero::dicom2018e::uidEnhancedMRImageStorage,
    dicomhero::dicom2018e::uidMRSpectroscopyStorage,
    dicomhero::dicom2018e::uidEnhancedMRColorImageStorage,
    dicomhero::dicom2018e::uidLegacyConvertedEnhancedMRImageStorage,
    dicomhero::dicom2018e::uidUltrasoundImageStorage,
    dicomhero::dicom2018e::uidEnhancedUSVolumeStorage,
    dicomhero::dicom2018e::uidSecondaryCaptureImageStorage,
    dicomhero::dicom2018e::uidMultiframeSingleBitSecondaryCaptureImageStorage,
    dicomhero::dicom2018e::uidMultiframeGrayscaleByteSecondaryCaptureImageStorage,
    dicomhero::dicom2018e::uidMultiframeGrayscaleWordSecondaryCaptureImageStorage,
    dicomhero::dicom2018e::uidMultiframeTrueColorSecondaryCaptureImageStorage,
    dicomhero::dicom2018e::uidStandaloneOverlayStorage,
    dicomhero::dicom2018e::uidStandaloneCurveStorage,
    dicomhero::dicom2018e::uidWaveformStorageTrial,
    dicomhero::dicom2018e::uid12leadECGWaveformStorage,
    dicomhero::dicom2018e::uidGeneralECGWaveformStorage,
    dicomhero::dicom2018e::uidAmbulatoryECGWaveformStorage,
    dicomhero::dicom2018e::uidHemodynamicWaveformStorage,
    dicomhero::dicom2018e::uidCardiacElectrophysiologyWaveformStorage,
    dicomhero::dicom2018e::uidBasicVoiceAudioWaveformStorage,
    dicomhero::dicom2018e::uidGeneralAudioWaveformStorage,
    dicomhero::dicom2018e::uidArterialPulseWaveformStorage,
    dicomhero::dicom2018e::uidRespiratoryWaveformStorage,
    dicomhero::dicom2018e::uidStandaloneModalityLUTStorage,
    dicomhero::dicom2018e::uidStandaloneVOILUTStorage,
    dicomhero::dicom2018e::uidGrayscaleSoftcopyPresentationStateStorage,
    dicomhero::dicom2018e::uidColorSoftcopyPresentationStateStorage,
    dicomhero::dicom2018e::uidPseudoColorSoftcopyPresentationStateStorage,
    dicomhero::dicom2018e::uidBlendingSoftcopyPresentationStateStorage,
    dicomhero::dicom2018e::uidXAXRFGrayscaleSoftcopyPresentationStateStorage,
    dicomhero::dicom2018e::uidGrayscalePlanarMPRVolumetricPresentationStateStorage,
    dicomhero::dicom2018e::uidCompositingPlanarMPRVolumetricPresentationStateStorage,
    dicomhero::dicom2018e::uidAdvancedBlendingPresentationStateStorage,
    dicomhero::dicom2018e::uidVolumeRenderingVolumetricPresentationStateStorage,
    dicomhero::dicom2018e::uidSegmentedVolumeRenderingVolumetricPresentationStateStorage,
    dicomhero::dicom2018e::uidMultipleVolumeRenderingVolumetricPresentationStateStorage,
    dicomhero::dicom2018e::uidXRayAngiographicImageStorage,
    dicomhero::dicom2018e::uidEnhancedXAImageStorage,
    dicomhero::dicom2018e::uidXRayRadiofluoroscopicImageStorage,
    dicomhero::dicom2018e::uidEnhancedXRFImageStorage,
    dicomhero::dicom2018e::uidXRayAngiographicBiPlaneImageStorage,
    dicomhero::dicom2018e::uidXRay3DAngiographicImageStorage,
    dicomhero::dicom2018e::uidXRay3DCraniofacialImageStorage,
    dicomhero::dicom2018e::uidBreastTomosynthesisImageStorage,
    dicomhero::dicom2018e::uidNuclearMedicineImageStorageRetired,
    dicomhero::dicom2018e::uidNuclearMedicineImageStorage,
    dicomhero::dicom2018e::uidParametricMapStorage,
    dicomhero::dicom2018e::uidRawDataStorage,
    dicomhero::dicom2018e::uidSpatialRegistrationStorage,
    dicomhero::dicom2018e::uidSpatialFiducialsStorage,
    dicomhero::dicom2018e::uidDeformableSpatialRegistrationStorage,
    dicomhero::dicom2018e::uidSegmentationStorage,
    dicomhero::dicom2018e::uidSurfaceSegmentationStorage,
    dicomhero::dicom2018e::uidTractographyResultsStorage,
    dicomhero::dicom2018e::uidRealWorldValueMappingStorage,
    dicomhero::dicom2018e::uidSurfaceScanMeshStorage,
    dicomhero::dicom2018e::uidSurfaceScanPointCloudStorage,
    dicomhero::dicom2018e::uidVLImageStorageTrial,
    dicomhero::dicom2018e::uidVLMultiframeImageStorageTrial,
    dicomhero::dicom2018e::uidVLEndoscopicImageStorage,
    dicomhero::dicom2018e::uidVideoEndoscopicImageStorage,
    dicomhero::dicom2018e::uidVLMicroscopicImageStorage,
    dicomhero::dicom2018e::uidVideoMicroscopicImageStorage,
    dicomhero::dicom2018e::uidVLSlideCoordinatesMicroscopicImageStorage,
    dicomhero::dicom2018e::uidVLPhotographicImageStorage,
    dicomhero::dicom2018e::uidVideoPhotographicImageStorage,
    dicomhero::dicom2018e::uidOphthalmicPhotography8BitImageStorage,
    dicomhero::dicom2018e::uidOphthalmicPhotography16BitImageStorage,
    dicomhero::dicom2018e::uidStereometricRelationshipStorage,
    dicomhero::dicom2018e::uidOphthalmicTomographyImageStorage,
    dicomhero::dicom2018e::uidTextSRStorageTrial,
    dicomhero::dicom2018e::uidAudioSRStorageTrial,
    dicomhero::dicom2018e::uidDetailSRStorageTrial,
    dicomhero::dicom2018e::uidComprehensiveSRStorageTrial,
    dicomhero::dicom2018e::uidBasicTextSRStorage,
    dicomhero::dicom2018e::uidEnhancedSRStorage,
    dicomhero::dicom2018e::uidComprehensiveSRStorage,
    dicomhero::dicom2018e::uidComprehensive3DSRStorage,
    dicomhero::dicom2018e::uidExtensibleSRStorage,
    dicomhero::dicom2018e::uidProcedureLogStorage,
    dicomhero::dicom2018e::uidMammographyCADSRStorage,
    dicomhero::dicom2018e::uidKeyObjectSelectionDocumentStorage,
    dicomhero::dicom2018e::uidChestCADSRStorage,
    dicomhero::dicom2018e::uidXRayRadiationDoseSRStorage,
    dicomhero::dicom2018e::uidRadiopharmaceuticalRadiationDoseSRStorage,
    dicomhero::dicom2018e::uidColonCADSRStorage,
    dicomhero::dicom2018e::uidImplantationPlanSRStorage,
    dicomhero::dicom2018e::uidAcquisitionContextSRStorage,
    dicomhero::dicom2018e::uidSimplifiedAdultEchoSRStorage,
    dicomhero::dicom2018e::uidPatientRadiationDoseSRStorage,
    dicomhero::dicom2018e::uidPlannedImagingAgentAdministrationSRStorage,
    dicomhero::dicom2018e::uidPerformedImagingAgentAdministrationSRStorage,
    dicomhero::dicom2018e::uidContentAssessmentResultsStorage,
    dicomhero::dicom2018e::uidEncapsulatedPDFStorage,
    dicomhero::dicom2018e::uidEncapsulatedCDAStorage,
    dicomhero::dicom2018e::uidEncapsulatedSTLStorage,
    dicomhero::dicom2018e::uidPositronEmissionTomographyImageStorage,
    dicomhero::dicom2018e::uidLegacyConvertedEnhancedPETImageStorage,
    dicomhero::dicom2018e::uidStandalonePETCurveStorage,
    dicomhero::dicom2018e::uidEnhancedPETImageStorage,
    dicomhero::dicom2018e::uidBasicStructuredDisplayStorage,
    dicomhero::dicom2018e::uidCTDefinedProcedureProtocolStorage,
    dicomhero::dicom2018e::uidCTPerformedProcedureProtocolStorage,
    dicomhero::dicom2018e::uidProtocolApprovalStorage,
    dicomhero::dicom2018e::uidProtocolApprovalInformationModelFIND,
    dicomhero::dicom2018e::uidProtocolApprovalInformationModelMOVE,
    dicomhero::dicom2018e::uidProtocolApprovalInformationModelGET,
    dicomhero::dicom2018e::uidRTImageStorage,
    dicomhero::dicom2018e::uidRTDoseStorage,
    dicomhero::dicom2018e::uidRTStructureSetStorage,
    dicomhero::dicom2018e::uidRTBeamsTreatmentRecordStorage,
    dicomhero::dicom2018e::uidRTPlanStorage,
    dicomhero::dicom2018e::uidRTBrachyTreatmentRecordStorage,
    dicomhero::dicom2018e::uidRTTreatmentSummaryRecordStorage,
    dicomhero::dicom2018e::uidRTIonPlanStorage,
    dicomhero::dicom2018e::uidRTIonBeamsTreatmentRecordStorage,
    dicomhero::dicom2018e::uidRTPhysicianIntentStorage,
    dicomhero::dicom2018e::uidRTSegmentAnnotationStorage,
    dicomhero::dicom2018e::uidDICOSCTImageStorage,
    dicomhero::dicom2018e::uidDICOSDigitalXRayImageStorageForPresentation,
    dicomhero::dicom2018e::uidDICOSDigitalXRayImageStorageForProcessing,
    dicomhero::dicom2018e::uidDICOSThreatDetectionReportStorage,
    dicomhero::dicom2018e::uidDICOS2DAITStorage,
    dicomhero::dicom2018e::uidDICOS3DAITStorage,
    dicomhero::dicom2018e::uidDICOSQuadrupoleResonanceQRStorage,
    dicomhero::dicom2018e::uidEddyCurrentImageStorage,
    dicomhero::dicom2018e::uidEddyCurrentMultiframeImageStorage,
    dicomhero::dicom2018e::uidPatientRootQueryRetrieveInformationModelFIND,
    dicomhero::dicom2018e::uidPatientRootQueryRetrieveInformationModelMOVE,
    dicomhero::dicom2018e::uidPatientRootQueryRetrieveInformationModelGET,
    dicomhero::dicom2018e::uidStudyRootQueryRetrieveInformationModelFIND,
    dicomhero::dicom2018e::uidStudyRootQueryRetrieveInformationModelMOVE,
    dicomhero::dicom2018e::uidStudyRootQueryRetrieveInformationModelGET,
    dicomhero::dicom2018e::uidPatientStudyOnlyQueryRetrieveInformationModelFIND,
    dicomhero::dicom2018e::uidPatientStudyOnlyQueryRetrieveInformationModelMOVE,
    dicomhero::dicom2018e::uidPatientStudyOnlyQueryRetrieveInformationModelGET,
    dicomhero::dicom2018e::uidCompositeInstanceRootRetrieveMOVE,
    dicomhero::dicom2018e::uidCompositeInstanceRootRetrieveGET,
    dicomhero::dicom2018e::uidCompositeInstanceRetrieveWithoutBulkDataGET,
    dicomhero::dicom2018e::uidDefinedProcedureProtocolInformationModelFIND,
    dicomhero::dicom2018e::uidDefinedProcedureProtocolInformationModelMOVE,
    dicomhero::dicom2018e::uidDefinedProcedureProtocolInformationModelGET,
    dicomhero::dicom2018e::uidModalityWorklistInformationModelFIND,
    dicomhero::dicom2018e::uidGeneralPurposeWorklistInformationModelFIND,
    dicomhero::dicom2018e::uidRTBeamsDeliveryInstructionStorageTrial,
    dicomhero::dicom2018e::uidRTBeamsDeliveryInstructionStorage,
    dicomhero::dicom2018e::uidRTBrachyApplicationSetupDeliveryInstructionStorage,
    dicomhero::dicom2018e::uidGeneralRelevantPatientInformationQuery,
    dicomhero::dicom2018e::uidBreastImagingRelevantPatientInformationQuery,
    dicomhero::dicom2018e::uidCardiacRelevantPatientInformationQuery,
    dicomhero::dicom2018e::uidColorPaletteStorage,
    dicomhero::dicom2018e::uidColorPaletteQueryRetrieveInformationModelFIND,
    dicomhero::dicom2018e::uidColorPaletteQueryRetrieveInformationModelMOVE,
    dicomhero::dicom2018e::uidColorPaletteQueryRetrieveInformationModelGET,
};

// List of accepted transfer syntaxes
const std::list<std::string> transferSyntaxes
{
    dicomhero::dicom2018e::uidImplicitVRLittleEndian,
    dicomhero::dicom2018e::uidExplicitVRLittleEndian,
    dicomhero::dicom2018e::uidExplicitVRBigEndian,
    dicomhero::dicom2018e::uidJPEGBaselineProcess1,
    dicomhero::dicom2018e::uidJPEGExtendedProcess2_4,
    dicomhero::dicom2018e::uidJPEGExtendedProcess3_5,
    dicomhero::dicom2018e::uidJPEGSpectralSelectionNonHierarchicalProcess6_8,
    dicomhero::dicom2018e::uidJPEGSpectralSelectionNonHierarchicalProcess7_9,
    dicomhero::dicom2018e::uidJPEGFullProgressionNonHierarchicalProcess10_12,
    dicomhero::dicom2018e::uidJPEGFullProgressionNonHierarchicalProcess11_13,
    dicomhero::dicom2018e::uidJPEGLosslessNonHierarchicalProcess14,
    dicomhero::dicom2018e::uidJPEGLosslessNonHierarchicalProcess15,
    dicomhero::dicom2018e::uidJPEGExtendedHierarchicalProcess16_18,
    dicomhero::dicom2018e::uidJPEGExtendedHierarchicalProcess17_19,
    dicomhero::dicom2018e::uidJPEGSpectralSelectionHierarchicalProcess20_22,
    dicomhero::dicom2018e::uidJPEGSpectralSelectionHierarchicalProcess21_23,
    dicomhero::dicom2018e::uidJPEGFullProgressionHierarchicalProcess24_26,
    dicomhero::dicom2018e::uidJPEGFullProgressionHierarchicalProcess25_27,
    dicomhero::dicom2018e::uidJPEGLosslessHierarchicalProcess28,
    dicomhero::dicom2018e::uidJPEGLosslessHierarchicalProcess29,
    dicomhero::dicom2018e::uidJPEGLosslessNonHierarchicalFirstOrderPredictionProcess14SelectionValue1,
    dicomhero::dicom2018e::uidJPEGLSLosslessImageCompression,
    dicomhero::dicom2018e::uidJPEGLSLossyNearLosslessImageCompression,
    dicomhero::dicom2018e::uidJPEG2000ImageCompressionLosslessOnly,
    dicomhero::dicom2018e::uidJPEG2000ImageCompression,
    dicomhero::dicom2018e::uidJPEG2000Part2MulticomponentImageCompressionLosslessOnly,
    dicomhero::dicom2018e::uidJPEG2000Part2MulticomponentImageCompression,
    dicomhero::dicom2018e::uidJPIPReferenced,
    dicomhero::dicom2018e::uidJPIPReferencedDeflate,
    dicomhero::dicom2018e::uidMPEG2MainProfileMainLevel,
    dicomhero::dicom2018e::uidMPEG2MainProfileHighLevel,
    dicomhero::dicom2018e::uidMPEG4AVCH264HighProfileLevel41,
    dicomhero::dicom2018e::uidMPEG4AVCH264BDcompatibleHighProfileLevel41,
    dicomhero::dicom2018e::uidMPEG4AVCH264HighProfileLevel42For2DVideo,
    dicomhero::dicom2018e::uidMPEG4AVCH264HighProfileLevel42For3DVideo,
    dicomhero::dicom2018e::uidMPEG4AVCH264StereoHighProfileLevel42,
    dicomhero::dicom2018e::uidHEVCH265MainProfileLevel51,
    dicomhero::dicom2018e::uidHEVCH265Main10ProfileLevel51,
    dicomhero::dicom2018e::uidRLELossless
};


///
/// \brief Output to the standard output all the tags contained in a dataset
///
/// \param dataset the dataset to output
/// \param prefix  a string to display before each tag (used for indentation
///                in recursive calls of this method)
///
//////////////////////////////////////////////////////////////////////////////////////
void outputDatasetTags(const dicomhero::DataSet& dataset, const std::wstring& prefix)
{
    // Get all the tags
    dicomhero::tagsIds_t tags = dataset.getTags();

    // Output all the tags
    for(const dicomhero::TagId& tagId: tags)
    {
        try
        {
            std::wstring tagName = dicomhero::DicomDictionary::getUnicodeTagDescription(tagId);
            std::wcout << prefix << L"Tag " << tagId.getGroupId() << L"," << tagId.getTagId() << L" (" << tagName << L")" << std::endl;
        }
        catch(const dicomhero::DictionaryUnknownTagError&)
        {
            std::wcout << prefix << L"Tag " << tagId.getGroupId() << L"," << tagId.getTagId() << L" (Unknown tag)" << std::endl;
        }

        dicomhero::Tag tag(dataset.getTag(tagId));

        for(size_t itemId(0); ; ++itemId)
        {
            try
            {
                dicomhero::DataSet sequence = tag.getSequenceItem(itemId);
                std::wcout << prefix << L"  SEQUENCE " << itemId << std::endl;
                outputDatasetTags(sequence, prefix + L"    ");
            }
            catch(const dicomhero::MissingDataElementError&)
            {
                break;
            }
        }

        for(size_t bufferId(0); bufferId != tag.getBuffersCount(); ++bufferId)
        {
            dicomhero::ReadingDataHandler handler = tag.getReadingDataHandler(bufferId);
            if(handler.getDataType() != dicomhero::tagVR_t::OW && handler.getDataType() != dicomhero::tagVR_t::OB)
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
void outputCommandTags(const std::string& title, const dicomhero::DimseCommand& command)
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
        dicomhero::DataSet header = command.getCommandDataSet();
        std::wcout << std::endl;
        std::wcout << L"    HEADER:" << std::endl;
        std::wcout << L"    -------" << std::endl;
        outputDatasetTags(header, L"    ");

        // Get the payload dataset
        dicomhero::DataSet payload = command.getPayloadDataSet();
        std::wcout << std::endl;
        std::wcout << L"    PAYLOAD:" << std::endl;
        std::wcout << L"    --------" << std::endl;
        outputDatasetTags(payload, L"    ");
    }
    catch (const dicomhero::MissingItemError&)
    {
        // We arrive here if the payload we request above does not exist.
    }
}


// When an association is created then its address is inserted
// in the set below, when it is destroyed it is removed from the set.
// When the app must terminate then we abort all the active associations.
static std::set<dicomhero::AssociationBase*> activeAssociations;
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
void processDimseCommands(dicomhero::TCPStream tcpStream, std::string aet)
{
    try
    {
        // tcpStream represents the connected socket. Allocate a stream reader and a writer
        // to read and write on the connected socket
        dicomhero::StreamReader readSCU(tcpStream.getStreamInput());
        dicomhero::StreamWriter writeSCU(tcpStream.getStreamOutput());

        // Specify which presentation contexts we accept (declared on the top of this file)
        dicomhero::PresentationContexts presentationContexts;
        for(const std::string& abstractSyntax: abstractSyntaxes)
        {
            dicomhero::PresentationContext context(abstractSyntax);
            for(const std::string& transferSyntax: transferSyntaxes)
            {
                context.addTransferSyntax(transferSyntax);
            }
            presentationContexts.addPresentationContext(context);
        }

        // The AssociationSCP constructor will negotiate the assocation
        dicomhero::AssociationSCP scp(aet, 1, 1, presentationContexts, readSCU, writeSCU, 0, 10);

        {
            std::lock_guard<std::mutex> lock(lockActiveAssociations);
            activeAssociations.insert(&scp);
        }

        try
        {
            // Receive commands via the dimse service, which uses the scp association
            dicomhero::DimseService dimse(scp);

            // Receive commands until the association is closed
            for(;;)
            {
                // Blocks until a command is received, throws EOF when the connection
                // is closed.
                dicomhero::DimseCommand command(dimse.getCommand());

                // Act accordingly to the type of the received command
                switch(command.getCommandType())
                {
                case dicomhero::dimseCommandType_t::cStore:
                    // Received a CSTORE command
                    ////////////////////////////
                    {
                        outputCommandTags("**** Received CSTORE command from " + scp.getOtherAET(), command);

                        dicomhero::CStoreCommand cstore = command.getAsCStoreCommand(); // Convert to cstore to retrieve cstore-specific data
                        dimse.sendCommandOrResponse(dicomhero::CStoreResponse(cstore, dicomhero::dimseStatusCode_t::success));
                    }
                    break;
                case dicomhero::dimseCommandType_t::cGet:
                    // Received a CGET command
                    ////////////////////////////
                    {
                        outputCommandTags("**** Received CGET command from " + scp.getOtherAET(), command);

                        dicomhero::CGetCommand cget = command.getAsCGetCommand(); // Convert to cget to retrieve cget-specific data

                        // Respond with an error
                        dimse.sendCommandOrResponse(dicomhero::CGetResponse(cget, dicomhero::dimseStatusCode_t::unappropriateActionForInstance, 0, 0, 0, 0));
                    }
                    break;

                case dicomhero::dimseCommandType_t::cFind:
                    // Received a CFIND command
                    ////////////////////////////
                    {
                        outputCommandTags("**** Received CFIND command from " + scp.getOtherAET(), command);

                        dicomhero::CFindCommand cfind = command.getAsCFindCommand(); // Convert to cfind to retrieve cfind-specific data

                        // CFIND processing example
                        //-------------------------
                        const dicomhero::DataSet payload = cfind.getPayloadDataSet();

                        // Find the root of the query
                        std::string abstractSyntax = cfind.getAbstractSyntax();
                        if(abstractSyntax == dicomhero::dicom2018e::uidPatientRootQueryRetrieveInformationModelFIND)
                        {
                            // Patient root
                            // ....
                        }
                        else if(abstractSyntax == dicomhero::dicom2018e::uidStudyRootQueryRetrieveInformationModelFIND)
                        {
                            // Study root
                            // ....
                        }

                        // Find out what we should retrieve (e.g. "PATIENT", "STUDY")
                        std::string queryLevel = payload.getString(dicomhero::TagId(dicomhero::tagId_t::QueryRetrieveLevel_0008_0052), 0);

                        // Find out the query parameters
                        std::string patientId = payload.getString(dicomhero::TagId(dicomhero::tagId_t::PatientID_0010_0020), 0, "");
                        std::string patientIdIssuer = payload.getString(dicomhero::TagId(dicomhero::tagId_t::IssuerOfPatientID_0010_0021), 0, "");
                        std::string patientName = payload.getString(dicomhero::TagId(dicomhero::tagId_t::PatientName_0010_0010), 0, "");

                        // Search the database for results
                        // .....

                        // For each result:
                            dicomhero::charsetsList_t charsets;
                            charsets.push_back("ISO_IR 192");
                            dicomhero::DataSet responseDataSet(scp.getTransferSyntax(abstractSyntax), charsets);

                            responseDataSet.setString(dicomhero::TagId(dicomhero::tagId_t::QueryRetrieveLevel_0008_0052), queryLevel);

                            //...Set the key attributes for the found record
                            responseDataSet.setString(dicomhero::TagId(dicomhero::tagId_t::PatientID_0010_0020), "FoundPatientId");
                            //...
                            responseDataSet.setString(dicomhero::TagId(dicomhero::tagId_t::RetrieveAETitle_0008_0054), "AET where the file can be retrieved with c-get or c-move");
                            responseDataSet.setString(dicomhero::TagId(dicomhero::tagId_t::SOPInstanceUID_0008_0018), "SOP.INSTANCE.FOUND.RECORD");

                            // Send the response
                            dicomhero::CFindResponse response(cfind, responseDataSet);
                            dimse.sendCommandOrResponse(response);

                        // At the end, send the final confirmation for c-find
                        dicomhero::CFindResponse finalResponse(cfind, dicomhero::dimseStatusCode_t::success);
                        dimse.sendCommandOrResponse(finalResponse);

                    }
                    break;
                case dicomhero::dimseCommandType_t::cMove:
                    // Received a CMOVE command
                    ////////////////////////////
                    {
                        outputCommandTags("**** Received CMOVE command from " + scp.getOtherAET(), command);

                        dicomhero::CMoveCommand cmove = command.getAsCMoveCommand(); // Convert to cmove to retrieve cmove-specific data

                        // Respond with an error
                        dimse.sendCommandOrResponse(dicomhero::CMoveResponse(cmove, dicomhero::dimseStatusCode_t::unappropriateActionForInstance, 0, 0, 0, 0));
                    }
                    break;
                case dicomhero::dimseCommandType_t::cCancel:
                    // Received a CMOVE command
                    ////////////////////////////
                    {
                        outputCommandTags("**** Received CCANCEL command from " + scp.getOtherAET(), command);
                    }
                    break;
                case dicomhero::dimseCommandType_t::cEcho:
                    // Received a CECHO command
                    ////////////////////////////
                    {
                        outputCommandTags("**** Received CECHO command from " + scp.getOtherAET(), command);

                        dicomhero::CEchoCommand cecho = command.getAsCEchoCommand(); // Convert to cmove to retrieve cecho-specific data

                        // Respond with an error
                        dimse.sendCommandOrResponse(dicomhero::CEchoResponse(cecho, dicomhero::dimseStatusCode_t::success));
                    }
                    break;
                case dicomhero::dimseCommandType_t::nEventReport:
                    // Received a NEVENTREPORT command
                    ///////////////////////////////////
                    {
                        outputCommandTags("**** Received NEVENTREPORT command from " + scp.getOtherAET(), command);

                        dicomhero::NEventReportCommand neventreport = command.getAsNEventReportCommand(); // Convert to neventreport to retrieve neventreport-specific data

                        // Respond with an error
                        dimse.sendCommandOrResponse(dicomhero::NEventReportResponse(neventreport, dicomhero::dimseStatusCode_t::unappropriateActionForInstance));
                    }
                    break;
                case dicomhero::dimseCommandType_t::nGet:
                    // Received a NGET command
                    ///////////////////////////////////
                    {
                        outputCommandTags("**** Received NGET command from " + scp.getOtherAET(), command);

                        dicomhero::NGetCommand nget = command.getAsNGetCommand(); // Convert to nget to retrieve nget-specific data

                        // Respond with an error
                        dimse.sendCommandOrResponse(dicomhero::NGetResponse(nget, dicomhero::dimseStatusCode_t::unappropriateActionForInstance));
                    }
                    break;
                case dicomhero::dimseCommandType_t::nSet:
                    // Received a NSET command
                    ///////////////////////////////////
                    {
                        outputCommandTags("**** Received NSET command from " + scp.getOtherAET(), command);

                        dicomhero::NSetCommand nset = command.getAsNSetCommand(); // Convert to nset to retrieve nset-specific data

                        // Respond with an error
                        dimse.sendCommandOrResponse(dicomhero::NSetResponse(nset, dicomhero::dimseStatusCode_t::unappropriateActionForInstance));
                    }
                    break;
                case dicomhero::dimseCommandType_t::nAction:
                    // Received a NACTION command
                    ///////////////////////////////////
                    {
                        outputCommandTags("**** Received NACTION command from " + scp.getOtherAET(), command);

                        dicomhero::NActionCommand naction = command.getAsNActionCommand(); // Convert to naction to retrieve naction-specific data

                        // Respond with an error
                        dimse.sendCommandOrResponse(dicomhero::NActionResponse(naction, dicomhero::dimseStatusCode_t::unappropriateActionForInstance));
                    }
                    break;
                case dicomhero::dimseCommandType_t::nCreate:
                    // Received a NCREATE command
                    ///////////////////////////////////
                    {
                        outputCommandTags("**** Received NCREATE command from " + scp.getOtherAET(), command);

                        dicomhero::NCreateCommand ncreate = command.getAsNCreateCommand(); // Convert to ncreate to retrieve ncreate-specific data

                        // Respond with an error
                        dimse.sendCommandOrResponse(dicomhero::NCreateResponse(ncreate, dicomhero::dimseStatusCode_t::unappropriateActionForInstance));
                    }
                    break;
                case dicomhero::dimseCommandType_t::nDelete:
                    // Received a NDELETE command
                    ///////////////////////////////////
                    {
                        outputCommandTags("**** Received NDELETE command from " + scp.getOtherAET(), command);

                        dicomhero::NDeleteCommand ndelete = command.getAsNDeleteCommand(); // Convert to ndelete to retrieve ndelete-specific data

                        // Respond with an error
                        dimse.sendCommandOrResponse(dicomhero::NDeleteResponse(ndelete, dicomhero::dimseStatusCode_t::unappropriateActionForInstance));
                    }
                    break;
                default:
                    std::wcout << L"Wrong command received" << std::endl;
                }
            }
        }
        catch(const dicomhero::StreamEOFError&)
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
    catch(const dicomhero::StreamEOFError&)
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
        dicomhero::TCPPassiveAddress listeningAddress("127.0.0.1", argv[1]);
        dicomhero::TCPListener listenForConnections(listeningAddress);

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
                    dicomhero::TCPStream newTCPStream = listenForConnections.waitForConnection();

                    // Launch a thread that processes the dimse commands on the new connection
                    std::thread processDimseCommandsThread(processDimseCommands, newTCPStream, aet);

                    // We detach the thread so we can forget about it.
                    processDimseCommandsThread.detach();
                }
            }
            catch (const dicomhero::StreamEOFError&)
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
                for(dicomhero::AssociationBase* pAssociation: activeAssociations)
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

