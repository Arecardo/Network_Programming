/*
先是上面那位老哥的分析：
提取出相同字符的位置，比如ababa中a的位置为（0，2，4），b的位置为（1，3）。对每个位置向量用动态规划求解。
字符a的位置数组为arr，动态规划过程：
dp(i,j)表示字符a第i个位置到第j个位置的字符要全部相邻，至少要用需要多少次交换。
1. i==j时，表示一个字符，不用交换，dp(i,j)为0；
2. i+1==j时，表示两个字符，位置相差arr[j]-arr[i]；
3.其他情况，dp(i,j) = dp(i+1,j-1) + arr[j]-arr[i] - (j - i)；
 
思路:
首先思考下第3种转移。因为[i+1,j-1]之间已经成了一个连续的段，所以左右两边都是往中间靠的，不管
怎么靠，交换的次数肯定都一样。然后就非常简单了
*/
#include<bits/stdc++.h>
using namespace std;
#define N 1005
int dp[N][N];//dp[i][j]表示第i个某种字符和相同的第j个字符成为一个连续段的花费
char str[2005];//我开了1005竟然说我越界,怀疑数据有问题
int main()
{
    int m, len, ans=1;
    scanf("%s %d", str, &m);
    len=strlen(str);
    for(int ch=0; ch<26; ch++)
    {
        int siz=0;
        vector<int> v;
        memset(dp, 63, sizeof(dp));
        for(int i=0; i<len; i++)
            if(str[i]==(ch+'a'))
            {
                v.push_back(i);
                siz++;
                dp[siz][siz]=0;
            }
        for(int i=siz-1; i>=0; i--)
        {
            for(int j=i+1; j<siz; j++)
            {
                int dis=v[j]-v[i]-(j-i);
                if(i+1!=j)
                    dis+=dp[i+1][j-1];
                dp[i][j]=min(dp[i][j], dis);
                if(dp[i][j]<=m) ans=max(ans, j-i+1);
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}