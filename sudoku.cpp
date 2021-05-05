#include "sudoku.h"
#include <iostream>
#include <ctime>
#include <vector>
#include <cstdlib>

Sudoku::Sudoku() {};

// generate
void Sudoku::generate() {
    int array[9][9]= {{9,0,3,0,0,5,0,6,0},
        {2,1,0,0,0,7,5,0,0},
        {0,0,7,0,6,9,2,4,0},
        {7,0,0,0,0,0,6,0,4},
        {0,0,4,7,0,8,9,0,0},
        {1,0,5,0,0,0,0,0,8},
        {0,6,9,5,1,0,8,0,0},
        {0,0,2,9,0,0,0,1,5},
        {0,5,0,2,0,0,4,0,6}
    };
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 8; j++) {
            cout<<array[i][j]<<" ";
        }
        cout<<array[i][8]<<endl;
    }
}

// transform
void Sudoku::swapNum(int x, int y, int arr[9][9]) {
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            if(arr[i][j] == x)
                arr[i][j] = y;
            else if(arr[i][j] == y)
                arr[i][j] = x;
        }
    }
}
void Sudoku::swapRow(int x, int y, int arr[9][9]) {
    int temp;
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 9; j++) {
            temp = arr[3*x+i][j];
            arr[3*x+i][j] = arr[3*y+i][j];
            arr[3*y+i][j] = temp;
        }
    }
};
void Sudoku::swapCol(int x, int y, int arr[9][9]) {
    int temp;
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 3; j++) {
            temp = arr[i][3*x+j];
            arr[i][3*x+j] = arr[i][3*y+j];
            arr[i][3*y+j] = temp;
        }
    }
};
void Sudoku::rotate(int x, int arr[9][9]) {
    int temp;
    while(x != 0) {
        for(int i = 0; i < 5; i++) {
            for(int j = 0; j < 4; j++) {
                temp = arr[i][j];
                arr[i][j] = arr[9-j-1][i];
                arr[9-j-1][i] = arr[9-i-1][9-j-1];
                arr[9-i-1][9-j-1] = arr[j][9-i-1];
                arr[j][9-i-1] = temp;
            }
        }
        x--;
    }
};
void Sudoku::flip(int x, int arr[9][9]) {
    int temp;
    if(x == 1) {
        for(int i = 0; i < 9; i++) {
            for(int j = 0; j < 5; j++) {
                temp = arr[i][j];
                arr[i][j] = arr[i][8-j];
                arr[i][8-j] = temp;
            }
        }
    } else {
        for(int i = 0; i < 5; i++) {
            for(int j = 0; j < 9; j++) {
                temp = arr[i][j];
                arr[i][j] = arr[8-i][j];
                arr[8-i][j] = temp;
            }
        }
    }
};

// solve
int Sudoku::Ans = 0; //數獨解個數計數器 (Global變數)
vector < int > Sudoku::board_Ans(SIZE*SIZE);

Sudoku::Sudoku(vector<int> board,int A) {
    in_board = board;
    //初始化 count, tag, Found變數
    for (i=0; i<SIZE; i++)
        for (j=0; j<SIZE; j++) {
            count[i*SIZE+j] = 0;
        }
    for (i=0; i<SIZE*SIZE; i++)
        for (j=0; j<SIZE; j++) {
            tag[i][j] = false;
        }
    Found = 0;
    zero = 0;
    setAns(A);
    sol();
};

void Sudoku::sol() {
    int check, Max, iMax;
    /* 一般解法
    Found: 計算已知數字的個數
    count, tag: 掃描直、橫排又九宮格找出空格裡排除的數字
    */

    for (i=0; i<SIZE*SIZE; i++) {
        if (in_board.at(i) != 0) {
            Found++;
        } else {
            for (j=0; j<SIZE; j++) {
                if (in_board.at((i/SIZE)*SIZE+j) != 0 && !tag[i][in_board[(i/SIZE)*SIZE+j]-1]) {
                    count[i]++;
                    tag[i][in_board[(i/SIZE)*SIZE+j]-1] = true;
                }
                if (in_board.at(j*SIZE+i%SIZE) != 0 && !tag[i][in_board[j*SIZE+i%SIZE]-1]) {
                    count[i]++;
                    tag[i][in_board[j*SIZE+i%SIZE]-1] = true;
                }
                check = in_board.at(((i/(SIZE*3))*3+j/3)*SIZE + ((i%SIZE)/3)*3+j%3) - 1;
                if (in_board.at(((i/(SIZE*3))*3+j/3)*SIZE + ((i%SIZE)/3)*3+j%3) != 0 && !tag[i][check]) {
                    count[i]++;
                    tag[i][check] = true;
                }
            }
            zero ++;
        }
    }
    if (zero > 66) {
        count[0] = 8;
        cout<<"2"<<endl;
        exit(0);
    }
    /* 將排除數字有8個的空格填入正確的數字&增加Found個數
    並更新其直、橫排、九宮格內之空格的count, tag*/
    for (i=0; i<SIZE*SIZE; i++) {
        if (in_board.at(i) == 0 && count[i]==8) {
            count[i] = 0;
            Found++;
            for (j=0; j<SIZE; j++) {
                if(!tag[i][j]) {
                    in_board.at(i) = j+1;
                    // cout<<"No. "<<i<<" : "<<in_board[i]<<" in."<<endl;
                    for (k=0; k<SIZE; k++) {
                        if (in_board.at((i/SIZE)*SIZE+k) == 0 && !tag[(i/SIZE)*SIZE+k][j]) {
                            count[(i/SIZE)*SIZE+k]++;
                            tag[(i/SIZE)*SIZE+k][j] = true;
                        }
                        if (in_board.at(k*SIZE+i%SIZE) == 0 && !tag[k*SIZE+i%SIZE][j]) {
                            count[k*SIZE+i%SIZE]++;
                            tag[k*SIZE+i%SIZE][j] = true;
                        }
                        check = ((i/(SIZE*3))*3+k/3)*SIZE + ((i%SIZE)/3)*3+k%3;
                        if (in_board.at(check) == 0 && !tag[check][j]) {
                            count[check]++;
                            tag[check][j] = true;
                        }
                    }
                }
            }
            i = -1; //新填入空格數字就重新開始迴圈
        }
    }
    if (Found == 81) { //全部空格數字都找到
        setAns(Ans+1); //數獨解個數加1
        if(Ans == 1) {
            for(int i = 0; i < SIZE*SIZE; i++) {
                board_Ans.push_back(i);
            }
            for (i=0; i<SIZE; i++)
                for (j=0; j<SIZE; j++) {
                    board_Ans.at(i*SIZE+j) = in_board.at(i*SIZE+j);
                }
        }
    } else { //一般解法不行，只好用暴力解了XD
        //找出排除數字最多的空格
        Max = 0;
        iMax = -1;
        for (i=0; i<SIZE*SIZE; i++) {
            if (count[i] > Max) {
                Max = count[i];
                iMax = i;
            }
        }
        //暴力解開始!!
        //從排除數字最多的空格開始猜答案，把每個有可能的解法都跑一次
        for (j=0; j<SIZE; j++) {
            if(!tag[iMax][j]) {
                in_board.at(iMax) = j+1;
                // cout<<"violence: set "<<"No. "<<iMax<<" : "<<in_board[iMax]<<" then check...Found="<<Found<<endl;
                // cout<<"repeat class again"<<endl;
                /*
                建立一個新的解題物件，並把目前數獨解個數代入
                若有新的解，將會更新數獨解(Ans)的個數，in_board則為其解
                若題目有多重解(Ans>1)，in_board只會紀錄下最後一組的數獨解
                */
                Sudoku *tmp = new Sudoku(get_board(),getAns());
                //刪除此物件，並開始下一個可能解(節省記憶體的用量)
                delete tmp;
            }
        }
    }
};

vector < int > Sudoku::get_board() { //取得數獨解答
    vector <int> out_board(SIZE*SIZE);
    for (i=0; i<SIZE*SIZE; i++) {
        out_board.at(i) = in_board.at(i);
    }
    /*
            for(int i = 0;i < 9; i++){
                for(int j = 0; j < 8; j++){
                    cout<<out_board[i*SIZE+j]<<" ";
                }
                cout<<out_board[i*SIZE+8]<<endl;
            }
            cout<<"finished get board!!"<<endl;
    */
    return out_board;
};

int Sudoku::getAns() { //取得數獨解答的個數
    return Ans;
};

void Sudoku::setAns(int A) { //設定數獨解答的個數
    Ans = A;
};
