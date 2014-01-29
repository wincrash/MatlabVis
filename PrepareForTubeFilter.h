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
#ifndef __PrepareForTubeFilter_h
#define __PrepareForTubeFilter_h

#include "vtkPolyDataAlgorithm.h"
#include "vtkSmartPointer.h"

class vtkDataArray;

class  PrepareForTubeFilter : public vtkPolyDataAlgorithm {
public:
    static PrepareForTubeFilter *New();
    vtkTypeRevisionMacro(PrepareForTubeFilter, vtkPolyDataAlgorithm);
    void PrintSelf(ostream& os, vtkIndent indent);

protected:
    PrepareForTubeFilter();
    ~PrepareForTubeFilter();

    // Usual data generation method
    virtual int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *);

    virtual int FillInputPortInformation(int port, vtkInformation *info);

private:
    PrepareForTubeFilter(const PrepareForTubeFilter&); // Not implemented.
    void operator=(const PrepareForTubeFilter&); // Not implemented.
};

#endif
