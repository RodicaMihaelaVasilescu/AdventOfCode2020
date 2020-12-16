#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

struct betweenRange
{
  int i, j, i2, j2;

};
bool isValid(int x, betweenRange r)
{
  return x >= r.i && x <= r.j || x >= r.i2 && x <= r.j2;
}
int main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);


  string inputLine;
  map <string, betweenRange> fieldsAndRanges;
  vector <string> fields;

  getline(cin, inputLine);

  while (inputLine != "")
  {
    int i = inputLine.find(':');
    string field = inputLine.substr(0, i);
    fields.push_back(field);
    betweenRange b;
    int j = i + 2;

    i = inputLine.find('-', j);
    string x = inputLine.substr(j, i - j);
    b.i = stoi(inputLine.substr(j, i - j));

    j = i + 1;
    i = inputLine.find(' ', j);
    b.j = stoi(inputLine.substr(j, i - j));

    j = i + 4;
    i = inputLine.find('-', j);
    b.i2 = stoi(inputLine.substr(j, i - j));

    j = i + 1;
    b.j2 = stoi(inputLine.substr(j, inputLine.size() - j));

    fieldsAndRanges[field] = b;

    getline(cin, inputLine);
  }

  map < string, int> yourTicket;
  getline(cin, inputLine);
  if (inputLine == "your ticket:")
  {
    getline(cin, inputLine);
    inputLine += ',';
    int j = 0;
    int i = inputLine.find(',', j);
    string x = inputLine.substr(j, i - j);
    int index = 0;
    while (i != string::npos) {
      yourTicket[fields[index++]] = stoi(inputLine.substr(j, i - j));
      j = i + 1;
      i = inputLine.find(',', j);
    }
    getline(cin, inputLine);
  }

  vector < map<string, int>> nearbyTickets;
  getline(cin, inputLine);
  if (inputLine == "nearby tickets:") {
    while (getline(cin, inputLine)) {
      inputLine += ',';
      int j = 0;
      int i = inputLine.find(',', j);
      string x = inputLine.substr(j, i - j);
      int index = 0;
      map<string, int> nearbyTicketFields;
      while (i != string::npos) {
        nearbyTicketFields[fields[index++]] = stoi(inputLine.substr(j, i - j));
        j = i + 1;
        i = inputLine.find(',', j);
      }
      nearbyTickets.push_back(nearbyTicketFields);
    }
  }

  int sum = 0;
  set<map<string, int>> invalidTickets;
  for (map<string, int> ticket : nearbyTickets)
  {
    for (auto ticketValue : ticket)
    {
      bool valid = false;
      for (auto range : fieldsAndRanges)
      {
        if (isValid(ticketValue.second, range.second))
        {
          valid = true;
        }
      }
      if (!valid)
      {
        sum += ticketValue.second;
        invalidTickets.insert(ticket);
      }
    }

  }

  set<map<string, int>> validTickets;
  for (auto i : nearbyTickets)
  {
    if (invalidTickets.find(i) == invalidTickets.end())
    {
      validTickets.insert(i);
    }
  }

  cout << sum;

}