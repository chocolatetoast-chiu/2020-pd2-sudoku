#include "sudoku.h"
#include <iostream>
using namespace std;
int main() {
    // finish your generate code...
    Sudoku sudo;
    int type;
    int x;
    int y;
    // input 2 dimensional array...
    int array[9][9];
    // cout<<"please input problem: "<<endl;
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            cin>>array[i][j];
        }
    }
    /*
    //for testing...
    int array[9][9]={{3,0,2,0,0,5,6,9,0},
                    {0,4,0,0,9,6,0,3,0},
                    {0,5,0,0,0,8,0,0,0},
                    {1,9,0,0,8,0,7,0,3},
                    {0,0,0,0,0,0,0,0,0},
                    {5,0,7,0,3,0,0,6,1},
                    {0,0,0,8,0,0,0,2,0},
                    {0,8,0,9,6,0,0,7,0},
                    {0,6,5,7,0,0,3,0,0}};
    for(int i = 0;i < 9; i++){
        for(int j = 0; j < 8; j++){
            cout<<array[i][j]<<" ";
        }
        cout<<array[i][8]<<endl;
    }
    */
    // read the instruction...
    // cout<<"please input command:"<<endl;
    while(1) {
        type = 0;
        x = 0;
        y = 0;
        cin>>type;
        if(type == 0)
            break;
        else {
            cin>>x;
            if(type != 4 && type != 5)
                cin>>y;
        }
        switch(type) {
        case 1:
            sudo.swapNum(x, y, array);
            break;
        case 2:
            sudo.swapRow(x, y, array);
            break;
        case 3:
            sudo.swapCol(x, y, array);
            break;
        case 4:
            sudo.rotate(x, array);
            break;
        case 5:
            sudo.flip(x, array);
            break;
        default:
            break;
        }
    }
    // output the array...
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 8; j++) {
            cout<<array[i][j]<<" ";
        }
        cout<<array[i][8]<<endl;
    }
    //
    return 0;
}
