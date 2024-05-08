#include<bits/stdc++.h>
using namespace std; 



class HuffmanNode{
private: 
    char c; 
    int freq; 
    int prior;  
    HuffmanNode *left, *right; 
public: 
    HuffmanNode(char c, int freq) {
        this->c = c; 
        this->freq = freq; 
        this->left = this->right = NULL;
        this->prior = 0;  
    }

    HuffmanNode(char c, int freq, int prior) {
        this->c = c; 
        this->freq = freq; 
        this->left = this->right = NULL;
        this->prior = prior;
    } 
    ~HuffmanNode() {
        this->c = '#'; 
        this->freq = 0; 
        this->prior = 0; 
        this->left = this->right = NULL; 
    }

    int getFreq() {
        return this->freq; 
    }
    char getChr() {
        return this->c; 
    }

    int getPriority() {
        return this->prior;
    }

    void setLeft(HuffmanNode *left) {
        this->left = left; 
    }
    void setRight(HuffmanNode *right) {
        this->right = right; 
    }
    HuffmanNode* getLeft() {
        return this->left; 
    }
    HuffmanNode* getRight() {
        return this->right; 
    }

    friend class compare; 
};

class compare {
public:
    bool operator() (HuffmanNode *left, HuffmanNode* right) 
    {
        if (left->getFreq() != right->getFreq()) {
            return (left->getFreq() > right->getFreq());
        } else {
            if (left->getChr() != right->getChr()) {
                if ((left->getChr() >= 65 && left->getChr() <= 122) 
                && (right->getChr() >= 65 && right->getChr() <= 122)) {
                    return (left->getChr() > right->getChr()); 
                } else {
                    return (left->getPriority() > right->getPriority());
                }
            } else {
                return (left->getPriority() > right->getPriority());  
            }
        }
    }
}; 

void getHuffMan(HuffmanNode *root, string s,string huffmanCode[256]) {
    if (root == NULL) {
        return; 
    }
    if (root->getChr() != '#') {
        huffmanCode[root->getChr()] = s; 
    }
    getHuffMan(root->getLeft(), s + "0",huffmanCode); 
    getHuffMan(root->getRight(), s + "1",huffmanCode); 
}

void buildHuffmanTree(unordered_map<char,int> huffman,string huffmanCode[256]) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, compare> huffmanTree;
    int i = 0;  
    for (unordered_map<char,int>::iterator it=huffman.begin();it!=huffman.end();it++) {
        huffmanTree.push(new HuffmanNode(it->first, it->second, 0));        
    }
    int prior = 1; 
    queue<HuffmanNode*> q;
    while (huffmanTree.size() != 1) {
        if (huffmanTree.size() == 0 ) {
            break; 
        }
        HuffmanNode *left = huffmanTree.top();
        huffmanTree.pop();  
        HuffmanNode *right = huffmanTree.top(); 
        huffmanTree.pop(); 
        HuffmanNode *top = new HuffmanNode('#', left->getFreq() + right->getFreq(), prior);
        top->setLeft(left); 
        top->setRight(right);  
        huffmanTree.push(top);
        prior++; 
    }
    
    getHuffMan(huffmanTree.top(), "",huffmanCode);
}

int Binary_to_Decimal(string str) {
    int ans = 0;
    for(int i = str.length() - 1;i>=0;i--) {
        ans = ans + pow(2,str.length() - i - 1)*int(str[i] - '0');
    }
    return ans;
}

int main() {
    string huffmanCode[256];
    for (int i = 0; i < 256; i++) {
        huffmanCode[i] = ""; 
    }
    string s = "Johnuigfifbahjasbdfhjbasdhjf"; 
    unordered_map<char,int> huffman;
    for(int i = 0;s[i] != '\0';i++) {
        huffman[s[i]]++;
    }
    buildHuffmanTree(huffman,huffmanCode); 
    
    string getHuffMan = ""; 
    for (int i = 0; i < s.length(); i++) {
        getHuffMan += huffmanCode[s[i]]; 
    }
    int n = getHuffMan.length();
    if(n > 15) {
        getHuffMan = getHuffMan.substr(n-15,n);
    }
    int result = Binary_to_Decimal(getHuffMan);
    cout << result;
    
}