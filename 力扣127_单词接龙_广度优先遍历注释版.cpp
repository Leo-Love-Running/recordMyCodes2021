#include<iostream>
#include<vector>
#include<queue>
#include<unordered_map>
using namespace std;

class Solution {
public:
    /** �ֵ�wordId ��ÿ�����ʷ���һ��id���൱��һ��΢�����ݿ⣬��ͼ�����ָ��ò��������������Ŀ���ǽ������ַ��������ֵ�ӳ���ϵ */
    unordered_map<string, int> wordId;
    /**
     //ͼ��ʵ�֡�edge[0]���б��ʾidΪ0���ַ�����ͨ����Щid
    //��ͼ��ʱ�����ֱ�ӶԱ������ַ����Ƿ�ֻ���һ���ַ�����ҪO(n^2)���Ӷȣ����Բ���һ���Ż���ͼ��˼·�������м�״̬
    //���絥��hit����������ָ��"*it","h*t","hi*"����ģ��״̬��ͬʱ��������ģ��״ָ̬��hit��hit-h*t,hit-*it,hit-hi*
    //������BFSʱ����ÿ�������ĵ��ʷ�ɢ��ȥ�Ķ�������ģ��״̬������ģ��״̬һ�����Եõ���������һ��������ĵ���
    //�������������ط���Ҫע�⣺һ�ǲ�����ʵ����������Ϊ�������һ����ģ��̬��
    //���Ǵӵ���A��ģ��̬a��ģ��̬a�����ٷ�ɢ������A(A��aͨ���id�б���)�����Ҫ�����Ѿ��������ĵ���
     */
    vector<vector<int>> edge;
    /** nodeNum���Ǳ�� */
    int nodeNum = 0;

    /** ����ֵ�wordId����û�и��ַ�������Ѹ��ַ����ӽ�ȥ
        ���һ���ʵ�nodeNumӳ������wordId�У�ͬʱΪ���nodeNum���һ���յı߼��ϣ���ָ���κ�id)
    */
    void addWord(string& word) {
        if (!wordId.count(word)) {
            wordId[word] = nodeNum++;
            /** ������һ���յ�vector<int>����!
             edges��������idͬ�����ӣ�����һֱ��ƥ���
            */
            edge.emplace_back();
        }
    }

    /** ���һ�����ʵ�idӳ���У�����������ģ��̬��˫�����ӹ�ϵ */
    void addEdge(string& word) {
        addWord(word);
        /** ��ȡword��Ӧ��intֵ��id1 */
        /** id1���ض����ʵı�ţ�id2��ģ��̬�ı�� */
        int id1 = wordId[word];
        /** ����word��ÿһ���ַ� */
        for (char& it : word) {
            char tmp = it;
            it = '*';
            addWord(word);
            int id2 = wordId[word];
            //�������ʺ�ģ��̬��˫�����ӹ�ϵ
            edge[id1].push_back(id2);
            edge[id2].push_back(id1);
            //��ģ��̬�ָ���ԭ����
            it = tmp;
        }
    }

    /** ��ʼBFS */
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        /** �������������������ַ��� */
        for (string& word : wordList) {
            addEdge(word);
        }

        addEdge(beginWord);
        if (!wordId.count(endWord)) {
            return 0;
        }

        //���ﲻ����һ��step������¼��ǰ�����˼�������Ϊ�����ǰ����嵥�� -> ģ��̬ ->���嵥�������Ĳ㼶��
        //�ڴ�ģ��̬�����嵥��ʱ���п��ܱ�������һ���ѱ������ĵ��ʡ�
        /**������һ�������¼����ʼ̬��ĳ�����ʾ����˶��ٴα䶯*/
        //nodeNum��һ��������������nodeNum�պ�������ģ��̬�����д�����
        /**����һ��ֻ��nodeNum���ʣ����������ܴ���nodeNum*/
        vector<int> dis(nodeNum, INT_MAX);
        int beginId = wordId[beginWord], endId = wordId[endWord];
        //˵���Ƿ��ʹ���begin�ĵ���
        dis[beginId] = 0;

        queue<int> que;
        que.push(beginId);//��beginWord���״̬��ʼ���������BFS

        while (!que.empty()) {
            int x = que.front();
            que.pop();
            if (x == endId) {
                //����2��ԭ���Ƕ����һ����ģ��̬������
                /** +1����Ϊ����Ҫ��ת�����еĳ��ȣ�������ת������ */
                //����ת��������Ȼ���ü�1
                return dis[endId] / 2 + 1;
            }
            //������ǰ����nodeNum���ӵ���ÿ��״̬
            //�����ض�word��Ӧ��ŵı�����
            /** ��������һ��һ�������ÿһ��ı��dis[xxx]��һ���� */
            for (int& it : edge[x]) {
                if (dis[it] == INT_MAX) {//��û��������״̬
                    //dis[it]�Ƕ�Ӧģ��̬��word
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
