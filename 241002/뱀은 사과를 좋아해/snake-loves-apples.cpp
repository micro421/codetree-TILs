#include <iostream>
#define APPLE 5
using namespace std;

int n,m,k;

char d[1000]; /* direction */
int dir_mapper[1000];
int p[1000]; /* 움직이는 길이 길이 */
int grid[100][100] ={0,0};
int exist[100][100] ={0,0};
int t, curr_x, curr_y;
int map_idx;
int accumul_idx;
int del_idx;
int length = 1;
int del_x[1000];
int del_y[1000];
int dir_change_numb = 0;
int dx[4]={0,1,0 ,-1};
int dy[4] = {1,0,-1,0};

bool AppleExist(int x, int y)
{
    if(grid[x][y] == APPLE)
        return true;
    else
        return false;
}

bool InRange(int x, int y)
{
    return 0<=x && x<n && 0<=y && y<n;
}
void Simulate(int next_x, int next_y)
{
    if(AppleExist(next_x, next_y))
    {
        grid[next_x][next_y] = 1;
        exist[next_x][next_y] += 1;
        length++;
        del_x[accumul_idx] = next_x;
        del_y[accumul_idx] = next_y;
        accumul_idx++;
    }
    else
    {
        grid[next_x][next_y] = 1;
        exist[next_x][next_y] += 1;
        /* 길이가 1인 경우 del_x, del_y에 next_x, next_y 대입 불필요*/
        //if(length>1)/* delete 역할 */
        //{
            grid[del_x[del_idx]][del_y[del_idx]] = 0;
            exist[del_x[del_idx]][del_y[del_idx]] = 0;
            del_idx++; /* 위치 조정 */
            // length--; /* 길이가 줄어드는 것은 잘못된 구현! */
            del_x[accumul_idx] = next_x;
            del_y[accumul_idx] = next_y;
            accumul_idx++;
        //}
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    t = 0;
    curr_x = 0;
    curr_y = 0;
    del_idx = 0;
    map_idx = 0;
    grid[0][0] = 1;
    del_x[0] = 0;
    del_y[0] = 0;
    accumul_idx = 1;
    cin >> n >> m >> k;
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        grid[x - 1][y - 1] = APPLE;
    }

    for (int i = 0; i < k; i++) {
        cin >> d[i] >> p[i];
        dir_change_numb += p[i];

        for(int j=0; j<p[i]; j++) {
            if (d[i] == 'R') {
                dir_mapper[map_idx] = 0;
            } else if (d[i] == 'D') {
                dir_mapper[map_idx] = 1;
            } else if (d[i] == 'L') {
                dir_mapper[map_idx] = 2;
            } else {
                dir_mapper[map_idx] = 3;
            }
            map_idx++;
        }
    }

   /* cout<<"t is "<<t<<" and grid is \n";
    for(int i=0; i<n; i++) {
        for (int j = 0; j < n; j++) {
            cout<<grid[i][j]<<" ";
        }
        cout<<"\n";
    }*/

    while (dir_change_numb--) {
        int next_x = curr_x + dx[dir_mapper[t]];
        int next_y = curr_y + dy[dir_mapper[t]];
        t++;

        if (!InRange(next_x, next_y)) {
            break;
        }

        Simulate(next_x, next_y);
/*
        cout<<"t is "<<t<<" and grid is \n";
        for(int i=0; i<n; i++) {
            for (int j = 0; j < n; j++) {
                cout<<grid[i][j]<<" ";
            }
            cout<<"\n";
        }

        cout<<"t is "<<t<<" and exist is \n";
        for(int i=0; i<n; i++) {
            for (int j = 0; j < n; j++) {
                cout<<exist[i][j]<<" ";
            }
            cout<<"\n";
        }
        */

        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                if(exist[i][j] >= 2) { /*몸이 겹치는 경우 */
                    cout<<t;
                    exit(0);
                }
            }
        }
        curr_x = next_x;
        curr_y = next_y;
    }

    cout<<t;
}