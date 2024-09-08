#include <iostream>
#include <algorithm>

using namespace std;

int n,m, r, c;
int curr_x, curr_y;
int sum;

int grid[100][100] = {0,0};
int dice[3][2] = { {1,6},
                  {2,5},
                  {3,4}};
int temp[4] = {0,0};

void Roll_Dn_Right()
{
    int tmp = temp[3];
    for(int i=3; i>=1; i--)
    {
        temp[i] = temp[i-1];
    }
    temp[0] = tmp;
}
void Roll_Up_Left ()
{
    int tmp = temp[0];
    for(int i=0; i<3; i++)
    {
        temp[i]=temp[i+1];
    }
    temp[3]= tmp;
}
void Copy_Up_Dn_Roll_Dice ()
{
    fill(temp, temp+4, 0);
    temp[0] = dice[0][0];
    temp[1] = dice[1][0];
    temp[2] = dice[0][1];
    temp[3] = dice[1][1];
}

void Copy_Left_Right_Roll_Dice ()
{
    fill(temp, temp+4, 0);
    temp[0] = dice[0][0];
    temp[1] = dice[2][0];
    temp[2] = dice[0][1];
    temp[3] = dice[2][1];
}
void Simul_Up()
{
    Copy_Up_Dn_Roll_Dice();
    Roll_Up_Left();
    dice[0][0] = temp[0];
    dice[1][0] = temp[1];
    dice[0][1] = temp[2];
    dice[1][1] = temp[3];

}
void Simul_Dn()
{
    Copy_Up_Dn_Roll_Dice();
    Roll_Dn_Right();
    dice[0][0] = temp[0];
    dice[1][0] = temp[1];
    dice[0][1] = temp[2];
    dice[1][1] = temp[3];

}

void Simul_Left()
{
    Copy_Left_Right_Roll_Dice();
    Roll_Up_Left();
    dice[0][0] = temp[0];
    dice[2][0] = temp[1];
    dice[0][1] = temp[2];
    dice[2][1] = temp[3];
 
}

void Simul_Right()
{
    Copy_Left_Right_Roll_Dice();
    Roll_Dn_Right();
    dice[0][0] = temp[0];
    dice[2][0] = temp[1];
    dice[0][1] = temp[2];
    dice[2][1] = temp[3];
    
}

bool InRange(int x, int y)
{
    return (0<=x && x<n && 0<=y && y<n);
}

int SumOfGrid()
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            sum += grid[i][j];
        }
    }

    return sum;
}
int main() {

    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m>>r>>c;

    curr_x = r-1;
    curr_y = c-1;
    grid[curr_x][curr_y] = dice[0][1];

    for(int i=0; i<m; i++)
    {
        char dir;
        bool in_the_grid = false;
        cin>>dir;
        if(dir == 'L')
        {
            in_the_grid = InRange(curr_x, curr_y-1);
            if(in_the_grid)
            {
                curr_y = curr_y - 1;
                Simul_Left();
                grid[curr_x][curr_y] = dice[0][1];
            }
            /*else{
                break;
            }*/
        }
        if(dir=='R')
        {
            in_the_grid = InRange(curr_x, curr_y+1);
            if(in_the_grid)
            {
                curr_y = curr_y + 1;
                Simul_Right();
                grid[curr_x][curr_y] = dice[0][1];
            }
            /*else{
                break;
            }*/
        }
        if(dir == 'U')
        {
            in_the_grid = InRange(curr_x-1, curr_y);
            if(in_the_grid)
            {
                curr_x = curr_x - 1;
                Simul_Up();
                grid[curr_x][curr_y] = dice[0][1];
            }
            /*else{
                break;
            }*/
        }
        if(dir == 'D')
        {
            in_the_grid = InRange(curr_x+1, curr_y);
            if(in_the_grid)
            {
                curr_x = curr_x + 1;
                Simul_Dn();
                grid[curr_x][curr_y] = dice[0][1];
            }
            /*else{
                break;
            }*/
        }

    }

    sum = SumOfGrid();

    cout<<sum;
    return 0;
}