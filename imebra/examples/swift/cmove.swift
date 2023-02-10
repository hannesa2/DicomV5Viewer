// This example sends a C-MOVE command to a SCP.
//
// If we are the destination of the C-MOVE, then the file is saved
// in the current folder
//
// Usage:
// cmove ourAET serverAET destinationAET ourPort serverAddress 
//       serverPort instanceUID classUID
//////////////////////////////////////////////////////////////////
import Foundation

if CommandLine.arguments.count < 9
{
    print("Usage: cmove ourAET serverAET destinationAET ourPort serverAddress serverPort instanceUID classUID")
    exit(0)
}

let ourAET = CommandLine.arguments[1]
let serverAET = CommandLine.arguments[2]
let destinationAET = CommandLine.arguments[3]
let ourPort = CommandLine.arguments[4]
let serverAddress = CommandLine.arguments[5]
let serverPort = CommandLine.arguments[6]
let instanceUID = CommandLine.arguments[7]
let classUID = CommandLine.arguments[8]

do
{
    // Open a TCP stream used to receive the data
    let tcpListener = try ImebraTCPListener(address: ImebraTCPPassiveAddress(node: "", service: ourPort))

    // Launch a tread that will receive the moved data
    DispatchQueue.global(qos: .background).async
    {
        do
        {
            // Wait for an incoming connection. Will throw if the listener is closed
            // before a connection arrives
            let tcpStream = try tcpListener.waitForConnection()

            // Allocate a reader and a writer that read and write into the TCP stream
            let readScp = ImebraStreamReader(inputStream: tcpStream.getInput())
            let writeScp = ImebraStreamWriter(outputStream: tcpStream.getOutput())

            // Tell that we accept the class UID specified in the command line, and which
            // transfer syntaxes we can handle for that class
            let context = ImebraPresentationContext(abstractSyntax: classUID)
            context?.addTransferSyntax(ImebraUidImplicitVRLittleEndian_1_2_840_10008_1_2)
            context?.addTransferSyntax(ImebraUidExplicitVRLittleEndian_1_2_840_10008_1_2_1)
            context?.addTransferSyntax(ImebraUidJPEGBaselineProcess1_1_2_840_10008_1_2_4_50)
            context?.addTransferSyntax(ImebraUidJPEGExtendedProcess2_4_1_2_840_10008_1_2_4_51)
            context?.addTransferSyntax(ImebraUidJPEGLosslessNonHierarchicalProcess14_1_2_840_10008_1_2_4_57)
            context?.addTransferSyntax(ImebraUidJPEGLosslessNonHierarchicalFirstOrderPredictionProcess14SelectionValue1_1_2_840_10008_1_2_4_70)
            let presentationContexts = ImebraPresentationContexts()
            presentationContexts?.add(context)

            // Negotiate the association with the SCU (we act as SCP here)
            let scp = try ImebraAssociationSCP(thisAET: ourAET, 
                                               maxInvokedOperations: 1, 
                                               maxPerformedOperations: 1, 
                                               presentationContexts: presentationContexts, 
                                               reader: readScp, 
                                               writer: writeScp, 
                                               dimseTimeoutSeconds: 30, 
                                               artimTimeoutSeconds:30)

            // Use a DIMSE service to send and receive commands/response
            let scpDimseService = ImebraDimseService(association: scp)

            // We wait for just one command
            let command = try scpDimseService!.getCommand()
    
            if command.commandType == ImebraDimseCommandType.cStore
            {
                let dataSet = try command.getPayloadDataSet()
                try ImebraCodecFactory.save(toFile: instanceUID, dataSet: dataSet, codecType: ImebraCodecType.dicom)
            }

            try scp.release()
        }
        catch let error as ImebraStreamError 
        {
            print("ImebraStreamError")
            print("Error: \(error.domain)")
            print(error.userInfo[NSUnderlyingErrorKey])
        }
        catch let error as NSError 
        {
            print("NSError")
            print("Error: \(error.domain)")
            print(error.userInfo[NSUnderlyingErrorKey])
        }
    }


    //---------------------------------------
    //
    // Create the SCU
    //
    //---------------------------------------

    // Open a TCP stream connected to the other SCP
    let tcpStream = try ImebraTCPStream(address: ImebraTCPActiveAddress(node: serverAddress, service: serverPort))

    // Allocate a reader and a writer that read and write into the TCP stream
    let readScu = ImebraStreamReader(inputStream: tcpStream.getInput())
    let writeScu = ImebraStreamWriter(outputStream: tcpStream.getOutput())

    // Tell that we want to use C-MOVE
    let context = ImebraPresentationContext(abstractSyntax: ImebraUidPatientRootQueryRetrieveInformationModelMOVE_1_2_840_10008_5_1_4_1_2_1_2)
    context?.addTransferSyntax(ImebraUidImplicitVRLittleEndian_1_2_840_10008_1_2)
    context?.addTransferSyntax(ImebraUidExplicitVRLittleEndian_1_2_840_10008_1_2_1)
    let presentationContexts = ImebraPresentationContexts()
    presentationContexts?.add(context)

    // Negotiate the association with the SCP
    let scu = try ImebraAssociationSCU(thisAET: ourAET, 
                                       otherAET: serverAET, 
                                       maxInvokedOperations: 1,
                                       maxPerformedOperations: 1,
                                       presentationContexts: presentationContexts,
                                       reader: readScu,
                                       writer: writeScu,
                                       dimseTimeoutSeconds: 0)

    // Use a DIMSE service to send and receive commands/response
    let scuDimseService = ImebraDimseService(association: scu)

    // Create a datase where we set the matching tags used to find the instances to move
    let identifierDataset = ImebraMutableDataSet(transferSyntax: ImebraUidImplicitVRLittleEndian_1_2_840_10008_1_2)
    try identifierDataset!.setString(ImebraTagId(id: ImebraTagEnum.enumSOPInstanceUID_0008_0018), newValue: instanceUID)

    // Prepare a C-MOVE command and send it to the SCP
    let moveCommand = ImebraCMoveCommand(abstractSyntax: classUID, 
                                         messageID: scuDimseService!.getNextCommandID(),
                                         priority: ImebraDimseCommandPriority.medium,
                                         affectedSopClassUid: ImebraUidEnhancedMRImageStorage_1_2_840_10008_5_1_4_1_1_4_1,
                                         destinationAET:destinationAET, 
                                         identifier: identifierDataset)

    try scuDimseService!.sendCommandOrResponse(moveCommand)

    // Wait for a response to the C-MOVE command
    let moveResponse = try scuDimseService!.getCMoveResponse(moveCommand)
    if moveResponse.status == ImebraDimseStatus.success
    {
        print("OK")
    }
    else
    {
        print("Error")
    }

    // Release gracefully
    try scu.release()

    

}
catch let error as ImebraStreamError 
{
    print("ImebraStreamError")
    print("Error: \(error.domain)")
    print(error.userInfo[NSUnderlyingErrorKey])
}
catch let error as NSError 
{
    print("NSError")
    print("Error: \(error.domain)")
    print(error.userInfo[NSUnderlyingErrorKey])
}
