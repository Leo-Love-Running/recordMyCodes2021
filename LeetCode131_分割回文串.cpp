#include<iostream>
#include<string>
#include<vector>
using namespace std;

class Solution {
private:
    vector<vector<int>> f;
    vector<vector<string>> ret;
    vector<string> ans;       //
    int n;      //n是字符串长度

public:
    void dfs(const string& s, int i) {
        if (i == n) {
            ret.push_back(ans);
            return;
        }
        ///深搜加回溯
        for (int j = i; j < n; ++j) {
            if (f[i][j]) {
                ans.push_back(s.substr(i, j - i + 1));
                dfs(s, j + 1);
                ans.pop_back();
            }
        }
    }

    vector<vector<string>> partition(string s) {
        n = s.size();
        //将f全部赋值为1，f有点像是ret的键
        f.assign(n, vector<int>(n, true));

        ///i是开头的下标，j是i后面的子串末尾的下标
        for (int i = n - 1; i >= 0; --i) {
            for (int j = i + 1; j < n; ++j) {
                ///动态规划
                ///如果字符串第i位和第j位相同，且它们分别相邻的一位也相同，那么f[i][j]=1
                f[i][j] = (s[i] == s[j]) && f[i + 1][j - 1];
            }
        }
        dfs(s, 0);
        return ret;
    }
};

int main(){
    string s;
    cin>>s;
    Solution sol;
    vector<vector<string>> res=sol.partition(s);
    for(auto i:res){
        for(auto ans:i){
            cout<<ans<<" ";
        }
        cout<<endl;
    }
    return 0;
}