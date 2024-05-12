#include <iostream>
#include <cstring> //memset
#define BLANK 0

using namespace std;
int n,m;
int grid[200][200] = {0, 0}; /*  memset(nextgrid, 0, sizeof(nextgrid)); */
int nextgrid[200][200] = {0, 0};
int column[10] ={0,0};
bool InBombRange(int x, int y, int center_x, int center_y, int bomb_range)
{
    return (x == center_x || y == center_y) &&
           abs(x - center_x) + abs(y - center_y) < bomb_range;
    /* 금 채굴하기는 abs + abs <= bomb_range */
}

bool ColumnDone(int col)
{
    bool column_done = true;
    for(int i=0; i<n; i++)
    {
        if(grid[i][col]!= 0)
        {
            column_done = false;
        }
    }
        return column_done;
}

int CenterRowNum(int col)
{
    int row = 0;
    for(int i=0; i<n; i++)
    {
        if(grid[i][col]!= 0)
        {
            row = i; /*처음으로 0이 아닌 숫자가 등장하는 요소의 행을 i로 반환/ i = 행 -1 */
            break; /*반환 시 내 놓음*/
        }
    }
    return row;
}

void ShiftAsBumb()
{
    memset(nextgrid, 0, sizeof(nextgrid));
    for(int j=0; j<n; j++)
    {
        int end_of_array = n-1;
        for(int i=n-1; i>=0; i--)
        {
            if(grid[i][j])
            {
                nextgrid[end_of_array][j] = grid[i][j];
                end_of_array--;
            }
        }
    }
}

void Copy()
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            grid[i][j]=nextgrid[i][j];
        }
    }
}
void BombFunc(int cent_col)
{
    /* 1. Bomb range 시작점 잡기 및 가능성 및 range 판단
    * 선행 요소 : bomb 넣어도 되는지 그거는 BLANK로 채워진 배열 요소인지 확인 후 아니면 행 늘려
    * 만약 col에 해당하는 모든 요소가 O이면 아무 것도 일어나지 않음.
    * 맨허튼 거리 활용해서 Bomb 채우는 range 잡기*/
    int cent_row = 0;
    int temp_m;
    if(ColumnDone(cent_col))
    {
        return; /* Nothing TO DO*/
    }
    else
    {
        cent_row = CenterRowNum(cent_col);
        temp_m = grid[cent_row][cent_col];
    }
    /*BumbFill*/
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(InBombRange(i, j, cent_row ,cent_col, temp_m)) /* 0<0은 false이기에 0처리 필요 무*/
            {
                grid[i][j]= BLANK;
            }
        }
    }

    ShiftAsBumb(); /*Bumb에 인해 전체 grid sift 해주는데 end_of_array 방식 활용*/
    Copy(); /* 원본 grid에 next grid 채워 넣음*/

}
int main() {

    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m;
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            cin>>grid[i][j];
        }
    }
    for(int k=0; k<m; k++)
    {
        cin>>column[k];
        BombFunc(column[k]-1); /*column[k]는 1부터 n까지 범위를 갖는 행이므로 인자로 들어갈 때는 -1 해줘야*/
    }
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            cout<<grid[i][j];
            if(j !=n-1)
                cout<<" ";
        }
        if(i!=n-1)
            cout<<"\n";
    }

    return 0;
}