#include<iostream>
#include<string>
#include<queue>
#include<algorithm>
using namespace std;

class Node{
public:
    char data;
    Node* left;
    Node* right;
    Node(char ch){
        data=ch;
        left=nullptr;
        right=nullptr;
    }
    void setLeft(Node* left){
        this->left=left;
    }
    void setRight(Node* right){
        this->right=right;
    }
};

class Tree{
    Node* root;
    int pos;
    string strTree;
public:
    void create(string s){
        pos=0;
        strTree=s;
        root=createTree();
    }
    Node* createTree(){
        Node* t;
        char ch=strTree.at(pos++);
        if(ch=='0'){
            t=nullptr;
        }else{
            t=new Node(ch);
            t->setLeft(createTree());
            t->setRight(createTree());
        }
        return t;
    }
    void levelOrderShow(){
        levelOrder(root);
    }
    void levelOrder(Node* t){
        queue<Node*> q;
        q.emplace(t);
        while(!q.empty()){
            Node* node=q.front();
            q.pop();
            if(node->left!=nullptr){
                q.emplace(node->left);
            }
            if(node->right!=nullptr){
                q.emplace(node->right);
            }
            cout<<node->data;
        }
    }
};

class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(Node* root) {
        vector<vector<int>> res;
        if(!root)
            return res;
        vector<int> level;
        queue<Node*> q;
        q.emplace(root);
        Node* board=new Node(0);
        q.emplace(board);
        int flg=0;
        while(!q.empty()){
            Node* tmp=q.front();
            q.pop();
            if(tmp==board){
                if(flg){
                    vector<int>::iterator start=level.begin();
                    vector<int>::iterator endd=level.end();
                    reverse(start,endd);
                    flg=0;
                }else{
                    flg=1;
                }
                res.emplace_back(level);
                level.clear();
                if(!q.empty())
                    q.emplace(board);
            }else{
                level.emplace_back(tmp->data);
                if(tmp->left!=nullptr){
                    q.emplace(tmp->left);
                }
                if(tmp->right!=nullptr){
                    q.emplace(tmp->right);
                }
            }
        }
        return res;
    }
};

int main(){
    int t;
    cin>>t;
    while(t--){
        string s;
        cin>>s;
        Tree* tree=new Tree();
        tree->create(s);
        tree->levelOrderShow();
        cout<<endl;
    }
    return 0;
}