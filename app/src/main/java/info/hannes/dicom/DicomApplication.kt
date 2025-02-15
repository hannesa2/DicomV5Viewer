package info.hannes.dicom

import info.hannes.logcat.LoggingApplication

class DicomApplication : LoggingApplication() {

    override fun onCreate() {
        super.onCreate()

        System.loadLibrary("imebra_lib")
    }
}
