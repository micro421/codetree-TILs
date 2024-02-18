#include <iostream>
#include <algorithm>

using namespace std;

int x, y;

int Notation(int num)
{
	int sum = 0;
	int arr[7] = { 0, 0 };

	arr[0] = num / 10000; /* 10000 1000 이런 식으로 줄어드는 거는 t로 해서 일반화?!*/
	num = num % 10000;
	arr[1] = num / 1000;
	num = num % 1000;
	arr[2] = num / 100;
	num = num % 100;
	arr[3] = num / 10;
	num = num % 10;
	arr[4] = num / 1;
	num = num % 1;

	for (int i = 0; i < 5; i++)
	{
		if (arr[i] > 0)
		{
			sum += arr[i];
		}
	}
	return sum;
}
int main()
{
	int max_res = 0;
	cin.tie(0);
	ios::sync_with_stdio(0);

	cin >> x >> y;

	int res = 0;
	for (int i = x; i <= y; i++)
	{
		res = Notation(i);
		max_res = max(max_res, res);
	}

	cout << max_res;
	return 0;
}