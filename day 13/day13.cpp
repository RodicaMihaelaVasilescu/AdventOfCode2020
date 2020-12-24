#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include "MyLongLong.h"

using namespace std;

struct MyTuple
{
  MyLongLong X, Y, Z;
};

MyTuple euclid(MyLongLong  a, MyLongLong  b) {

  MyTuple t;
  if (a == 0)
  {
    return MyTuple{ b, 0, 1 };
  }
  else
  {
    t = euclid(b % a, a);
    swap(t.Y, t.Z);
    t.Y = t.Y - ((b / a)) * t.Z;
    return t;
  }
}

MyLongLong euclidModulo(MyLongLong a, MyLongLong b)
{
  MyTuple t = euclid(a, b);
  MyLongLong result = t.Y % b;
  if (result < 0)
  {
    result = max(t.Y, b) + result;
  }
  return result;
}


MyLongLong ChineseRemainderTheorem(vector<MyLongLong > busID, vector<MyLongLong > time)
{
  while (true) {

    MyLongLong a = euclidModulo(busID[1], busID[0]) * time[0] * busID[1] + euclidModulo(busID[0], busID[1]) * busID[0] * time[1];
    MyLongLong b = busID[0] * busID[1];

    time = vector<MyLongLong >(time.begin() + 2, time.end());

    time.insert(time.begin(), a % b);

    busID = vector<MyLongLong >(busID.begin() + 2, busID.end());
    busID.insert(busID.begin(), b);

    if (time.size() == 1)
    {
      break;
    }
  }
  return  time[0];
}

int main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  int initialTimestamp;
  cin >> initialTimestamp;
  string  line;
  cin >> line;
  vector<MyLongLong> buses, time;
  line += ",";
  int it1 = line.find(',');
  int it2 = 0;
  int index = 0;
  while (it1 != string::npos)
  {
    string stringID = line.substr(it2, it1 - it2);
    if (stringID != "x")
    {
      int intID = stoi(stringID);
      buses.push_back(intID);
      time.push_back(intID - index);
    }
    index++;
    it2 = it1 + 1;
    it1 = line.find(',', it1 + 1);
  }

  int timestamp = initialTimestamp;
  bool found = false;
  while (!found)
  {
    for (auto busID : buses)
    {
      if (initialTimestamp % busID.toInt() == 0)
      {
        cout << "Part 1: " << (initialTimestamp - timestamp) * busID.toInt() << endl;
        found = true;
        break;
      }
    }
    initialTimestamp++;
  }

  cout << "Part 2: " << ChineseRemainderTheorem(buses, time);
  return 0;
}
