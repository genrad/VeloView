//=========================================================================
//
// Copyright 2018 Kitware, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//=========================================================================

// LOCAL
#include "vtkRadarStream.h"
#include "NetworkSource.h"
#include "PacketConsumer.h"
#include "PacketFileWriter.h"

// VTK
#include <vtkInformationVector.h>
#include <vtkInformation.h>
#include <vtkStreamingDemandDrivenPipeline.h>

class vtkRadarStreamInternal
{
public:
  vtkRadarStreamInternal(int argRadarPort, int ForwardedRadarPort,
                         std::string ForwardedIpAddress, bool isForwarding, bool isCrashAnalysing)
    : Consumer(new PacketConsumer)
    , Writer(new PacketFileWriter)
    , Network(std::unique_ptr<NetworkSource>(new NetworkSource(this->Consumer, argRadarPort, ForwardedRadarPort,
                                                               ForwardedIpAddress, isForwarding, isCrashAnalysing))) {}


  //! where to save a live record of the sensor
  std::string OutputFileName;
  std::shared_ptr<PacketConsumer> Consumer;
  std::shared_ptr<PacketFileWriter> Writer;
  std::unique_ptr<NetworkSource> Network;
};


//-----------------------------------------------------------------------------
vtkStandardNewMacro(vtkRadarStream)

//-----------------------------------------------------------------------------
vtkRadarStream::vtkRadarStream()
{
  printf("Make new vtkRadarStream()\n");
  this->Internal = new vtkRadarStreamInternal(2368, 2369, "127.0.0.1", false, false);
}

//-----------------------------------------------------------------------------
vtkRadarStream::~vtkRadarStream()
{
  this->Stop();
  delete this->Internal;
}

//-----------------------------------------------------------------------------
int vtkRadarStream::GetNumberOfFrames()
{
  std::cerr << "this is not implemented yet" << std::endl;
  return 0;
}

//-----------------------------------------------------------------------------
std::string vtkRadarStream::GetOutputFile()
{
  return this->Internal->OutputFileName;
}

//-----------------------------------------------------------------------------
void vtkRadarStream::SetOutputFile(const std::string &filename)
{
  this->Internal->OutputFileName  = filename;
}

//-----------------------------------------------------------------------------
std::string vtkRadarStream::GetForwardedIpAddress()
{
  return this->Internal->Network->ForwardedIpAddress;
}

//-----------------------------------------------------------------------------
void vtkRadarStream::SetForwardedIpAddress(const std::string &ipAddress)
{
  this->Internal->Network->ForwardedIpAddress = ipAddress;
}

//-----------------------------------------------------------------------------
int vtkRadarStream::GetRadarPort()
{
  return 0;
}

//-----------------------------------------------------------------------------
void vtkRadarStream::SetRadarPort(const int value)
{
//  this->Internal->Network->RadarPort = value;
}

//-----------------------------------------------------------------------------
int vtkRadarStream::GetGPSPort()
{
  return this->Internal->Network->GPSPort;
}

//-----------------------------------------------------------------------------
void vtkRadarStream::SetGPSPort(const int value)
{
  this->Internal->Network->GPSPort = value;
}

//-----------------------------------------------------------------------------
int vtkRadarStream::GetForwardedRadarPort()
{
//  return this->Internal->Network->ForwardedRadarPort;
  return 0;
}

//-----------------------------------------------------------------------------
void vtkRadarStream::SetForwardedRadarPort(const int value)
{
//  this->Internal->Network->ForwardedRadarPort = value;
}

//-----------------------------------------------------------------------------
int vtkRadarStream::GetForwardedGPSPort()
{
  return this->Internal->Network->ForwardedGPSPort;
}

//-----------------------------------------------------------------------------
void vtkRadarStream::SetForwardedGPSPort(const int value)
{
  this->Internal->Network->ForwardedGPSPort = value;
}

//-----------------------------------------------------------------------------
bool vtkRadarStream::GetIsForwarding()
{
  return this->Internal->Network->IsForwarding;
}

//-----------------------------------------------------------------------------
void vtkRadarStream::EnableGPSListening(const bool value)
{
  this->Internal->Network->ListenGPS = value;
}


//-----------------------------------------------------------------------------
void vtkRadarStream::SetIsForwarding(bool value)
{
  this->Internal->Network->IsForwarding = value;
}

//-----------------------------------------------------------------------------
bool vtkRadarStream::GetIsCrashAnalysing()
{
  return this->Internal->Network->IsCrashAnalysing;
}

//-----------------------------------------------------------------------------
void vtkRadarStream::SetIsCrashAnalysing(const bool value)
{
  this->Internal->Network->IsCrashAnalysing = value;
}

//-----------------------------------------------------------------------------
bool vtkRadarStream::GetNeedsUpdate()
{
  Poll();
  this->Modified();
  return true;
}

//----------------------------------------------------------------------------
void vtkRadarStream::Start()
{
  printf("Sensor start\n");
//  printf("RadarStream start()\n");
//  if (!this->Interpreter)
//  {
//    vtkErrorMacro(<< "Please set a Interpreter")
//  }
//  this->Internal->Consumer->SetInterpreter(this->Interpreter);
//  if (this->Internal->OutputFileName.length())
//  {
//    this->Internal->Writer->Start(this->Internal->OutputFileName);
//  }
//
//  this->Internal->Network->Writer.reset();
//
//  if (this->Internal->Writer->IsOpen())
//  {
//    this->Internal->Network->Writer = this->Internal->Writer;
//  }
//
//  this->Internal->Consumer->Start();
//  this->Internal->Network->Start();
}

//----------------------------------------------------------------------------
void vtkRadarStream::Stop()
{
//  this->Internal->Network->Stop();
//  this->Internal->Consumer->Stop();
//  this->Internal->Writer->Stop();
}

//----------------------------------------------------------------------------
void vtkRadarStream::Poll()
{
//  if (this->Internal->Consumer->CheckForNewData())
//  {
//    this->Modified();
//  }
}

//----------------------------------------------------------------------------
int vtkRadarStream::GetCacheSize()
{
  return this->Internal->Consumer->GetMaxNumberOfFrames();
}

//----------------------------------------------------------------------------
void vtkRadarStream::SetCacheSize(int cacheSize)
{
  if (cacheSize == this->GetCacheSize())
  {
    return;
  }

  this->Internal->Consumer->SetMaxNumberOfFrames(cacheSize);
  this->Modified();
}

//-----------------------------------------------------------------------------
void vtkRadarStream::UnloadFrames()
{
  this->Internal->Consumer->UnloadData();
}


//-----------------------------------------------------------------------------
int vtkRadarStream::RequestInformation(vtkInformation* request,
                                       vtkInformationVector** inputVector,
                                       vtkInformationVector* outputVector)
{
  this->Superclass::RequestInformation(request, inputVector, outputVector);

  printf("RadarStream requestinformation\n");
  vtkInformation* outInfo = outputVector->GetInformationObject(0);

  double range[2] = {0};
  outInfo->Set(vtkStreamingDemandDrivenPipeline::TIME_RANGE(), range, 1);

  std::vector<double> steps = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  outInfo->Set(vtkStreamingDemandDrivenPipeline::TIME_STEPS(), &steps[0], static_cast<int>(steps.size()));

//  std::vector<double> timesteps = this->Internal->Consumer->GetTimesteps();
//  const size_t nTimesteps = timesteps.size();
//  if (nTimesteps > 0)
//  {
//    outInfo->Set(vtkStreamingDemandDrivenPipeline::TIME_STEPS(), &timesteps.front(),
//      static_cast<int>(nTimesteps));
//  }
//  else
//  {
//    outInfo->Remove(vtkStreamingDemandDrivenPipeline::TIME_STEPS());
//  }
//
//  double timeRange[2] = { 0.0, nTimesteps ? nTimesteps - 1.0 : 0.0 };
//  outInfo->Set(vtkStreamingDemandDrivenPipeline::TIME_RANGE(), timeRange, 2);

  return 1;
}

//----------------------------------------------------------------------------
int vtkRadarStream::RequestData(vtkInformation* request,
                                vtkInformationVector** vtkNotUsed(inputVector),
                                vtkInformationVector* outputVector)
{
  printf("RadarStream requestdata\n");
  vtkInformation* outInfo = outputVector->GetInformationObject(0);
  vtkDataSet* output = vtkDataSet::SafeDownCast(outInfo->Get(vtkDataObject::DATA_OBJECT()));

  double timeRequest = 0;
//  if (outInfo->Has(vtkStreamingDemandDrivenPipeline::UPDATE_TIME_STEP()))
//  {
    timeRequest = outInfo->Get(vtkStreamingDemandDrivenPipeline::UPDATE_TIME_STEP());
//  }

  {
    boost::lock_guard<boost::mutex> lock(this->Internal->Consumer->ConsumerMutex);
    double actualTime;

    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
    vtkSmartPointer<vtkCellArray> verts = vtkSmartPointer<vtkCellArray>::New();

    double x[3] = {1.0, 0.0, 0.0};
    double y[3] = {0.0, 0.0, 1.0};
    double z[3] = {0.0, 0.0, 0.0};
    for (unsigned int i = 0; i < 3; i++) {
      vtkIdType pid[1];
      pid[0] = points->InsertNextPoint(x[i], y[i], z[i]);
      verts->InsertNextCell(1, pid);

    }
    printf("points: %u\n", points->GetNumberOfPoints());

    vtkSmartPointer<vtkPolyData> polyData = vtkSmartPointer<vtkPolyData>::New();
    polyData->SetPoints(points);
    polyData->SetVerts(verts);

    if (polyData) {
      printf("request %f, returning %f\n", timeRequest, timeRequest);
      output->GetInformation()->Set(vtkDataObject::DATA_TIME_STEP(), 1);
      output->ShallowCopy(polyData);
    }
  }

//  request->Set(vtkStreamingDemandDrivenPipeline::CONTINUE_EXECUTING(), 1);
//  vtkTable* calibration = vtkTable::GetData(outputVector,1);
//  vtkTable *t = this->Interpreter->GetCalibrationTable();
//  calibration->ShallowCopy(t);

  return 1;
}
