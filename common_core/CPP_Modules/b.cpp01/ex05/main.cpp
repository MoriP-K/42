#include "Harl.hpp"

int main(void)
{
	Harl harl;

	std::cout << std::endl << "----- DEBUG LEVEL -----" << std::endl;;
	harl.complain("DEBUG");
	
	std::cout << std::endl << "----- INFO LEVEL -----" << std::endl;;
	harl.complain("INFO");
	
	std::cout << std::endl << "----- WARNING LEVEL -----" << std::endl;;
	harl.complain("WARNING");
	
	std::cout << std::endl << "----- ERROR LEVEL -----" << std::endl;;
	harl.complain("ERROR");
	
	std::cout << std::endl << "----- INVALID LEVEL -----" << std::endl;;
	harl.complain("TEST");
	return 0;
}
