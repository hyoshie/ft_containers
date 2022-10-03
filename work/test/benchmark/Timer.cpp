#include "Timer.hpp"

Timer::Timer() : elapsed_time_(0) {}

Timer::~Timer() {}

void Timer::start() { start_time_ = clock(); }

void Timer::stop() {
  end_time_ = clock();
  elapsed_time_ +=
      static_cast< double >(end_time_ - start_time_) / CLOCKS_PER_SEC;
}

void Timer::reset() { elapsed_time_ = 0; }

double Timer::elapsed_time() { return elapsed_time_; }
