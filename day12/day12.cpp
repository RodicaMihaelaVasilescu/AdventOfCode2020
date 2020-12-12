#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>

using namespace std;
//             0  1  2  3
//             N  S  E  W                          
int lin[] = { -1, 1, 0, 0 };
int col[] = { 0,  0, 1, -1 };
int main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  char s;
  int n;

  int i = 0, j = 0;
  int north_south = -1;
  int east_west = 10;

  while (cin >> s >> n)
  {
    if (s == 'F')
    {
      i += n * north_south;
      j += n * east_west;
    }
    else
      if (s == 'N')
      {
        north_south -= n;
      }
      else if (s == 'S')
      {
        north_south += n;
      }
      else if (s == 'E')
      {
        east_west += n;
      }
      else if (s == 'W')
      {
        east_west -= n;
      }
      else
      {
        if (s == 'R' && n == 90 || s == 'L' && n == 270)
        {
          north_south *= -1;
          swap(north_south, east_west);

        }
        else if (s == 'R' && n == 270 || s == 'L' && n == 90)
        {
          east_west *= -1;
          swap(north_south, east_west);

        }
        else if (s == 'R' && n == 180 || s == 'L' && n == 180)
        {
          // Obs: when it's 180 degree rotation, the north and east directions will have the opposite sign
          north_south *= -1;
          east_west *= -1;
        }
      }
  }
  cout << "Part 2: " << abs(i) + abs(j) << endl;


  return 0;
}