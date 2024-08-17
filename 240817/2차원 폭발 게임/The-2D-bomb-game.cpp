#include <iostream>
#include <algorithm>
#define BLANK 0

using namespace std;
int cnt;
int n, m, k;
int result;
int new_bumb_flag = 0;
int grid[100][100] = {0,0};
int converted_1d_arr[100] = {0, 0};
int temp_grid[100][100] = {0,0};

int Bumb_Oper(int len)
{
    int next_grid[100] = {0,0};
    int end_of_array = 0;
    for(int i=0; i<len; i++)
    {
        if(converted_1d_arr[i])
        {
            next_grid[end_of_array] = converted_1d_arr[i];
            end_of_array++;
        }
    }

    for(int i=0; i<len; i++)/* Mistake !!! copy whole array ! copy and paste */
    {
        converted_1d_arr[i] = next_grid[i];
    }


    return end_of_array;
}

void Bumb_Fill_Zero(int s_idx, int num, int len)
{
    for(int i=s_idx; i<len; i++)
    {
        if(converted_1d_arr[i]==num)
        {
            converted_1d_arr[i] = BLANK;
        }
        else
            break;
    }

}

void Consecutive_Func(int len)
{
    int consecutive_cnt = 1;
    int start_idx;
    new_bumb_flag = 0;

    /*Compare array yoso 2EA */
    for(int i=1; i<len;i++)
    {
        if(converted_1d_arr[i-1] == converted_1d_arr[i])
        {
            consecutive_cnt++;
        }
        else
        {
            consecutive_cnt = 1;
        }
        if(consecutive_cnt >=m) /* Bumb make condition OK */
        {
            new_bumb_flag = 1;
            start_idx = i-m + 1;
            Bumb_Fill_Zero(start_idx, converted_1d_arr[i], len);
        }
    }
}

void Func_1d_Process()
{
    /*consecutive function judgement and operating bumb*/
    while(1)
    {
        Consecutive_Func(result);
        if(new_bumb_flag == 1) /* New Bumb Occur! */
        {
            result = Bumb_Oper(result);
        }
        if(new_bumb_flag == 0)
        {
            break;
        }
    }

    /* temp_grid <= converted_1d_arr By Column like puzzle */
    return;
}

void Func_Convert_1d_to_2d ( int column_numb)
{
    for(int i=0; i<n; i++) /*i is same as row number */
    {
        /*2d to 1d converting */
        converted_1d_arr[i] = grid[i][column_numb];
    }

    return;
}

void Copy_By_Column(int column_numb)
{
    int i=n-1;
    for(int j=n-1; j>=0; j--) {
        if (converted_1d_arr[j] != BLANK) {
            temp_grid[i][column_numb] = converted_1d_arr[j];
            i--;
        }
    }

    return;
}
void Func_2d_Bumb( )
{
    for(int i=0; i<n; i++) /* Init Location Caution ! */
    {
        fill(temp_grid[i], temp_grid[i]+100, 0);
    }
    for(int i=0; i<n; i++) /* column n EA */
    {
        fill(converted_1d_arr, converted_1d_arr + 100, 0);
        Func_Convert_1d_to_2d (i);
        result = n;
        Func_1d_Process();
        Copy_By_Column(i); /*temp_grid에 대입 */
    }
    for(int i=0; i<n; i++)
    {
        for(int j=0;j<n; j++) {
                if(temp_grid[i][j] !=BLANK) {
                    grid[i][j] = temp_grid[i][j];
                }
                else
                {
                    grid[i][j] = BLANK; /*Mistake ! */
                }

        }
    }

    return;
}

void Func_2d_Rotate ( )
{
    for(int i=0; i<n; i++) /* Init Location Caution ! */
    {
        fill(temp_grid[i], temp_grid[i]+100, 0);
    }
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            temp_grid[j][n-1-i]=grid[i][j];
        }
    }

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            grid[i][j] = temp_grid[i][j];
        }
    }
    return;
}

void Count_Bumb ()
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(grid[i][j]!=BLANK)
            {
                cnt++;
            }
        }
    }
}

void Erase_Blank_After_Rotate ()
{
    for(int i=0; i<n; i++) /* Init Location Caution ! */
    {
        fill(temp_grid[i], temp_grid[i]+100, 0);
    }
    /* wrong init location ! int temp_end = n-1; */
    for (int j = 0; j < n; j++) { /* By 1 Column */
        int temp_end = n-1;
        for(int i=n-1; i>=0; i--) {
            if(grid[i][j]!=BLANK) {
                temp_grid[temp_end][j] = grid[i][j];
                temp_end--;
            }
        }
    }
    /*copy and paste*/
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            grid[i][j] = temp_grid[i][j];
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m>>k;
    cnt =0 ;
    result = n;
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            cin>>grid[i][j];
        }
    }

    for(int i=0; i<k; i++)
    {
        Func_2d_Bumb ();
        Func_2d_Rotate ();
        Erase_Blank_After_Rotate (); /*next process에서 제대로 폭탄 터뜨리기 위해서*/

        /*cout<<i<<"Try\n";

        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                cout<<grid[i][j]<<" ";
            }
            cout<<"\n";
        }
        */
    }


    Count_Bumb ();
    cout<<cnt;

    return 0;
}