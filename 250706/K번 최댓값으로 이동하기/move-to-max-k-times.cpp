#include <iostream>
#include <queue>
#include<algorithm>
#include <cstring>
#include <tuple>
#include <vector>
using namespace std;

int n, k;
int grid[100][100];
int visited[100][100];
int r, c;
int cnt;
queue<pair<int, int>> q;
vector<tuple<int, int, int>> candidates;
void ChooseNext();
void ProcessBFS(int x, int y);
int next_x, next_y;
void Push(int x, int y)
{
    visited[x][y]++;
    q.push(make_pair(x, y));
}
bool InRange(int x, int y)
{
    return x >= 0 && x < n && y >= 0 && y < n;
}

bool CanGo(int new_x, int new_y, int cur_x, int cur_y)
{
    if (!InRange(new_x, new_y))
    {
        return false;
    }
    if (visited[new_x][new_y])
    {
        return false;
    }
    if (grid[new_x][new_y] < grid[cur_x][cur_y])
    {
        return true;
    }
    return false;
}

void Debug()
{
    cout << "Debug=======\n";
    cout << " cnt is " << cnt << "\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
        {
            cout << visited[i][j] << " ";
        }
        cout << "\n";
    }
}
void BFS(int base_x, int base_y)
{
    int dx[4] = { -1,0,0,+1 };
    int dy[4] = { 0,-1,1,0 };

    while (!q.empty())
    {
        pair<int, int> curr_pos = q.front();
        q.pop();
        int x = curr_pos.first;
        int y = curr_pos.second;

        for (int i = 0; i < 4; i++)
        {
            int new_x = x + dx[i];
            int new_y = y + dy[i];
            if (CanGo(new_x, new_y, base_x, base_y)) {
                Push(new_x, new_y);
                tuple<int, int, int> t = make_tuple(grid[new_x][new_y], new_x, new_y);
                candidates.push_back(t);
            }
            else {
                continue;
            }
        }

        //Debug();
    }
    ChooseNext();
    //cout<<"Finally Queue Empty!\n";
}

void ProcessBFS(int x, int y)
{
    Push(x, y);
    BFS(x, y);
}
void ChooseNext()
{
    cnt++;

    // 최댓값 선택
    if (!candidates.empty()) // 변경점
    {
        sort(candidates.begin(), candidates.end(), [](auto a, auto b)
        {
            if (get<0>(a) != get<0>(b)) return get<0>(a) >= get<0>(b); // 값 큰 순서대로
            if (get<1>(a) != get<1>(b)) return get<1>(a) <= get<1>(b); // 행 작은 순
            return get<2>(a) <= get<2>(b); // 열 작은 순
        });
        next_x = get<1>(candidates[0]);
        next_y = get<2>(candidates[0]);
    }
    if ((cnt >= k) || (candidates.empty()))
    {
        cout << next_x + 1 << " " << next_y + 1; // 행과 열을 출력해야 하므로 idx + 1, idy + 1해준다.
        return;
    }

    candidates.clear();
    memset(visited, 0, sizeof(visited));
    ProcessBFS(next_x, next_y);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    cin >> n >> k;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }
    cin >> r >> c;

    cnt = 0;
    next_x = r - 1;
    next_y = c - 1;
    ProcessBFS(r - 1, c - 1);

    return 0;
}