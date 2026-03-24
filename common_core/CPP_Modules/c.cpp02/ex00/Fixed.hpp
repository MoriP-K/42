#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>

class Fixed
{
private:
	int fixedPointValue;
	static const int	fractionalBits = 8;

public:
	// Default constructor
	Fixed();
	// Copy constructor
	Fixed(const Fixed &copy);
	// Copy assignment operator
	Fixed &operator=(const Fixed &src);
	// Destructor
	~Fixed();

	int getRawBits(void) const;
	void setRawBits(int const raw);
};

#endif
