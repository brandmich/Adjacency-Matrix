#include "digraph.h"
#include <fstream>
#include <sstream>
#include <iostream>

DigraphMatrix::DigraphMatrix(const string& filename)
{
    ifstream file(filename);
    istringstream iss;
    string line;
    int first, second;
    
    //get n and m
    getline(file, line);
    iss.str(line);
    iss >> n >> m;
    iss.clear();
    
    if(n == 0)
        throw exception();

    //set up matrix
    matrix.resize(n);
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < n; j++)
        {
            matrix[i].push_back(j);
        }
    }

    
    //matrix[n][n] = 0;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            matrix[i][j] = 0;
        }
    }
    
    //add edges
    while(getline(file, line))
    {
        iss.str(line);
        iss >> first >> second;;
        AddEdge(first, second);
        iss.clear();
    }
    file.close();

    //print matrix
    /*for(int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix.size(); j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;*/
}

vector<int> DigraphMatrix::topologicalSort()
{
    stack<int>s;
    vector<int> vertexes;
    visited.resize(n);
    
    //initialize all states to false visitation
    for(int i = 0; i < n; i++)
        visited[i] = false;

    //clear discovered, then go to next available vertex
    for(int i = 0; i < n; i++)
    {
        discovered.clear();
        if(visited[i] != true)
        {
            Sort(matrix, i, s);
        }
    }

    //reverse order to be in sorted order
    vertexes.resize(n);
    int max = 0;
    while(max < n)
    {
        vertexes[max] = s.top();
        s.pop();
        max++;
    }
    cout << endl;
    return vertexes;

}

void DigraphMatrix::Sort(vector<vector<int>> matrix, int v, stack<int> &s)
{
    if(discovered.size() > n)//will only be true if a loop occurs
        throw exception();

    for(int i = 0; i < n; i++)
    {   
        if(i == v && matrix[v][i] == 1)
            throw exception();//self loop

        if(matrix[v][i] == 1 && visited[i] == false)//go to next vertex
        {
            discovered.push_back(v);
            Sort(matrix, i, s);
        }
    }
    visited[v] = true;
    s.push(v);
}

int DigraphMatrix::GetDegree(const int v) const
{
    int count = 0;
    for(int i = 0; i < n; i++)
    {
        if(matrix[i][v] == 1)
            count ++;
    }
    return count;
}