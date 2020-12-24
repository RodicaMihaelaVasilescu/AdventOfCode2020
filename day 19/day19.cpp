#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>

using namespace std;

set<string> computeSolution(multimap<int, vector<int>> allRules, unordered_map<int, string> rules, int start = 0)
{
  set<string> messages;

  auto range = allRules.equal_range(start);
  for (auto i = range.first; i != range.second; i++)
  {
    vector<int> vectorOfRules = i->second;
    vector<string> currentMessages;
    for (auto ruleID : vectorOfRules)
    {
      if (rules[ruleID] != "")
      {
        if (currentMessages.empty())
        {
          currentMessages.push_back(rules[ruleID]);
        }
        else
        {
          for (auto& element : currentMessages)
          {
            element += rules[ruleID];
          }
        }
      }
      else
      {
        set<string> setFromRecursion = computeSolution(allRules, rules, ruleID);
        if (currentMessages.empty())
        {
          for (auto f : setFromRecursion)
          {
            currentMessages.push_back(f);
          }
        }
        else
        {
          if (setFromRecursion.empty())
          {
            for (auto c : currentMessages)
            {
              messages.insert(c);
            }
          }
          else {
            set<string> temp;
            for (auto a : currentMessages)
            {
              for (auto b : setFromRecursion)
              {
                temp.insert(a + b);
              }
            }
            for (auto it : temp)
            {
              currentMessages.push_back(it);
            }
          }
        }
      }
    }

    for (auto c : currentMessages)
    {
      messages.insert(c);
    }
  }
  return messages;

}
int main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  string line;
  multimap<int, vector<int>> allRules;
  unordered_map<int, string> rulesValues;

  while (getline(cin, line)) {
    if (line.empty())
    {
      break;
    }
    int i = line.find(':');
    int ruleID = stoi(line.substr(0, i));
    if (line[i + 2] == '"')
    {
      rulesValues[ruleID] = line[i + 3];
    }
    else
    {
      line += ' ';
      int j = i + 2;
      i = line.find(' ', i + 2);
      vector<int> vectorOfRules;
      string numberToString;
      while (i != string::npos)
      {
        numberToString = line.substr(j, i - j);
        if (numberToString == "|")
        {
          allRules.insert({ ruleID,vectorOfRules });
          vectorOfRules.clear();
        }
        else
        {
          vectorOfRules.push_back(stoi(numberToString));
        }
        j = i + 1;
        i = line.find(' ', i + 1);
      }
      allRules.insert({ ruleID,vectorOfRules });
    }
  }
  auto  answer = computeSolution(allRules, rulesValues);

  int count = 0;
  while (getline(cin, line))
  {
    if (find(answer.begin(), answer.end(), line) != answer.end())
    {
      count++;
    }
  }
  cout << "Part 1: " << count;

  return 0;
}
