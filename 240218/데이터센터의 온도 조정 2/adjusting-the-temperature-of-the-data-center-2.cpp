#include <iostream>
#include <algorithm>

using namespace std;

int n, c, g, h;
int ta[1000] = { 0,0 };
int tb[1000] = { 0,0 };

int main()
{
	cin.tie(0);
	ios::sync_with_stdio(0);

	cin >> n >> c >> g >> h;
	
	int min_degree = 1001;
	int max_degree = 0;
	for (int i = 0; i < n; i++)
	{
		cin >> ta[i] >> tb[i];
		min_degree = min(ta[i], tb[i]);
		max_degree = max(ta[i], tb[i]);
	}

	int simul_one = 0;
	int simul_two = 0;
	int simul_three = 0;

	int max_sum = 0;
	for (int degree = min_degree - 1; degree <= max_degree + 1; degree++)
	{
		int sum = 0;
		for (int i = 0; i < n; i++) // 특정 degree에 대해서 장비 1~N까지 다 돌려서 max 구해보기 이게 핵심 
		{ // 그러니까 1대 n을 N번(장비 개수만큼 하기)
			if (degree < ta[i])
			{
				/*sum += Simul_Func1(degree, ta[i], tb[i]); */
				sum += c;
			}
			if ((degree >=ta[i]) && (degree<=tb[i]))
			{
				sum += g;
			}
			if (degree > tb[i])
			{
				sum += h;
			}
		}
		max_sum = max(sum, max_sum);
	}
	cout << max_sum;

	return 0;
}