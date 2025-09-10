#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <iostream>

Base* generate(void);
void identify(Base *obj); // pointer
void identify(Base &obj); // reference

int main()
{
	std::cout << "===== dynamic cast =====" << std::endl;
	for (int i = 0; i < 5; i++)
	{
		std::cout << "\n--- TEST " << (i + 1) << " ---" << std::endl;

		Base* obj = generate();
		if (obj)
		{
			identify(obj);
			identify(*obj);
			delete obj;
		}
	}

	std::cout << "\n===== Manual Test (Known Types) =====" << std::endl;
	A a;
	B b;
	C c;

	std::cout << "\n---Test A object ---" << std::endl;
	identify(a);
	identify(&a);

	std::cout << "\n---Test B object ---" << std::endl;
	identify(b);
	identify(&b);

	std::cout << "\n---Test C object ---" << std::endl;
	identify(c);
	identify(&c);

	return 0;
}
