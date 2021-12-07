//
//  main.cpp
//  a4q4
//
//  Created by 马弘德 on 2020/3/24.
//  Copyright © 2020 Mason. All rights reserved.
//

#include <iostream>
#include <string>
// You may include other allowed headers, as needed
#include "grid.hpp"
#include "state.hpp"
using namespace std;

// Do not remove any code; do not add code other than where indicated.

int main(int argc, char *argv[]) {
    cin.exceptions(ios::eofbit|ios::failbit);
    string cmd;
    Grid g;
    int turn = 0;
    try {
        while (true) {
            cin >> cmd;
            if (cin.eof()) return 0;
            if (cmd == "new") {
                int n;
                cin >> n;
                if (n < 4){
                    continue;
                }
                if (n % 2 != 0){
                    continue;
                }
                g.init(n);
                g.setPiece(n/2-1, n/2-1, Colour::Black);
                g.setPiece(n/2, n/2, Colour::Black);
                g.setPiece(n/2-1, n/2, Colour::White);
                g.setPiece(n/2, n/2-1, Colour::White);
                cout << g;
            }
            else if (cmd == "play") {
                int r = 0, c = 0;
                cin >> r >> c;
                if (turn == 0){
                    try{g.setPiece(r, c, Colour::Black);}
                    catch (InvalidMove l){
                        continue;
                    }
                    cout << g;
                    turn++;
                }
                if (turn == 1){
                    try{g.setPiece(r, c, Colour::White);}
                    catch (InvalidMove l){
                        continue;
                    }
                    cout << g;
                    turn--;
                }
                if (g.isFull()){
                    Colour win = g.whoWon();
                    if (win == Colour::Black){
                        cout << "Black wins!" << endl;
                    }
                    if (win == Colour::White){
                        cout << "White wins!" << endl;
                    }
                    else{
                        cout << "Tie!" << endl;
                    }
                    return 0;
                }
            }
        }
    }
    catch (ios::failure &) {}  // Any I/O failure quits
}
