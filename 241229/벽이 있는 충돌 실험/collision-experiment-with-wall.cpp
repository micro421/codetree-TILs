#include <iostream>
#include <algorithm>
#include <queue>
#define MAX_N 50
using namespace std;

int n,m;
/* 자료구조 최적화 가능함,
queue<int> grid[MAX_N][MAX_N]과 queue<int> new_grid[MAX_N][MAX_N]로*/
queue<pair<bool, int>> grid[MAX_N][MAX_N]; /* default is 0 initialization */
/* exist.first : exist 0 or 1 AND exist,second : direction numb */
queue<pair<bool, int>> next_grid[MAX_N][MAX_N]; /* 모든 next_count 값을 초기화*/

int dx[4] = {0,1,0,-1};
int dy[4] = {1,0,-1,0};

int GetDirNum(char dir)
{
    int dir_num = 0;
    if(dir == 'R')
        dir_num =0;
    else if(dir=='D')
        dir_num = 1;
    else if(dir=='L')
        dir_num = 2;
    else
    {
        if(dir == 'U')
            dir_num = 3;
    }
    return dir_num;
}

bool InGrid(int next_x, int next_y)
{
    return (0<=next_x && next_x <n && 0<=next_y && next_y <n);
}
void Move_One_Grid(int cur_x, int cur_y)
{
    int cur_dir = grid[cur_x][cur_y].front().second;
    //cout<<"Test : cur_dir"<<cur_dir<<"\n";
    int next_x = cur_x + dx[cur_dir];
    int next_y = cur_y + dy[cur_dir];

    if(InGrid(next_x, next_y))
    {
        pair<bool, int> next_input = make_pair(true, cur_dir);
        next_grid[next_x][next_y].push(next_input);
        //cout<<"Test : next_grid value is"<<next_grid[next_x][next_y].front().first<<" "<<next_grid[next_x][next_y].front().second<<"\n";
    }
    else
    {
        pair<bool, int> next_input = make_pair(true, (cur_dir+2)%4);
        next_grid[cur_x][cur_y].push(next_input); /* MISTAKE */
        //cout<<"Test : next_grid value is"<<next_grid[cur_x][cur_y].front().first<<" "<<next_grid[cur_x][cur_y].front().second<<"\n";
    }
}

void Bead_Exist()
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(!grid[i][j].empty() /*&& grid[i][j].front().first*/) /* 구슬이 존재하는가 */
            {
                Move_One_Grid(i,j); /* front에 있는 Bead를 움직이게!*/
            }
        }
    }
}

void Double_Check()
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {/* All grid를 다 돌았음에도 불구하고 */
            if(next_grid[i][j].size() >= 2)
            {
                while(!next_grid[i][j].empty())
                {
                    next_grid[i][j].pop();
                }
            }
        }
    }
}
void Init_Grid()
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            while(!grid[i][j].empty())
            {
                grid[i][j].pop();
            }
            //cout<<"queue size is "<<grid[i][j].size()<<"\n";
        }
    }
}
void Update_Grid()
{
    Init_Grid();
    for(int i=0; i<n; i++) {
        for (int j = 0; j < n; j++) {
            //cout << "queue size is " << grid[i][j].size() << "\n";
        }
    }
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            //cout<<"next_grid value is"<<next_grid[i][j].front().first<<" "<<next_grid[i][j].front().second<<"\n";
            if(!next_grid[i][j].empty()) /* Essential Condition, 비었는데 추가하면, default 값이 추가 됨!*/
            {
                grid[i][j].push(next_grid[i][j].front());
            }
                //cout << "NEW queue size is " << grid[i][j].size() << "\n";
        }
    }
}

void Init_NewGrid()
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            while(!next_grid[i][j].empty())
            {
                next_grid[i][j].pop();
            }
            // cout<<"queue size is "<<next_grid[i][j].size()<<"\n";
        }
    }
}



void Move_All_At_sec()
{
    Init_NewGrid();
    Bead_Exist();
    Double_Check();
    Update_Grid();
}

int Final_Result()
{
    int res=0;

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            if((!grid[i][j].empty()) && grid[i][j].front().first)
            {
                res++;
            }
        }
    }
    return res;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin>>t;

    for(int i=0;i<t;i++)
    {
        int result;
        cin>>n>>m;
        Init_Grid();
        for(int j=0; j<m; j++)
        {
            int x, y;
            char d;
            cin>>x>>y>>d;
            int dir_num = GetDirNum(d);
            //cout<<"dir_num is "<<dir_num<<"\n";
            pair<bool, int> input_pair = make_pair(true, dir_num);
            grid[x-1][y-1].push(input_pair);
        }
        for(int k=0; k<2*n; k++)
        {
            Move_All_At_sec();
        }
        result = Final_Result();
        cout<<result<<"\n";
    }
    return 0;
}