#include <iostream>

using namespace std;

int n;
int m;
int t;
int arr[21][21] ={0,0}; /*실수 노트 : 맨 처음 0,0 초기화 안함*/
int count[21][21] ={0,0};
int next_count[21][21] ={0,0};

/* arr과 count 구분*/
bool InRange(int x, int y)
{
    return ( 0<=x && 0<n && 0<=y && y<n);
}

pair<int, int> GetNextPos(int x,int y)
{

    pair<int, int> largest_pos;
    int dx[4] = {-1,1,0,0};
    int dy[4] = {0,0,-1,1};
    int max_num = 0;
    int curr_num = arr[x][y];
    int next_num;
    //int next_x, next_y;
    for(int dir_num=0; dir_num<4; dir_num++)
    {
        int next_x = x+dx[dir_num];
        int next_y = y+dy[dir_num];
        next_num = arr[next_x][next_y]; /*위에서 방지로직 int arr[20][20] ={0,0}; 있지만 없어도 하게끔 최적화 필요*/
        if(InRange(next_x, next_y) && (next_num > max_num)) {
            /*가장 큰 값이 여러 개 있을 때 우선순위가 있기에 if 조건에서 next_num>=max_num 불가능*/
            /*이에 관한 코드트리 구현 방식도 습득해보기*/
            /*max_num 또한 max 값이기에 갱신 필요*/
            max_num = arr[next_x][next_y];
            largest_pos = make_pair(next_x, next_y);
        }
    }
    //tie(curr_x, curr_y) = largest_pos; /* 간과 - 현재 position 갱신 빼먹음*/
    /* curr_x, curr_y를 갱신하려니 여러 객체여서 답이 흠...*/
    return largest_pos;
}
// [x, y] 위치에 있는 구슬을 움직입니다.
void Move(int x, int y)
{
    // 그 다음 위치를 계산합니다.
    pair<int, int> next_pos =GetNextPos(x,y);
    int next_x = next_pos.first, next_y = next_pos.second;

    // 그 다음 위치에 구슬의 개수를 1만큼 추가
    next_count[next_x][next_y]++;
}

// Step1 구슬을 전부 한 번씩 움직여 봅니다.
void MoveAll()
{
    // Step 1-1
    // 그 다음 각 위치에서 구슬 개수를 전부 초기화해놓습니다.
    // 즉, 그 다음 위치가 될 next_count 배열을 초기화해놓습니다.
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            next_count[i][j] =0;
        }
    }

    // Step 1-2
    //[i,j] 위치에 구슬이 있는 경우
    // 움직임을 시도해보고, 그 결과를 전부 next_count에 기록합니다.
    // 참고로 next_count에 기록하는 것은 Move(i,j) 함수서 합니다. - 동작 분리 유의!
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(count[i][j]==1)
            {
                Move(i,j);
            }
        }
    }

    // Step 1-3
    // next_count 값을 count에 복사합니다.
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        { /* 실수 여기서 불필요한  if(count[i][j]==1) 같은 조건 넣어서 망함*/
         /*단순 복사다! 그저 옮겨주는 copy!*/
            count[i][j] = next_count[i][j];
        }
    }


}

//Step2
//충돌이 일어나는 구슬은 전부 지워줍니다.
void RemoveDuplicatedMarbles()
{
    // 충돌이 일어난 구슬들이 있는 위치만 빈 곳으로 설정하면 됩니다.
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(count[i][j]>=2)
                count[i][j] = 0;
        }
    }
}
void Simulate()
{
    //Step1 구슬을 전부 한 번에 움직여 봅니다.
    MoveAll();

    // Step2
    // 움직임 이후에 충돌이 일어나는 구슬들을 골라
    // 목록에서 지워줍니다.
    RemoveDuplicatedMarbles();
}
int main() {

    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m>>t;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> arr[i][j];
        }
    }
    for (int i = 0; i < m; i++)
    {
        int r,c;
        cin>>r>>c;
        count[r-1][c-1] = 1;
    }
/*r행 c열이니 r-1, c-1로 인자 전달해서 편안하게 하자*/

    while(t--)
    {
        Simulate();
    }
    
    int total_cnt =0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if(count[i][j]==1)/* 실수 of ! 연산자 쓰기: if(!count[i][j])라는 거는 !count[i][j]가 참이 될 때다! */
            {
                total_cnt++;
            }
        }
    }
    cout<<total_cnt;
    return 0;
}