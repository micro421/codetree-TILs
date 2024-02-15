#include <iostream>
#include <algorithm>

#define ARR_MAX 200
using namespace std;

int n; /* arr size */
int t;
int up_arr[ARR_MAX] = {0, 0};
int dn_arr[ARR_MAX] = { 0,0 };

void Rotate_Once(void)
{
	int temp_up_dn = up_arr[n - 1];
	int temp_dn_up = dn_arr[0];
	\
	/* up array shift right*/
	for (int i=n-1; i>=1; i--)/* (int i = 1; i <= n - 1; i++) is wrong */
	{
		up_arr[i] = up_arr[i - 1];
	}
	/*dn array shift left */
	for (int i = 1; i <=n-1; i++)
	{
		dn_arr[i - 1] = dn_arr[i];
	}

	/* 다시 채우기 up-dn 오가며 */
	up_arr[0] = temp_dn_up;
	dn_arr[n-1] = temp_up_dn;
}
int main()
{
	cin.tie(0);
	ios::sync_with_stdio(0);
	cin >> n >> t;
	for (int i = 0; i < n; i++)
	{
		cin >> up_arr[i];
	}
	for (int i = n-1; i >=0; i--)
	{
		cin >> dn_arr[i];
	}
	/* 우측 이동, 좌측 이동 각각 하고 temp 저장 따로 해주고! */
	/*함수화*/
	/* for문으로 t만큼 돌린다. */
	for (int i = 0; i < t; i++)
	{
		Rotate_Once();
	}

	for (int i = 0; i < n; i++)
	{
		cout << up_arr[i];
		if (i != n - 1)
		{
			cout << " ";
		}
	}
	cout << "\n";
	for (int i = n - 1; i >= 0; i--)
	{
		cout << dn_arr[i];
		if (i != 0)
		{
			cout << " ";
		}
	}

	return 0;
}