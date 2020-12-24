#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

//            0  1  2  3
//            E  S  W  N                          
int lin[] = { 0, 1, 0,-1 };
int col[] = { 1, 0,-1, 0 };

map<char, int> CharToInt{ {'E',0}, {'S',1}, {'W',2}, {'N',3} };

/*
           (-)
            N
            ^
            |
  (-) W <---+---> E (+)
            |
            v
            S
           (+)
*/

int main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  //The ship starts by facing east
  int direction = CharToInt['E'];

  pair<int, int> point1, point2;

  // the waypoint starts 1 unit north (-) and 10 units east (+)
  pair<int, int> waypoint(-1, 10);

  char s;
  int n;
  while (cin >> s >> n)
  {
    if (s == 'F')
    {
      //---------------- 1st part -------------------
      point1.first += n * lin[direction];
      point1.second += n * col[direction];
      //---------------- 2nd part -------------------
      point2.first += n * waypoint.first;
      point2.second += n * waypoint.second;
    }
    else if (s == 'E' || s == 'S' || s == 'W' || s == 'N')
    {
      //---------------- 1st part -------------------
      point1.first += n * lin[CharToInt[s]];
      point1.second += n * col[CharToInt[s]];
      //---------------- 2nd part -------------------
      waypoint.first += n * lin[CharToInt[s]];
      waypoint.second += n * col[CharToInt[s]];
    }
    // right rotation
    else  if (s == 'R' && n == 90 || s == 'L' && n == 270)
    {
      //---------------- 1st part -------------------
      ++direction %= 4;
      //---------------- 2nd part -------------------
      waypoint.first *= -1;
      swap(waypoint.first, waypoint.second);
    }
    // left rotation
    else if (s == 'L' && n == 90 || s == 'R' && n == 270)
    {
      //---------------- 1st part -------------------
      if (--direction < 0)
      {
        direction = 3;
      }
      //---------------- 2nd part -------------------
      waypoint.second *= -1;
      swap(waypoint.first, waypoint.second);
    }
    // 180 rotation
    else if (s == 'R' && n == 180 || s == 'L' && n == 180)
    {
      //---------------- 1st part -------------------
      direction += 2;
      direction %= 4;
      //---------------- 2nd part -------------------
      waypoint.first *= -1;
      waypoint.second *= -1;
    }
  }

  cout << "Part 1: " << abs(point1.first) + abs(point1.second) << endl;
  cout << "Part 2: " << abs(point2.first) + abs(point2.second) << endl;

  return 0;
}