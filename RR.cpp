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

void checkifnew(int &counter,vector<tuple<int,int,int>>& q,queue<int>& ready_q)
{
    for(auto x:q)
    {
        if(get<1>(x)==counter)
        {
           ready_q.push(get<0>(x));
            return;
        }
    }
}

void solveLogic(vector<table>& t)
{
    vector<tuple<int,int,int>> q;
    vector<int> chart;
    queue<int> ready_q;
    // int req=0;
    for(auto x: t)
    {
        q.push_back(
            {
                x.p,  //process name
                x.at, //process arrival time
                x.bt  // process burst time
            }
        );
        // req+=x.bt;
    }
    int quantum=2;
    int counter=0;
    checkifnew(counter,q,ready_q);
    counter+=1;
    while(!ready_q.empty() )
    {
        int x = ready_q.front();
        ready_q.pop();
        int available = get<2>(q[x]);
        if(available>=quantum)
        {
            for(int i=0; i<quantum; i++)
            {
                checkifnew(counter,q,ready_q);
                get<2>(q[x])--;
                chart.push_back(x);
                if(get<2>(q[x])==0)
                {
                    t[x].ct=counter;
                }
                if(t[x].rt==0)
                    t[x].rt=counter - t[x].at; 
                counter++;
            }
            ready_q.push(x);
        }
        else if (available<= quantum)
        {
            while(get<2>(q[x]))
            {
                chart.push_back(x);
                checkifnew(counter,q,ready_q);
                get<2>(q[x])--;
                if(get<2>(q[x])==0)
                {
                    t[x].ct=counter;
                }
                if(t[x].rt==0)
                    t[x].rt=counter - t[x].at; 
                counter++;
            }
        }      
    }
    // /now setting tat and wt
    for(auto& x: t)
    {
        x.tat=x.ct-x.at;
        x.wt=x.tat-x.bt;
    }
    //printing gantt chart
    cout<< "Gantt chart"<< endl;
    for(int i=0;i<chart.size();i++)
        cout << i << " ";

    cout << endl;

    for(auto x:chart)
    {
        if(x!=-1)
            cout << x << " ";
        else
            cout << "X ";    
    }
    for(auto& x:t)
    {
        if(x.rt>0)
        {
            x.rt = x.rt - 1;
        }
    }
    cout << endl;
}

int main()
{
    vector<table> t;
    //please input in ascending order of AT
    // takeinput(t);
    t.push_back({0,0,5,0,0,0});
    t.push_back({1,1,4,0,0,0});
    t.push_back({2,2,2,0,0,0});
    t.push_back({3,4,1,0,0,0});
    solveLogic(t);
    printTable(t);
    return 0;
}