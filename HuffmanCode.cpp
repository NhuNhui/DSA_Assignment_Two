#include<bits/stdc++.h>
using namespace std;

struct MinHeap {
    char data;
    int freq;
    MinHeap* left;
    MinHeap* right;
    MinHeap(char data, int freq) {
        left = right = NULL;
        this->data = data;
        this->freq = freq;
    }
};

struct comp {
    bool operator()(MinHeap *left, MinHeap *right) {
        return (left->freq > right->freq);
    }
};

void getHuffManCode(MinHeap *root,string str,vector<pair<char,string>> &code) {
    if(root == NULL)    
        return;
    if(root->data != '$') {
        code.push_back({root->data,str});
    }
    
    getHuffManCode(root->left,str + "0",code);
    getHuffManCode(root->right,str + "1",code);
    
}

vector<pair<char,string>> HuffManCode(map<char,int> mp) {
    MinHeap *left, *right, *top;
    priority_queue<MinHeap*,vector<MinHeap*>,comp> min_Heap;
    for(auto it = mp.begin();it!=mp.end();it++) {
        min_Heap.push(new MinHeap(it->first,it->second));
    }
    while(min_Heap.size() != 1) {
        left = min_Heap.top();
        min_Heap.pop();
        right = min_Heap.top();
        min_Heap.pop();
        top = new MinHeap('$',left->freq + right->freq);
        top->left = left;
        top->right = right;
        min_Heap.push(top);
    }
    vector<pair<char,string>> ans;
    getHuffManCode(min_Heap.top(),"",ans);
    return ans;
}

int main() {
    string str = "Johnuigfifbahjasbdfhjbasdhjf";
    
    map<char,int> mp;
    for(int i=0;str[i]!='\0';i++) {
        mp[str[i]]++;
    } 
    
    
    vector<pair<char,string>> s = HuffManCode(mp);
    for(int i=0;i<s.size();i++) {
        cout<<s[i].first<<" | "<<s[i].second<<endl;;
    }
    return 0;
}