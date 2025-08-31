#include <string>

class ScalarConverter
{
private:
	
public:
	ScalarConverter();
	~ScalarConverter();
	ScalarConverter(std::string &copy);
	ScalarConverter &operator=(ScalarConverter& src);
};
