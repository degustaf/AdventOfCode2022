#include "day2.hpp"

#include <thread>
#include <utility>

#include "channels.hpp"

using std::pair;
using std::thread;

class RPS {
  public:
    enum Shape {
      Rock,
      Paper,
      Scissors
    };

    RPS(char c) : v(static_cast<Shape>(c)) {};

    int against(const RPS &opponent) const {
      if(v == opponent.v)
	return 3;
      if((v == Rock && opponent.v == Scissors) ||
	  (v == Paper && opponent.v == Rock) ||
	  (v == Scissors && opponent.v == Paper))
	return 6;
      return 0;
    }

    int value(void) const {
      return static_cast<int>(v) + 1;
    }

    RPS strategy(char result) const {
      switch(result) {
	case 'X':
	  switch(v) {
	    case Rock:
	      return Scissors;
	    case Paper:
	      return Rock;
	    case Scissors:
	      return Paper;
	  }
	  break;
	case 'Y':
	  return *this;
	case 'Z':
	  switch(v) {
	    case Rock:
	      return Paper;
	    case Paper:
	      return Scissors;
	    case Scissors:
	      return Rock;
	  }
      }
      throw std::runtime_error("Invalid stratgey");
    }

  private:
    Shape v;
};

static void producer(std::ifstream *data, channel<pair<char,char>> *cs1,
    channel<pair<char,char>> *cs2) {
  while(*data) {
    char c1, c2;
    *data >> c1;
    if(data->fail())
      break;
    *data >> c2;
    if(data->fail())
      break;

    pair<char,char> p(c1,c2);
    cs1->send(p);
    cs2->send(p);
  }

  cs1->close();
  cs2->close();
}

static void consume1(channel<pair<char,char>> *ch, int *acc) {
  while(true) {
    auto n = ch->receive();
    if(n) {
      auto pair = *n;
      RPS opponent(pair.first - 'A');
      RPS mine(pair.second - 'X');
      *acc += mine.against(opponent) + mine.value();
    } else {
      return;
    }
  }
}

static void consume2(channel<pair<char,char>> *ch, int *acc) {
  while(true) {
    auto n = ch->receive();
    if(n) {
      auto pair = *n;
      RPS opponent(pair.first - 'A');
      RPS mine = opponent.strategy(pair.second);
      *acc += mine.against(opponent) + mine.value();
    } else {
      return;
    }
  }
}

Day2::Day2(const std::string &filename) : data(filename), acc(0), acc2(0) {
  channel<pair<char,char>> ch1;
  channel<pair<char,char>> ch2;

  thread p(producer, &data, &ch1, &ch2);
  thread c1(consume1, &ch1, &acc);
  thread c2(consume2, &ch2, &acc2);

  p.join();
  c1.join();
  c2.join();
}

int Day2::part1(void) const {
  return acc;
}

int Day2::part2(void) const {
  return acc2;
}
