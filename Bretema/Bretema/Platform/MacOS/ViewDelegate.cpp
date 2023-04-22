//
//  ViewDelegate.cpp
//  Bretema
//
//  Created by Cl0ud7.
//

#include "ViewDelegate.hpp"

namespace Bretema {

    ViewDelegate::ViewDelegate(MTL::Device* device) : MTK::ViewDelegate(), m_Renderer(new MetalRenderer(device))
    {

    }

    ViewDelegate::~ViewDelegate()
    {
        delete m_Renderer;
    }

    void ViewDelegate::drawInMTKView(MTK::View* view)
    {
        m_Renderer->draw(view);
    }
}
