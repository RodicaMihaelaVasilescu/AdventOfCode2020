#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> X;
vector<int> Y;
vector<int> Z;
struct point
{
  int x, y, z;
  bool operator==(const point& o) const {
    return x == o.x && y == o.y && z == o.z;
  }

  bool operator<(const point& o)  const {
    return x < o.x || (x == o.x && y < o.y) || (x == o.x && y == o.y && z < o.z);
  }
};
int main()
{

  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  string inputLine;

  for (int x = -1; x <= 1; x++)
  {
    for (int y = -1; y <= 1; y++)
    {
      for (int z = -1; z <= 1; z++)
      {
        if (!(x == 0 && y == 0 && z == 0))
        {
          X.push_back(x);
          Y.push_back(y);
          Z.push_back(z);
        }
      }
    }
  }

  map<point, int> mapOfPoints;

  int x = 0;
  while (cin >> inputLine)
  {
    for (int y = 0; y < inputLine.size(); y++)
    {
      if (inputLine[y] == '#')
      {
        mapOfPoints[{x, y, 0}] = 1;
      }
    }
    x++;

  }

  int index = 0;

  while (index++ < 6) {

    map<point, int> activePoints;
    set<point> neighbors;
    for (auto p : mapOfPoints)
    {
      map<char, int> neighborsFrequecy;
      point key = p.first;
      for (int direction = 0; direction < X.size(); direction++)
      {
        int x = key.x + X[direction];
        int y = key.y + Y[direction];
        int z = key.z + Z[direction];

        auto found = mapOfPoints.find({ x, y, z });
        if (found != mapOfPoints.end())
        {
          neighborsFrequecy[found->second]++;
        }

        neighbors.insert({ x, y, z });
      }
      if (mapOfPoints[key] == 1 && (neighborsFrequecy[1] == 2 || neighborsFrequecy[1] == 3))
      {
        activePoints[key] = 1;
      }
    }
    for (auto p : neighbors)
    {
      map<char, int> neighborsFrequecy;
      point key = p;
      for (int direction = 0; direction < X.size(); direction++)
      {
        int x = key.x + X[direction];
        int y = key.y + Y[direction];
        int z = key.z + Z[direction];

        auto found = mapOfPoints.find({ x, y, z });
        if (found != mapOfPoints.end())
        {
          neighborsFrequecy[found->second]++;
        }
      }
      if (mapOfPoints[key] == 0 && (neighborsFrequecy[1] == 3))
      {
        activePoints[key] = 1;
      }
    }
    mapOfPoints = activePoints;
  }
  
  cout << "Part 1: " << mapOfPoints.size();
  return 0;
}

