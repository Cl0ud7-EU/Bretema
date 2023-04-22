//
//  Playground.cpp
//  Playground
//
//  Created by Cl0ud7.
//

#include <stdio.h>

#include "Bretema.hpp"

class Playground : public Bretema::Application
{
public:
    
    Playground()
    {
        
    }
    
    ~Playground(){}
    
};

Bretema::Application* Bretema::NewApp()
{
    return new Playground();
}
