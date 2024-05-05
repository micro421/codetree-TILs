#include <iostream>
#include <string>

using namespace std;
string str;
int str_len;

void DoRightShift()
{
    char temp = str[str_len-1];
    for(int i=str_len-1; i>=1; i--)
    {
        str[i] = str[i-1];
    }
    str[0] = temp;
}

/*int SeparateNum(int n)
{
    if(n<10)
        return n;

    return SeparateNum(n/10)+ SeparateNum(n%10);
}*/

int CalculateSame()
{
    int cnt = 1;
    int same_cnt=1;
    int encoding_len = 0;
    string temp;
   
    for(int i=1; i<str_len; i++)
    {
        if(str[i-1] == str[i])
        {
            cnt++;
        }
        else
        {
            same_cnt +=1;
            cnt = 1;
        }
    }

    if(cnt<10)
    {
        encoding_len = 2*same_cnt;
    }
    if(cnt == 10)
    {
        encoding_len = 3;
    }
    return encoding_len;

}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int cnt =0;
    cin>>str;

    str_len = str.length();

    int min_cnt = 26;
   for(int i=0; i< str_len; i++)
    {
        DoRightShift();
        cnt = CalculateSame();
        min_cnt = min(min_cnt, cnt);
    }
   cout<<min_cnt;

    return 0;
}