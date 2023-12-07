#include <iostream>
#include <algorithm>

using namespace std;

int n;
int ans = 2000000;
int segments[100][2] = {};

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    cin>>n;
    for(int x=0; x<n; x++) {
        cin >> segments[x][0]>>segments[x][1];
    }

    for(int i=0; i<n; i++)
    {
        for(int j=i+1; j<n; j++)
        {
            int x1 = segments[i][0], y1 = segments[i][1];
            int x2 = segments[j][0], y2 = segments[j][1];

            int res =(x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
            ans = min(res, ans);

        }
    }
    cout<<ans;
        return 0;
}