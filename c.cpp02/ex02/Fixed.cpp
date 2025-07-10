#include "Fixed.hpp"

Fixed::Fixed(): fixedPointValue(0)
{
	std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const int number) 
{
	std::cout << "Int constructor called" << std::endl;
	this->fixedPointValue = number << this->fractionalBits;
}

Fixed::Fixed(const float number)
{
	std::cout << "Float constructor called" << std::endl;
	this->fixedPointValue = roundf(number * (1 << this->fractionalBits));
}

Fixed::Fixed(const Fixed &copy)
{
	std::cout << "Copy constructor called" << std::endl;
	*this = copy;
}

Fixed &Fixed::operator=(const Fixed &src)
{
	std::cout << "Copy assignment operator called" << std::endl;
	if (this != &src)
		this->fixedPointValue = src.getRawBits();
	return *this;
}

Fixed::~Fixed()
{
	std::cout << "Destructor called" << std::endl;
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
	return this->fixedPointValue;
}

std::ostream &operator<<(std::ostream &o, Fixed const &fixed)
{
	o << fixed.toFloat();
	return o;
}
