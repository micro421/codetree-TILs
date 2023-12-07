#include <iostream>
#include <algorithm>

using namespace std;
int n;
int ans = 0;
int segments[100][2]={};
int GetTri(int i1, int i2, int i3)
{
    int res = 0;
    int x1 = segments[i1][0];
    int y1 = segments[i1][1];
    int x2 = segments[i2][0];
    int y2 = segments[i2][1];
    int x3 = segments[i3][0];
    int y3 = segments[i3][1];

    res = abs((x1*y2+x2*y3+x3*y1) - (x2*y1+x3*y2+x1*y3));
    return res;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cin >> n;

    for(int x=0; x<n; x++) {
        cin>>segments[x][0]>>segments[x][1];
    }

    int result;
    for(int i=0; i<n; i++)
    {
        for(int j=i+1; j<n; j++)
        {
            for(int k=j+1; k<n; k++)
            {
               result = GetTri(i,j,k);
               ans = max(result, ans);
            }
        }
    }

    cout<<ans;
    return 0;
}