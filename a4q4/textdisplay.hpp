//
//  textdisplay.hpp
//  a4q4
//
//  Created by 马弘德 on 2020/3/24.
//  Copyright © 2020 Mason. All rights reserved.
//

#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <iostream>
#include <vector>
#include "observer.hpp"
#include "state.hpp"
#include "info.hpp"
#include "subject.hpp"
class Cell;

class TextDisplay: public Observer<Info, State> {
    std::vector<std::vector<char>> theDisplay;
    const int gridSize;
public:
    TextDisplay(int n);
    
    void notify(Subject<Info, State> &whoNotified) override;
    
    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};
#endif
