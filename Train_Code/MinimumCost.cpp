//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;


// } Driver Code Ends
class Solution
{
    public:
    //Function to return the minimum cost of connecting the ropes.
    long long minCost(long long arr[], long long n) {
        // Your code here
        if(n == 1) 
            return arr[0];
        if(n == 0) 
            return 0;
        if(n == 2)
            return arr[0] + arr[1];
        priority_queue<long long, vector<long long>, greater<long long>> pri_queue;
        for(int i=0;i<n;i++) {
            pri_queue.push(arr[i]);
        }
        long long cost = 0;
        while(!pri_queue.empty()) {
            long long top1 = pri_queue.top();
            pri_queue.pop();
            long long top2 = pri_queue.top();
            cost = cost + top1 + top2;
            pri_queue.pop();
            pri_queue.push(top1 + top2);
            if(pri_queue.size() == 1) {
                //cost = cost + pri_queue.top();
                break;
            }
        }
        return cost;
    }
};


//{ Driver Code Starts.

int main() {
    long long t;
    cin >> t;
    while (t--) {
        long long n;
        cin >> n;
        long long i, a[n];
        for (i = 0; i < n; i++) {
            cin >> a[i];
        }
        Solution ob;
        cout << ob.minCost(a, n) << endl;
    }
    return 0;
}

// } Driver Code Ends