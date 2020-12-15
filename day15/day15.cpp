// warning: this solution takes about 10 seconds in the release mode..

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

int main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  long n;
  char delimiter;
  unordered_map<long, long> last1;
  unordered_map<long, long> last2;

  long  index = 1;

  string line;
  cin >> line;
  line += ',';

  int i = 0;
  int j = line.find(',');

  while (j != string::npos)
  {
    n = stoi(line.substr(i, j - i));
    i = j + 1;
    j = line.find(',', i);

    if (last1[n] == 0)
    {
      last1[n] = index;
    }
    else
    {
      last2[index] = last1[index];
      last1[index] = n;
    }

    index++;
  }

  while (index <= 30000000)
  {
    if (last2[n] == 0)
    {
      n = 0;
      last2[n] = last1[n];
      last1[n] = index;
    }
    else
      if (last2[n] == 0)
      {
        long  x = index - last1[x];
        last2[n] = last1[n];
        last1[n] = index;

        if (last1[x] == 0)
        {
          last1[x] = index;
        }
        else
        {
          last2[x] = last1[x];
          last1[x] = index;
        }
      }
      else
      {
        n = last1[n] - last2[n];
        if (last1[n] == 0)
        {
          last1[n] = index;
        }
        else
        {
          last2[n] = last1[n];
          last1[n] = index;
        }
      }
    if (index == 2020)
    {
      cout << "Part 1: " << n << endl;
    }
    if (index == 30000000)
    {
      cout << "Part 2: " << n << endl;
    }
    index++;
  }

  return 0;
}