/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoshie <hyoshie@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 11:40:16 by hyoshie           #+#    #+#             */
/*   Updated: 2022/10/04 23:29:46 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

Fixed::Fixed() : _rawBits(0) {}

Fixed::~Fixed() {}

Fixed::Fixed(const int num) { _rawBits = num << _fractionalBits; }

Fixed::Fixed(const float num) {
  float float_fb = (float)(1 << _fractionalBits);

  _rawBits = roundf(num * float_fb);
}

Fixed::Fixed(const Fixed& other) { _rawBits = other.getRawBits(); }

Fixed& Fixed::operator=(const Fixed& other) {
  if (this != &other) {
    this->_rawBits = other.getRawBits();
  }

  return *this;
}

int Fixed::getRawBits(void) const { return (_rawBits); }

void Fixed::setRawBits(int const raw) { _rawBits = raw; }

float Fixed::toFloat(void) const {
  float float_fb = (float)(1 << _fractionalBits);

  return (_rawBits / float_fb);
}

int Fixed::toInt(void) const { return (_rawBits >> _fractionalBits); }

Fixed Fixed::operator+(const Fixed& other) const {
  Fixed ret;

  ret.setRawBits(this->getRawBits() + other.getRawBits());
  return ret;
}

Fixed Fixed::operator-(const Fixed& other) const {
  Fixed ret;

  ret.setRawBits(this->getRawBits() - other.getRawBits());
  return ret;
}

Fixed Fixed::operator*(const Fixed& other) const {
  Fixed ret;
  long left = this->getRawBits();
  long right = other.getRawBits();

  ret.setRawBits(left * right >> _fractionalBits);
  return ret;
}

Fixed Fixed::operator/(const Fixed& other) const {
  Fixed ret;
  long left = this->getRawBits();
  long right = other.getRawBits();

  if (right == 0) {
    std::cout << "zero division, it is undefined" << std::endl;
    return ret;
  }
  ret.setRawBits((left << _fractionalBits) / right);
  return ret;
}

Fixed& Fixed::operator++() {
  _rawBits += 1;

  return *this;
}

Fixed Fixed::operator++(int d) {
  (void)d;

  Fixed before(*this);

  ++*this;
  return before;
}

Fixed& Fixed::operator--() {
  _rawBits -= 1;

  return *this;
}

Fixed Fixed::operator--(int d) {
  (void)d;

  Fixed before(*this);

  --*this;
  return before;
}

Fixed& Fixed::min(Fixed& f1, Fixed& f2) {
  if (f1.getRawBits() < f2.getRawBits()) {
    return f1;
  } else {
    return f2;
  }
}

Fixed& Fixed::max(Fixed& f1, Fixed& f2) {
  if (f1.getRawBits() > f2.getRawBits()) {
    return f1;
  } else {
    return f2;
  }
}

const Fixed& Fixed::min(const Fixed& f1, const Fixed& f2) {
  if (f1.getRawBits() < f2.getRawBits()) {
    return f1;
  } else {
    return f2;
  }
}

const Fixed& Fixed::max(const Fixed& f1, const Fixed& f2) {
  if (f1.getRawBits() > f2.getRawBits()) {
    return f1;
  } else {
    return f2;
  }
}

std::ostream& operator<<(std::ostream& ostream, const Fixed& num) {
  ostream << num.toFloat();

  return (ostream);
}

bool operator==(const Fixed& lhs, const Fixed& rhs) {
  return (lhs.getRawBits() == rhs.getRawBits());
}

bool operator!=(const Fixed& lhs, const Fixed& rhs) { return !(lhs == rhs); }

bool operator<(const Fixed& lhs, const Fixed& rhs) {
  return (lhs.getRawBits() < rhs.getRawBits());
}

bool operator<=(const Fixed& lhs, const Fixed& rhs) { return !(lhs > rhs); }

bool operator>(const Fixed& lhs, const Fixed& rhs) { return (rhs < lhs); }

bool operator>=(const Fixed& lhs, const Fixed& rhs) { return !(lhs < rhs); }
