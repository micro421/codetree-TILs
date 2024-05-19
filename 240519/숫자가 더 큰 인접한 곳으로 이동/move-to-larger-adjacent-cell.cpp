#include <iostream>
#include <vector>
using namespace std;

int grid[100][100] = {0,0};
int n;
int r,c;
int curr_x, curr_y;
bool next_move_able = true; /*실수 노트 - bool 변수의 경우 명시적 초기화 필요*/
vector<int> v_curr_num;
int curr_num = 0;

bool InRange(int x, int y)
{
    return 0<=x && x<n && 0<=y && y<n;
}
void Simulate()
{
    next_move_able =false;

    v_curr_num.push_back( grid[curr_x][curr_y] ); /*다시 보기 - pair형을 담는 vector인지 확인*/
    //cout<<grid[curr_x][curr_y]<<" ";
    pair<int, int> max_pos;
    int dx[4] = {-1,1,0,0};
    int dy[4] ={0,0,-1,1};
    /*우선순위가 걸리기에 next_num>=curr_num 처럼 등호를 붙이는 게 아닌
     * next_num>curr_num으로 해주면 됨!*/
    /* 실수노트 - 그러면  무한 루프 돌게됨 항상 갱신이 되니까 due to Simulate 부를 때마다 curr_num을 0으로 계속 초기화 int curr_num = 0; */

    /*더 이상 못 움직일 때 return해주게 flag도 필요하고
     * curr_x, curr_y를 담아서 출력해주는 pair를 담는 vector?도 필요할 듯!*/

    curr_num = grid[curr_x][curr_y];

    for(int i=0; i<4; i++)
    {
        int next_x = curr_x+dx[i];
        int next_y = curr_y+dy[i];
        int next_num = grid[next_x][next_y];
        if(InRange(next_x, next_y) && (next_num > curr_num))
        {
            next_move_able = true;
            /*Max Position 갱신해준다*/
            /*즉 max_pos에 담는다*/
            curr_num = next_num;
            max_pos = make_pair(next_x, next_y);
            break; /*5보다 큰 숫자 8과 10 이렇게 2개여도 아래의 우선순위 높아서 중단*/
        }

    }
    /*tie로 curr_x,curr_y 쌍에 max_pos를 대입해서
     * 현 위치를 갱신해준다.*/
    tie(curr_x, curr_y) = max_pos;
    /*위와 같이 갱신 시, 다음번에 Simulate() 호출 시
     * 다음 번 Simulate() 호출 기준으로 curr_x, curr_y 저장*/
}

int main()
{

    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>r>>c;
    curr_x = r-1;
    curr_y = c-1;
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            cin>>grid[i][j];
        }
    }

    while(next_move_able) {
        Simulate();
        if (!next_move_able)
            break; /*그런데 이 탈출 조건 없어도 괜찮은지 확인*/
    }

    /*curr_num을 담는 vector를 출력*/
        for (int i = 0; i < v_curr_num.size(); i++)
            cout << v_curr_num[i] << " ";

        return 0;
}