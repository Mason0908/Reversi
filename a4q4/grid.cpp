//
//  grid.cpp
//  a4q4
//
//  Created by 马弘德 on 2020/3/24.
//  Copyright © 2020 Mason. All rights reserved.
//

#include "grid.hpp"


Grid::~Grid(){
    delete td;
    delete ob;        
}

void Grid::setObserver(Observer<Info, State> *ob){
    this->ob = ob;
}


bool Grid::isFull() const{
    for (auto col: theGrid){
        for (auto row: col){
            if ((row.getInfo().colour != Colour::Black) &&
                (row.getInfo().colour != Colour::White)){
                return false;
            }
        }
    }
    return true;
}

Colour Grid::whoWon() const{
    int black = 0;
    int white = 0;
    for (auto row: theGrid){
        for (auto col: row){
            if (col.getInfo().colour == Colour::Black){
                black++;
            }
            if (col.getInfo().colour == Colour::White){
                white++;
            }
        }
    }
    if (black > white){
        return Colour::Black;
    }
    if (black < white){
        return Colour::White;
    }
    else{
        return Colour::NoColour;
    }
}


void Grid::init(size_t n){
    // check if the grid is clear
    if (theGrid.size() != 0){
        for (int x = 0; x < theGrid.size(); ++x){
            theGrid[x].clear();
        }
        theGrid.clear();
    }
    if (td != nullptr) delete td;
    if (ob != nullptr) delete ob;
    td = new TextDisplay(n);
    //set new observer Graphics
    ob = new GraphicsDisplay(n);
    // Create a new empty grid
    for (int row = 0; row < n; row++){
        std::vector<Cell> temp;
        for (int col = 0; col < n; col++){
            temp.emplace_back(Cell(row, col));
        }
        theGrid.emplace_back(temp);
    }
    
    
}

void Grid::setPiece(size_t r, size_t c, Colour colour){
    int row = r;
    int col = c;
    InvalidMove Error;
    if ((r < 0) || c < 0 || r > theGrid.size() || c > theGrid.size()){
        throw Error;
        return;
    }
    if (theGrid[r][c].getInfo().colour != Colour::NoColour){
        throw Error;
        return;
    }
    for (int i = row - 1; i < row + 2; i++){
        for (int x = col - 1; x < col + 2; x++) {
            if (i >= theGrid.size() || i < 0 || x < 0 ||
                x >= theGrid.size() || (i == r && x == c)) {
                continue;
            }
            theGrid[r][c].attach(&theGrid[i][x]);
        }
    }
    theGrid[r][c].attach(td);
    theGrid[r][c].attach(ob);
    theGrid[r][c].setPiece(colour);
}

void Grid::toggle(size_t r, size_t c){
    if (theGrid[r][c].getInfo().colour == Colour::NoColour){
        return;
    }
    theGrid[r][c].toggle();
}

std::ostream &operator <<(std::ostream &out, const Grid &g){
    out << *(g.td);
    return out;
}
