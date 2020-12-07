#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

map<string, vector<pair<int, string>>> TypeQuantity;

int sum = 0;
set<string> bags;
set<string> visitedBags;
bool visited = false;
int dfs1(string containerType)
{
  if (bags.find(containerType) != bags.end() || containerType == "shiny gold")
  {
    return 1;
  }
  if (visitedBags.find(containerType) != visitedBags.end())
  {
    return 0;
  }
  visitedBags.insert(containerType);
  for (auto val : TypeQuantity[containerType])
  {
    if (bags.find(val.second) != bags.end())
    {
      bags.insert(containerType);
      return 1;
    }
    if (visitedBags.find(val.second) == visitedBags.end())
    {
      if (dfs1(val.second))
      {
        bags.insert(containerType);
        return 1;
      }
    }
  }
  return 0;
}
int dfs2(string containerType, int q = 1)
{
  auto h = TypeQuantity[containerType];
  for (auto val : TypeQuantity[containerType])
  {
    if (val.first == 0)
      continue;
    sum += (q * val.first);
    dfs2(val.second, q * val.first);

  }
  return sum;
}

int main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  string inputLine;
  string input;
  string type;
  string containerType;
  bool isQuantity = false;
  bool isContainerQuantity = false;
  int quantity;
  bool isContainer = true;

  while (cin >> input)
  {

    if (isContainerQuantity)
    {
      quantity = stoi(input);
      isContainerQuantity = false;
      containerType = containerType.substr(0, containerType.size() - 1);
      isQuantity = true;
      continue;
    }
    if (isQuantity)
    {
      if (input == "no")
      {
        quantity = 0;
      }
      else
        quantity = stoi(input);

      isQuantity = false;
      continue;
    }
    if (input == "contain")
    {
      containerType = containerType.substr(0, containerType.size() - 1);
      isQuantity = true;
      isContainer = false;
      continue;
    }

    if (input.find(",") != string::npos)
    {
      type = type.substr(0, type.length() - 1);

      TypeQuantity[containerType].push_back(make_pair(quantity, type));
      isQuantity = true;
      type = "";
      continue;
    }
    if (input.find(".") != string::npos)
    {
      type = type.substr(0, type.length() - 1);
      TypeQuantity[containerType].push_back(make_pair(quantity, type));
      isContainer = true;
      containerType = "";
      type = "";
      quantity = 0;
      isQuantity = false;

      continue;

    }
    if (input == "bags")
    {
      continue;
    }
    if (isContainer)
    {
      containerType += input;
      containerType += " ";

    }
    else
    {
      type += input;
      type += " ";
    }
  }
  int bagsContainingShinyGoldBags = 0;
  for (auto m : TypeQuantity)
  {
    if (m.first != "shiny gold")
    {
      bagsContainingShinyGoldBags += dfs1(m.first);
    }
  }
  cout << "Part 1: " << bagsContainingShinyGoldBags << endl;
  cout << "Part 2: " << dfs2("shiny gold") << endl;
  return 0;
}