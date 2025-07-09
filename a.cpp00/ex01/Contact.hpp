#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <string>
#include <iostream>
#include <iomanip>
#include <cstdlib>

class Contact
{
	// member vars
	private:
		std::string firstName;
		std::string lastName;
		std::string nickName;
		std::string phoneNumber;
		std::string darkestSecret;

	public:
		Contact(); // constructor
		~Contact(); // destructor

		void setFirstName(const std::string& name); // read only, not make a copy
		void setLastName(const std::string& name);
		void setNickName(const std::string& name);
		void setPhoneNumber(const std::string& number);
		void setDarkestSecret(const std::string& secret);

		std::string getFirstName() const; // can be called from a const object, 
		std::string getLastName() const; // can't be changed member vars
		std::string getNickName() const; // getter func is a const to not change the object
		std::string getPhoneNumber() const;
		std::string getDarkestSecret() const;

		bool isEmpty() const;
		void displayContact() const;
};

#endif
