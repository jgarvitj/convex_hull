#include <bits/stdc++.h>

using namespace std;

//! This class is used to split input lines taken by class Points
class Operation
{
    public:
    //! A normal function taking a string and a character and returning a vector is used to split the string with the character as the delimeter and put the output in the vector 
    vector<string> split(string str, char delimiter) 
    {
        vector<string> internal;
        stringstream ss(str); // Turn the string into a stream.
        string tok;
        
        while(getline(ss, tok, delimiter)) 
        {
            internal.push_back(tok);
        }
        
        return internal;
    }
};

//! This class is used to generate the graph.
/*! It takes input as the object is created from its constructor. 
 * It has basic data types and functions defined for use in the rest of the project
 */
class Points{

    public:
    
    int numPt; //!< an integer value which stores the number of points in the graph */
    //vector points to store all input points
    vector <pair <float,float> >points; //!< A vector which holds the entire graph's coordinates */
    //stores the index of current point
    int currentPt; //!< A integer value to hold the index of current point
    //vector check to handle iterative approches of jarvis march
    // vector <bool>check;
    //vector hullPoints to check which points are in are in the hull 
    vector <bool> hullPoints; //!< A vector which holds the coordinates of the hull points
    //! A constructor
    /*! takes input from p1.txt and fills it into vector points
    */
    void takeInput(string str1)
    {
        numPt = 0;
        Operation op;
        ifstream file(str1);
        string str;
        int count=0;
        while (getline(file, str))
        {
            vector <string> p=op.split(str,' ');
            points.push_back(make_pair(stof(p[0]), stof(p[1])));
            numPt++;
        }
    }

    //! A normal member taking no argument and returning nothing used for initilization of vector hullPoints which shall store all hull points
    void inithullPoints()
    {
        for(int i = 0; i < numPt; i++)
        {
            hullPoints.push_back(false);
        }
    }

    //! A normal member taking no argument and returning nothing used for sorting the vector points first by x-coordinates and then by y-coordinates
    void sortByx()
    {
        sort(points.begin(), points.end());
    }

    //! A normal member taking no argument and returning a point used to find the leftmost element. If more then 1 elements are leftmost then it takes the one occuring first
    int findLeftmost()
    {
        float min;
        min = points[0].first;
        int tmp = 0;
        for(int i = 0; i < numPt; i++)
        {
            if(points[i].first < min)
            {
                min = points[i].first;
                tmp = i;
            }
        }
        return tmp;
    }

    //! A normal member taking a argument and returning an integer value used to tell the index of the point
    int getIndex(pair <float,float> a)
    {
        for(int i = 0; i < numPt; i++)
        {
            if(points[i].first == a.first && points[i].second == a.second)
            {
                return i;
            }
        }
        cout<<a.first<<','<<a.second<<"not found"<<endl;
        return -1;
    }

    //! A normal member taking 3 points and returning a point p,q,r used to find most counterclockwise point to p 
    pair <float,float> checkOrientation(pair <float,float> p, pair <float,float> q, pair <float,float>r)
    {
        float val = ((q.second - p.second) * (r.first - q.first)) - ((q.first - p.first) * (r.second - q.second));
        if(val <= 0)
        {
            return q;
        }
        else
        {
            return r;
        }
    }

    //! A funtion taking 3 points and returning an integer is used to return orientation of three points.
    int orientation(pair <float,float> p, pair <float,float> q, pair <float,float>r)
    {
        int slope_comp = (q.second-p.second) * (r.first-q.first) - (q.first-p.first) * (r.second-q.second);
        if (slope_comp == 0) return 0; 
            return (slope_comp > 0)? 1: 2;
    }
};
