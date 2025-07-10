#pragma once
#include <iostream>
#include <cmath>

const int	fractionalBits = 8;

class Fixed
{
private:
	int	fixedPointValue;
	static const int	fractionalBits = 8;

public:
	Fixed();
	Fixed(const int number);
	Fixed(const float number);
	Fixed(const Fixed& copy);
	Fixed &operator=(const Fixed &src);
	~Fixed();

	float toFloat(void) const;
	int toInt(void) const;

	int getRawBits(void) const;
	void setRawBits(int const raw);
};


std::ostream &operator<<(std::ostream &o, Fixed const &fixed);
