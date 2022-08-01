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


#include "MainWindow.h"

#include <iostream>
//#include "ParameterWindow.h"
//#include "PlotCartesianWidget.h"
//#include "Plot3DWidget.h"
//#include "PlotPolarWidget.h"
//#include "LitSphereWindow.h"
//#include "PlotCartesianWindow.h"
//#include "ImageSliceWindow.h"
//#include "IBLWindow.h"
//#include "ShowingDockWidget.h"
//#include "ViewerWindow.h"



MainWindow::MainWindow()
{
    glfwSetErrorCallback(glfw_error_callback);

    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW" << std::endl;
        glfwTerminate();
        return;
    }
    glfwWindowHint(GLFW_MAXIMIZED, GL_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    mWindow = glfwCreateWindow(800, 600, "BRDF Explorer", NULL, NULL);

    if (mWindow == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(mWindow);
    gladLoadGL();
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking

    ImGui::StyleColorsDark();
    ImGuiStyle& style = ImGui::GetStyle();

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    const char* glsl_version = "#version 130";
    ImGui_ImplGlfw_InitForOpenGL(mWindow, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    glfwSetFramebufferSizeCallback(mWindow, framebuffer_size_callback);

#if 0
    setWindowTitle( "BRDF Explorer" );

    // create the parameter window
    paramWnd = new ParameterWindow();

    viewer3D = new Plot3DWidget( this->windowHandle(), paramWnd->getBRDFList() );
    connect( paramWnd, SIGNAL(incidentDirectionChanged(float,float)), viewer3D, SLOT(incidentDirectionChanged(float,float)) );
    connect( paramWnd, SIGNAL(graphParametersChanged(bool,bool)), viewer3D, SLOT(graphParametersChanged(bool,bool)) );
    connect( paramWnd, SIGNAL(brdfListChanged(std::vector<brdfPackage>)), viewer3D, SLOT(brdfListChanged(std::vector<brdfPackage>)) );
    plot3D = new ViewerWindow( viewer3D );

    cartesianThetaV = new PlotCartesianWindow( paramWnd, THETA_V_PLOT );
    cartesianThetaH = new PlotCartesianWindow( paramWnd, THETA_H_PLOT );
    cartesianThetaD = new PlotCartesianWindow( paramWnd, THETA_D_PLOT );
    cartesianAlbedo = new PlotCartesianWindow( paramWnd, ALBEDO_PLOT );

    viewer2D = new PlotPolarWidget( this->windowHandle(), paramWnd->getBRDFList() );
    connect( paramWnd, SIGNAL(incidentDirectionChanged(float,float)), viewer2D, SLOT(incidentDirectionChanged(float,float)) );
    connect( paramWnd, SIGNAL(graphParametersChanged(bool,bool)), viewer2D, SLOT(graphParametersChanged(bool,bool)) );
    connect( paramWnd, SIGNAL(brdfListChanged(std::vector<brdfPackage>)), viewer2D, SLOT(brdfListChanged(std::vector<brdfPackage>)) );
    polarPlot = new ViewerWindow(viewer2D);

    viewerSphere = new LitSphereWindow( paramWnd );

    ibl = new IBLWindow( paramWnd );

    imageSlice = new ImageSliceWindow( paramWnd );

    
    
    
    ShowingDockWidget* Plot3DWidget = new ShowingDockWidget("3D Plot", this);
    Plot3DWidget->setWidget( plot3D );
    addDockWidget( Qt::RightDockWidgetArea, Plot3DWidget );
    
    
    

    ShowingDockWidget* paramsWidget = new ShowingDockWidget(tr("BRDF Parameters"), this);
    paramsWidget->setWidget( paramWnd );
    addDockWidget( Qt::LeftDockWidgetArea, paramsWidget );

    ShowingDockWidget* PlotPolarWidget = new ShowingDockWidget(tr("Polar Plot"), this);
    PlotPolarWidget->setWidget( polarPlot );
    addDockWidget( Qt::RightDockWidgetArea, PlotPolarWidget );

    ShowingDockWidget* thetaVWidget = new ShowingDockWidget(tr("Theta V"), this);
    thetaVWidget->setWidget( cartesianThetaV );
    addDockWidget( Qt::RightDockWidgetArea, thetaVWidget );

    ShowingDockWidget* thetaHWidget = new ShowingDockWidget(tr("Theta H"), this);
    thetaHWidget->setWidget( cartesianThetaH );
    addDockWidget( Qt::RightDockWidgetArea, thetaHWidget );

    ShowingDockWidget* thetaDWidget = new ShowingDockWidget(tr("Theta D"), this);
    thetaDWidget->setWidget( cartesianThetaD );
    addDockWidget( Qt::RightDockWidgetArea, thetaDWidget );

    ShowingDockWidget* albedoWidget = new ShowingDockWidget(tr("Albedo"), this);
    albedoWidget->setWidget( cartesianAlbedo );
    addDockWidget( Qt::RightDockWidgetArea, albedoWidget );

    tabifyDockWidget( Plot3DWidget, albedoWidget);
    tabifyDockWidget( albedoWidget, thetaHWidget);
    tabifyDockWidget( thetaHWidget, thetaDWidget );
    tabifyDockWidget( thetaDWidget, thetaVWidget );
    tabifyDockWidget( thetaVWidget, PlotPolarWidget );

    ShowingDockWidget* litSphereWidget = new ShowingDockWidget(tr("Lit Sphere"), this);
    litSphereWidget->setWidget( viewerSphere );
    addDockWidget( Qt::RightDockWidgetArea, litSphereWidget );


    ShowingDockWidget* imageSliceWidget = new ShowingDockWidget(tr("Image Slice"), this);
    imageSliceWidget->setWidget( imageSlice );
    addDockWidget( Qt::RightDockWidgetArea, imageSliceWidget );

    ShowingDockWidget* iblWidget = new ShowingDockWidget(tr("Lit Object"), this);
    iblWidget->setWidget( ibl );
    addDockWidget( Qt::RightDockWidgetArea, iblWidget );


    tabifyDockWidget( imageSliceWidget, iblWidget );
    tabifyDockWidget( iblWidget, litSphereWidget );
    //tabifyDockWidget( litSphereWidget, imageSliceWidget );


    setCorner( Qt::BottomLeftCorner, Qt::LeftDockWidgetArea );
    setCorner( Qt::BottomRightCorner, Qt::RightDockWidgetArea );

    setCentralWidget( new QWidget() ); // dummy central widget
    centralWidget()->hide();

    QMenu* fileMenu = menuBar()->addMenu(tr("&File"));
    QAction* openBRDF = fileMenu->addAction( "Open BRDF..." );
    openBRDF->setShortcut( QKeySequence("Ctrl+O") );
    connect( openBRDF, SIGNAL(triggered()), paramWnd, SLOT(openBRDFFromFile()) );
    fileMenu->addAction( "&Quit", this, SLOT(close()), QKeySequence("Ctrl+Q") );

    QMenu* utilMenu = menuBar()->addMenu(tr("&Utilities"));
    QAction* reloadAuxShaders = utilMenu->addAction( "Reload Auxiliary Shaders" );
    connect( reloadAuxShaders, SIGNAL(triggered()), ibl->getWidget(), SLOT(reloadAuxShaders()) );

    QMenu* helpMenu = menuBar()->addMenu(tr("&Help"));
    QAction* helpAbout = helpMenu->addAction( "About..." );
    connect( helpAbout, SIGNAL(triggered()), this, SLOT(about()) );

    // make sure everything has the correct incident direction param values at the start
    paramWnd->emitIncidentDirectionChanged();
#endif
}


MainWindow::~MainWindow()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(mWindow);

}

void MainWindow::Refresh()
{
#if 0
    viewer2D->updateGL();
    viewer3D->updateGL();
    viewerSphere->getWidget()->updateGL();
    cartesianAlbedo->getWidget()->updateGL();
    cartesianThetaD->getWidget()->updateGL();
    cartesianThetaH->getWidget()->updateGL();
    cartesianThetaV->getWidget()->updateGL();
    imageSlice->getWidget()->updateGL();
    ibl->getWidget()->updateGL();
#endif
}

void MainWindow::About()
{
    ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
    if (ImGui::BeginPopupModal("DunDun", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("Copyright Disney Enterprises, Inc. All rights reserved.");
        ImGui::EndPopup();
    }
}

void MainWindow::OpenBRDFFile(std::string filename, bool emitChanges)
{

}

void MainWindow::DockSpace(bool* pOpen)
{
        static bool opt_fullscreen = true;
        static bool opt_padding = false;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // because it would be confusing to have two docking targets within each others.
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen)
        {
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }
        else
        {
            dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
        }

        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        {
            window_flags |= ImGuiWindowFlags_NoBackground;
        }

        if (!opt_padding)
        {
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        }

        if (ImGui::Begin("DockSpace Demo", pOpen, window_flags))
        {

            if (!opt_padding)
            {
                ImGui::PopStyleVar();
            }

            if (opt_fullscreen)
            {
                ImGui::PopStyleVar(2);
            }

            // Submit the DockSpace
            ImGuiIO& io = ImGui::GetIO();
            if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
            {
                ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
                ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
            }
            else
            {
                //ShowDockingDisabledMessage();
            }

            if (ImGui::BeginMenuBar())
            {
                if (ImGui::BeginMenu("File"))
                {
                    if (ImGui::MenuItem("Open BRDF...", "CTRL+O", false, pOpen != NULL))
                    {
                        bool success = false;
                        std::vector<COMDLG_FILTERSPEC> spec = { { L"BRDF Files (*.brdf *.binary *.dat *.bparam *.bsdf)", L"*.brdf;*.binary;*.dat;*.bparam;*.bsdf" } };
                        std::wstring fileName;

                        OpenDialogBox(spec, fileName, success);
                        if (success)
                        {
                            std::string name(fileName.begin(), fileName.end());
                            OpenBRDFFile(name, false);
                        }
                    }

                    if (ImGui::MenuItem("Close", "CTRL+Q", false, pOpen != NULL))
                    {
                        glfwSetWindowShouldClose(mWindow, true);
                    }
                    ImGui::EndMenu();
                }

                if (ImGui::BeginMenu("Utilities"))
                {
                    if (ImGui::MenuItem("Reload Auxiliary Shaders", nullptr, false, pOpen != NULL))
                    {

                    }

                    ImGui::EndMenu();
                }

                if (ImGui::BeginMenu("Help"))
                {
                    if (ImGui::MenuItem("About...", nullptr, false, pOpen != NULL))
                    {
                        ImGui::OpenPopup("DunDun");
                    }

                    ImGui::EndMenu();
                }

                ImGui::EndMenuBar();
            }

            ImGui::End();
        }
}

void MainWindow::Run()
{
    while (!glfwWindowShouldClose(mWindow))
    {
        glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        static bool showDemoWindow = true;
        static bool dockspace = true;

        DockSpace(&dockspace);

        ImGui::ShowDemoWindow(&showDemoWindow);

        ImGui::Render();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(mWindow);
    }
}
void MainWindow::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void GLAPIENTRY MainWindow::MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
    fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
        (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
        type, severity, message);
}

bool MainWindow::OpenDialogBox(std::vector<COMDLG_FILTERSPEC> rgSpec, std::wstring& fileName, bool& success)
{
    PWSTR pszFilePath = nullptr;

    HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    if (SUCCEEDED(hr))
    {
        IFileOpenDialog* pFileOpen;

        hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));

        if (SUCCEEDED(hr))
        {
            pFileOpen->SetFileTypes(rgSpec.size(), &rgSpec[0]);
            hr = pFileOpen->Show(NULL);
            if (SUCCEEDED(hr))
            {
                IShellItem* pItem;
                hr = pFileOpen->GetResult(&pItem);
                if (SUCCEEDED(hr))
                {
                    hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
                    if (SUCCEEDED(hr))
                    {
                        success = true;
                        LPWSTR a;
                        pItem->GetDisplayName(SIGDN_FILESYSPATH, &a);
                        fileName = a;
                    }
                    pItem->Release();
                }
            }
            pFileOpen->Release();
        }
        CoUninitialize();
    }
    return true;
}
