/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoshie <hyoshie@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 11:40:02 by hyoshie           #+#    #+#             */
/*   Updated: 2022/01/21 12:25:11 by hyoshie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

# include <iostream>
# include <cmath>

class Fixed
{
	private:
		int					_rawBits;
		static const int	_fractionalBits = 8;

	public:
		Fixed();
		Fixed(const int num);
		Fixed(const float num);
		~Fixed();
		Fixed(const Fixed& other);
		Fixed&	operator=(const Fixed& other);
		int		getRawBits(void) const;
		void	setRawBits(int const raw);
		float	toFloat(void) const;
		int		toInt(void) const;

		//arithmetic operator
		Fixed	operator+(const Fixed& other) const;
		Fixed	operator-(const Fixed& other) const;
		Fixed	operator*(const Fixed& other) const;
		Fixed	operator/(const Fixed& other) const;

		//comparison operator
		bool	operator>(Fixed& other) const;
		bool	operator<(Fixed& other) const;
		bool	operator>=(Fixed& other) const;
		bool	operator<=(Fixed& other) const;
		bool	operator==(Fixed& other) const;
		bool	operator!=(Fixed& other) const;

		//increment/decrement operator
		Fixed&	operator++();
		Fixed&	operator--();
		Fixed	operator++(int d);
		Fixed	operator--(int d);

		static Fixed&	min(Fixed& f1, Fixed& f2);
		static Fixed&	max(Fixed& f1, Fixed& f2);
		static const Fixed&	min(const Fixed& f1, const Fixed& f2);
		static const Fixed&	max(const Fixed& f1, const Fixed& f2);
};

std::ostream&	operator<<(std::ostream& ostream, const Fixed& num);

#endif /* FIXED_HPP */
