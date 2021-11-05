#include<iostream>
#include<vector>
#include<queue>
#include<unordered_map>
using namespace std;

class Solution {
public:
    /** 字典wordId 给每个单词分配一个id，相当于一个微型数据库，在图中数字更好操作，所以这里的目的是建立从字符串到数字的映射关系 */
    unordered_map<string, int> wordId;
    /**
     //图的实现。edge[0]的列表表示id为0的字符串连通向哪些id
    //建图的时候如果直接对比两个字符串是否只相差一个字符，需要O(n^2)复杂度，所以采用一种优化建图的思路：利用中间状态
    //比如单词hit，我们让它指向"*it","h*t","hi*"三个模糊状态，同时让这三个模糊状态指向hit：hit-h*t,hit-*it,hit-hi*
    //这样在BFS时，从每个真正的单词发散出去的都是它的模糊状态，而从模糊状态一定可以得到其它可以一步变成它的单词
    //这样做有两个地方需要注意：一是步数其实是两倍，因为多遍历了一倍的模糊态。
    //二是从单词A到模糊态a后，模糊态a可以再发散到单词A(A在a通向的id列表中)，因此要跳过已经遍历过的单词
     */
    vector<vector<int>> edge;
    /** nodeNum就是编号 */
    int nodeNum = 0;

    /** 如果字典wordId里面没有该字符串，则把该字符串加进去
        添加一个词到nodeNum映射容器wordId中，同时为这个nodeNum添加一个空的边集合（不指向任何id)
    */
    void addWord(string& word) {
        if (!wordId.count(word)) {
            wordId[word] = nodeNum++;
            /** 加入了一个空的vector<int>数组!
             edges的索引跟id同步增加，所以一直是匹配的
            */
            edge.emplace_back();
        }
    }

    /** 添加一个单词到id映射中，并建立它和模糊态的双向连接关系 */
    void addEdge(string& word) {
        addWord(word);
        /** 先取word对应的int值给id1 */
        /** id1是特定单词的编号，id2是模糊态的编号 */
        int id1 = wordId[word];
        /** 遍历word的每一个字符 */
        for (char& it : word) {
            char tmp = it;
            it = '*';
            addWord(word);
            int id2 = wordId[word];
            //建立单词和模糊态的双向连接关系
            edge[id1].push_back(id2);
            edge[id2].push_back(id1);
            //将模糊态恢复成原单词
            it = tmp;
        }
    }

    /** 开始BFS */
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        /** 遍历输入的数组里面的字符串 */
        for (string& word : wordList) {
            addEdge(word);
        }

        addEdge(beginWord);
        if (!wordId.count(endWord)) {
            return 0;
        }

        //这里不能用一个step变量记录当前经历了几步，因为遍历是按具体单词 -> 模糊态 ->具体单词这样的层级，
        //在从模糊态到具体单词时，有可能遍历到上一层已遍历过的单词。
        /**所以用一个数组记录从起始态到某个单词经历了多少次变动*/
        //nodeNum是一个计数器，这里nodeNum刚好是算上模糊态的所有词总数
        /**由于一共只有nodeNum个词，步数不可能大于nodeNum*/
        vector<int> dis(nodeNum, INT_MAX);
        int beginId = wordId[beginWord], endId = wordId[endWord];
        //说明是访问过了begin的单词
        dis[beginId] = 0;

        queue<int> que;
        que.push(beginId);//从beginWord这个状态开始，向下逐层BFS

        while (!que.empty()) {
            int x = que.front();
            que.pop();
            if (x == endId) {
                //除以2的原因是多遍历一倍的模糊态层数，
                /** +1是因为题意要求转换序列的长度，而不是转换次数 */
                //所以转换次数显然不用加1
                return dis[endId] / 2 + 1;
            }
            //遍历当前单词nodeNum连接到的每个状态
            //遍历特定word对应序号的边数组
            /** 本质上是一层一层遍历，每一层的编号dis[xxx]是一样的 */
            for (int& it : edge[x]) {
                if (dis[it] == INT_MAX) {//是没遍历过的状态
                    //dis[it]是对应模糊态的word
                    dis[it] = dis[x] + 1;
                    que.push(it);
                }
            }
        }
        return 0;
    }
};

int main(){
    string beginWord;
    string endWord;
    string tmp;
    vector<string> wordList;
    cin >> beginWord >> endWord;
    while (cin >> tmp) {
        wordList.emplace_back(tmp);
    }
    Solution sol;
    int ans = sol.ladderLength(beginWord, endWord, wordList);
    cout << ans << endl;
    return 0;
}
