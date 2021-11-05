#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<unordered_set>
#include<unordered_map>
#include<queue>
using namespace std;

class Solution {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string> &wordList) {
        vector<vector<string>> res;
        // 因为需要快速判断扩展出的单词是否在 wordList 里，因此需要将 wordList 存入哈希表，这里命名为「字典」
        /** dict里面存的就是vector里面的字符串 */
        unordered_set<string> dict = {wordList.begin(), wordList.end()};
        // 修改以后看一下，如果根本就不在 dict 里面，跳过
        /** set的find函数如果找不到目标则返回end */
        if (dict.find(endWord) == dict.end()) {
            return res;
        }

        // 特殊用例处理，删除指定元素
        dict.erase(beginWord);

        //第 1 步：广度优先遍历建图
        //记录扩展出的单词是在第几次扩展的时候得到的，key：单词，value：在广度优先遍历的第几层
        /** 为什么要加两个大括号呢？map的形式是这样子的：{{}，{}，{}，{}} */
        unordered_map<string, int> steps = {{beginWord, 0}};
        //记录了单词是从哪些单词扩展而来，key：单词，value：单词列表，这些单词可以变换到 key ，它们是一对多关系
        unordered_map<string, set<string>> from = {{beginWord, {}}};
        //step是层数
        int step = 0;
        bool found = false;

        /** q的初始化就先放一个beginWord进去 */
        queue<string> q = queue<string>{{beginWord}};
        int wordLen = beginWord.length();

        while (!q.empty()) {
            step++;
            int size = q.size();
            for (int i = 0; i < size; i++) {
                /** 等价于 string currWord = q.front(); */
                //那加上move是为了什么呢
                //std::move并不能移动任何东西，它唯一的功能是将一个左值强制转化为右值引用，继而可以通过右值引用使用该值，
                //以用于移动语义。从实现上讲，std::move基本等同于一个类型转换：static_cast<T&&>(lvalue);
                //std::move是为性能而生。
                //std::move是将对象的状态或者所有权从一个对象转移到另一个对象，只是转移，没有内存的搬迁或者内存拷贝。
                const string currWord = move(q.front());
                string nextWord = currWord;
                q.pop();
                //将每一位替换成 26 个小写英文字母
                /** 注意注意，这里是每一位都要替换成26个小写的英文字母 */
                for (int j = 0; j < wordLen; ++j) {
                    /** 依次取字符串的每一个字母赋值给origin */
                    /** origin用于保存这个字母 */
                    const char origin = nextWord[j];
                    for (char c = 'a'; c <= 'z'; ++c) {
                        nextWord[j] = c;
                        if (steps[nextWord] == step) {
                            from[nextWord].insert(currWord);
                        }
                        if (dict.find(nextWord) == dict.end()) {
                            continue;
                        }
                        // 如果从一个单词扩展出来的单词以前遍历过，距离一定更远，为了避免搜索到已经遍历到，且距离更远的单词，需要将它从 dict 中删除
                        dict.erase(nextWord);
                        // 这一层扩展出的单词进入队列
                        q.push(nextWord);
                        // 记录 nextWord 从 currWord 而来
                        from[nextWord].insert(currWord);
                        // 记录 nextWord 的 step
                        steps[nextWord] = step;
                        if (nextWord == endWord) {
                            found = true;
                        }
                    }
                    nextWord[j] = origin;
                }
            }
            if (found) {
                break;
            }
        }
        // 第 2 步：深度优先遍历找到所有解，从 endWord 恢复到 beginWord ，所以每次尝试操作 path 列表的头部
        if (found) {
            /** 开个Path来记录路径 */
            vector<string> Path = {endWord};
            dfs(res, endWord, from, Path);
        }
        return res;
    }

    void dfs(vector<vector<string>> &res, const string &Node, unordered_map<string, set<string>> &from,
             vector<string> &path) {
        if (from[Node].empty()) {
            /** 首先res存入了一个数组，其次这里使用的是逆序迭代器 */
            res.push_back({path.rbegin(), path.rend()});
            return;
        }
        for (const string &Parent: from[Node]) {
            path.push_back(Parent);
            dfs(res, Parent, from, path);
            path.pop_back();
        }
    }
};

int main(){
    string beginWord;
    string endWord;
    string tmp;
    vector<string> wordList;
    cin >> beginWord >> endWord;
    while (1) {
        cin >> tmp;
        if(tmp=="Z")
            break;
        wordList.emplace_back(tmp);
    }
    Solution sol;
    vector<vector<string>> ans=sol.findLadders(beginWord,endWord,wordList);
    for(auto& vec:ans){
        for(auto ele:vec){
            cout<<ele<<" ";
        }
        cout<<endl;
    }
    return 0;
}