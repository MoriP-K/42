#include "Animal.hpp"

class Cat: public Animal
{
private:
	
public:
	Cat();
	Cat(const Cat& copy);
	virtual ~Cat();

	Cat &operator=(const Cat &src);

	void makeSound(void);
	std::string getType(void);
protected:
	std::string type;
};
