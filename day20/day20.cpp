#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

vector<string> finalMatrix;

struct Tile
{
  int ID;
  vector<string> borders;
  vector<string> Map;
  vector<int>isLinked = vector<int>(4, 0);
};

bool operator==(const Tile& a, const Tile& b)
{
  return  a.ID == b.ID;
}
bool operator!=(const Tile& a, const Tile& b)
{
  return  a.ID != b.ID;
}

vector<string> flipMatrix(vector<string> matrix)
{
  for (auto& s : matrix)
  {
    s = string(s.rbegin(), s.rend());
  }
  return matrix;
}
vector<string> rotateRight(vector<string> matrix)
{
  vector<string>v2;
  string s;
  // line will be column
  for (int i = 0; i < matrix.size(); i++)
  {
    s = "";
    for (int j = 0; j < matrix.size(); j++)
    {
      s += matrix[j][i];
    }
    s = string(s.rbegin(), s.rend());
    v2.push_back(s);
  }
  return v2;
}

set<int>usedTiles;

string getRightBorder(vector<string> matrix)
{
  string right;
  for (auto i : matrix)
  {
    right += i[matrix.size() - 1];
  }
  return right;
}

string getLeftBorder(vector<string> matrix)
{
  string left;
  for (auto i : matrix)
  {
    left += i[0];
  }
  return left;
}


vector<string> lastRotationLeft(10, "");
string getNextRotationForRightBorder(vector<string> matrix, string leftBorder)
{
  string left, right;
  for (auto i : matrix)
  {
    left += i[0];
    right += i[matrix.size() - 1];
  }

  int rotation = 0;
  while (left != leftBorder)
  {
    rotation++;
    matrix = rotateRight(matrix);
    left = "";
    right = "";
    for (auto i : matrix)
    {
      left += i[0];
      right += i[matrix.size() - 1];
    }
    if (left == leftBorder)
    {
      lastRotationLeft = matrix;
      return right;
    }
    if (rotation == 4)
    {
      return "";
    }
  }
  lastRotationLeft = matrix;
  return right;
}

vector<int>usedTileIDs;

vector<string > lastRotationDown;
string getRotationsForBottomBorder(vector<string> matrix, string upperBorder)
{
  string up = matrix[0];
  string bottom = matrix[matrix.size() - 1];

  int rotation = 0;
  while (up != upperBorder)
  {
    rotation++;
    matrix = rotateRight(matrix);
    up = matrix[0];
    if (up == upperBorder)
    {
      lastRotationDown = matrix;
      return matrix[matrix.size() - 1];
    }
    if (rotation == 4)
    {
      return "";
    }
  }
  lastRotationDown = matrix;
  return matrix[matrix.size() - 1];
}

void SearchTilesToRight(Tile currentTile, vector<Tile> allTiles)
{
  auto matrix = lastRotationDown;
  string right = getLeftBorder(matrix);

  bool foundNextRight = true;
  vector<string> finalMap(10, "");

  while (foundNextRight)
  {
    usedTileIDs.push_back(currentTile.ID);
    string rightCopy = right;
    right = getNextRotationForRightBorder(currentTile.Map, right);
    if (right == "")
    {
      currentTile.Map = flipMatrix(currentTile.Map);
      right = getNextRotationForRightBorder(currentTile.Map, rightCopy);
    }

    for (int i = 1; i < lastRotationLeft[0].size() - 1; i++)
    {
      for (int j = 1; j < lastRotationLeft.size() - 1; j++)
      {
        finalMap[i] += lastRotationLeft[i][j];
      }

    }

    // supposing there won't be a next right border
    foundNextRight = false;
    for (auto tile : allTiles)
    {
      if (foundNextRight)
      {
        break;
      }
      if (tile == currentTile || usedTiles.find(tile.ID) != usedTiles.end())
      {
        continue;
      }
      string border = right;
      string reversedBorder = right;
      reverse(reversedBorder.begin(), reversedBorder.end());

      for (auto nextBorder : tile.borders)
      {
        string reversedNextBorder = nextBorder;
        reverse(reversedNextBorder.begin(), reversedNextBorder.end());

        if (border == nextBorder || border == reversedNextBorder)
        {
          foundNextRight = true;
          currentTile = tile;
          break;
        }
      }
    }
  }

  for (auto i : finalMap)
  {
    if (i != "")
    {
      finalMatrix.push_back(i);
    }
  }
}


void SearchTilesDown(Tile currentTile, vector<Tile> allTiles)
{
  string bottom = currentTile.borders[0];
  bool foundNextDown = true;

  while (foundNextDown)
  {
    usedTiles.insert(currentTile.ID);

    string downCopy = bottom;
    bottom = getRotationsForBottomBorder(currentTile.Map, bottom);
    if (bottom == "")
    {
      currentTile.Map = flipMatrix(currentTile.Map);
      bottom = getRotationsForBottomBorder(currentTile.Map, downCopy);
    }
    currentTile.Map = lastRotationDown;
    SearchTilesToRight(currentTile, allTiles);

    // supposing there's no next tile to the bottom
    foundNextDown = false;
    for (auto tile : allTiles)
    {
      if (foundNextDown)
      {
        break;
      }
      if (tile == currentTile || usedTiles.find(tile.ID) != usedTiles.end())
      {
        continue;
      }

      string border = bottom;
      string reversedBorder = bottom;
      reverse(reversedBorder.begin(), reversedBorder.end());
      for (auto nextBorder : tile.borders)
      {
        string reversedNextBorder = nextBorder;
        reverse(reversedNextBorder.begin(), reversedNextBorder.end());
        if (border == nextBorder || border == reversedNextBorder)
        {
          foundNextDown = true;
          currentTile = tile;
          break;
        }
      }
    }
  }
}

int main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  string inputLine;
  int tileID;
  char ch;

  vector<Tile> allTiles;
  while (cin >> inputLine >> tileID >> ch)
  {
    Tile tile;
    tile.ID = tileID;

    getline(cin, inputLine); // cin empty line
    getline(cin, inputLine);

    vector<string> matrix;
    vector<string> borders;

    string lastLine;
    if (inputLine != "")
    {
      borders.push_back(inputLine);
    }

    while (inputLine != "")
    {
      matrix.push_back(inputLine);
      lastLine = inputLine;
      getline(cin, inputLine);
    }

    borders.push_back(lastLine);

    string borderLeft, borderRight;

    int n = matrix[0].size() - 1;
    for (int i = 0; i < matrix.size(); i++)
    {
      borderLeft += matrix[i][0];
      borderRight += matrix[i][n];
    }
    borders.push_back(borderLeft);
    borders.push_back(borderRight);
    tile.borders = borders;

    tile.Map = matrix;
    allTiles.push_back(tile);
  }

  vector<Tile> usedInTheQueueOfTiles;
  queue<Tile> queueOfTiles;
  queueOfTiles.push(allTiles[0]);

  Tile currentTile = queueOfTiles.front();
  usedInTheQueueOfTiles.push_back(currentTile);

  vector<Tile> linkedTiles;
  while (!queueOfTiles.empty())
  {
    currentTile = queueOfTiles.front();
    queueOfTiles.pop();
    for (auto& tile : allTiles)
    {
      if (tile == currentTile)
      {
        continue;
      }
      for (int i = 0; i < 4; i++)
      {
        string border = currentTile.borders[i];
        for (int j = 0; j < 4; j++)
        {
          string nextBorder = tile.borders[j];
          string reversedNextBorder = nextBorder;
          reverse(reversedNextBorder.begin(), reversedNextBorder.end());
          if (border == nextBorder || border == reversedNextBorder)
          {
            vector<string> tileMap = tile.Map;
            int rotation = 0;
            while (rotation < 4 && tileMap[0] != border)
            {
              rotation++;
              tileMap = rotateRight(tileMap);
            }
            if (tileMap[0] != border)
            {
              tileMap = flipMatrix(tileMap);
              rotation = 0;
              while (rotation < 4 && tileMap[0] != border)
              {
                rotation++;
                tileMap = rotateRight(tileMap);
              }
            }
            currentTile.isLinked[i] = 1;
            tile.isLinked[j] = 1;
            if (find(usedInTheQueueOfTiles.begin(), usedInTheQueueOfTiles.end(), tile) == usedInTheQueueOfTiles.end())
            {
              queueOfTiles.push(tile);
              usedInTheQueueOfTiles.push_back(tile);
            }
          }
        }
      }
    }
    linkedTiles.push_back(currentTile);
  }

  long long solutionPart1 = 1;

  vector<Tile>corners;
  for (Tile t : linkedTiles)
  {
    int nr = t.isLinked[0] + t.isLinked[1] + t.isLinked[2] + t.isLinked[3];
    if (nr == 2)
    {
      solutionPart1 *= t.ID;
      currentTile = t;
      corners.push_back(t);
    }
  }

  cout << "Part 1: " << solutionPart1 << endl;

  for (auto corner : corners)
  {
    if (corner.isLinked[0] == 0 && corner.isLinked[2] == 0)
    {
      currentTile = corner; // top left corner
    }
  }

  SearchTilesDown(currentTile, linkedTiles);

  //rotatong the map until it has sea monsters
  finalMatrix = rotateRight(finalMatrix);
  finalMatrix = flipMatrix(finalMatrix);
  finalMatrix = rotateRight(finalMatrix);
  finalMatrix = rotateRight(finalMatrix);

  int count = 0;
  for (auto i : finalMatrix)
  {
    cout << i << endl;
    for (auto j : i)
    {
      if (j == '#')
        count++;
    }
  }

  cout << "Number of #: " << count << endl;

  int numberOfSeaMonsters = 0;
  auto matrixWithSeaMonsters = finalMatrix;
  /*
    01234567891123456789
              0123456789

                      #
    #    ##    ##    ###
     #  #  #  #  #  #
*/
  for (int i = 0; i < finalMatrix[0].size() - 2; i++)
  {
    for (int j = 0; j < finalMatrix.size() - 19; j++)
    {
      if (j + 19 <= finalMatrix.size() && i + 2 <= finalMatrix.size() &&
        finalMatrix[i][j + 18] == '#' &&

        finalMatrix[i + 1][j] == '#' && finalMatrix[i + 1][j + 5] == '#' && finalMatrix[i + 1][j + 6] == '#' &&
        finalMatrix[i + 1][j + 11] == '#' && finalMatrix[i + 1][j + 12] == '#' &&
        finalMatrix[i + 1][j + 17] == '#' && finalMatrix[i + 1][j + 18] == '#' && finalMatrix[i + 1][j + 19] == '#' &&

        finalMatrix[i + 2][j + 1] == '#' && finalMatrix[i + 2][j + 4] == '#' && finalMatrix[i + 2][j + 7] == '#' &&
        finalMatrix[i + 2][j + 10] == '#' && finalMatrix[i + 2][j + 13] == '#' && finalMatrix[i + 2][j + 16] == '#')
      {
        matrixWithSeaMonsters[i][j + 18] = 'O';

        matrixWithSeaMonsters[i + 1][j] = 'O';
        matrixWithSeaMonsters[i + 1][j + 5] = 'O';
        matrixWithSeaMonsters[i + 1][j + 6] = 'O';

        matrixWithSeaMonsters[i + 1][j + 11] = 'O';
        matrixWithSeaMonsters[i + 1][j + 12] = 'O';
        matrixWithSeaMonsters[i + 1][j + 17] = 'O';
        matrixWithSeaMonsters[i + 1][j + 18] = 'O';
        matrixWithSeaMonsters[i + 1][j + 19] = 'O';

        matrixWithSeaMonsters[i + 2][j + 1] = 'O';
        matrixWithSeaMonsters[i + 2][j + 4] = 'O';
        matrixWithSeaMonsters[i + 2][j + 7] = 'O';

        matrixWithSeaMonsters[i + 2][j + 10] = 'O';
        matrixWithSeaMonsters[i + 2][j + 13] = 'O';
        matrixWithSeaMonsters[i + 2][j + 16] = 'O';
        numberOfSeaMonsters++;
      }
    }
  }

  int solutionPart2 = 0;
  for (auto i : matrixWithSeaMonsters)
  {
    for (auto j : i)
    {
      if (j == '#')
        solutionPart2++;
    }
  }

  cout << "\n\n\nSea monsters: \n";
  for (auto i : matrixWithSeaMonsters)
  {
    cout << i << endl;
  }

  cout << "Number of sea monsters: " << numberOfSeaMonsters << endl;
  cout << "Part 2: " << solutionPart2 << endl;
  return 0;
}