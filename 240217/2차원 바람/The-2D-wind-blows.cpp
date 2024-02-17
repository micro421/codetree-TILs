#include <iostream>
#include <algorithm>
#define ARR_MAX 100

using namespace std;
int base[ARR_MAX][ARR_MAX] = { 0,0 };
int checked[ARR_MAX][ARR_MAX] = { 0, 0 };
int changed[ARR_MAX][ARR_MAX] = { 0,0 };
int dx[4] = { 0,1,0,-1 };
int dy[4] = { 1,0,-1,0 };
int n, m, q;
int r1[ARR_MAX] = { 0,0 };
int c1[ARR_MAX] = { 0,0 };
int r2[ARR_MAX] = { 0,0 };
int c2[ARR_MAX] = { 0,0 };

void BoundaryShift(int row1, int col1, int row2, int col2)
{
	for (int i = col2; i >= col1+1; i--) /* row1행 친구들 우측으로*/
	{
		 changed[row1][i] = base[row1][i - 1];
	}
	for (int i = row2; i >= row1+1; i--) /* 아래로*/
	{
		changed[i][col2] = base[i - 1][col2];
	}
	for (int i = col1; i <= col2 - 1; i++) /* row2행 친구들 좌측으로 */
	{
		changed[row2][i] = base[row2][i+1];
	}
	for (int i = row1; i <= row2-1; i++)
	{
		changed[i][col1] = base[i + 1][col1];
	}
	/* 다시 재 복사 in base 배열*/
	for (int i = col2; i >= col1 + 1; i--) /* row1행 친구들 우측으로*/
	{
		base[row1][i] = changed[row1][i];
		changed[row1][i] = 0; /* 원상복구 */
	}
	for (int i = row2; i >= row1 + 1; i--) /* 아래로*/
	{
		base[i][col2] = changed[i][col2];
		changed[i][col2] = 0;
	}
	for (int i = col1; i <= col2 - 1; i++) /* row2행 친구들 좌측으로 */
	{
		base[row2][i] = changed[row2][i];
		changed[row2][i] = 0;
	}
	for (int i = row1; i <= row2 - 1; i++)
	{
		base[i][col1] = changed[i][col1];
		changed[i][col1] = 0;
	}
	
	return;
}

bool IdxRange(int x, int y)
{
	return (0 <= x && x < n &&  0<= y && y < m);
}

void AverageChange(int row1, int col1, int row2, int col2)
{
	for (int i = row1; i <= row2; i++)
	{
		for (int j = col1; j <= col2; j++)
		{
			int sum = 0;
			int cnt = 0;
			int avr = 0;
			sum += base[i][j];
			cnt++;
			for (int dir = 0; dir < 4; dir++)
			{
				int nx = i + dx[dir], ny = j + dy[dir];
				if (IdxRange(nx, ny) == 1)
				{
					sum += base[nx][ny];
					cnt++;
				}
			}
			avr = sum / cnt;
			changed[i][j] = avr;
		}
	}

	for (int i = row1; i <= row2; i++)
	{
		for (int j = col1; j <= col2; j++)
		{
			base[i][j] = changed[i][j];
			changed[i][j] = 0;
		}
	}
	return;
}
int main()
{
	cin.tie(0);
	ios::sync_with_stdio(0);

	cin >> n >> m >> q;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> base[i][j];
		}
	}
	for (int i = 0; i < q; i++)
	{
		cin >> r1[i] >> c1[i] >> r2[i] >> c2[i];
	}
	for (int i = 0; i < q; i++)
	{
		BoundaryShift(r1[i] - 1, c1[i] - 1, r2[i] - 1, c2[i] - 1); /*base 바꿈 */
		AverageChange(r1[i] - 1, c1[i] - 1, r2[i] - 1, c2[i] - 1);
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cout <<base[i][j]<<" ";
		}
		cout<<"\n";
	}

	return 0;
}