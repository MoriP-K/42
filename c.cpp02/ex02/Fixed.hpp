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
	~Fixed();

	Fixed &operator=(const Fixed &src);

	bool operator>(Fixed fixed) const;
	bool operator<(Fixed fixed) const;
	bool operator>=(Fixed fixed) const;
	bool operator<=(Fixed fixed) const;
	bool operator==(Fixed fixed) const;
	bool operator!=(Fixed fixed) const;

	Fixed operator+(Fixed fixed) const;
	Fixed operator-(Fixed fixed) const;
	Fixed operator*(Fixed fixed) const;
	Fixed operator/(Fixed fixed) const;

	Fixed operator++(void);
	Fixed operator--(void);
	Fixed operator++(int);
	Fixed operator--(int);

	float toFloat(void) const;
	int toInt(void) const;

	static Fixed &min(Fixed &a, Fixed &b);
	static const Fixed &min(Fixed const &a, Fixed const &b);

	static Fixed &max(Fixed &a, Fixed &b);
	static const Fixed &max(Fixed const &a, Fixed const &b);

	int getRawBits(void) const;
	void setRawBits(int const raw);
};


std::ostream &operator<<(std::ostream &o, Fixed const &fixed);
