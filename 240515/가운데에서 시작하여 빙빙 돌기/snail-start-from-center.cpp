#include <iostream>

using namespace std;

int n;
int grid[100][100] = {0,0};
int dx[4] = {0,-1,0,1};
int dy[4] = {1,0,-1,0};

bool InRange(int x, int y)
{
    return (0<=x && x<n && 0<=y && y<n);
}
int AdapatableRangeNum(int i)
{
    int dx_num;
    for(int j=0; j<=50; j++)
    {
        int k1 = (2*j+1);
        int k2 = (2*j+3);
        if(i>=k1*k1 && i<k2*k2) /* AND OR 로직 실수 주의! */
        {
            dx_num = j+2;
            break;
        }
    }

    return dx_num;
}
/*range_num은 1부터 3^2-1까지는 2
 * (2*j+1)^2부터 (2*j+3)^2-1은 j+2를 반환해줌
 * 3^2부터 5^2-1까지는 3
 * 5^2부터 7^2-1까지는 4
 * 7^2부터 9^2-1까지는 5를 반환 해준다*/
bool AdaptableFunc(int nx, int ny,int range_num)
{
    return (abs(nx - n/2)<range_num) && (abs(ny- n/2)<range_num);
    // wrong return (nx<(n/2+range_num))&&(ny<(n/2+range_num)) &&(nx>(n/2-(range_num))) && (ny>(n/2-(range_num)));
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
        //cout << "i is " << i << " and range_num is" << range_num << "\n";

        if(AdaptableFunc(nx,ny,range_num) && InRange(nx, ny) && (grid[nx][ny] == 0))
        {
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