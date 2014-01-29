#ifndef __Functions_h
#define __Functions_h


#include <vtkSphereSource.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include "vtkDataSetReader.h"
#include "vtkTubeFilter.h"
#include "PrepareForTubeFilter.h"
#include "vtkDataSetAttributes.h"
#include "vtkDataSetWriter.h"
#include "vtkPointData.h"
#include "vtkCellData.h"
#include <string>
#include "vtkSphereSource.h"
#include "vtkArrowSource.h"
#include "vtkGlyph3D.h"
#include "vtkProperty.h"
#include "vtkTransform.h"
#include "vtkVectorNorm.h"
#include "vtkThresholdPoints.h"
#include "vtkArrayCalculator.h"
#include "vtkScalarBarActor.h"
#include "vtkScalarBarWidget.h"
#include "vtkInteractorStyleTrackballCamera.h"
#include "vtkCellArray.h"
#include "vtkTransformPolyDataFilter.h"
#include "vtkTransform.h"
#include <string>
#include <iostream>

using namespace std;


#define VTK_CREATE(type, name) \
    type* name = type::New()

void Ground(vtkPolyData*output,vtkRenderer *renderer,double *color);
//###########################################################################################
vtkDataSetReader* ReadFile(string filename);

//###########################################################################################

void ScalarBar(vtkMapper *mapper,vtkRenderer *renderer,string title);

//###########################################################################################

void AddSimpleTubeFilter(vtkAlgorithmOutput*output,vtkRenderer *renderer);


//###########################################################################################

void AddTubeFilter(vtkAlgorithmOutput*output,vtkRenderer *renderer,string ScalarBarTitle,double StrypuSpinduliuScale,string StrypuSpinduliai,double  rangeX,double rangeY);

//###########################################################################################

void SimpleSphereGlyph(vtkAlgorithmOutput*output,vtkRenderer *renderer,double *color);

//###########################################################################################

void SimpleVectorGlyph(vtkAlgorithmOutput*output,vtkRenderer *renderer,string name,int direction,double scale,double *color);

//###########################################################################################




#endif
