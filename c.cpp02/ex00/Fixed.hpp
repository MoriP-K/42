#pragma once
#include <iostream>

class Fixed
{
private:
	int value;
	static const int bits;

public:
	Fixed();
	Fixed(const Fixed& copy);
	Fixed &operator=(const Fixed &src);
	Fixed(int value);
	~Fixed();

	int getRawBits(void) const;
	void setRawBits(int const raw);
};
