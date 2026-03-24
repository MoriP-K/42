#include "Account.hpp"

#include <iostream>

Account::Account(): _accountIndex(0), _amount(0), _nbDeposits(0), _nbWithdrawals(0) {};
Account::~Account() {};

void	Account::displayAccountsInfos(void)
{
	std::cout << "infos" << std::endl;
}

void	Account::displayStatus() const
{
	std::cout << "status" << std::endl;
}

void	Account::makeDeposit(int deposit)
{
	std::cout << "deposit" << std::endl;
}

bool	Account::makeWithdrawal(int withdrawal)
{
	std::cout << "withdrawal" << std::endl;
	return true;
}

int	Account::checkAmount(void) const
{
	return 5;
}

int	Account::getNbAccounts(void)
{
	return _nbAccounts;
}

int Account::getTotalAmount(void)
{
	return _totalAmount;
}

int Account::getNbDeposits(void)
{
	return _totalNbDeposits;
}

int Account::getNbWithdrawals(void)
{
	return _totalNbWithdrawals;
}

void	Account::_displayTimestamp(void)
{
	std::cout << "timestamp" << std::endl;
}

Account::Account(void)
{
	std::cout << "Account" << std::endl;
}