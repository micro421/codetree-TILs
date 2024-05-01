#include <iostream>
#define MAX_N 100
#define DIR_NUM 4

using namespace std;

int n; /* n x n */
int dir;
int r,c,m1,m2,m3,m4;
int grid[MAX_N][MAX_N];
int copied[4*MAX_N];
int dx[DIR_NUM] ={-1,-1,1,1};
int dy[DIR_NUM] = {1,-1,-1,1};

bool InRange(int x, int y)
{
    return 0<=x && x<n && 0<=y && y<n;
}

void RotateLeft()
{ /*Shift to Right */
    int cp_size = m1+m2+m3+m4;
    int temp = copied[cp_size - 1];

    for(int i=cp_size-1; i>=1; i--)
        copied[i] = copied[i-1];

    copied[0] = temp;

}

void RotateRight()
{/*Shift to Left */
    /* 2 3 4 2 3 1*/
    /* 3 4 2 3 1 2*/
    int cp_size = m1+m2+m3+m4;

    int temp = copied[0];

    for(int i=0; i<=cp_size-2; i++)
        copied[i] = copied[i+1];

    copied[cp_size-1] =temp;
}

void GetShifted(int x,int y, int k, int l)
{
    int move_num[DIR_NUM] = {k, l, k, l};
    int idx = 0;
    for(int d=0; d<DIR_NUM; d++)
    {
        for(int q=0; q<move_num[d]; q++)
        {
            grid[x][y] = copied[idx];
            x+=dx[d]; y+=dy[d];

            idx++;
        }
    }


}

void GetChange(int x,int y, int k, int l, int dir)
{
    int move_num[DIR_NUM] = {k, l, k, l};

    // follow rectangle
    int idx=0;
    for(int d=0; d<DIR_NUM; d++)
    {
        for(int q=0; q<move_num[d]; q++)
        {
            copied[idx] = grid[x][y];
            x+=dx[d]; y+=dy[d];

            //cout<<"copied[0] is "<<copied[0]<<"\n";
            idx++;
        }
    }
    /*for(int i=0; i<m1+m2+m3+m4; i++)
    {
        cout<<copied[i]<<" ";
    } */
    //cout<<"\n";

    if(dir == 0)
    {
        RotateLeft();
    }
    if(dir == 1)
    {
        RotateRight();
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            cin>>grid[i][j];
        }
    }
    cin>>r>>c>>m1>>m2>>m3>>m4>>dir;

    GetChange(r-1, c-1, m1, m2, dir);

    /*
    for(int i=0; i<m1+m2+m3+m4; i++)
    {
        cout<<copied[i]<<" ";
    }
     */

    GetShifted(r-1, c-1, m1, m2 );

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            cout<<grid[i][j]<<" ";
        }
        cout<<"\n";
    }
    return 0;
}

/* 2 3 4 2 3 1*/
/*toLeft*/
/* 1 2 3 4 2 3 */