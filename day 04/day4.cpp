#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

#define BYR "byr"
#define IYR "iyr"
#define EYR "eyr"
#define HGT "hgt"
#define HCL "hcl"
#define ECL "ecl"
#define PID "pid"
#define CID "cid"

string myFind1(string value, string inputLine, string fieldName)
{
  if (value != "")
  {
    return value;
  }
  auto fieldValuePosition = inputLine.find(fieldName);
  if (fieldValuePosition != string::npos)
  {
    fieldValuePosition += fieldName.length() + 1;
    auto delimiterPosition = inputLine.find(" ", fieldValuePosition);
    return inputLine.substr(fieldValuePosition, delimiterPosition - fieldValuePosition);
  }
  else return "";
}

string myFind2(string value, string inputLine, string fieldName)
{
  if (value != "")
  {
    return value;
  }

  auto fieldValuePosition = inputLine.find(fieldName);

  if (fieldValuePosition != std::string::npos)
  {
    fieldValuePosition += fieldName.length() + 1;
    auto delimiterPosition = inputLine.find(" ", fieldValuePosition);
    value = inputLine.substr(fieldValuePosition, delimiterPosition - fieldValuePosition);

    if (fieldName == BYR)
    {
      // byr(Birth Year) - four digits; at least 1920 and at most 2002.
      for_each(value.begin(), value.end(), [](char ch) { if (!isdigit(ch)) return ""; });
      int year = stoi(value);
      return year >= 1920 && year <= 2002 ? value : "";
    }
    else if (fieldName == IYR)
    {
      // iyr(Issue Year) - four digits; at least 2010 and at most 2020.
      for_each(value.begin(), value.end(), [](char ch) { if (!isdigit(ch)) return ""; });
      int year = stoi(value);
      return year >= 2010 && year <= 2020 ? value : "";
    }
    if (fieldName == EYR)
    {
      // eyr(Expiration Year) - four digits; at least 2020 and at most 2030.
      for_each(value.begin(), value.end(), [](char ch) { if (!isdigit(ch)) return ""; });
      int year = stoi(value);
      return year >= 2020 && year <= 2030 ? value : "";
    }
    if (fieldName == HGT)
    {
      // hgt(Height) - a number followed by either cm or in:
      //        If cm, the number must be at least 150 and at most 193.
      //        If in, the number must be at least 59 and at most 76.
      if (value.size() < 4)
      {
        return "";
      }
      for_each(value.begin(), value.end() - 2, [](char ch) { if (!isdigit(ch)) return ""; });

      string unit = value.substr(value.length() - 2, 2);
      if (unit != "cm" && unit != "in")
      {
        return "";
      }

      int height = stoi(value.substr(0, value.size() - 2));
      if (unit == "cm" && height >= 150 && height <= 193 ||
        unit == "in" && height >= 59 && height <= 76)
      {
        return value;
      }

      return "";
    }
    else if (fieldName == HCL)
    {
      // hcl (Hair Color) - a # followed by exactly six characters 0-9 or a-f.
      if (value[0] != '#' || value.size() != 7)
      {
        return "";
      }

      for (int i = 1; i < value.size(); i++)
      {
        char ch = value[i];
        if (!isdigit(ch) && !(ch >= 'a' && ch <= 'f'))
        {
          return "";
        }
        return value;
      }
    }
    else if (fieldName == ECL)
    {
      //ecl (Eye Color) - exactly one of: amb blu brn gry grn hzl oth.
      if (value != "amb" && value != "blu" && value != "brn" && value != "gry" && value != "grn" && value != "hzl" && value != "oth")
      {
        return "";
      }
      return value;
    }
    else if (fieldName == PID)
    {
      // pid(Passport ID) - a nine - digit number, including leading zeroes.
      if (value.size() != 9)
      {
        return "";
      }
      for_each(value.begin(), value.end(), [](char ch) { if (!isdigit(ch)) return ""; });
      return value;
    }
    return value;
  }
  else return "";
}

int main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  string inputLine;
  map<string, string> PassportPart1;
  map<string, string> PassportPart2;
  vector <string> passportFields = { BYR, IYR,EYR, HGT, HCL, ECL, PID, CID };

  int solution1 = 0, solution2 = 0;
  while (getline(cin, inputLine))
  {
    if (inputLine != "")
    {
      inputLine += " ";
      bool valid = true;
      for (auto p : passportFields)
      {
        PassportPart1[p] = myFind1(PassportPart1[p], inputLine, p);
        PassportPart2[p] = myFind2(PassportPart2[p], inputLine, p);
      }
    }
    else
    {
      bool isValid1 = true, isValid2 = true;

      for (auto field : passportFields)
      {
        if (field != CID)
        {
          if (PassportPart1[field] == "")
          {
            isValid1 = false;
          }
          if (PassportPart2[field] == "")
          {
            isValid2 = false;
          }
        }
      }

      if (isValid1)
      {
        solution1++;
      }
      if (isValid2)
      {
        solution2++;
      }
      PassportPart1.clear();
      PassportPart2.clear();
    }
  }

  cout << "Part 1: " << solution1 << endl;
  cout << "Part 2: " << solution2 << endl;

  return 0;
}