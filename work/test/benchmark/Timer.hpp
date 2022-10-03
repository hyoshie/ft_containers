#ifndef TIMER_HPP
#define TIMER_HPP

#include <time.h>

class Timer {
 public:
  Timer();
  ~Timer();

  void start();
  void stop();
  void reset();
  double elapsed_time();

 private:
  clock_t start_time_;
  clock_t end_time_;
  double elapsed_time_;
};

#endif /* TIMER_HPP */
