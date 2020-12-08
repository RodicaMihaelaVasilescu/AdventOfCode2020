#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>

using namespace std;
int f(vector <pair<string, int>> v)
{
  vector<bool> visited(v.size(), 0);
  long long acc = 0;
  for (int i = 0; i != v.size(); i++)
  {
    if (visited[i])
    {
      return acc;
    }
    visited[i] = 1;

    string instr = v[i].first;
    int val = v[i].second;

    if (instr == "nop")
    {
      continue;
    }
    else if (instr == "acc")
    {
      acc += val;
    }
    else if (instr == "jmp")
    {
      i += val - 1;
    }
  }
  cout << "Part 2: " << acc << endl;
  return acc;
}
int main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  string instr;
  int value;
  vector <pair<string, int>> instructions;

  while (cin >> instr)
  {
    cin >> value;
    instructions.push_back({ instr,value });
  }

  cout << "Part 1: " << f(instructions) << endl;

  for (auto& i : instructions)
  {
    if (i.first == "jmp")
    {
      i.first = "nop";
    }
    else if (i.first == "nop")
    {
      i.first = "jmp";
    }

    f(instructions);

    if (i.first == "jmp")
    {
      i.first = "nop";
    }
    else if (i.first == "nop")
    {
      i.first = "jmp";
    }
  }

  return 0;
}