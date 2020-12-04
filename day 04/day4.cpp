#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct passport {
  string   byr;
  string   iyr;
  string   eyr;
  string   hgt;
  string   hcl;
  string   ecl;
  string   pid;
  string   cid;
};

string myFind(string s, string substr)
{
  auto found = s.find(substr);

  if (found != std::string::npos)
  {
    int x = s.find(" ", found + 3);
    int y = x - found - 4;
    string i = s.substr(found + 4, y);
    if (substr == "byr")
    {
      for (int j = 0; j < i.size(); j++)
      {
        if (i[j] < '0' || i[j]>'9')
        {
          return"";
        }
      }
      int y = stoi(i);
      if (y < 1920 || y> 2002)
        return"";

    }
    if (substr == "iyr")
    {
      for (int j = 0; j < i.size(); j++)
      {
        if (i[j] < '0' || i[j]>'9')
        {
          return"";
        }
      }
      int y = stoi(i);
      if (y < 2010 || y> 2020)
        return"";

    }
    if (substr == "eyr")
    {
      for (int j = 0; j < i.size(); j++)
      {
        if (i[j] < '0' || i[j]>'9')
        {
          return"";
        }
      }
      int y = stoi(i);
      if (y < 2010 || y> 2030)
        return"";

    }
    if (substr == "hgt")
    {
      for (int j = 0; j < i.size() - 2; j++)
      {
        if (i[j] < '0' || i[j]>'9' || j > 3)
        {
          return"";
        }
      }
      if (i[i.size() - 2] != 'i' && i[i.size() - 2] != 'c')
        return "";
      int y = stoi(i.substr(0, i.size() - 2));
      if (i[i.size() - 2] == 'c' && i[i.size() - 1] == 'm')
      {

        if (y < 150 || y> 193)
          return"";
      }
      else if (i[i.size() - 2] == 'i' && i[i.size() - 1] == 'n')

      {
        if (y < 59 || y> 76)
          return"";
      }

    }

    if (substr == "hcl")
    {
      if (i[0] != '#' || i.size() != 7)
      {
        return "";
      }
      for (x = 1; x < i.size(); x++)
      {
        char ch = i[x];
        bool a = (ch >= '0' && ch <= '9');
        if (!a && !(ch >= 'a' && ch <= 'f'))
          return "";
      }
    }

    if (substr == "ecl")
    {
      if (i != "amb" && i != "blu" && i != "brn" && i != "gry" && i != "grn" && i != "hzl" && i != "oth")
        return"";
    }
    if (substr == "pid")
    {
      if (i.size() != 9)
        return"";
      for (x = 0; x < i.size(); x++)
      {
        if (!(i[x] >= '0' && i[x] <= '9'))
          return "";
      }

    }

    return i;
  }
  else return "";
}

int main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  vector<string> v;
  string s;
  passport p;
  int solution = 0;
  while (getline(cin, s))
  {
    if (s != "")
    {
      s += " ";
      bool valid = true;
      if (p.byr == "") p.byr = myFind(s, "byr");
      if (p.iyr == "") p.iyr = myFind(s, "iyr");
      if (p.eyr == "") p.eyr = myFind(s, "eyr");
      if (p.hgt == "") p.hgt = myFind(s, "hgt");
      if (p.hcl == "") p.hcl = myFind(s, "hcl");
      if (p.ecl == "") p.ecl = myFind(s, "ecl");
      if (p.pid == "") p.pid = myFind(s, "pid");
      if (p.cid == "") p.cid = myFind(s, "cid");
    }
    else
    {
      passport newPassport;

      if (p.byr == "" || p.iyr == "" || p.eyr == "" || p.hgt == "" ||
        p.hcl == "" || p.ecl == "" || p.pid == "" /*|| p.cid == ""*/)
      {
        //it's invalid
      }
      else
        solution++;
      p = newPassport;
    }

  }

  cout << solution;

  return 0;
}
