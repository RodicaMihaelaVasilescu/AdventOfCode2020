#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);


  set<string> ingredientsSet;
  set<string> allergensSet;
  map<string, set<string>> allergen_possibleMappings;
  vector<string> allIngredients;

  string element;
  bool isIngredient = true;
  bool isFirstIngredient = true;

  while (cin >> element)
  {
    if (element == "(contains")
    {
      isIngredient = false;
    }
    else if (isIngredient)
    {
      if (isFirstIngredient)
      {
        isFirstIngredient = false;
      }
      allIngredients.push_back(element);
      ingredientsSet.insert(element);
    }
    else if (element[element.size() - 1] == ',' || element[element.size() - 1] == ')')
    {
      allergensSet.insert(element.substr(0, element.size() - 1));

      if (element[element.size() - 1] == ')')
      {
        for (auto allergen : allergensSet)
        {
          if (allergen_possibleMappings[allergen].empty())
          {
            allergen_possibleMappings[allergen] = ingredientsSet;
          }
          else
          {
            //get common from allergen_possibleMappings[allergen] and ingredientsSet;
            set<string> possibleIngredients = allergen_possibleMappings[allergen];
            set<string> commonIngredients;

            for (auto ingredient : possibleIngredients)
            {
              if (find(ingredientsSet.begin(), ingredientsSet.end(), ingredient) != ingredientsSet.end())
              {
                commonIngredients.insert(ingredient);
              }
            }
            allergen_possibleMappings[allergen] = commonIngredients;
          }
        }
        ingredientsSet.clear();
        allergensSet.clear();
        isFirstIngredient = true;
        isIngredient = true;
      }
    }

  }

  map<string, string> allergen_ingredient;
  map<string, string> ingredient_allergen;
  while (!allergen_possibleMappings.empty())
  {
    vector <string> toRemove;
    for (auto allergenMapping : allergen_possibleMappings)
    {
      //there's only one possible mapping of allergent with ingredient
      if (allergenMapping.second.size() == 1)
      {
        auto allergen = allergenMapping.first;
        auto ingredient = *allergenMapping.second.begin();

        allergen_ingredient[allergen] = ingredient;
        ingredient_allergen[ingredient] = allergen;
        toRemove.push_back(allergen);
      }
      if (allergenMapping.second.size() == 0)
      {
        toRemove.push_back(allergenMapping.first);
      }
    }

    for (auto allergenToRemove : toRemove)
    {
      allergen_possibleMappings.erase(allergenToRemove);
    }
    for (auto& allergenToRemove : allergen_possibleMappings)
    {
      for (auto j : toRemove)
      {
        allergenToRemove.second.erase(allergen_ingredient[j]);
      }
    }
  }

  int solutionPart1 = 0;
  for (auto ingredient : allIngredients)
  {
    if (ingredient_allergen[ingredient] == "")
    {
      solutionPart1++;
    }
  }
  cout << "Part 1: " << solutionPart1 << endl;

  string solutionPart2;
  for (auto m : allergen_ingredient)
  {
    solutionPart2 += m.second + ",";
  }

  cout << "Part 2: " << solutionPart2.substr(0, solutionPart2.size() - 1) << endl;
  return 0;
}