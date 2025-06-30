#include "PhoneBook.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <limits>

PhoneBook::PhoneBook() : contactCount(0), oldestIndex(0) {}
PhoneBook::~PhoneBook() {}

void PhoneBook::addContact()
{
	Contact newContact;
	std::string input;

	std::cout << "Adding new contact..." << std::endl;

	input = getInput("First Name: ");
	if (input.empty())
		return ;
	newContact.setFirstName(input);
	input = getInput("Last Name: ");
	if (input.empty())
		return ;
	newContact.setLastName(input);
	input = getInput("Nickname: ");
	if (input.empty())
		return ;
	newContact.setNickName(input);
	input = getInput("Phone Number: ");
	if (input.empty())
		return ;
	newContact.setPhoneNumber(input);
	input = getInput("Darkest Secret: ");
	if (input.empty())
		return ;
	newContact.setDarkestSecret(input);
	if (contactCount < MAX_CONTACTS)
	{
		contacts[contactCount] = newContact;
		contactCount++;
	}
	else
	{
		contacts[oldestIndex] = newContact;
		oldestIndex = (oldestIndex + 1) % MAX_CONTACTS;
	}
	std::cout << "Contact added successfully!" << std::endl;
}

void PhoneBook::searchContact() const
{
	if (contactCount == 0)
	{
		std::cout << "No contacts available." << std::endl;
		return ;
	}
	displayContactList();
	std::string input;
	int index;

	std::cout << "Enter contact index: ";
	std::getline(std::cin, input);
	if (!isValidIndex(input, index))
	{
		std::cout << "Invalid index." << std::endl;
		return ;
	}
	displayContactDetails(index);
}

void PhoneBook::displayContactList() const
{
	std::cout << std::setfill(' ') << std::right;
	std::cout << std::setw(10) << "Index" << "|";
	std::cout << std::setw(10) << "First Name" << "|";
	std::cout << std::setw(10) << "Last Name" << "|";
	std::cout << std::setw(10) << "Nickname" << "|" << std::endl;
	for (int i = 0; i < contactCount; i++)
	{
		if (!contacts[i].isEmpty())
		{
			std::cout << std::setw(10) << i << "|";
			std::cout << std::setw(10) << truncateString(contacts[i].getFirstName(), 10) << "|";
			std::cout << std::setw(10) << truncateString(contacts[i].getLastName(), 10) << "|";
			std::cout << std::setw(10) << truncateString(contacts[i].getNickName(), 10) << std::endl;
		}
	}
}

void PhoneBook::displayContactDetails(int index) const
{
	if (index >= 0 && index < contactCount && !contacts[index].isEmpty())
		contacts[index].displayContact();
	else
		std::cout << "Contact not found." << std::endl;
}

std::string PhoneBook::getInput(const std::string& prompt) const
{
	std::string input;

	while (true)
	{
		std::cout << prompt;
		std::getline(std::cin, input);

		if (std::cin.eof())
		{
			std::cout << std::endl << "EOF detected. Exiting..." << std::endl;
			exit(0);
		}
		if (!input.empty())
			return input;
		std::cout << "Field cannot be empty. Please try again." << std::endl;
	}
}

std::string PhoneBook::truncateString(const std::string& str, size_t witdh) const
{
	if (str.length() <= witdh)
		return str;
	std::string truncated = str.substr(0, witdh - 2);
	truncated += ".";
	return truncated;
}

bool PhoneBook::isValidIndex(const std::string& input, int& index) const
{
	std::stringstream ss(input);

	if (!(ss >> index) || !ss.eof())
		return false;
	return (index >= 0 && index < contactCount && !contacts[index].isEmpty());
}