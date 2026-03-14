#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm> //sort

using namespace std;
int n, k, m;
int grid[100][100];
int temp_grid[100][100];
int r[10000], c[10000];
int grid_cnt = 0;
vector<int> grid_vec;
bool visited[100][100];

vector<pair<int, int>> org_stones;
vector<int> remove_stone_numb;
vector<pair<int, int>> org_bfs_starts;

queue<pair<int, int>> bfs_q;

bool CanGo(int x, int y)
{
    return (x>=0 && x<n && y>=0 && y<n) && (!visited[x][y]) && (!temp_grid[x][y]);
}

void Bfs_Starts_Set() {
    for (int i = 0; i < k; i++) {
        bfs_q.push(org_bfs_starts[i]);
    }
}

void BFS_K()
{
    Bfs_Starts_Set ();
    memset(visited, false, sizeof(visited)); /* visited[100][100] 배열 0으로 초기화 방법 memset ?*/
    /* starts */
    grid_cnt = 0; /* 누우적이니 초기화 조심 */
    while(!bfs_q.empty())
    {
        pair<int, int> curr_pos = bfs_q.front();
        int x = curr_pos.first;
        int y=curr_pos.second;
        bfs_q.pop();

        int dx[4]={-1,0,1,0};
        int dy[4]={0,1,0,-1};
        for(int dir=0; dir<4; dir++)
        {
            int nx = x + dx[dir];
            int ny = y + dy[dir];

            // 아직 방문한 적이 없으면서 갈 수 있는 곳이라면
            // 새로 queue에 넣어주고 방문 여부를 표시해줍니다.
            if(CanGo(nx, ny))
            {
                bfs_q.emplace(nx, ny);
                visited[nx][ny] = true;
                grid_cnt++;
            }
        }
    }
    grid_vec.push_back(grid_cnt);
}

void Remove_Stones()
{
    fill(&visited[0][0], &visited[0][0] + 100*100, false);
    memcpy(temp_grid, grid, sizeof(grid));
    /*
    temp_stones.clear();
    temp_stones = org_stones; // remove_stone_numb나 stones 같은 배열들 언제 Init 해야하는지
    */

    for(int i=0; i<remove_stone_numb.size(); i++)
    {
     /*
      * int del_stone_x = temp_stones[i].first;
        int del_stone_y = temp_stones[i].second; */

        int del_num_i = remove_stone_numb[i];
        int del_x = org_stones[del_num_i].first;
        int del_y = org_stones[del_num_i].second;
        temp_grid[del_x][del_y] = 0;
    }
}
void Choose(int curr_num, int cnt)
{
    if(cnt == m)
    {
        /* remove_stone_numb는 언제 clear 해요? 설계 key-point! */
        Remove_Stones(); //stones vector에 remove_stone_numb에 있는 pair들(x번째 pair) delete
        BFS_K(); // K개의 시작점을 Push하고 탐색 - 어차피 탐색할 지점을 넣는거니까...
        // 그런데 K개의 시작점이 동시에 시작하는거나 따로 시작하는 거나 상관 있나?!
        return;
    }

    if(curr_num == n)
    {
        return;
    }
    /* cnt번째 돌 무선택 */
    Choose(curr_num+1, cnt);

    /* cnt번째 돌 선택 */
    if(cnt < org_stones.size()) { /* 예외처리 안하면 org_Stones[2]에 접근해서 segmentation fault 남 */
        remove_stone_numb.push_back(cnt);
        Choose(curr_num+1, cnt+1);
        remove_stone_numb.pop_back();
    }
    /* 어차피 remove_stones_numb 벡터는 초기화 됩니다~*/
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> k >> m;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == 1) {
                org_stones.emplace_back(i, j);
            }
        }
    }
    // cout<<"org_stones.size()"<<org_stones.size()<<"\n";
    for (int i = 0; i < k; i++) {
        cin >> r[i] >> c[i];
        org_bfs_starts.emplace_back(r[i]-1, c[i]-1);
    }

    Choose(0, 0);
    sort(grid_vec.begin(), grid_vec.end());
    cout<<grid_vec[0]<<"\n";

    return 0;
}