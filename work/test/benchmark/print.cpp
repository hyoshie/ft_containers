#include <iomanip>
#include <iostream>

#include "print.hpp"

void print_func(const std::string& func_name) {
  std::cout << std::setw(kFieldWidth) << std::left << func_name << ": ";
}

void print_time(double elapsed_time) {
  std::cout << std::fixed << elapsed_time << std::endl;
}
