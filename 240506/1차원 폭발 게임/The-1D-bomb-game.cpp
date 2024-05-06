#include <iostream>
#define BLANK 0

using namespace std;

int n, m;
int grid[100]={0,0};


int Bumb(int s_idx,int num, int len)
{
    int next_grid[100]={0,0};
    int end_of_array = 0;
    for(int i=s_idx; i<len; i++)
    {
        if(grid[i]== num)
        {
            grid[i]=BLANK;
        }
        else
            break;
    }

    for(int i=0; i<len; i++)
    {
        if(grid[i])
        {
            next_grid[end_of_array] = grid[i];
            end_of_array++;
        }
    }

    for(int i=0; i<end_of_array; i++)
    {
        grid[i]= next_grid[i];
    }

    return end_of_array;
}

int Consecutive_Func(int len)
{
    int length = len;
    int consecutive_flag = 0;
    int consecutive_cnt=1;
    int start_idx;

    for(int i=1/*1*/; i<len/*len*/; i++)
    {
        if(grid[i-1] == grid[i])
        {
            consecutive_cnt++;

        }
        else
        {
            consecutive_cnt = 1;
        }
        if(consecutive_cnt>=m)
        {
            consecutive_flag = 1;
            start_idx = i-m+1;/*i-m+1*/
            length = Bumb(start_idx, grid[i], length);
            break;
        }
    }

    if(length == 1 && m==1) /* 길이가 1인데 m=1이어서 하나를 지워야 하는 상황*/
    {
        length=Bumb(0, grid[0], length);
        consecutive_flag = 0;
    }

   if(consecutive_flag == 0)
    {
        return length;
    }
    else
    {
        return Consecutive_Func(length);
    }

}

int main() {

    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m;

    for(int i=n-1; i>=0; i--)
    {
        cin>>grid[i];
    }

    int res = Consecutive_Func(n);


    cout<<res<<"\n";
    for(int i=res-1; i>=0; i--)
        cout<<grid[i]<<"\n";
    return 0;
}