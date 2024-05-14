#include <iostream>

using namespace std;

int grid[100][100] = {0,0};
int visited[100][100] = {0,0};
int n,m;

int dx[4] = {1,0,-1,0};
int dy[4] = {0,1,0,-1};
bool InRange(int x, int y)
{
    return (0<=x && x<n && 0<=y && y<m);
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n>> m;
    int x=0; int y = 0;
    int nx = 0; int ny = 0;

    int dir = 0;
    int fill = 1;
    grid[nx][ny] = fill;
    fill++;
    visited[nx][ny] = 1;

    for(int i=2; i<=n*m; i++)
    {
        /*nx는 다음 범위 체크용*/
        nx = x+dx[dir];
        ny = y+dy[dir];
        if(!InRange(nx, ny) || visited[nx][ny] == 1)
        {
            dir = (dir+1) %4;
            /*x,y는 진정으로 넣을 친구*/
            x = x+dx[dir];
            y = y+dy[dir];
            grid[x][y] = fill;
            fill++;
            visited[x][y] = 1;
        }
        else
        {
            /* wrong nx = x+dx[dir];
             * wrong ny = y+dy[dir];
             * wrong 두 줄은 x던 nx던 값이 제대로 갱신이 안됨!*/
            /*x,y는 진정으로 넣을 친구*/
            x = x+dx[dir];
            y = y+dy[dir];
            grid[x][y] = fill;
            fill++;
            visited[x][y] = 1;
        }
    }

    for(int i=0;i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            cout<<grid[i][j];
            if(j != m-1)
                cout<<" ";
        }
        if(i!=n-1)
            cout<<"\n";
    }
    return 0;
}