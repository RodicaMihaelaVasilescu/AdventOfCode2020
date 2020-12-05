#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

#define FRONT 'F'
#define BACK 'B'
#define LEFT 'L'
#define RIGHT 'R'

int main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  string inputLine;
  int Max = 0, Min = 1000;
  int SeatIDsFrequency[1000]{};

  while (getline(cin, inputLine))
  {
    int front = 0, back = 127;
    int left = 0, right = 7;
    char lastFrontBack, lastLeftRight;

    for (char direction : inputLine)
    {
      if (direction == FRONT)
      {
        back = (front + back) / 2;
        lastFrontBack = direction;
      }
      else  if (direction == BACK)
      {
        front = ((front + back) / 2 + 1);
        lastFrontBack = direction;
      }
      if (direction == LEFT)
      {
        right = (left + right) / 2;
        lastLeftRight = direction;
      }
      else  if (direction == RIGHT)
      {
        left = ((left + right) / 2 + 1);
        lastLeftRight = direction;
      }
    }

    int seatID = 8; // the 8 columns
    seatID *= lastFrontBack == FRONT ? front : back; // row
    seatID += lastLeftRight == LEFT ? left : right; // column

    SeatIDsFrequency[seatID]++;

    Min = min(seatID, Min);
    Max = max(seatID, Max);
  }

  cout << "Part 1: " << Max << endl;
  for (int i = Min; i <= Max; i++)
  {
    if (SeatIDsFrequency[i] == 0)
    {
      cout << "Part 2: " << i << endl;
    }
  }

  return 0;
}
