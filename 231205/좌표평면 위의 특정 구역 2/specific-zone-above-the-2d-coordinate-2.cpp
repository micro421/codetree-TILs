#include <iostream>
#include <algorithm>
/* https://dojang.io/mod/page/view.php?id=1969 */
using namespace std;

int n;
int xyarr[100][2] = {}; /* max 100, poin is x, y */

int minnubi = 1600000000;
int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
/* input */
    cin>>n;
    for(int t=0; t<n; t++)
    {
        cin >> xyarr[t][0] >> xyarr[t][1];
    }

    for(int i = 0; i< n; i++) /* jungbok index i */
    {
        int nubi = 0;
        int xmax=0, ymax = 0;
        int xmin=40000, ymin=40000;
        int counting[100] = {}; // initialize
        for(int j=0; j<n; j++)
        {
            if(i == j)
                continue;
            int x = xyarr[j][0];
            int y = xyarr[j][1];
            xmax = max(xmax, x);
            ymax = max(ymax, y);
            xmin = min(xmin, x);
            ymin = min(ymin, y);
        }
        nubi = (xmax-xmin)*(ymax-ymin);
        minnubi = min(nubi, minnubi);

    }
    cout<<minnubi;
    return 0;
}