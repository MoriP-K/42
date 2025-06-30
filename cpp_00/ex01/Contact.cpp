#include "Contact.hpp"
#include <iostream>
#include <iomanip>

Contact::Contact() {}
Contact::~Contact() {}

void Contact::setFirstName(const std::string& name)
{
	firstName = name;
}

void Contact::setLastName(const std::string& name)
{
	lastName = name;
}

void Contact::setNickName(const std::string& name)
{
	nickName = name;
}

void Contact::setPhoneNumber(const std::string& number)
{
	phoneNumber = number;
}

void Contact::setDarkestSecret(const std::string& secret)
{
	darkestSecret = secret;
}

std::string Contact::getFirstName() const
{
	return firstName;
}

std::string Contact::getLastName() const
{
	return  lastName;
}

std::string Contact::getNickName() const
{
	return nickName;
}

std::string Contact::getPhoneNumber() const
{
	return phoneNumber;
}

std::string Contact::getDarkestSecret() const
{
	return darkestSecret;
}

bool Contact::isEmpty() const
{
	return (firstName.empty() || lastName.empty()
		|| nickName.empty() || phoneNumber.empty() || darkestSecret.empty());
}

void Contact::displayContact() const
{
	std::cout << "First Name: " << firstName << std::endl;
	std::cout << "Last Name: " << lastName << std::endl;
	std::cout << "Nick Name: " << nickName << std::endl;
	std::cout << "Phone Number: " << phoneNumber << std::endl;
	std::cout << "Darkest Secret: " << darkestSecret << std::endl;
}