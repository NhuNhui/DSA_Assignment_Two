#ifndef MAIN_H
#define MAIN_H
#include<bits/stdc++.h> 
#include<string>

using namespace std;
#define MAXSIZE 32

#endif

//AVL ==========================================================
class AVL
{
	public:
        int id;
        int result;
        int NUM;
        AVL *left;
        AVL *right;
        int height;
};
int height(AVL *N)
{
	if (N == NULL)
		return 0;
	return N->height;
}
AVL* newNode(int id, int result, int NUM)
{
	AVL* node = new AVL();
    node->id = id;
    node->result = result;
    node->NUM = NUM;
	node->left = NULL;
	node->right = NULL;
	node->height = 1; 
	return(node);
}

AVL *rightRotate(AVL *y)
{
	AVL *x = y->left;
	AVL *T2 = x->right;
	x->right = y;
	y->left = T2;

	// Update heights
	y->height = max(height(y->left),height(y->right)) + 1;
	x->height = max(height(x->left),height(x->right)) + 1;

	// Return new root
	return x;
}

AVL *leftRotate(AVL *x)
{
	AVL *y = x->right;
	AVL *T2 = y->left;
	y->left = x;
	x->right = T2;

	// Update heights
	x->height = max(height(x->left),height(x->right)) + 1;
	y->height = max(height(y->left),height(y->right)) + 1;

	// Return new root
	return y;
}

// Get Balance factor of AVL N
int getBalance(AVL *N)
{
	if (N == NULL)
		return 0;
	return height(N->left) - height(N->right);
}

AVL* insert(AVL* node,int id, int result, int NUM)
{
	/* 1. Perform the normal BST rotation */
	if (node == NULL)
		return(newNode(id,result,NUM));

	if (result < node->result)
		node->left = insert(node->left,id,result,NUM);
	else 
		node->right = insert(node->right,id,result,NUM);

	// Cập nhật lại độ cao của cây
	node->height = 1 + max(height(node->left),height(node->right));

	// cân bằng lại cây
	int balance = getBalance(node);

	// Left Left Case
	if (balance > 1 && result < node->left->result)
		return rightRotate(node);

	// Right Right Case
	if (balance < -1 && result > node->right->result)
		return leftRotate(node);

	// Left Right Case
	if (balance > 1 && result > node->left->result)
	{
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}

	// Right Left Case
	if (balance < -1 && result < node->right->result)
	{
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}
	return node;
}

// Delete =============================================================
AVL* minValueNode(AVL* node)
{
	AVL* current = node;
	while (current->left != NULL)
		current = current->left;

	return current;
}

AVL* deleteNode(AVL* &root, int id,int result,int NUM)
{
	if (root == NULL)
		return root;

	if (result < root->result)
		root->left = deleteNode(root->left,id,result,NUM);

	else if(result > root->result)
		root->right = deleteNode(root->right,id,result,NUM);

	// if infor is same as root's infor, then
	// This is the node to be deleted
	else
	{
		// node with only one child or no child
		if( (root->left == NULL) ||
			(root->right == NULL) )
		{
			AVL *temp = root->left ? root->left : root->right;

			// No child case
			if (temp == NULL)
			{
				temp = root;
				root = NULL;
			}
			else // One child case
			*root = *temp; // Copy the contents of
						// the non-empty child
			free(temp);
		}
		else
		{
			AVL* temp = minValueNode(root->right);
			root->id = temp->id;
            root->result = temp->result;
            root->NUM = temp->NUM;
			root->right = deleteNode(root->right,temp->id,temp->result,temp->NUM);
		}
	}

	// If the tree had only one node
	// then return
	if (root == NULL)
	    return root;

	// STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
	root->height = 1 + max(height(root->left),height(root->right));
	int balance = getBalance(root);
	// Left Left Case
	if (balance > 1 && getBalance(root->left) >= 0)
		return rightRotate(root);

	// Left Right Case
	if (balance > 1 && getBalance(root->left) < 0)
	{
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}

	// Right Right Case
	if (balance < -1 && getBalance(root->right) <= 0)
		return leftRotate(root);

	// Right Left Case
	if (balance < -1 && getBalance(root->right) > 0)
	{
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}

	return root;
}
//start Huff_Man-----------------------------------------------------------------------
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
        huffmanCode[int(root->getChr())] = s; 
    }
    getHuffMan(root->getLeft(), s + "0",huffmanCode); 
    getHuffMan(root->getRight(), s + "1",huffmanCode); 
}

void buildHuffmanTree(unordered_map<char,int> huffman,string huffmanCode[256]) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, compare> huffmanTree;
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
// End Huff_Man ---------------------------------------------------------------------------------------------
int Binary_to_Decimal(string str) {
    int ans = 0;
    for(int i = str.length() - 1;i>=0;i--) {
        ans = ans + pow(2,str.length() - i - 1)*int(str[i] - '0');
    }
    return ans;
}
//======================Min Heap=============================================
class Heap {
protected:
    vector<pair<int,int>> minHeap;
    //first: id, second: NUM
public:
    Heap()
    {
        this->minHeap = minHeap;
    }
    ~Heap()
    {
        minHeap.clear();
    }
    void push(pair<int,int> item) {
        this->minHeap.push_back(item);
        reheapUp(int(minHeap.size() - 1));
    }
    
    bool isEmpty();
    bool contains(pair<int,int> item) {
        for(int i=0;i<int(minHeap.size());i++) {
            if(minHeap[i].first == item.first && minHeap[i].second == item.second) {
                return true;
            }
        }
        return false;
    }
    int getItem(pair<int,int> item) {
        for(int i=0;i<int(minHeap.size());i++) {
            if(minHeap[i].first == item.first && minHeap[i].second == item.second) {
                return i;
            }
        }
        return -1;
    }
    void remove(pair<int,int> item) {
        int index = getItem(item);
        if(index == -1){
            return;
        }
        swap(minHeap[index],minHeap[int(minHeap.size()) - 1]);
        minHeap.pop_back();
        reheapUp(index);
        reheapDown(index);   

    }
    void replace(int id, int NUM) {
        remove({id,NUM-1});
        push({id,NUM});
    }
    void clear() {
        minHeap.clear();
    }
    void print(int index) {
        if(index >= int(minHeap.size())) return;
        cout<<minHeap[index].first<<"-"<<minHeap[index].second<<"\n";
        print(index*2 + 1);
        print(index*2 + 2);
    }
    int get(int n) {
        return minHeap[n].first;
    }
    
private:
    void reheapUp(int position) {
        if(position > 0) {
            int parent = (position-1)/2;
            if(this->minHeap[parent].second > this->minHeap[position].second) {
                swap(this->minHeap[parent],this->minHeap[position]);
                reheapUp(parent);
            }
        }
    }
    void reheapDown(int position) {
        int left = position*2 + 1;
        int right = position*2 + 2;
        int large = position;
        int count = int(minHeap.size());
        if(left < count && this->minHeap[left].second < this->minHeap[large].second) {
            large = left;
        }
        if(right < count && this->minHeap[right].second < this->minHeap[large].second) {
            large = right;
        }
        if(large != position) {
            swap(this->minHeap[position],this->minHeap[large]);
            reheapDown(large);
        }
    }
};
//========================================Khu vực 1==============================================================
void Area_One(vector<vector<int>> &area_one,int id, int result, int NUM) {
       
    int n = MAXSIZE/2;
    int index = result%n;
    if(area_one[index][1] == -1) {
        area_one[index][0] = id;
        area_one[index][1] = result;
        area_one[index][2] = NUM;
        return;
    }
    else {
        //bool check = false;
        for(int i=index + 1;i<MAXSIZE/2;i++) {
            if(area_one[i][1] == -1) {
                area_one[i][0] = id;
                area_one[i][1] = result;
                area_one[i][2] = NUM;
                return;
            }
        }
        for(int i=0;i<index;i++) {
            if(area_one[i][1] == -1) {
                area_one[i][0] = id;
                area_one[i][1] = result;
                area_one[i][2] = NUM;
                return;
            }
        }
        return;
    }
}

//========================================Khu vực 2===============================================================
void Area_Two(AVL* &area_two, int &count_AVL, int id,int result,int NUM) {
    area_two = insert(area_two,id,result,NUM);
    count_AVL++;
}


void Replace_AVL(AVL *&t, int n) {
    if(t == NULL)   return;
    Replace_AVL(t->left,n);
    if(t->id == n) {
        t->NUM++;
        return;
    }
    Replace_AVL(t->right,n);
}
void Replace_result_AVL(AVL *&t, int id, int result) {
    if(t == NULL)   return;
    Replace_result_AVL(t->left,id,result);
    if(t->id == id) {
        t->NUM = 1;
        t->result = result;
        return;
    }
    Replace_result_AVL(t->right,id,result);
}
void Replace(int id, vector<vector<int>> &area_one, AVL *&area_two, int NUM, Heap &min_heap) {
    for(int i=0;i<int(area_one.size());i++) {
        if(area_one[i][0] == id) {
            area_one[i][2]++;
            return;
        }
    }
    Replace_AVL(area_two,id);
    min_heap.replace(id,NUM);
}
struct infor{
    int id;
    int result;
    int NUM;
};
void Search_AVL(infor &st, AVL *t, int n) {
    if(t == NULL)   return;
    Search_AVL(st,t->left,n);
    if(t->id == n) {
        st.id = n;
        st.result = t->result;
        st.NUM = t->NUM;
        return;
    }
    Search_AVL(st,t->right,n);
}
void CLE(int n, vector<vector<int>> &area_one, AVL *&area_two, vector<string> &FIFO, vector<string> &LRCO, 
    vector<pair<string,int>> &string_to_id, Heap &min_heap, int &count_HT,int &count_AVL) {
    //cout<<"Xoa id = "<<n<<endl;
    // tìm string ứng với id
    bool check = false;
    string string_delete;
    for(int i=0;i<int(string_to_id.size());i++) {
        if(string_to_id[i].second == n) {
            string_delete = string_to_id[i].first;
            string_to_id.erase(string_to_id.begin() + i);
            check = true;
            break;
        }
    }
    if(check == false)  return;
    int heap_id = n;
    int heap_NUM = 0;
    bool check_HT = false;
    for(int i=0;i<int(area_one.size());i++) {
        if(area_one[i][0] == n) {
            heap_NUM = area_one[i][1];
            area_one[i][0] = -1;
            area_one[i][1] = -1;
            area_one[i][2] = -1;
            check_HT = true;
            count_HT--;
            break;
        }
    }
    if(check_HT == false) {
        infor st;
        Search_AVL(st,area_two,n);
        heap_NUM = st.NUM;
        area_two = deleteNode(area_two,st.id,st.result,st.NUM);
        count_AVL--;
    }
        
    //giải quyết xoá trong LRCO vs FIFO
    for(int i=0;i<int(FIFO.size());i++) {
        if(FIFO[i] == string_delete) {
            FIFO.erase(FIFO.begin() + i);
        }
    }
    for(int i=0;i<int(LRCO.size());i++) {
        if(LRCO[i] == string_delete) {
            LRCO.erase(LRCO.begin() + i);
        }
    }
    min_heap.remove({heap_id,heap_NUM});
}

void REG(string str, vector<vector<int>> &area_one, int &countHash, AVL* &area_two, int &count_AVL, 
    map<int,int> &hash_id,unordered_map<string,int> &order, vector<string> &num_order, 
    Heap &min_heap, vector<string> &FIFO, vector<string> &LRCO, vector<pair<string,int>> &string_to_id) {
    
    num_order.push_back(str);
    //huffman
    string huffmanCode[256];
    for (int i = 0; i < 256; i++) {
        huffmanCode[i] = ""; 
    }
    
    unordered_map<char,int> huffman;
    for(int i = 0;str[i] != '\0';i++) {
        huffman[str[i]]++;
    }
    buildHuffmanTree(huffman,huffmanCode); 
    
    string getHuffMan = ""; 
    for (int i = 0; i < int(str.length()); i++) {
        getHuffMan += huffmanCode[int(str[i])]; 
    }
    int n = getHuffMan.length();
    if(n > 15) {
        getHuffMan = getHuffMan.substr(n-15,n);
    }
    int result = Binary_to_Decimal(getHuffMan);
    
    //=====================================End huffman=========================
    //Area_One(area_one,result,area_two,count_AVL);
    order[str]++;//gọi món, oder.second là NUM
    // xử lí khi khách gọi món lần 2
    if(order.find(str) != order.end() && order[str] > 1) {
        int id;
        for(int i = 0;i<int(string_to_id.size());i++) {
            if(string_to_id[i].first == str) {
                id = string_to_id[i].second;
                break;
            }
        }
        Replace(id,area_one,area_two,order[str],min_heap);
        for(int i=0;i<int(LRCO.size());i++) {
            if(LRCO[i] == str) {
                LRCO.erase(LRCO.begin() + i);
                break;
            }
        }
        LRCO.push_back(str);
        return;
    }
    // Xử lí id
    int id = result%MAXSIZE + 1;
    
    if(hash_id.find(id) != hash_id.end() && hash_id[id] > 0) {
        bool check_id = false;
        for(int k = id;k <= MAXSIZE;k++) {
            if(hash_id.find(k) == hash_id.end() || hash_id[k] == 0) {
                id = k;
                check_id = true;
                break;
            }
        }
        if(check_id == false) {
            for(int k = 1;k <= id - 1;k++) {
                if(hash_id.find(k) == hash_id.end() || hash_id[k] == 0) {
                    id = k;
                    break;
                }
            }
        }
    }
    hash_id[id]++;
    
    //==================== Xử lí đầy khách ======================
    if(countHash > MAXSIZE/2 && count_AVL > MAXSIZE/2) {
        //giải quyết khi hết bàn
        int OPT = result%3;
        string Vi;
        if(OPT == 0) {          
            Vi = FIFO.front();
            //FIFO.erase(FIFO.begin());
            for(int i=0;i<int(string_to_id.size());i++) {
                if(string_to_id[i].first == Vi) {
                    id = string_to_id[i].second;
                    break;
                }
            }
            CLE(id,area_one,area_two,FIFO,LRCO,string_to_id,min_heap,countHash,count_AVL);
            string_to_id.push_back({str,id});
            min_heap.push({id,order[str]});
            FIFO.push_back(str);
            LRCO.push_back(str);
            if(count_AVL < MAXSIZE/2) {
                Area_Two(area_two,count_AVL,id,result,1);
            }
            else {
                Area_One(area_one,id,result,1);
                countHash++;
            }
        }
        else if(OPT == 1) {
            Vi = LRCO.front();
            //FIFO.erase(FIFO.begin());
            for(int i=0;i<int(string_to_id.size());i++) {
                if(string_to_id[i].first == Vi) {
                    id = string_to_id[i].second;
                    break;
                }
            }
            CLE(id,area_one,area_two,FIFO,LRCO,string_to_id,min_heap,countHash,count_AVL);
            string_to_id.push_back({str,id});
            min_heap.push({id,order[str]});
            FIFO.push_back(str);
            LRCO.push_back(str);
            if(count_AVL < MAXSIZE/2) {
                Area_Two(area_two,count_AVL,id,result,1);
            }
            else {
                Area_One(area_one,id,result,1);
                countHash++;
            }
        }
        else {
            id = min_heap.get(0);
            for(int i=0;i<int(string_to_id.size());i++) {
                if(string_to_id[i].second == id) {
                    Vi = string_to_id[i].first;
                    break;
                }
            }
            CLE(id,area_one,area_two,FIFO,LRCO,string_to_id,min_heap,countHash,count_AVL);
            string_to_id.push_back({str,id});
            min_heap.push({id,order[str]});
            FIFO.push_back(str);
            LRCO.push_back(str);
            if(count_AVL < MAXSIZE/2) {
                Area_Two(area_two,count_AVL,id,result,1);
            }
            else {
                Area_One(area_one,id,result,1);
                countHash++;
            }
        }
        order[Vi]--;
        return;
    }
    else if(countHash > MAXSIZE/2) {
        Area_Two(area_two,count_AVL,id,result,order[str]);
    }
    else if(count_AVL > MAXSIZE/2) {
        Area_One(area_one,id,result,order[str]);
        countHash++;
    }
    else if(result%2 == 1) {
        Area_One(area_one,id,result,order[str]);
        countHash++;
    }
    else {
        Area_Two(area_two,count_AVL,id,result,order[str]);
    }
    string_to_id.push_back({str,id});
    min_heap.push({id,order[str]});
    FIFO.push_back(str);
    LRCO.push_back(str);
    return;
}




void PrintHT(vector<vector<int>> vt) {
    //cout<<"PrintHT\n";
    for(int i=0;i<int(vt.size());i++) {
        if(vt[i][0] != -1) {
            cout<<vt[i][0]<<"-"<<vt[i][1]<<"-"<<vt[i][2]<<"\n";
        }
    }
}

void PrintAVL(AVL* root) {
    //cout<<"Print AVL\n";
    if(root == NULL)    return;
    queue<AVL*> qu;
    qu.push(root);
    while(!qu.empty()) {
        vector<vector<int>> v;
        int length = qu.size();
        while(length > 0) {
            AVL *t = qu.front();
            vector<int> x = {t->id,t->result,t->NUM};
            v.push_back(x);
            qu.pop();
            if(t->left!=NULL)   qu.push(t->left);
            if(t->right!=NULL)  qu.push(t->right);
            length--;
        }
        for(int i=0;i<int(v.size());i++) {
			cout<<v[i][0]<<"-"<<v[i][1]<<"-"<<v[i][2]<<"\n";
		}
		v.clear();
    }
}

void PrintMH(Heap min_heap) {
    min_heap.print(0);
}

void simulate(string filename)
{
	ifstream filein;
	filein.open(filename, ios_base::in);
    vector<vector<int>> area_one;//hash_table KHu vực 1
    vector<int> x = {-1,-1,-1};
    for(int i=0;i<MAXSIZE/2;i++) {
        area_one.push_back(x);
    }
    // Khu vực 2
    AVL* area_two = NULL;
    //FIFO khách khi nhà hàng đầy
    

    int countHash = 0; // đếm số khách kv1
    int count_AVL = 0; // đếm số khách kv2
    map<int,int> hash_id;// check id
    unordered_map<string,int> order;
    string str = "";
    vector<string> num_order;
    Heap min_heap;
    vector<pair<string,int>> string_to_id; // ứng với mỗi string => 1 id duy nhất
    vector<string> FIFO;
    vector<string> LRCO;
    while(!filein.eof()) {
        filein>>str;
        if(str == "REG") {
            filein>>str;
            REG(str,area_one,countHash,area_two,count_AVL,hash_id,order,num_order,min_heap,FIFO,LRCO,string_to_id);
        }
        if(str == "CLE") {
            filein>>str;
            CLE(stoi(str),area_one,area_two,FIFO,LRCO,string_to_id,min_heap,countHash,count_AVL);
        }
        if(str == "PrintHT") {
            PrintHT(area_one);
        }
        if(str == "PrintAVL") {
            PrintAVL(area_two);
        }
        if(str == "PrintMH") {
            PrintMH(min_heap);
        }
        
    }
    area_one.clear();
    delete area_two;
    area_two = NULL;
    return;
}

int main(int argc, char* argv[]) {
    string fileName = "test.txt";
    simulate(fileName);

    return 0;
}