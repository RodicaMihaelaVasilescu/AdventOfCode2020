#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct game {
  int winnerID;
  queue<int> deck1, deck2;
};

game combat(queue<int> deck1, queue <int> deck2)
{
  set <pair<queue<int>, queue<int>>> usedConfigurations;
  while (!deck1.empty() && !deck2.empty())
  {
    int winner = 0;
    if (usedConfigurations.find({ deck1,deck2 }) != usedConfigurations.end())
    {
      /*
        if there was a previous round in this game that had exactly the same cards in the same order
        in the same players' decks, the game instantly ends in a win for player 1.
      */
      return { 1, deck1, deck2 };
    }
    else
    {
      usedConfigurations.insert({ deck1,deck2 });
    }

    int card1 = deck1.front();
    int card2 = deck2.front();
    deck1.pop();
    deck2.pop();

    /*
      If both players have at least as many cards remaining in their deck as the value of the card
      they just drew, the winner of the round is determined by playing a new game of Recursive Combat
    */
    if (deck1.size() >= card1 && deck2.size() >= card2)
    {
      auto deck1Copy = deck1;
      auto deck2Copy = deck2;
      int c1 = card1, c2 = card2;
      queue<int> firstC1CardsOfDeck1, firstC2CardsOfDeck2;
      while (c1--)
      {
        firstC1CardsOfDeck1.push(deck1Copy.front());
        deck1Copy.pop();
      }
      while (c2--)
      {
        firstC2CardsOfDeck2.push(deck2Copy.front());
        deck2Copy.pop();
      }
      winner = combat(firstC1CardsOfDeck1, firstC2CardsOfDeck2).winnerID;
    }
    if (winner == 0)
    {
      winner = card1 > card2 ? 1 : 2;
    }
    if (winner == 1)
    {
      deck1.push(card1);
      deck1.push(card2);
    }
    else if (winner == 2)
    {
      deck2.push(card2);
      deck2.push(card1);
    }
  }

  if (!deck1.empty())
  {

    return { 1, deck1, deck2 };
  }
  else
  {
    return { 2,deck1, deck2 };
  }

}

int getScore(queue<int> winner)
{
  int sum = 0;
  int numberOfCards = winner.size();
  while (!winner.empty())
  {
    sum += (numberOfCards--) * winner.front();
    winner.pop();
  }
  return sum;
}

int main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  string inputLine;
  bool isPlayer1 = true;

  queue<int> deck1, deck2;
  while (getline(cin, inputLine))
  {
    if (inputLine == "Player 1:" || inputLine == "")
    {
      continue;
    }
    else if (inputLine == "Player 2:")
    {
      isPlayer1 = false;
      continue;
    }
    else if (inputLine == "")
    {
      continue;
    }
    else if (isPlayer1)
    {
      deck1.push(stoi(inputLine));
    }
    else
    {
      deck2.push(stoi(inputLine));
    }

  }

  queue<int> copyDeck1 = deck1, copyDeck2 = deck2;

  while (!deck1.empty() && !deck2.empty())
  {
    int card1 = deck1.front();
    deck1.pop();

    int card2 = deck2.front();
    deck2.pop();

    if (card1 > card2)
    {
      deck1.push(card1);
      deck1.push(card2);
    }
    else if (card1 < card2)
    {
      deck2.push(card2);
      deck2.push(card1);
    }
  }

  int numberOfCards = max(deck1.size(), deck2.size());
  int sumPart1 = 0;

  queue<int> winnerPart1 = deck1.size() > deck2.size() ? deck1 : deck2;

  game result = combat(copyDeck1, copyDeck2);
  auto winnerPart2 = result.winnerID == 1 ? result.deck1 : result.deck2;

  cout << "Part 1: " << getScore(winnerPart1) << endl;
  cout << "Part 2: " << getScore(winnerPart2) << endl;
  return 0;
}