#include <iostream>
#include <algorithm>
#define BLANK 0
int arr[100] = { 0, 0 };
int temp[100] = { 0,0 };
int end_of_array = 0;
int end_of_temp_array = 0;

int se[100][2] = { 0,0 };
using namespace std;

void Make_Zero(int a, int b)
{
		for (int j = a; j <= b; j++)
		{
			arr[j] = 0;
		}
	
	return;
}

void Push_Temp(int end_of_array )
{
	end_of_temp_array = 0;
	for (int i = 0; i < end_of_array; i++)
	{
		if (arr[i] != BLANK)
		{
			temp[end_of_temp_array] = arr[i];
			end_of_temp_array++;
		}
	}
	return;
}

void Copy_Array(int end_of_temp_array)
{
	for (int i = 0; i < end_of_temp_array; i++)
	{
		arr[i] = temp[i];
	}

	return;
}

void Temp_To_Zero(void)
{
	for (int i = 0; i < end_of_array; i++)
	{
		temp[i] = 0;
	}
}

int main()
{
	cin.tie(0);
	ios::sync_with_stdio(0);

	int n;
	cin >> n;
	end_of_array = n;

	for (int i = 0; i < n; i++)
	{
		cin >> arr[i];
	}
	for (int i = 0; i < 2; i++)
	{
		Temp_To_Zero();
		cin >> se[i][0] >> se[i][1];
		Make_Zero(se[i][0]-1, se[i][1]-1);
		Push_Temp(end_of_array);
		Copy_Array(end_of_temp_array);
		end_of_array = end_of_temp_array;
	}
	cout << end_of_array<<"\n";
	if (end_of_array != 0)
	{
		for (int i = 0; i < end_of_array; i++)
		{
			cout << arr[i] << "\n";
		}
	}

	return 0;
}