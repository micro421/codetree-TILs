#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>

#define WATER 0
#define GLACIER 1
#define MELTING 2

using namespace std;

int N, M;
int grid[200][200];
bool visited[200][200];
int t, cnt;

int dx[4] = {-1,0,1,0};
int dy[4] = {0,1,0,-1};
vector<int> glacier_cnt;


pair<int,int> Find_Glacier_Start()
{
    pair<int, int> start = make_pair(-1, -1);
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<M; j++)
        {
            if(grid[i][j] == GLACIER)
            {
                start.first = i;
                start.second = j;
                return start;
            }
        }
    }
    return start;
}

pair<int,int> Find_Water_Start()
{
    pair<int, int> start = make_pair(-1, -1);
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<M; j++)
        {
            if(grid[i][j] == WATER)
            {
                start.first = i;
                start.second = j;
                return start;
            }
        }
    }
    return start;
}

bool InRange(int x, int y)
{
    return x>=0 && x<N && y>=0 && y<M;
}
void Water_BFS(int start_x, int start_y)
{
    queue<pair<int,int>> conversion; /* 함수가 불릴 때마다 queue가 초기화 되지? */
    conversion.push(make_pair(start_x, start_y)); /* 시작점 push */
    visited[start_x][start_y] = true; /* 시작점 pop */

    while(!conversion.empty()) /* conversion 큐가 빌 때까지 BFS 돌려주는 게 BFS 핵심! */
    {
        pair<int, int> curr_pos = conversion.front();
        int x = curr_pos.first;
        int y = curr_pos.second;
        conversion.pop();
       for(int i=0; i<4; i++) {
           int nx = x + dx[i]; /* 후에 start_x, start_y 갱신 */
           int ny = y + dy[i];
           if (InRange(nx, ny) && !visited[nx][ny] && (grid[nx][ny] == WATER)) {
               conversion.push(make_pair(nx, ny));
               /* MELTING */
               visited[nx][ny] = true;
           } else if(InRange(nx, ny) && !visited[nx][ny] && (grid[nx][ny] == GLACIER)){

               grid[nx][ny] = MELTING;
               visited[nx][ny] = true;
           }
       }

       }
    }


void Water_BFS_Start()
{
    pair<int, int> water_start = Find_Water_Start();
    if(water_start == make_pair(-1, -1)) return;
    Water_BFS(water_start.first, water_start.second);
}

void Conversion_Glacier_to_Water()
{
    cnt = 0;

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            if(grid[i][j] == MELTING) {
                grid[i][j] = WATER;
                cnt++;
            }
        }
    }
    glacier_cnt.push_back(cnt);
}


int main() {
    t = 0;
    cin >> N >> M;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> grid[i][j];
        }
    }

    while(true)
    {
        pair<int,int> glacier_start = Find_Glacier_Start();
        if(glacier_start == make_pair(-1,-1))
        {
            break;
        }
        memset(visited,false, sizeof(visited));
        Water_BFS_Start(); /* MELTING으로 바꿔줌 */
        Conversion_Glacier_to_Water();
        t++;
    }

    cout<<t<<" "<<glacier_cnt[t-1]; /* 검증 해보기*/
    return 0;
}