//
//  MetalWindow.cpp
//  Bretema
//
//  Created by Cl0ud7.
//

#include "MetalWindow.hpp"

namespace Bretema {

    MetalWindow::MetalWindow(const WindowConfig& config)
    {
        Init(config);
    }

    MetalWindow::~MetalWindow()
    {
        
        Close();
        m_View->release();
        m_Window->release();
        m_Device->release();
        
    }

    void MetalWindow::Init(const WindowConfig& config)
    {
        
        // Returns the default Device selected for Metal
        m_Device = MTL::CreateSystemDefaultDevice();
    
        if (!glfwInit())
        {
            throw ("ERROR: Can't initialize GLFW");
        }
        
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        m_GLFWWindow = glfwCreateWindow(config.Height, config.Width, (config.Title+std::string(" [Metal]")).c_str(), NULL, NULL);

        if (m_GLFWWindow == NULL)
        {
            throw ("ERROR: Can't create GLFW window");
        }

        m_Window = static_cast<NS::Window *>(glfwGetCocoaWindow(m_GLFWWindow));

        // Window frame
        CGRect frame{{0,0}, {static_cast<CGFloat>(config.Height),static_cast<CGFloat>(config.Width)}};

        // View that display Metal objects
        m_View = MTK::View::alloc()->init(frame, m_Device);

        m_View->setColorPixelFormat(MTL::PixelFormat::PixelFormatBGRA8Unorm_sRGB);
        m_View->setClearColor(MTL::ClearColor::Make(0.2, 0.3, 0.3, 1.0));

        m_ViewDelegate = new ViewDelegate(m_Device);
        //m_View->setDelegate(m_ViewDelegate);

        // Set the view to the window
        m_Window->setContentView(m_View);

        // Moves the window
        m_Window->makeKeyAndOrderFront(nullptr);
        
//        glfwTerminate();
    }

    void MetalWindow::Update()
    {
        glfwPollEvents();
        m_ViewDelegate->drawInMTKView(m_View);
    }
    
    void MetalWindow::Close()
    {
        glfwDestroyWindow(m_GLFWWindow);
    }
}
