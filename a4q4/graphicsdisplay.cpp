//
//  GraphicsDisplay.cpp
//  a4q4
//
//  Created by 马弘德 on 2020/3/25.
//  Copyright © 2020 Mason. All rights reserved.
//

#include "graphicsdisplay.hpp"

GraphicsDisplay::GraphicsDisplay(int n): SquareSize{500 / n}{
    int size = 500 / n;
    for (int r = 0; r < size; r += size){
        for (int c = 0; c < size; c += size){
            xw.fillRectangle(r, c, size, size, Xwindow::Blue);
        }
    }
}

void GraphicsDisplay::notify(Subject<Info, State> &whoNotified){
    if (whoNotified.getInfo().colour == Colour::White){
        xw.fillRectangle(whoNotified.getInfo().row * SquareSize,
                         whoNotified.getInfo().col * SquareSize,
                         SquareSize, SquareSize, Xwindow::White);
    }
    if (whoNotified.getInfo().colour == Colour::Black){
        xw.fillRectangle(whoNotified.getInfo().row * SquareSize,
                         whoNotified.getInfo().col * SquareSize,
                         SquareSize, SquareSize, Xwindow::Black);
    }
}
