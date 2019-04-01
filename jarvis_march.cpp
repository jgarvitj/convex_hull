/**
@file jarvis_march.cpp
*/
#include <bits/stdc++.h>
#include "Points.h"


using namespace std;
ofstream myfile; //!< A variable of type ofstream used to store the location of jarvis_hull.txt
ofstream myfile1; //!< A variable of type ofstream used to store the location of process.txt

vector <int>hullindex; //!< A vector of integers to store the index of hull points

//! This class has functions to generate the convex hull using jarvis march
class Jarvis{
    public:
    //! A recursive function which keeps updating graph object to form convex hull
    void jarvis_march(Points graph)
    {
        int tmp;
        int i;
        bool flag = true;
        pair <float,float> q;
        pair <float,float> r;
        pair <float,float> p;
        pair <float,float> isSame;
            
        p = graph.points[graph.currentPt];
            
        //finding q(a point not in convex hull)
        for(i = 0; i < graph.numPt; i++)
        {
            if(graph.hullPoints[i] == false)
            {
                q = graph.points[i];
                myfile1<<q.first<<" "<<q.second<<" "<<"first"<<endl;
                flag = false;
                break;
            }
        }
        if(flag)
            return;
            
        //checking orientation of q wrt all points r
        //after this loop q shall hold the next currentPt
        for(int j = 0; j < graph.numPt; j++)
        {
            r = graph.points[j];
            isSame.first = q.first;
            isSame.second = q.second;
            q = graph.checkOrientation(p,q,r);
            if(isSame.first != q.first || isSame.second != q.second)
            {
                myfile1<<q.first<<" "<<q.second<<endl;
            }
        }

        tmp = graph.getIndex(q);

        //just a precaution
        if(tmp == -1)
        {
            cout<<"error"<<endl;
            return;
        }

        //the found point q should be a point in the hull
        if(graph.hullPoints[tmp] == true)
        {
            return;
        }
        else
        {
            graph.hullPoints[tmp] = true;
            hullindex.push_back(tmp);
            cout<<q.first<<','<<q.second<<" added"<<endl;
            graph.currentPt = tmp;
            jarvis_march(graph);
        }
        return;
    }
};

//! Calls jarvis_march to form convex hull
int main(int argc, char *argv[])
{    
    myfile.open("jarvis_hull.txt");
    myfile1.open("process.txt");
    Points graph;
    graph.takeInput("p1.txt");
    int leftMost = graph.findLeftmost();
    hullindex.push_back(leftMost);
    cout<<graph.points[leftMost].first<<','<<graph.points[leftMost].second<<" added"<<endl;
    graph.inithullPoints();
    graph.hullPoints[leftMost] = true;
    graph.currentPt = leftMost;
    Jarvis j;
    j.jarvis_march(graph);
    for(int i = 0; i < hullindex.size(); i++)
    {
        myfile<<graph.points[hullindex[i]].first<<" "<<graph.points[hullindex[i]].second<<endl;
    }
    for(int k = 0; k < hullindex.size(); k++)
    {
        myfile<<hullindex[k]<<" ";
    }
    return 0;
}