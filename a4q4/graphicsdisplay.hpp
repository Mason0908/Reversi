//
//  GraphicsDisplay.hpp
//  a4q4
//
//  Created by 马弘德 on 2020/3/25.
//  Copyright © 2020 Mason. All rights reserved.
//


#ifndef GRAPHICSDISPLAY_H
#define GRAPHICSDISPLAY_H
#include <iostream>
#include <vector>
#include "observer.hpp"
#include "state.hpp"
#include "window.hpp"
#include "info.hpp"
#include "subject.hpp"

class GraphicsDisplay: public Observer<Info, State> {
    int SquareSize;
    Xwindow xw;
    
public:
    GraphicsDisplay(int n);
    void notify(Subject<Info, State> &whoNotified) override;
};
#endif
