#ifndef SUDOKU_H
#define SUDOKU_H

/***************************************************
 * Finish your .cpp according to this header file. *
 * You can modify this file if needed.             *
 ***************************************************/
#include <iostream>
#include <vector>
#define SIZE 9
using namespace std;
class Sudoku {
  public:
    Sudoku();

    // generate
    void generate();

    // transform
    void swapNum(int x, int y, int arr[9][9]);
    void swapRow(int x, int y, int arr[9][9]);
    void swapCol(int x, int y, int arr[9][9]);
    void rotate(int x, int arr[9][9]);
    void flip(int x, int arr[9][9]);

    // solve
    static int Ans; //數獨解個數計數器 (這是個Global的變數)
    static vector < int > board_Ans; //數獨解
    Sudoku(vector<int>,int); //建構子
    void sol(); //解題函式
    vector < int > get_board(); //取得數獨解
    int getAns(); //取得數獨解的個數
  private:
    int i,j,k; //迴圈用變數
    vector < int > in_board; //數獨題目
    int count[SIZE*SIZE]; //每個空格排除數字個數
    int Found; //已知空格數字的個數
    int zero;
    bool tag[SIZE*SIZE][SIZE]; //每個空格排除的數字
    void setAns(int A); //設定Ans變數
    bool FLAG;
};

#endif // SUDOKU_H
