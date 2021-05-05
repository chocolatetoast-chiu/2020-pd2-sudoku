#include "sudoku.h"
#include <iostream>
#include <ctime>
#include <vector>
#include <cstdlib>
using namespace std;

int main() {
    // finish your solve code...
    int Ans = 0;

    // input 2 dimensional array...
    vector < int > board_Q(SIZE*SIZE);
    for(int i = 0; i < 81; i++) {
        cin>>board_Q[i];
    }

    /*
            //for testing...
            vector < int > board_Q={0,0,0,0,0,0,0,0,0
                                   ,0,0,0,0,0,0,0,0,0
                                   ,0,0,0,0,0,0,0,0,0
                                   ,0,0,0,0,0,0,0,0,0
                                   ,0,0,0,0,0,0,0,0,0
                                   ,0,0,0,0,0,0,0,0,0
                                   ,0,0,0,0,0,0,0,0,0
                                   ,0,0,0,0,0,0,0,0,0
                                   ,0,0,0,0,0,0,0,0,0};

            for(int i = 0;i < 9; i++){
                for(int j = 0; j < 8; j++){
                    cout<<board_Q[i*SIZE+j]<<" ";
                }
                cout<<board_Q[i*SIZE+8]<<endl;
            }
    */
    // cout<<"start one time!!"<<endl;
    Sudoku sudo(board_Q, Ans);
    // cout<<"finished one time!!"<<endl;
    Ans = sudo.getAns();
    vector < int > board_ANS(81);
    for (int i=0; i<SIZE; i++)
        for (int j=0; j<SIZE; j++) {
            board_ANS[i*SIZE+j] = sudo.board_Ans[i*SIZE+j];
        }

    // output the array...
    if(Ans == 1) {
        cout<<Ans<<endl;
        for(int i = 0; i < 9; i++) {
            for(int j = 0; j < 8; j++) {
                cout<<board_ANS[i*SIZE+j]<<" ";
            }
            cout<<board_ANS[i*SIZE+8]<<endl;
        }
    } else {
        cout<<"0"<<endl;
    }

    //
    return 0;
}
