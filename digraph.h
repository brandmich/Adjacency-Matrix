#ifndef __DIGRAPH_H
#define __DIGRAPH_H

#include <string>
#include <vector>
#include <stack>
#include <exception>
using namespace std;

class DigraphMatrix
{
public:
  DigraphMatrix(const string& filename);
  vector<int> topologicalSort();
  void Sort(vector<vector<int>> matrix, int v, stack<int> &s);
  int GetDegree(const int v) const;//gets the in degrees
  void AddEdge(int u, int v){matrix[u][v] = 1;}
private:
  int n, m, u, v;
  vector<vector<int>> matrix;
  vector<bool> visited;
  vector<int> discovered;//tracks which vertexes have been discovered in current iteration
};
#endif