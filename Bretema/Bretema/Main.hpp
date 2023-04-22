//
//  Main.cpp
//  Bretema
//
//  Created by Cl0ud7.
//

#include <iostream>

extern Bretema::Application* Bretema::NewApp();

int main(int argc, const char * argv[]) {
    
    auto Application = Bretema::NewApp();
    Application->Run();
    delete Application;
}
