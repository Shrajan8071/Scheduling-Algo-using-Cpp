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
    int priority; //more value high priority
};

void takeinput(vector<table>& t)
{
    int n; cout << "Enter number of processes: "; cin >> n;
    for(int i=0;i<n;i++)
    {
        int at;int bt;int priority; 
        cout<< "Arrival Time for process " << i << ": "; cin >> at;
        cout<< "Burst Time for process " << i << ": "; cin >> bt;
        cout<< "Priority for process " << i << ": "; cin >> priority;
        t.push_back({i+1,at,bt,0,0,0,0,priority});
    }
}

void printTable(vector<table> t)
{
    cout << "P no." << "\t" << "AT" << "\t" << "BT" << "\t" << "CT" << "\t" << "TAT" << "\t" << "WT"<< "\t" << "RT" <<
    "\t" << "Priority" << endl;
    for (auto& row : t) {
        cout << row.p << "\t" << row.at << "\t" << row.bt << "\t" << row.ct << "\t" << row.tat << "\t" << row.wt << 
        "\t" << row.rt << "\t" << row.priority <<endl;
    }
}

bool comparator(const tuple<int, int, int,int>& a, const tuple<int, int, int,int>& b) {
    if (get<1>(a) < get<1>(b))
        return get<1>(a) < get<1>(b);
    else if(get<1>(a) == get<1>(b))
        return get<3>(a)>get<3>(b);
}

tuple<int,int,int,int> findMin(vector<tuple<int,int,int,int>>& q,int counter)
{
    sort(q.begin(),q.end(),comparator);
    int priority=INT_MIN;
    tuple<int,int,int,int> temp;
    int process;
    for(auto x:q)
    {   
        if(get<1>(x) <= counter)
        {
            if(get<3>(x)>=priority)
            {
                process = get<0>(x); priority = get<3>(x);temp=x;
            }
        }
    }
    vector<tuple<int,int,int,int>> newtuplearray;
    for(auto x:q )
    {
        if(get<0>(x)!=process)
            newtuplearray.push_back(x);
    }
    q=newtuplearray;
    // q.pop_back();
    return temp;
}

void solveLogic(vector<table>& t)
{
    vector<tuple<int,int,int,int>> q;
    vector<int> chart;
    for(auto& x: t)
    {
        q.push_back(
            {
                x.p,  //process name
                x.at, //process arrival time
                x.bt,  // process burst time
                x.priority  //priority
            }
        );
    }
    int counter=0;
    while(q.size()!=0)
    {
        auto p = findMin(q,counter); 
        int a=get<0>(p); //process name
        int b=get<1>(p); //process AT
        int c=get<2>(p); //process burst time
        t[a].rt=counter - b;
        if(counter>=b)
        {
            for(int i=0;i<c;i++)
            {
                chart.push_back(a);
                counter++;
            }
            t[a].ct=counter; // setting completion time
        }
        else{
            chart.push_back(-1);
            counter++;
        }
    }
    for(auto& x: t)
    {
        x.tat=x.ct-x.at;
        x.wt=x.tat-x.bt;
    }

    for(auto x: chart)
    {
        cout << x << " ";
    }
    cout << endl;
}

int main()
{
    vector<table> t;
    //please input in ascending order of AT
    // takeinput(t);
    t.push_back({0,0,5,0,0,0,0,10});
    t.push_back({1,1,4,0,0,0,0,20});
    t.push_back({2,2,2,0,0,0,0,30});
    t.push_back({3,4,1,0,0,0,0,6});
    solveLogic(t);
    printTable(t);
    return 0;
}