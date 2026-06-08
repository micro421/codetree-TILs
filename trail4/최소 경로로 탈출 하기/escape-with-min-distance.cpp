#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

int grid[100][100];
bool visited[100][100];
int step[100][100];
int n,m;
int dx[4] = {0,1,-1,0};
int dy[4] = {1,0,0,-1};
queue<pair<int, int>> q;


void Push(int x, int y, int s)
{
    step[x][y] = s;
    visited[x][y] = true;
    q.push(make_pair(x, y));
}

bool InRange(int x, int y)
{
    return x>=0 && x<n && y>=0 && y<m && (grid[x][y]==1);
}
void BFS()
{
    while(!q.empty()) { /* Today Mistake */ /* queue가 빌 때까지니까 if가 아닌 while이다! */
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        for (int i = 0; i < 4; i++) {
            int new_x = x + dx[i];
            int new_y = y + dy[i];
            if (InRange(new_x, new_y) && !visited[new_x][new_y]) {
                Push(new_x, new_y, step[x][y] + 1);
            }
        }
    }

}

int main() {
    cin>>n>>m;
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            cin>>grid[i][j];
        }
    }
    Push(0,0,0);
    BFS();

    cout<<step[n-1][m-1];

    return 0;
}