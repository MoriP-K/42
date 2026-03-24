#include "Harl.hpp"

Harl::Harl()
{
}

Harl::~Harl()
{
}

void	Harl::debug(void)
{
	std::cout << "I love having extra bacon for ";
	std::cout << "my 7XL-double-cheese-triple-pickle-specialketchup burger. ";
	std::cout << "I really do!\n" << std::endl;
}

void	Harl::info(void)
{
	std::cout << "I cannot believe adding extra bacon costs more money. ";
	std::cout << "You didn't put enough bacon in my burger! If you did, ";
	std::cout << "I wouldn't be asking for more!\n" << std::endl;
}

void	Harl::warning(void)
{
	std::cout << "I think I deserve to have some extra bacon for free. ";
	std::cout << "I've been coming for years, ";
	std::cout <<  "whereas you started working here just last month.\n" << std::endl;
}

void	Harl::error(void)
{
	std::cout << "This is unacceptable! I want to speak to the manager now." << std::endl;
}

void	Harl::complain(std::string level)
{
	std::string levels[4] = {
		"DEBUG",
		"INFO",
		"WARNING",
		"ERROR"
	};
	int i = 0;

	while (i < 4)
	{
		if (levels[i] == level)
			break ;
		i++;
	}
	switch (i)
	{
	case 0:
		std::cout << "[ DEBUG ]" << std::endl;
		Harl::debug();
		std::cout << "[ INFO ]" << std::endl;
		Harl::info();
		std::cout << "[ WARNING ]" << std::endl;
		Harl::warning();
		std::cout << "[ ERROR ]" << std::endl;
		Harl::error();
		break ;
	case 1:
		std::cout << "[ INFO ]" << std::endl;
		Harl::info();
		std::cout << "[ WARNING ]" << std::endl;
		Harl::warning();
		std::cout << "[ ERROR ]" << std::endl;
		Harl::error();
		break ;
	case 2:
		std::cout << "[ WARNING ]" << std::endl;
		Harl::warning();
		std::cout << "[ ERROR ]" << std::endl;
		Harl::error();
		break ;	
	case 3:;
		std::cout << "[ ERROR ]" << std::endl;
		Harl::error();
		break ;
	default:
		std::cout << "INVALID LEVEL." << std::endl;
		break;
	}
}
