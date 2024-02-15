#include <iostream>
#include <algorithm>

#define ARR_MAX 200
using namespace std;

int n; /* arr size */
int t;
int up_arr[ARR_MAX] = { 0, 0 };
int mid_arr[ARR_MAX] = { 0,0 };
int dn_arr[ARR_MAX] = { 0,0 };

void Rotate(void)
{
	int temp_1_to_2 = up_arr[n - 1];
	int temp_2_to_3 = mid_arr[n - 1];
	int temp_3_to_1 = dn_arr[0];
	/* temp가 찍힌 자리부터 채워주는게 의미 있따*/
	for (int i = n - 1; i >= 1; i--)
	{
		up_arr[i] = up_arr[i - 1];
		mid_arr[i] = mid_arr[i - 1];
	}
	for (int i = 1; i <= n - 1; i++)
	{
		dn_arr[i - 1] = dn_arr[i];
	}
	
	mid_arr[0] = temp_1_to_2;
	dn_arr[n - 1] = temp_2_to_3;
	up_arr[0] = temp_3_to_1;
	return;
}
int main(void)
{
	cin.tie(0);
	ios::sync_with_stdio(0);
	cin >> n >> t;
	for (int i = 0; i < n; i++)
	{
		cin >> up_arr[i];
	}
	for (int i = 0; i < n; i++)
	{
		cin >> mid_arr[i];
	}
	for (int i = n - 1; i >= 0; i--)
	{
		cin >> dn_arr[i];
	}

	for( int i=0; i<t; i++)
	{	Rotate();
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
	for (int i = 0; i < n; i++)
	{
		cout << mid_arr[i];
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