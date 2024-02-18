#include <iostream>
#include <algorithm>
#define OFFSET	1000000 /* off set */
using namespace std;

int n;
int x1[100] = { 0,0 }; /* y=0인 x 좌표+OFFSET*/
int x2[100] = { 0,0 }; /* y=1인 x 좌표+OFFSET*/
int cnt;
int zeroone[100][2* OFFSET + 1] = { 0,0 };

void Func(int i, int j, int k)
{
	if ((zeroone[i][k] == 1) && (zeroone[j][k] == 1))
	{
		cnt++;
		return;
	}
}

int main()
{
	cin.tie(0);
	ios::sync_with_stdio(0);

	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> x1[i] >> x2[i]; /* (x1, x2]*/
		x1[i] += OFFSET;
		x2[i] += OFFSET;

		for (int j = x1[i] + 1; j <= x2[i]; j++)
		{
			zeroone[i][j] = 1;
		}
	}

	
	for (int i = 0; i < n; i++)
	{
		for (int j = i+1; j < n; j++)
		{

			for (int k = 0; k < 2 * OFFSET + 1; k++)
			{
				Func(i, j, k);
			}
		}
	}
	cout << cnt;

	return 0;
}