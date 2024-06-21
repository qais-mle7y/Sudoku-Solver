#include <iostream> 
#include <vector>
#include <map>
#include <unordered_set>
#include <string>

using namespace std; 

char board[25][25];

unordered_set<char> Possible[25][25] = {};

char Chars[25]= {'1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P'};

bool IsValid(int row,int col,char num){
    int i,j;
    for(i=0;i<25;i++){
        if(board[i][col] == num) return false;
    }
    for(j=0;j<25;j++){
        if(board[row][j] == num) return false;
    }
    row -= row%5;
    col -= col%5;
    for(i=row;i<row+5;i++){
        for(j=col;j<col+5;j++){
            if(board[i][j] == num) return false;
        }
    }
        
    return true;
}

bool isEmpty(int &row, int &col)
{
    for(row= 0; row< 25; row++)
        for(col= 0; col <25; col++)
            if(board[row][col] == '0') return true; 
    return false; 
}

void Possiblites()
{
    for (int row = 0; row < 25; row++) {
        for (int col = 0; col < 25; col++) {
            if (board[row][col] == '0') {
                for (int num = 0; num < 25; num++) {
                    if (IsValid(row, col, Chars[num]))
                    {
                        Possible[row][col].insert(Chars[num]);
                    }
                }
            }
        }
    }
}

bool Star()
{
    for (int row = 0; row < 25; row++) {
        map<char, int> found;
        for (int col = 0; col < 25; col++) {
            if (board[row][col] == '0') {
                for (char num : Possible[row][col]) {
                    found[num]++;
                }
            }
        }
        for (auto i : found) {
            if (i.second == 1) { 
                for (int col = 0; col < 25; col++) {
                    if (board[row][col] == '0') {
                        if (Possible[row][col].find(i.first) != Possible[row][col].end()) {
                            board[row][col] = i.first;
                            for (int r = 0; r < 25; r++) {
                                if (board[r][col] == '0')
                                    Possible[r][col].erase(i.first);
                            }
                            return true;
                        }
                    }
                }

            }
        }
    }

    for (int col = 0; col < 25; col++) {
        map<char, int> found;
        for (int row = 0; row < 25; row++) {
            if (board[row][col] == '0') {
                for (char num : Possible[row][col]) {
                    found[num]++;
                }
            }
        }
        for (auto i : found) {
            if (i.second == 1) { 
                for (int row = 0; row < 25; row++) {
                    if (board[row][col] == '0') {
                        if (Possible[row][col].find(i.first) != Possible[row][col].end()) {
                            board[row][col] = i.first;
                            for (int c = 0; c < 25; c++) {
                                if (board[row][c] == '0')
                                    Possible[row][c].erase(i.first);
                            }
                            return true;
                        }
                    }
                }

            }
        }
    }
    return false;
}

bool Single()
{
    for (int row = 0; row < 25; row++) {
        for (int col = 0; col < 25; col++) {
            if (board[row][col] == '0') {
                if (Possible[row][col].size() == 1) {
                    char num = *Possible[row][col].begin();
                    board[row][col] = num;
                    for (int r = 0; r < 25; r++) {
                        if (board[r][col] == '0')
                            Possible[r][col].erase(num);
                    }
                    for (int c = 0; c < 25; c++) {
                        if (board[row][c] == '0')
                            Possible[row][c].erase(num);
                    }
                    return true;
                }
            }
        }
    }
    return false;
}

bool Solveboard()
{
    int row, col;
    if(!isEmpty(row,col)) return true;
        
    for (char num: Possible[row][col]) {
        if (IsValid(row, col, num))
        {
            board[row][col] = num;
            if (Solveboard()) return true;
            board[row][col] = '0';
        }
    }
    return false; 
}

void PrintBoard()
{
    for(int row=0; row<25; row++){
        for(int col=0; col<25; col++){
            if (col==24){
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
	for(int i=0; i<25; i++){
		for(int j=0; j<25; j++){
			cin>>board[i][j];
		}
	}
    
    Possiblites();
    while (Star()) {
        while(Single());
    }
        if(Solveboard()) PrintBoard();
        else{
            cout << "No Solution"<<endl; 
        }
    
} 