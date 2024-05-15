#include <iostream>

using namespace std;

int n;
int grid[100][100] = {0,0};
int dx[4] = {0,-1,0,1};
int dy[4] = {1,0,-1,0};

bool InRange(int nx, int ny)
{
    return (0<=nx && nx<n && 0<=ny && ny<n);
}
int AdapatableRangeNum(int i)
{
    int range_num = 3;
    for(int j=0; j<=4; j++)
    {
        int k1 = (2*j+1);
        int k2 = (2*j+3);
        if(i>=k1*k1 && i<k2*k2) /* AND OR 로직 실수 주의! */
        {
            range_num = k2;
            break;
        }
    }

    return range_num;
}

bool AdaptableFunc(int nx, int ny,int range_num)
{
    /*abs 쓰는 맨허튼 공식 말고 기준점 격자 인덱스 범위 공식!*/
    return (nx<(n/2+range_num-1))&&(ny<(n/2+range_num-1)) &&(nx>(n/2-(range_num-1))) && (ny>(n/2-(range_num-1)));
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);


    cin>>n;
    int dir_num = 0;
    int x = n/2; int y=n/2;
    grid[x][y] = 1;

    /*test*/
    for(int i=2; i<=n*n; i++)
    {
        /* i =2부터 쓰일 미래 인덱스*/
        int nx = x+dx[dir_num];
        int ny = y+dy[dir_num];
        int range_num = AdapatableRangeNum(i);
        // cout << "i is " << i << " and range_num is" << range_num << "\n";

        if(AdaptableFunc(nx,ny,range_num) && InRange(nx, ny) && (grid[nx][ny] == 0))
        {
            /* https://www.codetree.ai/missions/5/problems/snail-number-square-2/explanation*/
            /* 미래에 쓰일 인덱스가 된다면 nx, ny를 x, y에 그대로 대입*/
            x = nx;
            y = ny;
        }
        else
        {
            dir_num = (dir_num + 1)%4;
           // cout<<" rotate i is "<<i<<"\n";
            x = x+dx[dir_num];
            y = y+dy[dir_num];
        }

        grid[x][y] = i;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << grid[i][j] << " ";
        cout << "\n";
    }



    return 0;
}