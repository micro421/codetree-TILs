/* number-of-happy-sequence */
/* 문제 해석 좀 시간 필요 */
#include <iostream>
using namespace std;

int grid[100][100] = { 0, 0};
int m = 0;
int n = 0;
int happy_row_seq = 0;
int happy_col_seq = 0;
int happy_seq=0;
/* 0부터 100-1 index면  100-2 = 98이 마지막 시작점 */
void GetStartColFunction( int col_start, int col_end_of_start ) {
    for (int co_row = 0; co_row < m; co_row++)
    {
        for(int var_col = col_start; var_col <= col_end_of_start; var_col++)
        {
            if( var_col + 1 >= m )
            {
                break; /* 반복문 탈출 */
            }
            if(grid[co_row][var_col] ==grid[co_row][var_col+1] )
            {
                happy_col_seq += 1;
                break; /* 반복문 탈출 */
            }
        }
    }
}

void GetStartRowFunction( int row_start, int row_end_of_start )
{/* 인덱스 아웃 처리 필요 */
    for(int co_col = 0; co_col<m; co_col++) {
        for (int var_row = row_start; var_row <= row_end_of_start; var_row++)
        {
            if( var_row + 1 >= m )
            {
                break;
            }
            if(grid[co_col][var_row] == grid[co_col][var_row+1])
            {
                happy_row_seq += 1;
                break; /* or break */
            }
        }
    }
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    cin>>m>>n;

    for(int i=0; i<m; i++)
    {
        for(int j=0; j<m; j++)
        {
            cin>>grid[i][j];
        }
    }

    GetStartRowFunction(0, m-n);
    GetStartColFunction( 0, m-n);
    cout<<happy_row_seq+happy_col_seq;

    return 0;
}