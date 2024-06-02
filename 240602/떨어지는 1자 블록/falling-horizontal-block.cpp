#include <iostream>
using namespace std;
int n, m, k;
int grid[100][100] ={0,0};
int curr_row = 0; /*처음 1*m 블록이 떨어지는 행*/
bool flag_result = false;
int dx[4] = {-1,1,0,0};
int dy[4] = {0,0,-1,1};
/* k번째 열 부터 k + m - 1번째 열까지의 공간을 차지*/
/*밑으로 내려갈 때를 대비해서 ClearPosition이라는 것과
 * BlockShift를 만들되,
 * 1*m을 유동적으로 움직이기 위해서 FillBoard(int row, int col_s, int col_e)로 받고
 * 아키텍처 짜기*/

pair<int, int> curr_pos = {0, 0}; /*Rev 0602 - curr_pos using architecture로 변경
 * curr_pos.first가 row, curr_pos.second가 col*/
bool InRange(int x, int y)
{
    return (0<=x && x<n && 0<=y && y<n);
}
void FillBoard(int row, int col_s) /*i=k-1부터 i<=k+m-2까지 채우는 함수*/
{
    for(int i=col_s; i<col_s+m; i++) {
        grid[row][i]++;
    }

    //cout<<"FillBoard Result Debugging"<<grid[0][0];

}

bool CheckFirstCol(int row, int col)
{
    bool each_block_touch = false;
    for (int dir_num = 0; dir_num < 4; dir_num++) {
        /*조사 블럭이 하나뿐 - 상하좌니까 dir_num !=3인 경우만*/
        int x = row+dx[dir_num];
        int y = col + dy[dir_num];
        if((dir_num == 0 || dir_num ==1)/*dir_num != 3*/) /*dir_num == 1 조건만으로 최적화 여부 확인*/
        {
            if(InRange(x,y) && grid[x][y]==1)
            {
                each_block_touch = true;
                break;
            }
        }
    }
    return each_block_touch;
}

bool CheckLastCol(int row, int col)
{
    bool each_block_touch = false;
    for (int dir_num = 0; dir_num < 4; dir_num++)
    { /*조사 블럭이 하나뿐 - 상하우니까 dir_num !=2인 경우만*/
        int x = row+dx[dir_num];
        int y = col + dy[dir_num];
        if((dir_num == 0 || dir_num ==1)/*dir_num != 2 */) /*dir_num == 1 조건만으로 최적화 여부 확인*/
        {
            if(InRange(x,y) && grid[x][y]==1)
            {
                each_block_touch = true;
                break;
            }
        }
    }

    return each_block_touch;
}

bool CheckMidCol(int row, int col)
{
    bool each_block_touch = false;
        for (int dir_num = 0; dir_num < 4; dir_num++) { /*조사 블럭 상 또는 하*/
            int x = row+dx[dir_num];
            int y = col + dy[dir_num];
            if( dir_num ==0 || dir_num ==1 ) /*dir_num == 1 조건만으로 최적화 여부 확인*/
            {
                if(InRange(x,y) && grid[x][y]==1)
                {
                    each_block_touch = true;
                    break;
                }
            }
        }
    return each_block_touch;
}
bool CheckBoardTouch(int row, int col_s)
{
    bool flag_touch = false;

    /*예외처리*/
    if(n==1 && m==1 && k==1) {
        flag_touch = true;
    }
    else {
        for (int i = col_s; i < col_s + m; i++) {
            if (i == col_s) {
                flag_touch = CheckFirstCol(row, i); /*상하좌*/
                /*이러한 Check__Col 함수 내부에서 flag_touch를  True로 하던지 말던지 한다.*/
                if (flag_touch) {
                    break;
                }
            } else if (i == col_s + m - 1) {
                flag_touch = CheckLastCol(row, i);
                if (flag_touch) {
                    break;
                }
            } else {
                flag_touch = CheckMidCol(row, i); /*아래만*/
                if (flag_touch) {
                    break; /*제어문 if말고 반복문을 빠져나가는 break*/
                }
            }
        }
    }
    return flag_touch;
}

void CheckClearToShift(int row, int col_s)
{
    for(int i=col_s; i<col_s+m; i++)
    {
        grid[row][i] =0;
    }

    return;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m>>k;
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            cin>>grid[i][j];
        }
    }
    curr_pos.first = 0;
    curr_pos.second = k-1;

    while(!flag_result) {

        //if (n == 1 && m == 1 && k==1) {
        //    flag_result = true;
        //}
        //else
        //{
            FillBoard(curr_pos.first, curr_pos.second); /*i=k-1부터 m개의 열을 채우는 함수*/
            flag_result = CheckBoardTouch(curr_pos.first, curr_pos.second);
        //}
        //cout<<"flag_result is "<<flag_result<<"\n"; /*Here debugging and find mistake as int x = row; at Check___Col Function*/
        if(flag_result)
        {
            break;
        }
        else
        {
            CheckClearToShift(curr_pos.first, curr_pos.second); /*기존 1*m짜리 블럭을 옮기기 위해 clear 해주는 작업*/
            curr_pos.first++; /* renew the row for block down*/
        }

        /*row에 관한 예외처리*/
        /*그런데 이런 예외처리에 관한 내용 문제 참고 필요한듯*/
        if(curr_pos.first >= n)
        {
            FillBoard(curr_pos.first - 1, curr_pos.second); /*test case #2 exceptions at 2nd trial for codetree */
            flag_result = true;
            break;
        }
    }
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
/*  설계 완료 시 논리 허점, 설계 오류, 프로세스 지킴 모두 확인 후 테스트 돌리기!*/
/*예외 1 1 1 enter 0 이라는 입력 있어서 예외처리 적절하게 아키텍처 설계*/

/*설계하면서 의문 - 기본개념처럼 pair<int, int> curr_pos 안 해도 괜찮지?
 * 아니 pair<int, int> curr_start_pos라도 쓰고 설계할까?
 * 블럭 접촉 안 되면, 전체 배열 claer 후 기존 쌓여있던 블록 대입 => 새로운 curr_start_pos부터 1*m 블럭 대입, 검사
 * 다시 블럭 접촉 안된지 아닌지에 따라 기존 process 진행 또는 답 내기! */