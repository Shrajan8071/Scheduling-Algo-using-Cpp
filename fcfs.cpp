#include<iostream>
#include<bits/stdc++.h>
using namespace std;

struct table
{
    int p; //process number
    int at;// arrival time
    int bt; //burst time
    int ct; // completion time
    int tat; // turn around time  // ct-at
    int wt; //wait time           // tat-bt
    int rt; //response time       //first access-at
};

void takeinput(vector<table>& t)
{
    int n; cout << "Enter number of processes: "; cin >> n;
    for(int i=0;i<n;i++)
    {
        int at;int bt; 
        cout<< "Arrival Time for process " << i << ": "; cin >> at;
        cout<< "Burst Time for process " << i << ": "; cin >> bt;
        t.push_back({i+1,at,bt,0,0,0});
    }
}

void printTable(vector<table> t)
{
    cout << "P no." << "\t" << "AT" << "\t" << "BT" << "\t" << "CT" << "\t" << "TAT" << "\t" << "WT"<< "\t" << "RT" << endl;
    for (auto& row : t) {
        cout << row.p << "\t" << row.at << "\t" << row.bt << "\t" << row.ct << "\t" << row.tat << "\t" << row.wt << 
        "\t" << row.rt << endl;
    }
}

void solveLogic(vector<table>& t)
{
    queue<tuple<int,int,int>> q;
    vector<int> v;
    for(auto x: t)
    {
        q.push(
            {
                x.p,  //process name
                x.at, //process arrival time
                x.bt  // process burst time
            }
        );
    }
    int counter=0;
    while(!q.empty())
    {
        auto p = q.front(); 
        int a=get<0>(p); //process name
        int b=get<1>(p); //process AT
        int c=get<2>(p); //process burst time
        t[a].rt=counter - b;
        if(counter>=b)
        {
            q.pop();
            for(int i=0;i<c;i++)
            {
                v.push_back(a);
                counter++;
            }
            t[a].ct=counter; // setting completion time
        }
        else{
            v.push_back(-1);
            counter++;
        }
    }
    //now setting tat and wt
    for(auto& x: t)
    {
        x.tat=x.ct-x.at;
        x.wt=x.tat-x.bt;
    }
    //printing gantt chart
    cout<< "Gantt chart"<< endl;
    for(int i=0;i<v.size();i++)
        cout << i << " ";

    cout << endl;

    for(auto x:v)
    {
        if(x!=-1)
            cout << x << " ";
        else
            cout << "X ";    
    }
    cout << endl;
}

int main()
{
    vector<table> t;
    //please input in increasing order of AT
    // takeinput(t);
    t.push_back({0,0,2,0,0,0});
    t.push_back({1,1,2,0,0,0});
    t.push_back({2,5,3,0,0,0});
    t.push_back({3,6,4,0,0,0});
    solveLogic(t);
    printTable(t);
    return 0;
}