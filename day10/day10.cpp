#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

int main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  vector <int> jolts;
  jolts.push_back(0);

  int adapter, MaxAdapter = 0;

  while (cin >> adapter)
  {
    MaxAdapter = max(MaxAdapter, adapter);
    jolts.push_back(adapter);
  }

  jolts.push_back(MaxAdapter + 3);
  sort(jolts.begin(), jolts.end());

  int oneJoltDiff = 0, threeJoltsDiff = 0;
  for (int i = 1; i < jolts.size(); i++)
  {
    if (jolts[i] - jolts[i - 1] == 1)
    {
      oneJoltDiff++;
    }
    else if (jolts[i] - jolts[i - 1] <= 3)
    {
      threeJoltsDiff++;
    }
  }

  cout << "Part 1: " << oneJoltDiff * threeJoltsDiff << endl;

  jolts.push_back(jolts[jolts.size() - 1] + 3);

  //number of distinct ways you can arrange the adapters
  map <int, long long> numberOfDistinctWays;
  numberOfDistinctWays[0] = 1;

  for (int i = 0; i < jolts.size(); i++)
  {
    for (int j = i + 1; j < jolts.size() && jolts[j] - jolts[i] <= 3; j++)
    {
      numberOfDistinctWays[j] += numberOfDistinctWays[i];
    }
  }

  cout << "Part 2: " << numberOfDistinctWays[jolts.size() - 1] << endl;
}