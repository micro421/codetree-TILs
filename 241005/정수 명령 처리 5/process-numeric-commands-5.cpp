#include <iostream>
#include <vector>
#include <string>
using namespace std;

int n;
vector<int> v;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        string s;
        int num;
        cin>>s;
        if(s=="push_back")
        {
            cin>>num;
            v.push_back(num);
        }
        else if(s=="get")
        {
            cin >> num;
            cout<<v[num-1]<<"\n";
        }
        else if(s=="pop_back")
        {
            v.pop_back();
        }
        else
        {
            if(s=="size")
            {
                cout<<v.size()<<"\n";
            }
        }
    }
    return 0;
}