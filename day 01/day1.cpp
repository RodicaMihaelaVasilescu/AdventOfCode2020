#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <set>

using namespace std;

int main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  int n;
  set<int> numbers;
  while (cin >> n)
  {
    if (numbers.find(2020 - n) != numbers.end())
    {
      cout << "Part 1: " << n * (2020 - n) << endl;
    }
    numbers.insert(n);
  }

  for (auto i : numbers)
  {
    for (auto j : numbers)
    {
      if (numbers.find((2020 - i - j)) != numbers.end())
      {
        cout << "Part 2: " << i * j * (2020 - i - j) << endl;
        return 0;
      }
    }
  }

}
