#include "PhoneBook.hpp"
#include <iostream>
#include <string>

int main()
{
	PhoneBook phoneBook;
	std::string command;

	std::cout << "You can use commands: ADD, SEARCH, EXIT" << std::endl;
	while (true)
	{
		std::cout << "\nEnter command: ";
		std::getline(std::cin, command);
		if (std::cin.eof())
		{
			std::cout << std::endl << "EOF detected. Exiting..." << std::endl;
			break ;
		}
		if (command == "ADD")
			phoneBook.addContact();
		else if (command == "SEARCH")
			phoneBook.searchContact();
		else if (command == "EXIT")
		{
			std::cout << "Au revoir!" << std::endl;
			break ;
		}
		else if (!command.empty())
			std::cout << "Unknown command. You can use commands: ADD, SEARCH, EXIT" << std::endl;
	}
}
