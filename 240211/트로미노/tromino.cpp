#include <iostream>
#include <algorithm>
using namespace std;

int grid[200][200]={0,0}; /* n*m */
int n,m=0;
int res=0;
int max_tri = 0;
int max_garo = 0;
int max_sero = 0;
/* rotation example
 * int dir_num = 2;
int x = 1, y = 5;
int dx[4] = {1, 0, -1, 0}, dy[4] = {0, -1, 0, 1};
int nx, ny;

nx = x + dx[dir_num], ny = y + dy[dir_num];
Ref) https://www.codetree.ai/missions/5/problems/move-in-direction/introduction */


int dx[4] ={1,0,-1,0};
int dy[4] = {0,-1,0,1};
int IndexOutTrimino( int x1, int x2, int y1, int y2) /* IndexOutTrimino(wing_x, foot_x, wing_y, foot_y); */
{
    int max_x = max(x1, x2);
    int min_x = min(x1, x2);
    int max_y = max(y1, y2);
    int min_y = min(y1, y2);

    if( min_x<0 || max_x>=m || min_y<0 || max_y>=n )
        return 1;
    else
        return 0;

}

int IndexOutGaro( int x1, int x2, int y)
{
    int max_x = max(x1, x2);
    int min_x = min(x1, x2);

    if( min_x<0 || max_x>=m || y<0 || y>=n )
        return 1;
    else
        return 0;
}

int IndexOutSero( int y1, int y2, int x)
{
    int max_y = max(y1, y2);
    int min_y = min(y1, y2);
    if( min_y<0 || max_y>=n || x<0 || x>=m)
        return 1;
    else
        return 0;
}
int TriminoMake(int mid_x, int mid_y, int dir)
{
   //int dir = 0;
    int sum = 0;

    //for(int dir = 0; dir<4; dir++) {
        int idx_err=0;
        int wing_x = mid_x + dx[dir];
        int wing_y = mid_y + dy[dir];
        int foot_x = mid_x + dx[ (dir+1) %4 ];
        int foot_y = mid_y + dy[ (dir+1) %4 ];

        idx_err = IndexOutTrimino(wing_x, foot_x, wing_y, foot_y);
        if( idx_err == 1)
            return 0; /* 탈출 */

        sum += grid[wing_x][wing_y];
        sum+=grid[mid_x][mid_y];
        sum += grid[foot_x][foot_y];
    //}
    return sum;
}

int GaroMake( int mid_x, int mid_y )
{
    int sum = 0;
    int garo_err = 0;
    int left_x = mid_x+dx[2];
    int left_y = mid_y+dy[2];
    int right_x = mid_x+dx[0];
    int right_y = mid_y+dy[0];

    garo_err = IndexOutGaro(left_x, right_x, left_y);
    if(garo_err == 1)
        return 0;

    sum +=grid[left_x][left_y];
    sum+=grid[mid_x][mid_y];
    sum += grid[right_x][right_y];
    return sum;
}

int SeroMake( int mid_x, int mid_y)
{
    int sum = 0;
    int sero_err =0;
    int up_x = mid_x+dx[3];
    int up_y = mid_y+dy[3];
    int dn_x = mid_x+dx[1];
    int dn_y = mid_y+dy[1];

    sero_err = IndexOutSero(up_y, dn_y, up_x);
    if(sero_err == 1)
        return 0;

    sum+= grid[up_x][up_y];
    sum+= grid[dn_x][dn_y];
    sum+=grid[mid_x][mid_y];

    return sum;
}
int main() {

    cin.tie(0);
    ios::sync_with_stdio(0);

    cin>>n>>m;

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            cin>>grid[i][j];
        }
    }

    int tri = 0;
    int garo = 0;
    int sero = 0;
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            for(int dir_num =0; dir_num<4; dir_num++) {
                tri = TriminoMake(i, j, dir_num);
                max_tri = max(max_tri, tri);
            }
        }
    }

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            garo = GaroMake(i,j);
            max_garo = max(max_garo, garo);
        }
    }

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            sero = SeroMake(i,j);
            max_sero=max(max_sero, sero);
        }
    }

    int max_square = max(max_garo, max_sero);
    res = max(max_square, max_tri );

    cout<<res;
    return 0;
}