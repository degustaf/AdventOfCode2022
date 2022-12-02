#ifndef AOC2022_CHANNELS_HPP
#define AOC2022_CHANNELS_HPP

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <optional>
#include <queue>

template<typename T>
class channel {
  public:
    channel(void) : _done(false), data() {};
    void close(void) {
      std::unique_lock lk(m);
      _done = true;
      lk.unlock();
      cv.notify_all();
    };

    void send(T &t) {
      std::unique_lock lk(m);
      cv.wait(lk, [this] {
	  return this->data.empty();
	});
      data.push(t);
      lk.unlock();
      cv.notify_all();
    };

    std::optional<T> receive(void) {
      std::unique_lock lk(m);
      cv.wait(lk, [this] {
	  return (!this->data.empty()) || ((bool)this->_done);
        });
      if(!data.empty()) {
	T temp = data.front();
	data.pop();
	cv.notify_all();
	return std::optional(temp);
      }
      cv.notify_all();
      return std::nullopt;
    }

  private:
    std::atomic<bool> _done;
    std::mutex m;
    std::condition_variable cv;
    std::queue<T> data;
};

#endif /* AOC2022_CHANNELS_HPP */
