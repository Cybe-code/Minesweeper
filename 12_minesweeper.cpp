#include <iostream>
#include <cstdlib>  
#include <ctime> 
using namespace std;
int main() 
{
    const int row= 8;
    const int col= 10;
    char matrix[row][col];
    char matrix2[row][col];
    int safe= 0;
    
    for (int i= 0; i< row; i++) 
    {
        for (int j= 0; j< col; j++)
            matrix[i][j] = '.';
    }
    for (int i= 0; i< row; i++) 
    {
        for (int j= 0; j< col; j++) 
            matrix2[i][j]= '.';
    }
    
    srand(time(0));
    int difficulty, bombCount;
    cout<< "enter difficulty (1=easy 10 bomb - 2=hard 20 bomb): ";
    while (!(cin>> difficulty))
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout<< "enter difficulty (1=easy or 2=hard): ";
    }
    
    if (difficulty== 1)
        bombCount= 10;
    else if (difficulty== 2)
        bombCount= 20;
    else 
    {
        cout<< "invalid! system use default(easy)."<< '\n';
        bombCount= 10;
    }
    
    int count= 0;
    while (count< bombCount) 
    {
        int randomRow= rand()% row;   
        int randomCol= rand()% col;    
        
        if (matrix[randomRow][randomCol]== '.')
        {
            matrix[randomRow][randomCol]= '+';
            count++;
        }
    }
    
    cout<< "\ntotal bombs: "<< bombCount<< endl;
    
    while (1)  
    {
        int userRow, userCol;
        cout<< "\nenter cell address (row, col): ";
        while (!(cin>> userRow>> userCol))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout<< "enter cell address (row, col): ";
        }
        
        cout<< "\033[2J";
        cout<< "\033[1;1H";
        
        int realRow= userRow- 1;
        int realCol= userCol- 1;

        if ((realRow>= 0)&&(realRow< row)&&(realCol>= 0)&&(realCol< col)) 
           {
            cout<< "\ncell details:\n";
            cout<< "address: ("<< userRow<< ", "<< userCol<< ")\n";
            cout<< "value: "<< matrix[realRow][realCol]<< "\n";
           
            if (matrix[realRow][realCol]== '+') 
            {
                cout<< "this is bomb"<< '\n'; 
                
                cout<< "\nMinesweeper("<< bombCount<< " bombs):\n";
                cout<< "  ";
                for (int j= 1; j<= col; j++)
                    cout<< j<< " ";
                cout<< '\n';
                
                for (int i= 0; i< row; i++)
                {
                    cout<< i+1<< " ";
                    for (int j= 0; j< col; j++) 
                        cout<< matrix[i][j]<< " ";
                    cout<< '\n';
                }
                break; 
            }
            else 
            {
                int bomb= 0;  
                if (matrix2[realRow][realCol]== '.')
                    safe++;
                
                if ((realRow+1< row)&&(realCol-1>= 0)&&(matrix[realRow+1][realCol-1]== '+'))
                    bomb++;
                if ((realRow+1< row)&&(matrix[realRow+1][realCol]== '+'))
                    bomb++;
                if ((realRow+1< row)&&(realCol+1< col)&&(matrix[realRow+1][realCol+1]== '+'))
                    bomb++;    
                if ((realCol-1>= 0)&&(matrix[realRow][realCol-1]== '+'))
                    bomb++;
                if ((realCol+1< col)&&(matrix[realRow][realCol+1]== '+'))
                    bomb++;
                if ((realRow-1>= 0)&&(realCol-1>= 0)&&(matrix[realRow-1][realCol-1]== '+'))
                    bomb++;
                if ((realRow-1>= 0)&&(matrix[realRow-1][realCol]== '+'))
                    bomb++;
                if ((realRow-1>= 0)&&(realCol+1< col)&&(matrix[realRow-1][realCol+1]== '+'))
                    bomb++;
                
                cout<< "number of bombs around: "<< bomb<< '\n';
                
                if (matrix[realRow][realCol]== '.')
                    matrix2[realRow][realCol]= '0'+ bomb;
                
                cout<< "\nMinesweeper:\n";
                cout<< "  ";
                for (int j= 1; j<= col; j++)
                    cout<< j<< " ";
                cout<< '\n';
                
                for (int i= 0; i< row; i++) 
                {
                    cout<< i+1<< " ";
                    for (int j= 0; j< col; j++)
                        cout<< matrix2[i][j]<< " ";
                    cout<< '\n';
                }
                
                if ((realRow>= 0)&&(realRow< row)&&(realCol>= 0)&&(realCol< col)) 
                {
                      cout<< "\ncell details:\n";
                      cout<< "address: ("<< userRow<< ", "<< userCol<< ")\n";
                      cout<< "value: "<< matrix[realRow][realCol]<< "\n";
                }
                if ((row* col) -bombCount== safe)
                {
                      cout<< "you win the game!!";
                      break;
                }
            }
        }
        else
            cout<< "invalid! try again."<< '\n';
    }
    
    return 0;
}
