#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int getNumberOfTrees(vector<string> map, int right, int left)
{
  int line = 0, column = 0, numberOfTrees = 0;
  int n = map.size(), m = map[0].size();

  while (line < n)
  {
    if (map[line][column % m] == '#')
    {
      numberOfTrees++;
    }

    column += right;
    line += left;
  }
  return numberOfTrees;
}

int main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  vector<string> v;
  string inputLine;

  while (cin >> inputLine)
  {
    v.push_back(inputLine);
  }

  cout << "Part 1: " << getNumberOfTrees(v, 3, 1) << endl;
  cout << "Part 2: " << 1ll *
    getNumberOfTrees(v, 1, 1) *
    getNumberOfTrees(v, 3, 1) *
    getNumberOfTrees(v, 5, 1) *
    getNumberOfTrees(v, 7, 1) *
    getNumberOfTrees(v, 1, 2) << endl;

  return 0;
}
