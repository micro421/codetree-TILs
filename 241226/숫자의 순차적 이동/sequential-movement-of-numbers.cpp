#include <iostream>
#define MAX_N 20
using namespace std;

int grid[MAX_N][MAX_N] = {0,0};
int n,m;
int turn_num;
int max_num;
int dx[8] = {-1,-1,-1,0,0,1,1,1};
int dy[8] = {-1,0,1,-1,1,-1,0,1};

bool InGrid(int x, int y)
{
    return (0<=x && x<n && 0<=y && y<n);
}
pair<int,int> LookForMaxPos(int x, int y)
{
    pair<int, int> max_pos;
    max_num = 0;
    for(int i=0; i<8; i++)
    {
        if(InGrid(x+dx[i], y+dy[i]))
        {
            if(max_num <grid[x+dx[i]][y+dy[i]])
            {
                max_num = grid[x+dx[i]][y+dy[i]];
                max_pos = make_pair(x+dx[i], y+dy[i]);
            }
        }
    }
    return max_pos;
}

void One_Turn_Process()
{   int turn_x;
    int turn_y;
    pair<int, int> max_pos;
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(grid[i][j] == turn_num) /* look for turn num */
            {
                turn_x = i;
                turn_y = j;
                max_pos = LookForMaxPos(turn_x,turn_y);
                break;
                /* turn_num 찾으면, 찾는 process 종료하고, 숫자 swap 해준다,
                * 그렇지 않으면 turn_num이 한 번  더 찾아질 수 있다.*/
            }
        }
    }
    grid[turn_x][turn_y] = max_num;
    grid[max_pos.first][max_pos.second] = turn_num;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m;
    turn_num = 1;
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            cin>>grid[i][j];
        }
    }
for(int i=0; i<m; i++) {
    for (turn_num = 1; turn_num <= n * n; turn_num++) {
        One_Turn_Process();
    }
}
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            cout<<grid[i][j]<<" ";
        }
        if(i!=n-1)
        {
            cout<<"\n";
        }
    }
    return 0;
}
