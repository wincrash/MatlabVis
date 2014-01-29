#include "Functions.h"

//PARAMETRAI
string ApkrovosMazguoseX="ApkrovosMazguoseX";
string ApkrovosMazguoseY="ApkrovosMazguoseY";
string ApkrovosMazguoseZ="ApkrovosMazguoseZ";
double whiteColor[3]={1,1,1};
double colorX[3]={1,0,0};
double colorY[3]={0,1,0};
double colorZ[3]={0,0,1};
double colorGlpyh[3]={0.5,0.5,0};
std::string StrypuSpinduliai="ElementuiSpinduliaiR";
double StrypuSpinduliuScale=0.005;
string ScalarBarTitle="Itempimai";
double windowSize[2]={900,900};
double ItempimuRange[2]={242.04*-1e+6,275.9e+6};

string filename="/home/ruslan/matlab.vtk";
// PARAMETRU PABAIGA



int main (int argc, char **argv)
{

    vtkDataSetReader* readeris=ReadFile(filename);
    VTK_CREATE(vtkRenderer,renderer);
    VTK_CREATE(vtkRenderWindow,renderWindow);
    VTK_CREATE(vtkRenderWindowInteractor,renderWindowInteractor);
    renderWindow->SetSize(windowSize[0],windowSize[1]);
    renderWindow->AddRenderer(renderer);
    renderer->ResetCamera();
    renderWindowInteractor->SetRenderWindow(renderWindow);
    VTK_CREATE(vtkInteractorStyleTrackballCamera,style);
    renderWindowInteractor->SetInteractorStyle(style);

    AddTubeFilter(readeris->GetOutputPort(),renderer,ScalarBarTitle,StrypuSpinduliuScale,StrypuSpinduliai,ItempimuRange[0],ItempimuRange[1]);
    SimpleSphereGlyph(readeris->GetOutputPort(),renderer,colorGlpyh);
    SimpleVectorGlyph(readeris->GetOutputPort(),renderer,ApkrovosMazguoseX.c_str(),0,1,colorX);
    SimpleVectorGlyph(readeris->GetOutputPort(),renderer,ApkrovosMazguoseY.c_str(),1,1,colorY);
    SimpleVectorGlyph(readeris->GetOutputPort(),renderer,ApkrovosMazguoseZ.c_str(),2,1,colorZ);
    Ground(vtkPolyData::SafeDownCast(readeris->GetOutput()),renderer,whiteColor);
    renderWindowInteractor->Render();
    renderWindowInteractor->Start();

    return EXIT_SUCCESS;
}
