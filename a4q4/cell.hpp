    //
//  cell.hpp
//  a4q4
//
//  Created by 马弘德 on 2020/3/24.
//  Copyright © 2020 Mason. All rights reserved.
//

#ifndef CELL_H
#define CELL_H
#include <cstddef>
#include "state.hpp"
#include "subject.hpp"
#include "observer.hpp"
#include "info.hpp"

class Cell : public Subject<Info, State>, public Observer<Info, State> {
    const size_t r, c;
    Colour colour = Colour::NoColour;
    // Add other private members if necessary
    Direction RltDir(Subject<Info, State> &whoFrom);
    bool Pair(Direction my, Direction oth);
public:
    Cell(size_t r, size_t c);
    
    void setPiece(Colour colour);    // Place a piece of given colour here.
    void toggle();         // Toggles my colour.
    
    void notify(Subject<Info, State> &whoFrom) override;// My neighbours will call this
    // when they've changed state
    Info getInfo() const override;
};
#endif
