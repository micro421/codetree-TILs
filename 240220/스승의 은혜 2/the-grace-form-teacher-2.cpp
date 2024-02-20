#include <iostream>
#include <algorithm>

#define ARR_MAX 1000
using namespace std;
int n, b;
int p[ARR_MAX] = { 0,0 };

int main() {

	cin.tie(0);
	ios::sync_with_stdio(0);

	cin >> n >> b;

	for (int i = 0; i < n; i++)
	{
		cin >> p[i];
	}

	sort(p, p + n);
	int max_cnt = 0;
	for (int i = 0; i < n; i++) /* i는 할인 쿠폰 쓰는 친구의 인덱스 */
	{
		int sum = 0;
		int cnt = 0;
		p[i] = p[i] / 2;
		for (int j = 0; j < n; j++) /* j는 전체를 순회하는데, j==i면 그 친구 할인 쿠폰 적용이얌*/
		{
			if (sum + p[j] > b)
			{
				continue;
			}
			if (sum + p[j] <= b)
			{
				sum += p[j];
				cnt++;
			}
			/*원상 복구 로직 여기서
			if(j==i){p[i] = 2 * p[i];} 하면,
			할인 쿠폰 적용 계속 안 됨*/
		}
		/*다시 원상 복구!*/
		p[i] = 2 * p[i];
		max_cnt = max(max_cnt, cnt); /* 할인 쿠폰 쓰는 친구의 인덱스인 i가 변하기 전에 max_cnt 갱신! */
	}

	std::cout << max_cnt;
	return 0;
}