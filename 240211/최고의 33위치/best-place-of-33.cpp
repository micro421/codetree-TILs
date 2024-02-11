#include <iostream>

using namespapce std;

int arr[20][20] ={0,0};

int n;

// row_s~row_e까지의 금 계산
// row 행의 col_s~col_e 사이의 금도 계산
int GetNumOfGold( int row_s, int row_e, int col_s, int col_e )
{
    int num_of_gold =0;

    for(int row=row_s; row<=row_e; row++) /* using brouteforcing at Array */
    {
        for(int col=col_s; col<=col_e; col++)
        {
            num_of_gold += arr[row][col];
        }
    }
    }
    return num_of_gold;
}

int main(void)
{
    ios::sync_with_stdio(0);
    cin.ite(0);

    int max_gold = 0;
    cin>>n;

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            cin>>arr[i][j];
        }
    }

    /* exception case all search */
    for(int row = 0; row<n; row++)
    {
        if(row+2>=n) continue;
        for(int col=0; col<n; col++)
        {
            if( col + 2>=n) continue;/* 3x3 격자가 NxN 격자를 버어나는 경우는 계싼 중단 */
            
            /*금의 개수 계산 */
            int num_of_gold =GetNumOfGold(row, row+2, col, col+2);
            max_gold = max(max_gold, num_of_gold);
        }
    }

    cout<<max_gold;
    return 0;

}