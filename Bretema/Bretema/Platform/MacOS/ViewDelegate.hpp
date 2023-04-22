//
//  ViewDelegate.hpp
//  Bretema
//
//  Created by Cl0ud7.
//

#ifndef ViewDelegate_hpp
#define ViewDelegate_hpp

#include <stdio.h>
#include "MetalRenderer.hpp"

namespace Bretema {

    class ViewDelegate : public MTK::ViewDelegate
    {
    public:
            ViewDelegate( MTL::Device* device );
            virtual ~ViewDelegate() override;
            virtual void drawInMTKView( MTK::View* view ) override;

    private:
            MetalRenderer* m_Renderer;
    };
}

#endif /* ViewDelegate_hpp */
