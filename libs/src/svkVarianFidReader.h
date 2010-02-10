/*
 *  Copyright © 2009-2010 The Regents of the University of California.
 *  All Rights Reserved.
 *
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions are met:
 *  •   Redistributions of source code must retain the above copyright notice, 
 *      this list of conditions and the following disclaimer.
 *  •   Redistributions in binary form must reproduce the above copyright notice, 
 *      this list of conditions and the following disclaimer in the documentation 
 *      and/or other materials provided with the distribution.
 *  •   None of the names of any campus of the University of California, the name 
 *      "The Regents of the University of California," or the names of any of its 
 *      contributors may be used to endorse or promote products derived from this 
 *      software without specific prior written permission.
 *  
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND 
 *  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
 *  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
 *  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
 *  INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
 *  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
 *  PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
 *  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
 *  OF SUCH DAMAGE.
 */



/*
 *  $URL$
 *  $Rev$
 *  $Author$
 *  $Date$
 *
 *  Authors:
 *      Jason C. Crane, Ph.D.
 *      Beck Olson
 */


#ifndef SVK_VARIAN_FID_READER_H
#define SVK_VARIAN_FID_READER_H


#include <vtkObjectFactory.h>
#include <vtkImageData.h>
#include <vtkInformation.h>
#include <vtkUnsignedCharArray.h>
#include <vtkUnsignedShortArray.h>
#include <vtkFloatArray.h>
#include <vtkPointData.h>
#include <vtkGlobFileNames.h>
#include <vtkSortFileNames.h>
#include <vtkStringArray.h>
#include <vtkDebugLeaks.h>
#include <vtkTransform.h>
#include <vtkMatrix4x4.h>

#include <svkVarianReader.h>
#include <svkByteSwap.h>

#include <sys/stat.h>
#include <map>


namespace svk {


using namespace std;


/*! 
 *  Reader for varian FID files. 
 */
class svkVarianFidReader : public svkVarianReader
{

    public:

        static svkVarianFidReader* New();
        vtkTypeRevisionMacro( svkVarianFidReader, svkVarianReader);

        //  Methods:
        virtual int             CanReadFile(const char* fname);


    protected:

        svkVarianFidReader();
        ~svkVarianFidReader();

        virtual int     FillOutputPortInformation(int port, vtkInformation* info);
        virtual void    ExecuteInformation();
        virtual void    ExecuteData(vtkDataObject *output);


    private:

        //  Methods:
        virtual void                     InitDcmHeader();
        void                             InitPatientModule();
        void                             InitGeneralStudyModule();
        void                             InitGeneralSeriesModule();
        void                             InitGeneralEquipmentModule();
        void                             InitMultiFrameFunctionalGroupsModule();
        void                             InitMultiFrameDimensionModule();
        void                             InitAcquisitionContextModule();
        void                             InitSharedFunctionalGroupMacros();
        void                             InitPerFrameFunctionalGroupMacros();
        void                             InitFrameContentMacro();
        void                             InitPlanePositionMacro();
        void                             InitPixelMeasuresMacro();
        void                             InitPlaneOrientationMacro();
        void                             InitMRReceiveCoilMacro();
        void                             InitMRSpectroscopyDataModule();
        void                             ReadFidFiles();
        svkDcmHeader::DcmPixelDataFormat GetFileType();
        string                           VarianToDicomDate(string* volumeDate);
        string                           GetDcmPatientPositionString(string patientPosition);
        void                             ParseFid();
        void                             GetFidKeyValuePair( vtkStringArray* keySet = NULL);
        void                             SetKeysToSearch(vtkStringArray* fltArray, int fileIndex);
        int                              GetDataBufferSize();
        int                              GetHeaderValueAsInt(
                                            string keyString, int valueIndex = 0, int procparRow = 0
                                         ); 
        float                            GetHeaderValueAsFloat(
                                            string keyString, int valueIndex = 0, int procparRow = 0 
                                         ); 
        string                           GetHeaderValueAsString(
                                            string keyString, int valueIndex = 0, int procparRow = 0
                                         ); 
        void                             ParseAndSetStringElements(string key, string valueArrayString);
        void                             AddDimensionTo2DData();
        void                             PrintKeyValuePairs();


        //  Members:
        void*                                       specData; 
        ifstream*                                   fidFile;
        map <string, vector<string> >               fidMap; 
        long                                        fileSize; 

};


}   //svk


#endif //SVK_VARIAN_FID_READER_H

