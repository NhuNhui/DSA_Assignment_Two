//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;

// } Driver Code Ends
class Solution
{
        
    public:
    vector<int> vt;
    //Function to insert heap.
    void insertHeap(int &x)
    {
        vt.push_back(x);
        sort(vt.begin(),vt.end());
    }
    
    //Function to balance heaps.
    void balanceHeaps()
    {
        
    }
    
    //Function to return Median.
    double getMedian()
    {
        if(vt.size()%2 == 1) {
            return vt[ceil(vt.size()/2)];
        }
        return (vt[vt.size()/2] + vt[vt.size()/2 + 1]);
    }
};


//{ Driver Code Starts.

int main()
{
    int n, x;
    int t;
    cin>>t;
    while(t--)
    {
    	Solution ob;
    	cin >> n;
    	for(int i = 1;i<= n; ++i)
    	{
    		cin >> x;
    		ob.insertHeap(x);
    	    cout << floor(ob.getMedian()) << endl;
    	}
    }
	return 0;
}
// } Driver Code Ends