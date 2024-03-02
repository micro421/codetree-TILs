#include <iostream>
#include <algorithm>
#include <tuple>
#define MAX_SIZE 100
using namespace std;
int max_num = 0;
int n, r, c;
int move_flag = 0;
int curr_x, curr_y;
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0,0,-1 ,1 };
int grid[MAX_SIZE][MAX_SIZE];
bool InRange(int x, int y)
{
	return 0<=x && x<n && 0<=y && y<n;
}

void Simul(void)
{
	pair<int, int> max_pos;
	int for_flag = 0; /* 좌표 A에 대해서 그것의 상하좌우를 돌아서 여기서 초기화!*/
	int prev_x = curr_x;
	int prev_y = curr_y;
	for (int i = 0; i < 4; i++)
	{
		int next_x = curr_x + dx[i];
		int next_y = curr_y + dy[i];
		
		if (InRange(next_x, next_y) && grid[next_x][next_y] > max_num && (for_flag == 0))
		{
			max_num = grid[next_x][next_y];
			max_pos = make_pair(next_x, next_y);
			tie(curr_x, curr_y) = max_pos;
			for_flag = 1;
			cout << max_num << " ";
		}

	}
	

	if(( curr_x == prev_x ) && (curr_y == prev_y))
	{
		move_flag = 1;
	}
	return;
}
int main()
{
	cin.tie(0);
	ios::sync_with_stdio(0);

	cin >> n>>r>>c;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> grid[i][j];
		}
	}

	curr_x = r-1;
	curr_y = c - 1;
	max_num = grid[curr_x][curr_y];
	cout << grid[curr_x][curr_y]<<" ";

	while (move_flag != 1)
	{
		Simul();
	}

	return 0;
}