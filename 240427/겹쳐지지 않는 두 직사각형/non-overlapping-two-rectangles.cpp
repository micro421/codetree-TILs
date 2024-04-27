#include <iostream>
#include <algorithm>

#define ERR_NUM 25001

/* Brouteforcing in Grid */


using namespace std;
int n, m;
int first_err_flag = 0;
int second_err_flag = 0;
int arr[5][5] = { 0,0 };
int check[5][5]{ 0,0 };

int max_sum = -25000; /*Minimum */

bool InRange(int x, int y)
{
    return 0 <= x && x < n && 0 <= y && y < m;
}
/*
void CheckArray_Init_TwoRect(int a, int b, int i, int j)
{
    for (int x = a; x <= i; x++)
    {
        for (int y = b; y <= j; y++)
        {
            if (check[i][j] == 2)
            {
                check[i][j] = 1;
            }
            else
            {
                if (check[i][j] == 1)
                {
                    check[i][j] = 0;
                }
            }
        }
    }
    return;
}
*/
int SecondRect(int a, int b, int p, int q)
{
    int second_sum = 0;

    for (int i = a; i < (a + p); i++)
    {
        for (int j = b; j < (b + q); j++)
        {
            check[i][j] += 1;
            if ((check[i][j] >= 2) || !InRange(i, j))
            {
                second_err_flag = ERR_NUM;
                //CheckArray_Init_TwoRect(a,b, i, j);
                return 0;
            }

            second_sum += arr[i][j];
        }
    }

    return second_sum;
}

int FirstRect(int x, int y, int k, int l)
{/* x,y is Start Point and k and l box */
    int first_sum = 0;
    //
    for (int i = x; i < (x + k); i++)
    {
        for (int j = y; j < (y + l); j++)
        {
            check[i][j] += 1;
            if (!InRange(i, j))
            {
                first_err_flag = ERR_NUM;
                return 0;
            }
            first_sum += arr[i][j];
        }
    }
    return first_sum;
}

void Check_Init_Proper(int x, int y, int k, int l)
{
    for (int i = 0; i < n; i++) fill(check[i], check[i] + m, 0);

    for (int i = x; i < (x + k); i++)
    {
        for (int j = y; j < (y + l); j++)
        {
            check[i][j] += 1;
        }
    }

    return;
}

int TotalRect(int x, int y)
{
    //*properly Init plz */

    for (int k = 1; k <= n; k++)
    {
        for (int l = 1; l <= m; l++)
        {
            first_err_flag = 0;
            second_err_flag = 0;

            for (int i = 0; i < n; i++) fill(check[i], check[i] + m, 0);
            int rect_first = 0;
            rect_first = FirstRect(x, y, k, l);
            if (first_err_flag == ERR_NUM)
            {
                rect_first = 0;
                continue;
            }
           
            for (int a = 0; a < n; a++) /* a and b is starting point! */
            {
                for (int b = 0; b < m; b++)
                {

                    for (int p = 1; p <= n; p++)
                    {
                        for (int q = 1; q <= m; q++)
                        {
                            int rect_second = 0;
                            second_err_flag = 0;
                            rect_second = SecondRect(a, b, p, q);
                            if (second_err_flag == ERR_NUM)
                            {
                                rect_second = 0;
                                Check_Init_Proper(x, y, k, l);
                                continue;
                            }
                            int total_sum = rect_first + rect_second;
                            max_sum = max(max_sum, total_sum);
                        }
                    }
                }
            }
        }
    }
    return max_sum;
}

int main() {

    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> arr[i][j];
        }
    }

    for (int x = 0; x < n; x++) {
        for (int y = 0; y < m; y++) {
            TotalRect(x, y);
        }
    }

    cout << max_sum;
    return 0;
}