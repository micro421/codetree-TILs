#include <iostream>
#define BLANK 0

using namespace std;

int n, m;
int grid[100]={0,0};
int result = 0;
int new_bumb_flag = 0; /*new bumb flag fill flag*/


int Bumb_Oper(int len)
{
    int next_grid[100]={0,0};

    int end_of_array = 0;

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
void Bumb_Fill(int s_idx,int num, int len)
{
    for(int i=s_idx; i<len; i++)
    {
        if(grid[i]== num)
        {
            grid[i]=BLANK;
        }
        else
            break;
    }

}

void Consecutive_Func(int len)
{
    int consecutive_cnt=1;
    int start_idx;
    new_bumb_flag = 0;

    /* Compare 2EA*/
    for(int i=1; i<len; i++) {
        if (grid[i - 1] == grid[i])
        {
            consecutive_cnt++;
        }
        else
        {
            consecutive_cnt = 1;
        }

        if (consecutive_cnt >= m ) /*Bumb Make Condition Ok*/
        {
            new_bumb_flag = 1;
            start_idx = i - m + 1; /*(m-1)+(i-m+1) = i */
            Bumb_Fill(start_idx, grid[i], len); /*Bumb Make Condition => Bumb_Fill*/
        }
    }
}

int main() {

    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;

    for (int i = n - 1; i >= 0; i--) {
        cin >> grid[i];
    }

    /*result 변수 재사용성 때문에*/
    result = n;

    /*Start Recursive*/
    while(1) {
        Consecutive_Func(result); /* Only Compare 2EA*/
        if (new_bumb_flag == 1) { /*New Bumb Occur!*/
            result = Bumb_Oper(result);
        }
        if (new_bumb_flag == 0) {
            break; /*If new bumb not Occur, break the infinite loop*/
        }
    }
    /*exception of test case #2 as 제출기록*/
    /*exception dealing because Consecutive_Func only compare 2EA >=result*/
    if(m == 1)
    {
        result = 0;
    }

   // cout<<"new_bumb_flag is "<<new_bumb_flag<<"\n";

    cout<<result<<"\n";
    if(result>=1) {
        for (int i = result-1; i >= 0; i--)
            cout << grid[i] << "\n";
    }
    return 0;
}