#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include "Contact.hpp"

class PhoneBook
{
	private:
		static const int MAX_CONTACTS = 8;
		Contact contacts[MAX_CONTACTS];
		int contactCount;
		int oldestIndex;

	public:
		PhoneBook();
		~PhoneBook();

		void addContact();
		void searchContact() const;
		void displayContactList() const;
		void displayContactDetails(int index) const;

	private:
		std::string getInput(const std::string& prompt) const;
		std::string truncateString(const std::string& str, size_t witdh) const;
		bool isValidIndex(const std::string& input, int&index) const;
};

#endif