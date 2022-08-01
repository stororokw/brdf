/*
Copyright Disney Enterprises, Inc. All rights reserved.

This license governs use of the accompanying software. If you use the software, you
accept this license. If you do not accept the license, do not use the software.

1. Definitions
The terms "reproduce," "reproduction," "derivative works," and "distribution" have
the same meaning here as under U.S. copyright law. A "contribution" is the original
software, or any additions or changes to the software. A "contributor" is any person
that distributes its contribution under this license. "Licensed patents" are a
contributor's patent claims that read directly on its contribution.

2. Grant of Rights
(A) Copyright Grant- Subject to the terms of this license, including the license
conditions and limitations in section 3, each contributor grants you a non-exclusive,
worldwide, royalty-free copyright license to reproduce its contribution, prepare
derivative works of its contribution, and distribute its contribution or any derivative
works that you create.
(B) Patent Grant- Subject to the terms of this license, including the license
conditions and limitations in section 3, each contributor grants you a non-exclusive,
worldwide, royalty-free license under its licensed patents to make, have made,
use, sell, offer for sale, import, and/or otherwise dispose of its contribution in the
software or derivative works of the contribution in the software.

3. Conditions and Limitations
(A) No Trademark License- This license does not grant you rights to use any
contributors' name, logo, or trademarks.
(B) If you bring a patent claim against any contributor over patents that you claim
are infringed by the software, your patent license from such contributor to the
software ends automatically.
(C) If you distribute any portion of the software, you must retain all copyright,
patent, trademark, and attribution notices that are present in the software.
(D) If you distribute any portion of the software in source code form, you may do
so only under this license by including a complete copy of this license with your
distribution. If you distribute any portion of the software in compiled or object code
form, you may only do so under a license that complies with this license.
(E) The software is licensed "as-is." You bear the risk of using it. The contributors
give no express warranties, guarantees or conditions. You may have additional
consumer rights under your local laws which this license cannot change.
To the extent permitted under your local laws, the contributors exclude the
implied warranties of merchantability, fitness for a particular purpose and non-
infringement.
*/

#ifndef MAIMWINDOW_H
#define MAIMWINDOW_H
#include <vector>
#include <string>
#include <glad/glad.h> 
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "BRDFBase.h"

#include <ShObjIdl_core.h>

//class ParameterWindow;
//class ImageSliceWindow;
//class Plot3DWidget;
//class PlotPolarWidget;
//class LitSphereWindow;
//class PlotCartesianWindow;
//class IBLWindow;
//class ViewerWindow;
//class ShowingDockWidget;


class MainWindow
{
public:
    MainWindow();
    ~MainWindow();

    void Refresh();

    void About();

    void OpenBRDFFile(std::string filename, bool emitChanges);
    void DockSpace(bool* pOpen);
    void Run();
private:
    GLFWwindow*                 mWindow;
    std::vector<BRDFBase*>      mBrdfs;
    std::vector<brdfPackage>    mBrdfPackages;

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

    static void glfw_error_callback(int error, const char* description)
    {
        fprintf(stderr, "GLFW Error %d: %s\n", error, description);
    }

    static void GLAPIENTRY
        MessageCallback(GLenum source,
            GLenum type,
            GLuint id,
            GLenum severity,
            GLsizei length,
            const GLchar* message,
            const void* userParam);

    static bool OpenDialogBox(std::vector<COMDLG_FILTERSPEC> rgSpec, std::wstring& fileName, bool& success);

#if 0
    ParameterWindow* paramWnd;
    Plot3DWidget* viewer3D;
    PlotPolarWidget* viewer2D;
    ViewerWindow* polarPlot;
    ViewerWindow* plot3D;
    LitSphereWindow* viewerSphere;
    ImageSliceWindow* imageSlice;
    IBLWindow* ibl;

    PlotCartesianWindow* cartesianThetaV;
    PlotCartesianWindow* cartesianThetaD;
    PlotCartesianWindow* cartesianThetaH;
    PlotCartesianWindow* cartesianAlbedo;
#endif
};


#endif
