#include <iostream> 

using namespace std; 

bool IsValid(char board[9][9],int row,int col,char num){
    int i,j;
    for(i=0;i<9;i++){
        if(board[i][col] == num) return false;
    }
    for(j=0;j<9;j++){
        if(board[row][j] == num) return false;
    }
    row -= row%3;
    col -= col%3;
    for(i=row;i<row+3;i++){
        for(j=col;j<col+3;j++){
            if(board[i][j] == num) return false;
        }
    }
        
    return true;
}

bool isEmpty(char board[9][9],int &row, int &col)
{
    for(row= 0; row< 9; row++)
        for(col= 0; col <9; col++)
            if(board[row][col] == '0') return true; 
    return false; 
}

bool Solveboard(char board[9][9])
{
    int row, col;
    char allowed[9]= {'1','2','3','4','5','6','7','8','9'};
    if(!isEmpty(board,row,col)) return true;
        
    for(int num =0; num< 9; num++){
        if(IsValid(board,row, col, allowed[num]))
        {
            board[row][col] = allowed[num];
            if(Solveboard(board)) return true; 
            board[row][col] = '0';
        }
    }
    return false; 
}

void PrintBoard(char board[9][9])
{
    for(int row=0; row<9; row++){
        for(int col=0; col<9; col++){
            if (col==8){
                cout<<board[row][col];
            }
            else{
                cout << board[row][col] <<" ";
            }
        }
        cout << endl;
    }
}

int main()
{
    char board[9][9];
	for(int i=0; i<9; i++){
		for(int j=0; j<9; j++){
			cin>>board[i][j];
		}
	}
    
    if(Solveboard(board)) PrintBoard(board);
    else{
        cout << "No Solution"<<endl; 
    }
} 