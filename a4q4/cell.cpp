//
//  cell.cpp
//  a4q4
//
//  Created by 马弘德 on 2020/3/24.
//  Copyright © 2020 Mason. All rights reserved.
//

#include "cell.hpp"

Cell::Cell(size_t r, size_t c): r{r}, c{c}{
}

void Cell::setPiece(Colour colour){
    this->colour = colour;
    // Set state to NewPiece at the beginning and notify neighbours
    setState(State{StateType::NewPiece, this->colour});
    notifyObservers();
    
    // change state to Relay after notifying observers
    setState(State{StateType::Relay, this->colour});
}

void Cell::toggle(){
    this->colour = (this->colour == Colour::Black) ? Colour::White : Colour::Black;
}

//find the direction from whoFrom
Direction Cell::RltDir(Subject<Info, State> &whoFrom){
    // get the position of and whofrom
    size_t who_row = whoFrom.getInfo().row;
    size_t who_col = whoFrom.getInfo().col;
    
    if (r < who_row){
        if (c < who_col){
            return Direction::NW;
        }
        if (c == who_col){
            return Direction::W;
        }
        else{
            return Direction::SW;
        }
    }
    if (r == who_row){
        if (c < who_col){
            return Direction::N;
        }
        else{
            return Direction::S;
        }
    }
    else{
        if (c < who_col){
            return Direction::NE;
        }
        if (c == who_col){
            return Direction::E;
        }
        else{
            return Direction::SE;
        }
    }
}

//determine if *this and other have opposite direction

bool Cell::Pair(Direction my, Direction oth){
    if ((my == Direction::S) && (oth == Direction::N)){
        return true;
    }
    else if ((my == Direction::SE) && (oth == Direction::NW)){
        return true;
    }
    else if ((my == Direction::SW) && (oth == Direction::NE)){
        return true;
    }
    else if ((my == Direction::E) && (oth == Direction::W)){
        return true;
    }
    else if ((my == Direction::W) && (oth == Direction::E)){
        return true;
    }
    else if ((my == Direction::N) && (oth == Direction::S)){
        return true;
    }
    else if ((my == Direction::NE) && (oth == Direction::SW)){
        return true;
    }
    else if ((my == Direction::NW) && (oth == Direction::SE)){
        return true;
    }
    else {
        return false;
    }
}


// require all observers being notified are neighbours of whoFrom
void Cell::notify(Subject<Info, State> &whoFrom){
    if (colour == Colour::NoColour){
        return;
    }
    StateType who_type = whoFrom.getState().type;
    Colour who_colour = whoFrom.getState().colour;
    
    // Relative direction from whoFrom to *this
    Direction dir_to_who = RltDir(whoFrom);
    
    if (who_type == StateType::NewPiece){
        // if same colour, set the type to Relay and the direction to dir_to_who
        if (colour == who_colour){
            setState(State{StateType::Relay, colour, dir_to_who});
        }
        // if different colour, do the above and set colour to whoFrom's colour
        else{
            setState(State{StateType::Relay, who_colour, dir_to_who});
            //notify neighbours that colour are changed
            notifyObservers();
        }
    }
    else if (who_type == StateType::Relay){
        //if *this and whoFrom have same direction relative to the original changed piece, change the state of this
        if (dir_to_who == whoFrom.getState().direction){
            //if same colour, set statetype to Reply
            if (colour == who_colour){
                setState(State{StateType::Reply, colour, dir_to_who});
                notifyObservers();
            }
            // if different colour, set colour the whoFrom's colour
            else{
                setState(State{StateType::Relay, who_colour, dir_to_who});
                notifyObservers();
            }
        }
    }
    else{
        // if this and whofrom have opposite direction and this is not NewPiece, toggle this
        if ((Pair(dir_to_who, whoFrom.getState().direction)) &&
            (getState().type != StateType::NewPiece)){
            toggle();
            setState(State{StateType::Reply, who_colour, whoFrom.getState().direction});
            notifyObservers();
            //change the state back to Relay after notifying observers
            setState(State{StateType::Relay, who_colour, whoFrom.getState().direction});
        }
    }
    
}

Info Cell::getInfo() const{
    return Info{r, c, colour};;
}
