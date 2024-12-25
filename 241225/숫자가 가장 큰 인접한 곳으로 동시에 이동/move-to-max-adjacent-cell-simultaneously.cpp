#include <iostream>

#define MAX_N 20
using namespace std;
int n, m, t;
int res;
int grid[MAX_N][MAX_N] ={0,0};
int count[MAX_N][MAX_N]={0,0};
int next_count[MAX_N][MAX_N]={0,0};
int dx[4]={-1,1,0,0};
int dy[4]={0,0,-1,1};

pair<int,int> GetNextPos(int x, int y)
{
    pair<int, int> next_pos;
    next_pos = make_pair(x, y);
    int near_max = grid[x][y];
    for(int dir_num=0; dir_num<4; dir_num++)
    {
        if(near_max < grid[x+dx[dir_num]][y+dy[dir_num]])
        {
            near_max = grid[x+dx[dir_num]][y+dy[dir_num]];
            int next_pos_x = x+dx[dir_num];
            int next_pos_y = y+dy[dir_num];
            next_pos = make_pair(next_pos_x, next_pos_y);
        }
    }
    return next_pos;
}

void Move(int x, int y)
{
    pair<int, int> next_pos = GetNextPos(x, y);
    int next_pos_x = next_pos.first;
    int next_pos_y = next_pos.second;

        next_count[next_pos_x][next_pos_y]++;
}
void MoveAll()
{
    //Step 1-1
    // 그 다음 각 위치에서의 구슬 개수를 전부 초기화.
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            next_count[i][j]=0;
        }
    }

    // Step 1-2
    // (i,j) 위치에 구슬 있는 경우 움직임을 시도하고,
    // 그 결과를 전부 next_count에 기록
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(count[i][j]==1)
                Move(i,j);
        }
    }

    // Step 1-3
    // next_count 값을 count에 복사합니다.
    for(int i=0; i<n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            count[i][j] = next_count[i][j];
        }
    }
}
void DeleteGuseul(int x, int y)
{
    if(count[x][y]>=2)
    {
        count[x][y] = 0;
    }
}
int main() {

    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> t;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }
    for (int i = 0; i < m; i++) {
        int r, c;
        cin >> r >> c;
        count[r - 1][c - 1] = 1;
    }
    while (t--)
    {
        MoveAll();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                DeleteGuseul(i, j);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (count[i][j] == 1)
                res++;
        }
    }
    cout<<res;
    return 0;
}