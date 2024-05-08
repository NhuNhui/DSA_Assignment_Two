//{ Driver Code Starts
//Initial Template for C++
#include<bits/stdc++.h>
using namespace std;


// } Driver Code Ends
//User function Template for C++

// CollegeCourse Class 
class CollegeCourse
{
    //your code here
    private:
        string courseID;
        char grade;
        int credits;   
    public:
        void set_CourseId(string s) {
            this->courseID = s;
        }
        void set_Grade(char c) {
            this->grade = c;
        }
        void set_Credit(int x) {
            this->credits = x;
        }
        int calculateGradePoints(char c) {
            if(c == 'a' || c == 'A') {
                return 10;
            }
            if(c == 'b' || c == 'B') {
                return 9;
            }
            if(c == 'c' || c == 'C') {
                return 8;
            }
            if(c == 'd' || c == 'D') {
                return 7;
            }
            if(c == 'e' || c == 'E') {
                return 6;
            }
            return 5;
        }

        float calculateHonorPoints(int a, int b) {
            return a*b;
        }
        void display() {
            cout<<calculateGradePoints(this->grade)<<" "<<calculateHonorPoints(calculateGradePoints(this->grade),this->credits)<<endl;
        }
};

//{ Driver Code Starts.

int main()
{
    int t;
    cin>>t;
    while(t--)
    {
    CollegeCourse cc;
    string courseId;
    int gp;
    char grade;
    int credits;
    cin>>courseId>>grade>>credits;
    cc.set_CourseId(courseId);
    cc.set_Grade(grade);
    cc.set_Credit(credits);
    gp=cc.calculateGradePoints(grade);
    cc.calculateHonorPoints(gp,credits);
    cc.display();
    }
    return 0;
}

// } Driver Code Ends