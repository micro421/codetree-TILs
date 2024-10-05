#include <iostream>
#include <list>
#include <string>

using namespace std;

int n;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    list<int> s;
    cin>>n;

    for(int i=0; i<n; i++)
    {
        string str;
        int num;
        cin>>str;
        if(str == "push_front")
        {
            cin>>num;
            s.push_front(num);
        }
        else if(str == "push_back")
        {
            cin>>num;
            s.push_back(num);
        }
        else if(str == "pop_front")
        {
            cout<<s.front()<<"\n";
            s.pop_front();
        }
        else if( str == "pop_back")
        {
            cout<<s.back()<<"\n";
            s.pop_back();
        }
        else if( str == "size")
        {
            cout<<s.size()<<"\n";
        }
        else if(str == "empty")
        {
            if(s.empty())
            {
                cout<<"1\n";
            }
            else
            {
                cout<<"0\n";
            }
        }
        else if(str == "front")
        {
            cout<<s.front()<<"\n";
        }
        else
        {
            cout<<s.back()<<"\n";
        }
    }

    return 0;
}