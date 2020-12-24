#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <numeric> 
#include <algorithm>

#define WHITE 0
#define BLACK 1

using namespace std;

//                     E   W    SE   SW   NE    NW
vector<double> lin = { 1, -1, 0.5, -0.5, 0.5, -0.5 };
vector<double> col = { 0,  0,   1,   1,  -1,   -1 };

int main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  string inputLine;
  map<pair<double, double>, bool> tiles;

  map<string, int> mapDirectionToInt;
  mapDirectionToInt["e"] = 0;
  mapDirectionToInt["w"] = 1;
  mapDirectionToInt["se"] = 2;
  mapDirectionToInt["sw"] = 3;
  mapDirectionToInt["ne"] = 4;
  mapDirectionToInt["nw"] = 5;

  while (cin >> inputLine)
  {
    double x = 0, y = 0;
    for (int i = 0; i < inputLine.size();)
    {
      string direction;
      direction += inputLine[i];
      if (inputLine[i] == 'e' || inputLine[i] == 'w')
      {
        i++;
      }
      else if (inputLine[i] == 'n' || inputLine[i] == 's')
      {
        direction += inputLine[i + 1];
        i += 2;
      }
      x += lin[mapDirectionToInt[direction]];
      y += col[mapDirectionToInt[direction]];
    }

    tiles[{x, y}] = !tiles[{x, y}];
  }
  int numberOfBlackFaces = accumulate(tiles.begin(), tiles.end(), 0,
    [](int value, const std::map<pair<double, double>, bool>::value_type& p)
    { return value + p.second; }
  );

  cout << "Part 1: " << numberOfBlackFaces << endl;

  for (int index = 0; index < 100; index++)
  {
    double x, y;
    auto nextTiles = tiles;
    // add white neighbours
    for (auto tile : tiles)
    {
      // all 6 directions
      for (int direction = 0; direction < lin.size(); direction++)
      {
        x = tile.first.first + lin[direction];
        y = tile.first.second + col[direction];
        if (nextTiles.find({ x,y }) == nextTiles.end())
        {
          nextTiles[{x, y}] = WHITE;
        }
      }
    }

    tiles = nextTiles;
    for (auto tile : tiles)
    {
      int blackNeghbours = 0;
      for (int j = 0; j < 6; j++)
      {
        x = tile.first.first + lin[j];
        y = tile.first.second + col[j];

        if (tiles.find({ x,y }) != tiles.end())
        {
          if (tiles[{x, y}] == BLACK)
            blackNeghbours++;
        }
      }
      if (tile.second == WHITE && blackNeghbours == 2)
      {
        nextTiles[tile.first] = BLACK;
        numberOfBlackFaces++;
      }
      else  if (tile.second == BLACK && (blackNeghbours == 0 || blackNeghbours > 2))
      {
        nextTiles[tile.first] = WHITE;
        numberOfBlackFaces--;
      }
    }
    tiles = nextTiles;
  }

  cout << "Part 2: " << numberOfBlackFaces << endl;
  return 0;
}