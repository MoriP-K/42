#include "Fixed.hpp"

Fixed::Fixed() : fixedPointValue(0)
{
}

Fixed::Fixed(const int number)
{
	this->fixedPointValue = number << this->fractionalBits;
}

Fixed::Fixed(const float number)
{
	this->fixedPointValue = roundf(number * (1 << this->fractionalBits));
}

Fixed::Fixed(const Fixed &copy)
{
	*this = copy;
}

Fixed::~Fixed()
{
}

Fixed &Fixed::operator=(const Fixed &src)
{
	if (this != &src)
		this->fixedPointValue = src.getRawBits();
	return (*this);
}

bool Fixed::operator==(Fixed src) const
{
	return (this->toFloat() == src.toFloat());
}

bool Fixed::operator>(Fixed src) const
{
	return (this->toFloat() > src.toFloat());
}

bool Fixed::operator<(Fixed src) const
{
	return (this->toFloat() < src.toFloat());
}

bool Fixed::operator>=(Fixed src) const
{
	return (this->toFloat() >= src.toFloat());
}

bool Fixed::operator<=(Fixed src) const
{
	return (this->toFloat() <= src.toFloat());
}

bool Fixed::operator!=(Fixed src) const
{
	return (this->toFloat() != src.toFloat());
}

Fixed Fixed::operator+(Fixed src) const
{
	return (this->toFloat() + src.toFloat());
}

Fixed Fixed::operator-(Fixed src) const
{
	return (this->toFloat() - src.toFloat());
}

Fixed Fixed::operator*(Fixed src) const
{
	return (this->toFloat() * src.toFloat());
}

Fixed Fixed::operator/(Fixed src) const
{
	return (this->toFloat() / src.toFloat());
}

Fixed Fixed::operator++(void)
{
	this->fixedPointValue++;
	return (*this);
}

Fixed Fixed::operator--(void)
{
	this->fixedPointValue--;
	return (*this);
}

Fixed Fixed::operator++(int)
{
	Fixed	tmp;

	tmp = *this;
	++this->fixedPointValue;
	return (tmp);
}

Fixed Fixed::operator--(int)
{
	Fixed	tmp;

	tmp = *this;
	--this->fixedPointValue;
	return (tmp);
}

Fixed &Fixed::min(Fixed &a, Fixed &b)
{
	if (a < b)
		return (a);
	return (b);
}

const Fixed &Fixed::min(const Fixed &a, const Fixed &b)
{
	if (a < b)
		return (a);
	return (b);
}

Fixed &Fixed::max(Fixed &a, Fixed &b)
{
	if (a > b)
		return (a);
	return (b);
}

const Fixed &Fixed::max(const Fixed &a, const Fixed &b)
{
	if (a > b)
		return (a);
	return (b);
}

float Fixed::toFloat(void) const
{
	return ((float)this->fixedPointValue / (float)(1 << this->fractionalBits));
}

int Fixed::toInt(void) const
{
	return (this->fixedPointValue >> this->fractionalBits);
}

int Fixed::getRawBits(void) const
{
	return (this->fixedPointValue);
}

std::ostream &operator<<(std::ostream &o, Fixed const &fixed)
{
	o << fixed.toFloat();
	return (o);
}
