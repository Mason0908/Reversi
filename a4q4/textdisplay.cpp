//
//  textdisplay.cpp
//  a4q4
//
//  Created by 马弘德 on 2020/3/24.
//  Copyright © 2020 Mason. All rights reserved.
//

#include "textdisplay.hpp"


TextDisplay::TextDisplay(int n): gridSize{n} {
    for (int row = 0; row < n; row++){
        std::vector<char> temp;
        for (int col = 0; col < n; col++){
            temp.emplace_back('-');
        }
        theDisplay.emplace_back(temp);
    }
    
}

void TextDisplay::notify(Subject<Info, State> &whoNotified){
    if (whoNotified.getInfo().colour == Colour::White){
        theDisplay[whoNotified.getInfo().row][whoNotified.getInfo().col] = 'W';
    }
    if (whoNotified.getInfo().colour == Colour::Black){
        theDisplay[whoNotified.getInfo().row][whoNotified.getInfo().col] = 'B';
    }
}


std::ostream &operator<<(std::ostream &out, const TextDisplay &td){
    for (int row = 0; row < td.gridSize; row++){
        for (int col = 0; col < td.gridSize; col++){
            out << td.theDisplay[row][col];
        }
        out << std::endl;
    }
    return out;
}
