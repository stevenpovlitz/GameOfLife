//
//  main.cpp
//  GameOfLife
//
//  Created by Steven Povlitz and Ian Granger on 10/26/16.
//

#include <vector>
#include <iostream>
#include <stdlib.h> // random function
#include <unistd.h>

using namespace std;


// Class used to represent each individual position on the board
class LifeNode{
private:
    bool alive;
    
public:
    LifeNode(){ // used by resize, never accessed before "alive" is set
        
    }
    
    LifeNode(bool input) {
        alive = input;
    }
    
    bool isAlive() {
        return alive;
    }
    
    static bool inBounds(int x, int y, int sizeX, int sizeY) { // check if a position x,y is on the board
        return ( (x>= 0 && x < sizeX) && (y >= 0 && y < sizeY));
    }
    
    void setAlive (bool input) {
        alive = input;
    }
    
};

// fill up board randomly (50% chance of alive for each space)
void fillBoard (vector<vector<LifeNode>> &board, int sizeX, int sizeY) {
    board.resize(sizeX);
    for(int x=0; x < sizeX; x++)
        for(int y=0; y<sizeY; y++)
            board[x].push_back(LifeNode( 1 == int(rand()% 2 + 1))); // create and push new node
}

// display board to stdout
void printBoard(vector<vector<LifeNode>> board) {
    for (int i=0; i < board[0].size()-1; i++) // output a pretty line
        cout << "==";
    cout << "=" << endl;
    
    for (int x=0; x< board.size(); x++) {
        for (int y=0; y<board[x].size(); y++) {
            if (board[x][y].isAlive())
                cout << "X ";
            else
                cout << "  ";
        }
        cout << endl;
    }
}

// wait until user presses enter to go again
bool waitForInput() {
    
    cin.ignore();
    return true;
}

// evaluate if a point (x,y) is valid (on the board)
bool isValidBounds(int x, int y, int sizeX, int sizeY) {
    return ( x >= 0 && y >= 0 && x < sizeX && y < sizeY );
}

// checks if a node ought to be alive next round
bool isAliveNextRound(int sum, bool currentlyAlive) {
    if (currentlyAlive && (sum == 2 || sum == 3))
        return true;
    else if (!currentlyAlive && sum == 3)
        return true;
    else
        return false;
}

// main logic of game, evaluates board once and updates board
void stepForward(vector<vector<LifeNode>> &board) {
    
    vector<LifeNode> temp1, temp2; // for storing the two recent lines, saves memory compared to having two full boards
    
    for (int x=0; x < board.size(); x++) {
        for (int y=0; y < board[x].size(); y++) { // here x and y correspond to x/y positions on the board
            int tempSum = 0; // number of alive neighboars
            int bx = int(board.size());
            int by = int(board[x].size());
            
            // sum all eight adjacent nodes to position x,y
            
            // top three nodes
            if (isValidBounds(x-1, y-1, bx, by))
                tempSum += board[x-1][y-1].isAlive();
            if (isValidBounds(x-1, y, bx, by))
                tempSum += board[x-1][y].isAlive();
            if (isValidBounds(x-1, y+1, bx, by))
                tempSum += board[x-1][y+1].isAlive();
            
            // middle two nodes
            if (isValidBounds(x, y-1, bx, by))
                tempSum += board[x][y-1].isAlive();
            if (isValidBounds(x, y+1, bx, by))
                tempSum += board[x][y+1].isAlive();
            
            // bottom three nodes
            if (isValidBounds(x+1, y-1, bx, by))
                tempSum += board[x+1][y-1].isAlive();
            if (isValidBounds(x+1, y, bx, by))
                tempSum += board[x+1][y].isAlive();
            if (isValidBounds(x+1, y+1, bx, by))
                tempSum += board[x+1][y+1].isAlive();
            
            // evaluate if the node should be living next round and store that value
            // by storing two temporary lines, we optimize memory usage and still have access
            // too all information relevant to evaluating the current row
            if (x % 2 == 0) { // even x, stored in temp1
                if (temp1.size() != board[x].size())
                    temp1.resize(board[x].size()); // make sure temp1 is the right size
                
                temp1[y] = LifeNode(isAliveNextRound(tempSum, board[x][y].isAlive()));
                
            }
            else { // odd x, so store this line in temp 2
                if (temp2.size() != board[x].size())
                    temp2.resize(board[x].size()); // make sure temp2 is the right size
                
                temp2[y] = LifeNode(isAliveNextRound(tempSum, board[x][y].isAlive()));
            }
        }
        
        // store the appropriate temp value to their appropriate board line
        if (x % 2 == 0 && x > 1) {
            board[x-1] = temp2;
        }
        else if (x % 2 == 1 && x > 2) {
            board[x-1] = temp1;
        }
        
    }
    
    // store the last two lines, finalizing the board for this step
    if (board.size() % 2 == 0) {
        board[board.size()-1] = temp2;
        board[board.size()-2] = temp1;
    }
    else {
        board[board.size()-2] = temp2;
        board[board.size()-1] = temp1;
    }
    
}

int main(){
    
    vector<vector<LifeNode>> board;
    
    fillBoard(board, 40, 40); // 10 by 10 board of random nodes
    
    cout << "Welcome to GAME OF LIFE.\npress ENTER to start game" << endl << endl;
    cin.ignore();
    printBoard(board);
    unsigned int sleep = 500000;
    while (true){ //waitForInput()
        usleep(sleep);
        stepForward(board);
        
        printBoard(board);
    }
    return 0;
}
