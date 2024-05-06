#include <iostream>
#define BLANK 0
using namespace std;

int n;
int s1,e1,s2,e2;
int grid[100]={0,0};


int Func(int s, int e, int length)
{
    int next_grid[100] = {0,0};
    for(int i=s; i<=e; i++)
    {
        grid[i] = BLANK;
    }

    int end_of_temp_array = 0;
    for(int i=0; i<length; i++)
    {
        if(grid[i]) {
            next_grid[end_of_temp_array] = grid[i];
            end_of_temp_array++;
        }
    }

    for(int i=0; i<end_of_temp_array; i++) {
        grid[i] = next_grid[i];

    }

    return end_of_temp_array;
}

int main() {

    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    for(int i=0; i<n; i++)
    {
        cin>>grid[i];
    }
    cin>>s1>>e1;
    cin>>s2>>e2;
    int length1 = Func(s1-1,e1-1,n);
   int length2 = Func(s2-1, e2-1, length1);
    cout<<length2;
    if(length2>=1)
        cout<<"\n";
    if(length2>=1) {
        for (int i = 0; i < length2; i++) {
            cout << grid[i];
            if (i != length2 - 1)
                cout << "\n";
        }
    }

    return 0;
}