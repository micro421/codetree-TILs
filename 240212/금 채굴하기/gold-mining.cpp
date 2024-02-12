#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_NUM 20

using namespace std;

int res;
int n, m;
int grid[MAX_NUM][MAX_NUM];
vector<vector<int>> copy_array(19, vector<int>(19, 0)); /* 2k+1의 최댓값 */

/* 동적으로 2차원 벡터를 생성하고 그 벡터를 반환하는 함수 */
vector<vector<int>> createDia(int rows, int cols)
{ /*인자로 2k+1, 2k+1을 받아와 */
	// 기본 선언 vector<vector<int>> arr(rows, vector<int>(cols));

	/* 0으로 전체 초기화 로직 */
	vector<vector<int>> arr(rows, vector<int>(cols, 0));

	/* 다이아몬드 만드는 로직*/
	int k = (rows - 1) / 2;
	for (int i = 0; i < rows; i++)
	{
	
		for (int n = 0; n <= k; n++)
		{
			if ((i == (k - n)) || (i == (k + n)))
			{
				for (int j = n; j < cols - n; j++)
				{
					arr[i][j] = 1;
				}
			}
		}
	}

	return arr;
}

int  GetGoldCnt(int x, int y, int k)
{
	int sum_gold_cnt = 0;

	bool is_possible = true;
	for (int dx = 0; dx < 2*k+1; dx++)
	{
		for (int dy = 0; dy < 2*k+1; dy++)
		{
			if(copy_array[dx][dy] == 0) continue;
			if (x + dx >= n || y + dy >= n)
			{
				is_possible = false;
			}
			else sum_gold_cnt += grid[x + dx][y + dy];
		}
	}

	if (is_possible == false)
	{
		return 0;
	}
	else if (is_possible == true)
	{
		return sum_gold_cnt;
	}
}

int main()
{
	cin.tie(0);
	ios::sync_with_stdio(0);
	
	cin >> n >> m;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> grid[i][j];
		}
	}
	
	int cnt = 0; /* dia 채굴 횟수*/
	int sell = 0; /* 판매*/
	int cost = 0; /* 비용 */
	
	int max_diacnt = 0;
	for (int k = 0; k < 10; k++)
	{
		copy_array = createDia(2*k + 1, 2*k + 1);
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				cnt = GetGoldCnt(i, j, k);
				
				sell = cnt*m;
				cost = k*k+(k+1)*(k+1);
				if (sell - cost >= 0)
				{
					max_diacnt = max(cnt, max_diacnt);
				}
			}
		}
	}

	cout << max_diacnt;
	return 0;
}