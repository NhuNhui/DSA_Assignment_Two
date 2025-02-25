//{ Driver Code Starts
#include<bits/stdc++.h>
using namespace std;

struct Node
{
	int data;
	struct Node* next;
	
	Node(int x){
	    data = x;
	    next = NULL;
	}
	
};

class Solution
{
    public:
    struct Node* makeUnion(struct Node* head1, struct Node* head2)
    {
        // code here
        set<int> st;
        set<int>::iterator it;

        while(head1) {
            st.insert(head1->data);
            head1 = head1->next;
        }
        while(head2) {
            st.insert(head2->data);
            head2 = head2->next;
        }

        it = st.begin();

        Node *head = new Node(*it);
        Node *tail = head;

        for(++it;it!= st.end();it++) {
            tail->next = new Node(*it);
            tail = tail->next;
        }

        return head;

    }
};


//{ Driver Code Starts.

struct Node* buildList(int size)
{
    int val;
    cin>> val;
    
    Node* head = new Node(val);
    Node* tail = head;
    
    for(int i=0; i<size-1; i++)
    {
        cin>> val;
        tail->next = new Node(val);
        tail = tail->next;
    }
    
    return head;
}

void printList(Node* n)
{
    while(n)
    {
        cout<< n->data << " ";
        n = n->next;
    }
    cout<< endl;
}


int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n, m;
        
        cin>>n;
        Node* first = buildList(n);
        
        cin>>m;
        Node* second = buildList(m);
        Solution obj;
        Node* head = obj.makeUnion(first,second);
        printList(head);
    }
    return 0;
}

// } Driver Code Ends