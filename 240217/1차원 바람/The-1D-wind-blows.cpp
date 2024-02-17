#include <iostream>
#include <algorithm>
/* 큰 모듈 그리고 세부 구현 */
#define MAX_ARR 100
using namespace std;

int n, m, q;
int arr[MAX_ARR][MAX_ARR];
int r[MAX_ARR];
char d[MAX_ARR]; /* 자료형 주의!*/

char Wind_Reverse(char d)
{
	char rev = 'L';
	if (d == 'L')
	{
		rev = 'R';
	}
	else
	{
		if (d == 'R')
		{
			rev = 'L';
		}
	}
	return rev;
}

void Left_Shift(int r)
{ /* 12345 23451*/
	int temp = arr[r][0];

	for (int i = 1; i <= m - 1; i++)
	{
		arr[r][i - 1] = arr[r][i];
	}
	arr[r][m - 1] = temp;
	return;
}

void Right_Shift(int r)
{/* 12345 51234*/
	int temp = arr[r][m - 1];

	for (int i = m - 1; i > 0; i--)
	{
		arr[r][i] = arr[r][i - 1];
	}
	arr[r][0] = temp;

	return;
}

void Wind_Shift(int r, char d)
{
	if (d == 'L')
	{
		Right_Shift(r);
	}
	else
	{
		if (d == 'R')
		{
			Left_Shift(r);
		}
	}
	return;
}

int Up_Row_Col_Ck(int r)
{
	/* r, r-1  duple compare */
	for (int i = 0; i < m; i++)
	{
		if (arr[r][i] == arr[r - 1][i])
		{
			return 1;
		}
	}
	return 0; /* no jungbok */
}

int Dn_Row_Col_Ck(int r)
{
	for (int i = 0; i < m; i++)
	{
		if (arr[r][i] == arr[r + 1][i])
		{
			return 1;
		}
	}
	return 0; /* no jungbok */
}

void Wind_Up(int r, char d)
{
	Wind_Shift(r, d);
	/* 위의 행들만 쭉 체크하는 것으로 한정!*/
	int up_duple = 0;
	if (r - 1 >= 0) /* 위의 행을 체크할 수 있으면 */
	{
		up_duple = Up_Row_Col_Ck(r);
		if (up_duple == 1) /* 위의 행의 열의 요소에 중복이 있다 */
		{
			char rev;
			rev = Wind_Reverse(d);
			Wind_Up(r - 1, rev); /* 윗줄에서 반대로 전파*/
		}
	}
	if (up_duple == 0)
	{
		return;
	}
}

void Wind_Down(int r, char d)
{
	Wind_Shift(r, d);
	/* 아래의 행들만 쭉 체크하는 것으로 한정!*/
	int dn_duple = 0;
	if (r + 1 < n)
	{
		dn_duple = Dn_Row_Col_Ck(r);
		if (dn_duple == 1)
		{
			char rev;
			rev = Wind_Reverse(d);
			Wind_Down(r + 1, rev); /* 아랫줄에서 반대로 전파*/
		}
	}
	if (dn_duple == 0)
	{
		return;
	}
}
void Wind_Junpa(int r, char d) /* 0행부터 N-1행까지 들어온다. */
{
	Wind_Shift(r, d); /* 해당 행의 바람을 전파*/

	int up_duple = 0; /* 윗줄의 col에는 중복 없다는 것을 default, if 윗줄 인덱스 초과아니어도 중복이 없거나, 윗 줄이 인덱스 초과일 때 */
	int dn_duple = 0;
	if ( r-1>=0 ) /* 위의 행을 체크할 수 있으면 */
	{	
		up_duple = Up_Row_Col_Ck(r);
		if (up_duple == 1) /* 위의 행의 열의 요소에 중복이 있다 */
		{
			char rev;
			rev = Wind_Reverse(d);
			Wind_Up(r-1, rev); /* 윗줄에서 반대로 전파*/
		}
	}
	/*Idx of uprow_col and dnrow_col check need*/
	/*check PASS, Wind Call */

	if ( r+1 <n )
	{
		dn_duple = Dn_Row_Col_Ck(r);
		if (dn_duple == 1)
		{
			char rev;
			rev = Wind_Reverse(d);
			Wind_Down(r+1, rev); /* 아랫줄에서 반대로 전파*/
		}
	}
	if ((up_duple==0) && (dn_duple==0))
	{
		return;
	}
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
			cin>>arr[i][j];
		}
	}

	for (int i = 0; i < q; i++)
	{
		cin >> r[i] >> d[i];
	}


	for (int i = 0; i < q; i++)
	{
		Wind_Junpa(r[i]-1, d[i]);
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cout << arr[i][j]<<" ";
		}
		cout << "\n";
	}

	return 0;
}