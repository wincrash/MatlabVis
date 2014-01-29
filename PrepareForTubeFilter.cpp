/*

 #     # ###  #####  ######     #    ######  ####### ######  ####### #     #
 #     #  #  #     # #     #   # #   #     #    #    #     # #       ##   ##
 #     #  #  #       #     #  #   #  #     #    #    #     # #       # # # #
 #     #  #   #####  ######  #     # ######     #    #     # #####   #  #  #
  #   #   #        # #       ####### #   #      #    #     # #       #     #
   # #    #  #     # #       #     # #    #     #    #     # #       #     #
    #    ###  #####  #       #     # #     #    #    ######  ####### #     #


 * Author       : Ruslan Pacevic
 * E-mail       : rpa@sc.vgtu.lt
 * Vendor       : VGTU
 * Home page    : http://lsl.vgtu.lt/vispartdem
 */
#include "PrepareForTubeFilter.h"
#include "vtkCell.h"
#include "vtkCellData.h"
#include "vtkIdList.h"
#include "vtkInformation.h"
#include "vtkInformationVector.h"
#include "vtkObjectFactory.h"
#include "vtkPointData.h"
#include "vtkUnstructuredGrid.h"
#include "vtkPolyData.h"
#include "vtkCellArray.h"
#include <vector>
#include "vtkDoubleArray.h"


vtkCxxRevisionMacro(PrepareForTubeFilter, "$Revision: 1.71 $");
vtkStandardNewMacro(PrepareForTubeFilter);


PrepareForTubeFilter::PrepareForTubeFilter() {
    // by default process active point scalars
    this->SetInputArrayToProcess(0, 0, 0, vtkDataObject::FIELD_ASSOCIATION_POINTS_THEN_CELLS,
                                 vtkDataSetAttributes::SCALARS);
}

PrepareForTubeFilter::~PrepareForTubeFilter() {
}

int PrepareForTubeFilter::RequestData(
        vtkInformation *vtkNotUsed(request),
        vtkInformationVector **inputVector,
        vtkInformationVector *outputVector) {
    // get the info objects
    vtkInformation *inInfo = inputVector[0]->GetInformationObject(0);
    vtkInformation *outInfo = outputVector->GetInformationObject(0);

    // get the input and ouptut
    vtkPolyData *input = vtkPolyData::SafeDownCast(
                inInfo->Get(vtkDataObject::DATA_OBJECT()));

    vtkPolyData *output = vtkPolyData::SafeDownCast(
                outInfo->Get(vtkDataObject::DATA_OBJECT()));



    double x[3];
    vtkPointData *pd = input->GetPointData(), *outPD = output->GetPointData();
    vtkCellData *cd = input->GetCellData(), *outCD = output->GetCellData();


    vtkDebugMacro( << "Executing threshold filter");


    // vtkDataArray *inScalars = this->GetInputArrayToProcess(0, inputVector);

    //if (!inScalars) {
    vtkDebugMacro( << "No scalar data to threshold");
    //    return 1;
    // }

    vtkCellArray*newlines=vtkCellArray::New();

    newlines->Allocate(1,1);
    cout<<"kiekisss "<<input->GetCellData()->GetNumberOfArrays()<<endl;
    for(int i=0;i<input->GetCellData()->GetNumberOfArrays();i++)
    {
        {    vtkDoubleArray*arr=vtkDoubleArray::New();

            arr->SetName(input->GetCellData()->GetArray(i)->GetName());
            arr->SetNumberOfComponents(input->GetCellData()->GetArray(i)->GetNumberOfComponents());
              output->GetPointData()->AddArray(arr);
        }
        { vtkDoubleArray*arr=vtkDoubleArray::New();
            arr->SetName(input->GetCellData()->GetArray(i)->GetName());
            arr->SetNumberOfComponents(input->GetCellData()->GetArray(i)->GetNumberOfComponents());
             output->GetCellData()->AddArray(arr);
        }

    }


    vtkPoints*newPoints=vtkPoints::New();

    newPoints->SetDataType(input->GetPoints()->GetDataType());
    vtkIdType* connections =
            (vtkIdType*) (((input->GetLines()->GetPointer())));
    int numberOfLines=input->GetNumberOfLines();
    for(int i=0;i<numberOfLines;i++)
    {
        int id1,id2;
        id1=connections[i*3+1];
        id2=connections[i*3+2];
        input->GetPoints()->GetPoint(id1,x);
        newPoints->InsertNextPoint(x);
        for(int k=0;k<input->GetCellData()->GetNumberOfArrays();k++)
        {
            output->GetPointData()->GetArray(k)->InsertNextTuple1(input->GetCellData()->GetArray(k)->GetTuple1(i));
        }
        input->GetPoints()->GetPoint(id2,x);
        newPoints->InsertNextPoint(x);
        for(int k=0;k<input->GetCellData()->GetNumberOfArrays();k++)
        {
            output->GetPointData()->GetArray(k)->InsertNextTuple1(input->GetCellData()->GetArray(k)->GetTuple1(i));
        }
        newlines->InsertNextCell(2);
        newlines->InsertCellPoint(newPoints->GetNumberOfPoints()-2);
        newlines->InsertCellPoint(newPoints->GetNumberOfPoints()-1);
        for(int k=0;k<input->GetCellData()->GetNumberOfArrays();k++)
        {
            output->GetCellData()->GetArray(k)->InsertNextTuple1(input->GetCellData()->GetArray(k)->GetTuple1(i));
        }
    }
    output->SetLines(newlines);
    output->SetPoints(newPoints);
     newPoints->Delete();
     newlines->Delete();

    output->Squeeze();
    return 1;
}


int PrepareForTubeFilter::FillInputPortInformation(int, vtkInformation *info) {
    info->Set(vtkAlgorithm::INPUT_REQUIRED_DATA_TYPE(), "vtkDataSet");
    return 1;
}

void PrepareForTubeFilter::PrintSelf(ostream& os, vtkIndent indent) {
    this->Superclass::PrintSelf(os, indent);

    os << indent << "Attribute Mode: " << 0 << endl;
}
