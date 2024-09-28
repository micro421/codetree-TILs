#include <iostream>
#include <cmath>

/* 최종적으로 아키텍처 유효성 확인 바람! */
using namespace std;
int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};

int result;
int n,r,c,m; /* m is time */
int dist;
int grid[100][100] = {0,0};
bool exist[100][100]; /*grid bomb exist */

int temp[100][100] = { 0, 0};

int curr_x;
int curr_y;

bool InRange(int x, int y)
{
    return (0<=x && x<n && 0<=y && y<n);
}
void MakeBumb(int pos_x, int pos_y, int time)
{
    grid[pos_x][pos_y] = time;
    exist[pos_x][pos_y]=true;
}

void New_Bumb_Product(int cur_x, int cur_y, int distance, int time) {
    for (int i = 0; i < 4; i++)
    {
        int pos_x = cur_x+distance*dx[i];
        int pos_y = cur_y+distance*dy[i];
        if(InRange(pos_x, pos_y) && !exist[pos_x][pos_y])
        {
            MakeBumb(pos_x, pos_y,time);
        }
    }
}

int main() {

    ios::sync_with_stdio(0);
    cin.tie(0);

    result = 0;
    fill(&grid[0][0], &grid[99][100], 0);
    fill(&exist[0][0], &exist[99][100], false);

    cin >> n >> m >> r >> c;

    grid[r - 1][c - 1] = 1;
    exist[r - 1][c - 1] = true;

    dist = (int) pow(2, 0);

    curr_x = r - 1;
    curr_y = c - 1;

    for(int i=1; i<=m ;i++)
    {
        dist = (int)pow(2, i-1);
        if(i==1)
        {
            New_Bumb_Product(curr_x, curr_y, dist, i);
        }
        else
        {
            for(int j=0; j<n; j++)
            {
                for(int k=0; k<n; k++)
                {
                    if(grid[j][k]<i && exist[j][k])
                    {
                        New_Bumb_Product(j, k, dist, i);
                    }
                }
            }

        }
    }


    for (int i = 0; i < n; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(exist[i][j])
            {
                result++;
            }
        }
    }

    cout<<result;

    return 0;
}