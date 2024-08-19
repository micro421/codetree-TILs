#include <iostream>

using namespace std;

int n,x,y;
char board[100][100];
int dx[4] = {0,1,0,-1};
int dy[4] = {1,0,-1,0};
int dir_num;
int curr_x, curr_y;
int t;

bool OutOfGrid(int pos_x, int pos_y) /*바로 밖이 격자 밖인지 판별하는 경우*/
{
    return ((0<=pos_x) &&(pos_x<n) && (0<=pos_y) && (pos_y<n) );

}
bool CanGo(int pos_x, int pos_y)
{
    if(board[pos_x][pos_y] == '#')
    {
        return false;
    }
    return true;
}

bool RightWall(int pos_x, int pos_y)
{
    int temp_dir = (dir_num+1)%4;
    int check_x = pos_x+dx[temp_dir];
    int check_y = pos_y+dy[temp_dir];
    if(board[check_x][check_y] == '#')
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool AbleToWall(int pos_x, int pos_y)
{
    t++;
    curr_x = pos_x;
    curr_y = pos_y; /*여기까지가 한 칸 이동*/
    dir_num = (dir_num + 1)%4;


    int next_xx = curr_x + dx[dir_num];
    int next_yy = curr_y + dy[dir_num];
    t++;

    curr_x = next_xx;
    curr_y = next_yy;

    dir_num = (dir_num+1)%4;
    int check_xx = next_xx + dx[dir_num];
    int check_yy = next_yy + dy[dir_num];
    if(board[check_xx][check_yy] == '#')
    {
        return true; /*오른쪽에 벽이 있게끔 한다*/
    }
    return false;
}
bool Simulate ()
{
    int next_x = curr_x+dx[dir_num];
    int next_y = curr_y+dy[dir_num];
    bool can_go = CanGo(next_x, next_y);
    bool out_of_grid = OutOfGrid(next_x, next_y);
    bool right_wall = RightWall(next_x, next_y);
    bool able_wall;
    if(can_go)
    {
        /*case #1 - 바로 앞이 격자 밖이라면  */
        if(!out_of_grid)
        {
            t++;
            return false; /* 종료하는 경우*/
        }
        else/*case #2 */
        {
            if(right_wall)/*오른쪽에 짚을 벽이 있는지 확인 */
            {
                curr_x = next_x;
                curr_y = next_y;
                t++;
                return true;
            }
            else /*짚을 벽이 없으면 오른쪽에 짚을 벽이 있겠끔 만들어준다.*/
            {
                able_wall = AbleToWall(next_x, next_y);
                if(able_wall)
                {
                    return true;
                }
                else /*우측에 짚을 벽이 없다면?*/ /*case 처리가 걱정됨*/
                {
                    t = -1;
                    return false;
                }
            }
        }
    }
    else
    {
        dir_num = (( dir_num + 3 ) % 4); /* 방향만 trun*/
    }

    if(t>=n*n)
    {
        t=-1;
        return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    cin>>x>>y;
    curr_x = x - 1;
    curr_y = y - 1;
    dir_num = 0;
    t = 0;
    /*기본적인 Init */
    for(auto & i : board) /*2차원 배열의 각 행을 가리키는 주소 값이어서 i는 char&[100] type */
    {
        fill(i, i+100,'@');
    }

    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
        cin>>board[i][j];

    bool ing = true;
    while(true)
    {
        ing = Simulate ();
        if(!ing)
            break;
    }

    cout<<t;
    return 0;
}