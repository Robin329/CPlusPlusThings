//
// Created by renbin jiang on 2022/5/22.
//
// -----------------------------------------------------------------------------
//
// Chapter 12 Examples
/*
   These require the files that you can find in 'Graphics Files' in my git.
*/
//
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Graph.h"
#include "Simple_window.h"

// -----------------------------------------------------------------------------

int main() {
    using namespace Graph_lib;
    
    Simple_window win{ Point{100,100}, 600, 400, "My Window" };
    
    win.wait_for_button();
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------