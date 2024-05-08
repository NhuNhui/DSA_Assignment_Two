#include<bits/stdc++.h>
using namespace std;

//
class Heap {
protected:
    vector<pair<int,int>> minHeap;
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
    void clear() {
        minHeap.clear();
    }
    void print(int index) {
        if(index >= int(minHeap.size())) return;
        cout<<minHeap[index].first<<"-"<<minHeap[index].second<<"\n";
        print(index*2 + 1);
        print(index*2 + 2);
    }
    void printHeap() {
        if(minHeap.size() == 0) {
            cout<<"Khong co phan tu!\n";
            return;
        }
        for(int i=0;i<minHeap.size();i++) {
            cout<<minHeap[i].first<<" ";
        }
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

int main() {
    Heap minHeap;
    minHeap.push({21,1});
    minHeap.push({27,1});
    minHeap.push({22,1});
    minHeap.push({9,1});
    minHeap.push({15,1});
    minHeap.push({20,1});
    minHeap.push({16,1});
    minHeap.print(0);
    minHeap.~Heap();
    return 0;
}