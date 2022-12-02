#include "day1.hpp"

#include <algorithm>
#include <numeric>
#include <functional>
#include <sstream>
#include <thread>

#include "channels.hpp"

using std::ostream;
using std::string;

/*

   Single threaded.

Day1::Day1(const std::string &filename) : data(filename) {
  best.fill(0);
  string s;
  int current = 0;

  while(getline(data, s)) {
    std::stringstream ss(s);
    int n;
    if(ss >> n) {
      current += n;
    } else {
      better(current);
      current = 0;
    }
  }
  better(current);
}
*/

void producer(std::ifstream *data, channel<int> *ch) {
  string s;
  int current = 0;

  while(getline(*data, s)) {
    std::stringstream ss(s);
    int n;
    if(ss >> n) {
      current += n;
    } else {
      ch->send(current);
      current = 0;
    }
  }

  ch->close();
}

static void consume(std::array<int, 3> *best, channel<int> *ch) {
  while(true) {
    auto n = ch->receive();
    if(n) {
      auto candidate = *n;
      if(candidate > best->back()) {
	best->back() = candidate;
	std::sort(best->begin(), best->end(), std::greater<int>());
      }
    } else {
      return;
    }
  }
}

Day1::Day1(const std::string &filename) : data(filename) {
  best.fill(0);
  channel<int> ch;

  std::thread p(producer, &data, &ch);
  std::thread c(consume, &best, &ch);
  p.join();
  c.join();
}

void Day1::better(int candidate) {
  if(candidate > best.back()) {
    best.back() = candidate;
    std::sort(best.begin(), best.end(), std::greater<int>());
  }
}

int Day1::part1(void) const {
  return best.front();
}

int Day1::part2(void) const {
  return std::accumulate(best.begin(), best.end(), 0);
}
