#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

struct ranges
{
  // a, b - first range; x, y - second range
  int a, b, x, y;

};
bool isNumberBetweenRanges(int number, ranges range)
{
  return number >= range.a && number <= range.b || number >= range.x && number <= range.y;
}
int main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);


  string inputLine;
  map <string, ranges> fieldsAndRanges;
  vector <string> fieldNames;

  getline(cin, inputLine);

  while (inputLine != "")
  {
    int i = inputLine.find(':');

    string field = inputLine.substr(0, i);
    fieldNames.push_back(field);

    ranges range;
    int j = i + 2;

    i = inputLine.find('-', j);
    range.a = stoi(inputLine.substr(j, i - j));

    j = i + 1;
    i = inputLine.find(' ', j);
    range.b = stoi(inputLine.substr(j, i - j));

    j = i + 4;
    i = inputLine.find('-', j);
    range.x = stoi(inputLine.substr(j, i - j));

    j = i + 1;
    range.y = stoi(inputLine.substr(j, inputLine.size() - j));

    fieldsAndRanges[field] = range;

    getline(cin, inputLine);
  }

  map < string, int> yourTicket;
  getline(cin, inputLine);

  // reading the ticket
  if (inputLine == "your ticket:")
  {
    getline(cin, inputLine);
    inputLine += ',';

    int j = 0;
    int i = inputLine.find(',', j);
    int fieldIndex = 0;
    while (i != string::npos) {
      yourTicket[fieldNames[fieldIndex++]] = stoi(inputLine.substr(j, i - j));
      j = i + 1;
      i = inputLine.find(',', j);
    }
    getline(cin, inputLine);
  }

  vector < map<string, int>> nearbyTickets;
  getline(cin, inputLine);

  // reading nearby tickets
  if (inputLine == "nearby tickets:") {
    while (getline(cin, inputLine)) {
      inputLine += ',';
      int j = 0;
      int i = inputLine.find(',', j);
      int index = 0;

      map<string, int> nearbyTicketFields;
      while (i != string::npos) {
        nearbyTicketFields[fieldNames[index++]] = stoi(inputLine.substr(j, i - j));
        j = i + 1;
        i = inputLine.find(',', j);
      }
      nearbyTickets.push_back(nearbyTicketFields);
    }
  }

  int numberOfInvalidTickets = 0;
  set<map<string, int>> invalidTickets;

  for (map<string, int> ticket : nearbyTickets)
  {
    for (auto ticketValue : ticket)
    {
      bool valid = false;
      for (auto range : fieldsAndRanges)
      {
        if (isNumberBetweenRanges(ticketValue.second, range.second))
        {
          valid = true;
        }
      }
      if (!valid)
      {
        numberOfInvalidTickets += ticketValue.second;
        invalidTickets.insert(ticket);
      }
    }
  }

  set<map<string, int>> validTickets;
  for (auto ticket : nearbyTickets)
  {
    if (invalidTickets.find(ticket) == invalidTickets.end())
    {
      validTickets.insert(ticket);
    }
  }

  map<string, set<string>> possibleMappings;
  map<string, string> finalMapping;
  set<string> usedKeys, usedValues; // used field name, used mapping value for the field name

  for (auto fieldName : fieldNames)
  {
    for (auto anotherFieldName : fieldNames)
    {
      bool isMappingValid = true;
      for (auto ticket : validTickets)
      {
        int  ticketValue = ticket[fieldName];
        auto ranges = fieldsAndRanges[anotherFieldName];
        // for each ticket check if it's field can be map to another field
        if (!isNumberBetweenRanges(ticketValue, ranges))
        {
          isMappingValid = false;
          break;
        }
      }
      if (isMappingValid)
      {
        // the mapping is valid
        possibleMappings[fieldName].insert(anotherFieldName);
      }
    }
  }

  while (!possibleMappings.empty())
  {
    set<string> toRemove;
    for (auto field : fieldNames)
    {
      // if there's only one mapping for a field
      if (possibleMappings[field].size() == 1)
      {
        finalMapping[field] = *possibleMappings[field].begin();
        // the mapping will be a final mapping and will be removed from the possible mappings
        toRemove.insert(*possibleMappings[field].begin());
      }
      else
      {
        // if there's no mapping left for a field, the mapping will be removed from the possible mappings
        if (possibleMappings[field].empty())
        {
          possibleMappings.erase(field);
        }
      }
    }


    for (auto mapping : finalMapping)
    {
      possibleMappings.erase(mapping.first);
    }

    for (auto& mapping : possibleMappings)
    {
      for (auto removed : toRemove)
      {
        mapping.second.erase(removed);
      }
    }
  }

  unsigned long long multiplication = 1;
  for (auto field : fieldNames)
  {
    if (finalMapping[field].find("departure") != string::npos)
    {
      multiplication *= yourTicket[field];
    }
  }

  cout << "Part 1: " << numberOfInvalidTickets << endl;
  cout << "Part 2: " << multiplication << endl;

  return 0;
}