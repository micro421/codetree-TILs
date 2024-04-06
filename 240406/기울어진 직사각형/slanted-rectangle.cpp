#include <iostream>
#include <algorithm>

using namespace std;

int n;
int dx[4] = { 1,-1 ,-1 ,1 };
int dy[4] = { -1,-1, 1, 1 };
int arr[20][20] = { 0,0 };

int arrow1_x, arrow1_y;
int arrow2_x, arrow2_y;
int arrow3_x, arrow3_y;


bool InRange(int x, int y)
{
    return 0 <= x && x < n && 0 <= y && y < n;
}

int TotArea(int x, int y, int dodd, int deven)
{
    int area = 0;

    for (int i = 0; i < (dodd - 1); i++)
    {
        int x1, y1;
        y1 = y + dy[0] * i;
        x1 = x + dx[0] * i;
        area += arr[y1][x1];
    }

    for (int i = 0; i < (deven - 1); i++)
    {
        int x2, y2;
        y2 = arrow1_y + dy[1] * i;
        x2 = arrow1_x + dx[1] * i;
        area += arr[y2][x2];
    }

    for (int i = 0; i < (dodd - 1); i++)
    {
        int x3, y3;
        y3 = arrow2_y + dy[2] * i;
        x3 = arrow2_x + dx[2] * i;
        area += arr[y3][x3];
    }

    for (int i = 0; i < (deven - 1); i++)
    {
        int x4,y4;
        y4 = arrow3_y + dy[3] * i;
        x4 = arrow3_x + dx[3] * i;
        area += arr[y4][x4];
    }

    return area;
}
int MakeRectAble(int x, int y, int dodd, int deven) /* 화살표 번호에 따라 이름을 지어줌 */
{
    arrow1_x = x + dx[0] * (dodd - 1);
    arrow1_y = y + dy[0] * (dodd - 1);

    arrow2_x = arrow1_x + dx[1] * (deven - 1);
    arrow2_y = arrow1_y + dy[1] * (deven - 1);

    arrow3_x = arrow2_x + dx[2] * (dodd - 1);
    arrow3_y = arrow2_y + dy[2] * (dodd - 1);

    int err1 = InRange(arrow1_x, arrow1_y);
    int err2 = InRange(arrow2_x, arrow2_y);
    int err3 = InRange(arrow3_x, arrow3_y);
    int tot_err = err1 * err2 * err3;

    if (tot_err == 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


int main() {

    ios::sync_with_stdio(0);
    cin.tie(0);
    int max_area = 0;
    int sum = 0;
    int err_num;
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> arr[i][j];
        }
    }

    
   for (int y = 0; y < n; y++)
    {
        for (int x = 0; x < n; x++)
        {
            for (int dodd = 2; dodd<=n ; dodd++)
            {
                for (int deven = 2; deven <= n; deven++)
                {
                    err_num = MakeRectAble(x, y, dodd, deven);
                    if (err_num == 1)
                    {
                        sum=TotArea(x, y, dodd, deven);
                        max_area = max(max_area, sum);
                    }
                }
            }
        }
    }

    cout << max_area;
    return 0;
}