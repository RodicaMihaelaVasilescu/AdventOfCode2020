#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

using namespace std;

int main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  int n;
  vector<int> numbers;
  while (cin >> n)
  {
    if (find(numbers.begin(), numbers.end(), 2020 - n) != numbers.end())
    {
      cout << "Part 1: " << n * (2020 - n) << endl;
    }
    numbers.push_back(n);
  }

  for (int i = 0; i < numbers.size() - 2; i++)
  {
    for (int j = i + 1; j < numbers.size() - 1; j++)
    {
      auto z = find(numbers.begin() + j+1, numbers.end(), 2020 - numbers[i] - numbers[j]);

      if (z != numbers.end())
      {
        cout << "Part 2: " << numbers[i] * numbers[j] * (2020 - numbers[i] - numbers[j]) << endl;
        return 0;
      }
    }
  }

}
