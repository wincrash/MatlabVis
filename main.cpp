#include <iostream>

using namespace std;

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

std::string StrypuSpinduliai="ElementuiSpinduliaiR";
double StrypuSpinduliuScale=0.005;

#define VTK_CREATE(type, name) \
    type* name = type::New()

vtkDataSetReader* ReadFile(string filename){
    VTK_CREATE(vtkDataSetReader,readeris);
    readeris->SetFileName(filename.c_str());
    readeris->ReadAllScalarsOn();
    readeris->ReadAllVectorsOn();
    readeris->ReadAllTensorsOn();
    readeris->Update();
    return readeris;
}



void Ground(vtkPolyData*output,vtkRenderer *renderer,double *color)
{
    VTK_CREATE(vtkPolyData,poly);
    VTK_CREATE(vtkPoints,points);
    points->InsertNextPoint(output->GetPoint(output->GetNumberOfPoints()-1));
    points->InsertNextPoint(output->GetPoint(output->GetNumberOfPoints()-2));
    points->InsertNextPoint(output->GetPoint(output->GetNumberOfPoints()-3));
    points->InsertNextPoint(output->GetPoint(output->GetNumberOfPoints()-4));

    VTK_CREATE(vtkCellArray,cells);
    cells->Allocate(1,1);
    cells->InsertNextCell(4);
    cells->InsertCellPoint(0);
    cells->InsertCellPoint(1);
    cells->InsertCellPoint(2);
    cells->InsertCellPoint(3);
    poly->SetPolys(cells);
    poly->SetPoints(points);


    VTK_CREATE(vtkTransform,translation);
    translation->Scale(1.1,1.1,1);


    VTK_CREATE(vtkTransformPolyDataFilter,transformFilter);

    transformFilter->SetInputData(poly);
    transformFilter->SetTransform(translation);
    transformFilter->Update();

    VTK_CREATE(vtkPolyDataMapper,mapper);
    mapper->SetInputConnection(transformFilter->GetOutputPort());
    // mapper->SetScalarRange(1,10);
    VTK_CREATE(vtkActor,actor);
    actor->SetMapper(mapper);
    actor->GetProperty()->SetColor(color);
    actor->GetProperty()->LightingOff();
    renderer->AddActor(actor);

}




void ScalarBar(vtkMapper *mapper,vtkRenderer *renderer,string title)
{
    VTK_CREATE(vtkScalarBarActor,scalarBar);
    scalarBar->SetLookupTable(mapper->GetLookupTable());
    scalarBar->SetTitle(title.c_str());
    scalarBar->SetNumberOfLabels(10);
    scalarBar->SetLookupTable( mapper->GetLookupTable());
    scalarBar->SetLabelFormat("%.4g");
    scalarBar->VisibilityOn();
    renderer->AddActor2D(scalarBar);
}


void AddSimpleTubeFilter(vtkAlgorithmOutput*output,vtkRenderer *renderer)
{
    VTK_CREATE(vtkTubeFilter,tubes);
    tubes->SetNumberOfSides(12);
    tubes->SetRadius(0.05);
    tubes->CappingOn();
    tubes->SetInputConnection(output);
    VTK_CREATE(vtkPolyDataMapper,mapper);
    mapper->SetInputConnection(tubes->GetOutputPort());
    // mapper->SetScalarRange(1,10);
    VTK_CREATE(vtkActor,actor);
    actor->SetMapper(mapper);
    renderer->AddActor(actor);
}
void AddTubeFilter(vtkAlgorithmOutput*output,vtkRenderer *renderer)
{
    VTK_CREATE(PrepareForTubeFilter,prepare);
    prepare->SetInputConnection(output);
    prepare->Update();
    VTK_CREATE(vtkTubeFilter,tubes);
    tubes->SetNumberOfSides(12);
    tubes->SetRadius(StrypuSpinduliuScale);
    tubes->CappingOn();
    tubes->SetInputConnection(prepare->GetOutputPort());
    tubes->SetVaryRadiusToVaryRadiusByScalar();
    tubes->SetInputArrayToProcess(vtkDataSetAttributes::SCALARS, 0, 0, vtkDataObject::FIELD_ASSOCIATION_POINTS, StrypuSpinduliai.c_str());
    tubes->Update();
    VTK_CREATE(vtkPolyDataMapper,mapper);
    mapper->SetInputConnection(tubes->GetOutputPort());
    mapper->ColorByArrayComponent("Elementuitempimai",0);
    mapper->SetScalarModeToUseCellFieldData();
    mapper->SetScalarRange(242.04*-1e+6,275.9e+6);
    //mapper->SetScalarRange(tubes->GetOutput()->GetCellData()->GetArray("Elementuitempimai")->GetRange(-1));
    //mapper->ColorByArrayComponent(StrypuSpinduliai.c_str(),0);
    //mapper->SetScalarModeToUsePointFieldData();
    //mapper->SetScalarRange(tubes->GetOutput()->GetPointData()->GetArray(StrypuSpinduliai.c_str())->GetRange(-1));
    ScalarBar(mapper,renderer,"Itempimai");
    VTK_CREATE(vtkActor,actor);
    actor->SetMapper(mapper);
    renderer->AddActor(actor);
}

void SimpleSphereGlyph(vtkAlgorithmOutput*output,vtkRenderer *renderer,double *color){
    VTK_CREATE(vtkSphereSource,sphere);
    sphere->SetRadius(0.1);
    sphere->SetPhiResolution(12);
    sphere->SetThetaResolution(12);
    VTK_CREATE(vtkGlyph3D,glyph);
    glyph->SetSourceConnection(sphere->GetOutputPort());
    glyph->SetInputConnection(output);
    glyph->ScalingOff();
    VTK_CREATE(vtkPolyDataMapper,mapper);
    mapper->SetInputConnection(glyph->GetOutputPort());
    VTK_CREATE(vtkActor,actor);
    mapper->ScalarVisibilityOff();
    actor->SetMapper(mapper);
    actor->GetProperty()->SetColor(color[0],color[1],color[2]);
    renderer->AddActor(actor);
}

void SimpleVectorGlyph(vtkAlgorithmOutput*output,vtkRenderer *renderer,string name,int direction,double scale,double *color){

    VTK_CREATE(vtkArrayCalculator,cal);
    cal->SetInputConnection(output);
    cal->SetAttributeModeToUsePointData();
    cal->AddScalarVariable("var",name.c_str(),direction);
    cal->SetFunction("abs(var)");
    cal->SetResultArrayName("rez");
    cal->Update();

    VTK_CREATE(vtkThresholdPoints,threshold);
    threshold->SetInputConnection(cal->GetOutputPort());
    threshold->ThresholdByUpper(0.00001);
    threshold->SetInputArrayToProcess(vtkDataSetAttributes::SCALARS, 0, 0, vtkDataObject::FIELD_ASSOCIATION_POINTS, "rez");
    threshold->Update();

    VTK_CREATE(vtkArrowSource,arrow);
    VTK_CREATE(vtkGlyph3D,glyph);
    glyph->SetSourceConnection(arrow->GetOutputPort());
    glyph->SetInputConnection(threshold->GetOutputPort());
    glyph->SetScaleModeToScaleByVector();
    glyph->SetScaleFactor(scale);
    glyph->SetScaleModeToDataScalingOff();
    glyph->OrientOn();
    glyph->SetInputArrayToProcess(vtkDataSetAttributes::VECTORS, 0, 0, vtkDataObject::FIELD_ASSOCIATION_POINTS, name.c_str());

    VTK_CREATE(vtkTransform,tran);
    tran->Translate(-1,0,0);
    glyph->SetSourceTransform(tran);
    VTK_CREATE(vtkPolyDataMapper,mapper);
    mapper->SetInputConnection(glyph->GetOutputPort());
    VTK_CREATE(vtkActor,actor);
    mapper->ScalarVisibilityOff();
    actor->SetMapper(mapper);
    actor->GetProperty()->SetColor(color[0],color[1],color[2]);
    renderer->AddActor(actor);
}



int main (int argc, char **argv)
{

    vtkDataSetReader* readeris=ReadFile("/home/ruslan/matlab.vtk");
    VTK_CREATE(vtkRenderer,renderer);
    VTK_CREATE(vtkRenderWindow,renderWindow);
    VTK_CREATE(vtkRenderWindowInteractor,renderWindowInteractor);
    renderWindow->SetSize(900,900);
    renderWindow->AddRenderer(renderer);
    renderer->ResetCamera();
    renderWindowInteractor->SetRenderWindow(renderWindow);
    VTK_CREATE(vtkInteractorStyleTrackballCamera,style);
    renderWindowInteractor->SetInteractorStyle(style);


    AddTubeFilter(readeris->GetOutputPort(),renderer);


    double colorGlpyh[3];
    colorGlpyh[0]=0.5;
    colorGlpyh[1]=0.5;
    colorGlpyh[2]=0;

    SimpleSphereGlyph(readeris->GetOutputPort(),renderer,colorGlpyh);
    double colorX[3];
    double colorY[3];
    double colorZ[3];
    colorX[0]=1;
    colorX[1]=0;
    colorX[2]=0;

    colorY[0]=0;
    colorY[1]=1;
    colorY[2]=0;

    colorZ[0]=0;
    colorZ[1]=0;
    colorZ[2]=1;
    SimpleVectorGlyph(readeris->GetOutputPort(),renderer,"ApkrovosMazguoseX",0,1,colorX);
    SimpleVectorGlyph(readeris->GetOutputPort(),renderer,"ApkrovosMazguoseY",1,1,colorY);
    SimpleVectorGlyph(readeris->GetOutputPort(),renderer,"ApkrovosMazguoseZ",2,1,colorZ);

    double whiteColor[3];
    whiteColor[0]=1;
    whiteColor[1]=1;
    whiteColor[2]=1;


    Ground(vtkPolyData::SafeDownCast(readeris->GetOutput()),renderer,whiteColor);
    renderWindow->Render();
    renderWindowInteractor->Start();

    return EXIT_SUCCESS;
}
