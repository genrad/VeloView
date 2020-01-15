#include "vtkRadarProvider.h"
#include "vtkRadarPacketInterpreter.h"
// #include "vtkVelodyneTransformInterpolator.h"
// #include "vtkVelodynePacketInterpreter.h"

#include <vtkInformation.h>

#include <boost/filesystem.hpp>
#include <sstream>

//-----------------------------------------------------------------------------
int vtkRadarProvider::FillOutputPortInformation(int port, vtkInformation* info)
{
  if ( port == 0 )
  {
    info->Set(vtkDataObject::DATA_TYPE_NAME(), "vtkPolyData" );
    return 1;
  }
//  if ( port == 1 )
//  {
//    info->Set(vtkDataObject::DATA_TYPE_NAME(), "vtkTable" );
//    return 1;
//  }
  return 0;
}

//-----------------------------------------------------------------------------
std::string vtkRadarProvider::GetSensorInformation()
{
  return "";
//  return this->Interpreter->GetSensorInformation();
}

//-----------------------------------------------------------------------------
void vtkRadarProvider::SetCalibrationFileName(const std::string &filename)
{
  if (filename == this->CalibrationFileName)
  {
    return;
  }

  if (!boost::filesystem::exists(filename) ||
    boost::filesystem::is_directory(filename))
  {
    std::ostringstream errorMessage("Invalid sensor configuration file ");
    errorMessage << filename << ": ";
    if (!boost::filesystem::exists(filename))
    {
      errorMessage << "File not found!";
    }
    else
    {
      errorMessage << "It is a directory!";
    }
    vtkErrorMacro(<< errorMessage.str());
    return;
  }
  this->CalibrationFileName = filename;
  this->Modified();
}

//-----------------------------------------------------------------------------
void vtkRadarProvider::SetDummyProperty(int)
{
  return this->Modified();
}

//-----------------------------------------------------------------------------
vtkMTimeType vtkRadarProvider::GetMTime()
{
  //if (this->Interpreter)
  //{
  //  return std::max(this->Superclass::GetMTime(), this->Interpreter->GetMTime());
  //}
  return this->Superclass::GetMTime();
}

//-----------------------------------------------------------------------------
vtkRadarProvider::vtkRadarProvider()
{
  this->SetNumberOfInputPorts(0);
  this->SetNumberOfOutputPorts(1);
}

//-----------------------------------------------------------------------------
int vtkRadarProvider::RequestInformation(vtkInformation *request,
                                         vtkInformationVector **inputVector,
                                         vtkInformationVector *outputVector)
{
//  if (!this->Interpreter)
//  {
//    vtkErrorMacro(<< "Please select an Packet Interpreter" << endl);
//    printf("fail\n");
//    return 0;
//  }

  //// load the calibration file only now to allow to set it before the interpreter.
  //if (this->Interpreter->GetCalibrationFileName() != this->CalibrationFileName)
  //{
  //  this->Interpreter->LoadCalibration(this->CalibrationFileName);
  //}
  return this->Superclass::RequestInformation(request, inputVector, outputVector);
}

//-----------------------------------------------------------------------------
vtkCxxSetObjectMacro(vtkRadarProvider, Interpreter, vtkRadarPacketInterpreter)
