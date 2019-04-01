/**
@file grahams_scan.cpp
*/
#include<bits/stdc++.h>
#include "Points.h"

using namespace std;

#define endl "\n" //!< A macro to save end of line
#define PI 3.14159265 //!< A macro to save the value of pi

// typedef long long ll; 
typedef pair<float, float> ff; //!< A macro to hold a pair of float
typedef vector<ff> vff; //!< A macro to hold a vector of type ff
typedef vector<float> vf; //!< A macro to hold a vector of type float


//! A funtion taking 2 pointers pointing to 2 points and returning a boolean value is used as comaparator for sorting by second element of the pair of <float,float>
bool sort_by_sec(const ff &a, const ff &b)
{
    return(a.second<b.second);
}

//! A funtion taking 2 pointers pointing to 2 points and returning a boolean value is used as comaparator for sorting by second element of the pair of <ff,float>
bool sort_by_sec_float(const pair<ff,float> &a, const pair<ff,float> &b)
{
    return(a.second<b.second);
}

//! A function taking a object of type Points and returning a vector is used to sort points first by x and then by y??
vff sort_points(Points graph)
{
    sort(graph.points.begin(),graph.points.end());
    sort(graph.points.begin(),graph.points.end(),sort_by_sec);
    return graph.points;
}

//! A function taking a object of type Points and returning a vector is used to distances of points from p0
vf dist_from_p0(Points graph)
{
    vf distances;
    for(int i=0; i<graph.points.size(); i++)
    distances.push_back(pow(pow(graph.points[i].second-graph.points[0].second,2)+pow(graph.points[i].first-graph.points[0].first,2),0.5));

    return distances;
}

//! A function taking a object of type Points and returning a vector is used to measure angle of points with p0 and horizontal axis
vf polar_angle_from_p0(Points graph)
{
    vf polar_angles;
    vf dist_pi_p0 = dist_from_p0(graph);

    polar_angles.push_back(0);

    for(int i=1; i<graph.points.size(); i++)
        polar_angles.push_back(acos((graph.points[i].first-graph.points[0].first)/dist_pi_p0[i]) * 180 / PI);

    return polar_angles;
}

//! A function taking a object of type Points and a vector and returning a vector is used to sort points based on comparator
vff sort_by_sec_vec(Points graph, vf compare_vec)
{
    vector<pair<ff,float>> zipped_points;

    for(int i=0; i<graph.points.size();i++)
        zipped_points.push_back(make_pair(graph.points[i],compare_vec[i]));
    
    sort(zipped_points.begin(), zipped_points.end(), sort_by_sec_float);

    vff sortedPoints;
    for(int i=0; i<graph.points.size();i++)
        sortedPoints.push_back(zipped_points[i].first);
    
    return sortedPoints;
}

//! A function taking a object of type Points and returning a vector is used to remove linear points
vff remove_same_angle_points(Points graph)
{
    vf angles = polar_angle_from_p0(graph);
    float temp_ang_g = angles[angles.size()-1];
    int i=graph.points.size()-1;
    while(i!=1)
    {
        float temp_ang = angles[i-1];
        if(temp_ang==temp_ang_g)
        {
            graph.points.erase(graph.points.begin()+i-1);
            angles.erase(angles.begin()+i-1);
        }
        else
        {
            temp_ang_g = angles[i-1];
        }
        i--;
    }
    return graph.points;
}

//! A funtion taking an integer value and returning nothing used to check if hull possible
void hull_check(int size)
{
    if(size<3)
    {
        cout<<"Convex Hull Not Possible";
        exit(1);
    }
}



//! A function taking a object of type stack and returning a point is used to return next to top element of stack
ff top_next(stack<ff> hull)
{
    hull.pop();
    return hull.top();
}


//! A function taking a object of type stack and returing nothing is used to print stack
void showstack(stack <ff> s) 
{ 
    cout<<"stack\n";
    while (!s.empty()) 
    { 
        cout<<s.top().first<<","<<s.top().second<<endl; 
        s.pop(); 
    } 
} 

//! A function taking a object of type Points and returning nothing is used to make the hull bitch
void convex_hull(Points graph)
{
    stack<ff> hull;
    hull.push(graph.points[0]);
    hull.push(graph.points[1]);
    hull.push(graph.points[2]);

    for(int i=3; i<graph.points.size(); i++)
    {

        while(graph.orientation(top_next(hull),hull.top(),graph.points[i])!=2)
        {
            hull.pop();
            showstack(hull);
        }
        hull.push(graph.points[i]);
        showstack(hull);
    }
}

//! A function taking a vector and a string and returning nothing is used to print a set of points along with a message
void print_vec(vff points, string msg)
{
    cout<<msg<<endl;

    for (int i=0; i<points.size(); i++)
        cout<<points[i].first<<","<<points[i].second<<endl;

}

//!! Start of execution for graham's scan to form convex hull
int main()
{
    Points graph;
    graph.takeInput("p1.txt");
    int n = graph.points.size() ;

    print_vec(graph.points,"input_points");

    graph.points = sort_points(graph);
    print_vec(graph.points,"points_sorted");
    
    graph.points = sort_by_sec_vec(graph,dist_from_p0(graph));
    //! print_vec(graph.points,"points_sorted_by_distance");
    
    graph.points = sort_by_sec_vec(graph,polar_angle_from_p0(graph));
    //! print_vec(graph.points,"points_sorted_by_polar_angle");

    graph.points = remove_same_angle_points(graph);
    //! print_vec(graph.points,"points_after_removing_same_angle_points");
    
    hull_check(graph.points.size());

    convex_hull(graph);

    return 0;
}