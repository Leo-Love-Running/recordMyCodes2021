#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<unordered_map>
using namespace std;

class solution {
public:
	unordered_map<string, int> wordID;
	vector<vector<int>>  edge;
	int nodenum = 0;

	void addWord(string& word) {
		if (!wordID.count(word)) {
			wordID[word] = nodenum++;
			edge.emplace_back();
		}
	}

	void addEdge(string& word) {
		addWord(word);
		int id1 = wordID[word];
		for (char& it : word) {
			char tmp = it;
			it = '*';
			addWord(word);
			int id2 = wordID[word];
			edge[id1].emplace_back(id2);
			edge[id2].emplace_back(id1);
			it = tmp;
		}
	}

	int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
		for (string& word : wordList) {
			addEdge(word);
		}
		addEdge(beginWord);
		if (!wordID.count(endWord)) {
			return 0;
		}
		vector<int> dis(nodenum, INT_MAX);
		int beginID = wordID[beginWord], endID = wordID[endWord];
		dis[beginID] = 0;

		queue<int> que;
		que.emplace(beginID);

		while (!que.empty()) {
			int x = que.front();
			que.pop();
			if (x == endID) {
				return dis[endID] / 2 + 1;
			}
			for (int& it : edge[x]) {
				if (dis[it] == INT_MAX) {
					dis[it] = dis[x] + 1;
					que.emplace(it);
				}
			}
		}
		return 0;
	}
};

int main() {
	string beginWord;
	string endWord;
	string tmp;
	vector<string> wordList;
	cin >> beginWord >> endWord;
	while (cin >> tmp) {
		wordList.emplace_back(tmp);
	}
	solution sol;
	int ans = sol.ladderLength(beginWord, endWord, wordList);
	cout << ans << endl;
	return 0;
}