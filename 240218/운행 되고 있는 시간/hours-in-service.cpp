#include <iostream>
#define ARR_MAX	100
using namespace std;

int n;

int segments[ARR_MAX][2] = {0,0};

int main()
{
	cin.tie(0);
	ios::sync_with_stdio(0);

	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> segments[i][0] >> segments[i][1]; /* a, b*/
	}

	int max_cnt = 0;
	for (int i = 0; i < n; i++) /* i가 늘 때 마다 0번째 멤버 제거 시나리오, 1번째 멤버 제거 시나리오, ... j번째 멤버 제거 시나리오!*/
	{
		int onservice[1000] = {0, 0 }; /* 서비스가 온 된 시간 */
		int cnt = 0;
		for (int j = 0; j < n; j++) /* 제거 대상은 j==i인 조건, 여기서는 제거 시나리오 #x번 진행 하나 한다.*/
		{
			if (j == i)
				continue; /* 1명씩 제외 */

			int a = segments[j][0], b = segments[j][1];
			for (int k = a; k < b; k++)
			{
				if (onservice[k] != 1)
				{
					onservice[k] = 1; /* 한 명이라도 일 하고 있으니 on_service 해준다.*/
					cnt++;
				}
			}
		}
		max_cnt = max(max_cnt, cnt);
	}

	cout << max_cnt;
	return 0;
}