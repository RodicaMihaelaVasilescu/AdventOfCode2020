#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>

using namespace std;
int main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  int preamble = 25;
  vector <int> numbers;
  int n, offset = 0, solution = 0;

  for (int i = 0; i < preamble; i++)
  {
    cin >> n;
    numbers.push_back(n);
  }

  offset = 0;
  while (cin >> n)
  {
    bool valid = false;
    for (int i = offset; i < numbers.size(); i++)
    {
      for (int j = i + 1; j < numbers.size(); j++)
      {
        if (numbers[i] + numbers[j] == n)
        {
          valid = true;
        }
      }
    }

    offset++;
    numbers.push_back(n);

    if (!valid)
    {
      cout << "Part 1: " << n << endl;
      solution = n;
    }
  }

  for (int i = 0; i < numbers.size(); i++)
  {
    int sum = 0, Min = INT_MAX, Max = 0;
    for (int j = i; j < numbers.size() && sum < solution; j++)
    {
      Min = min(numbers[j], Min);
      Max = max(numbers[j], Max);
      sum += numbers[j];
      if (sum == solution && numbers[j] != solution)
      {
        cout << "Part 2: " << Min + Max << endl;
      }
    }
  }

  return 0;
}