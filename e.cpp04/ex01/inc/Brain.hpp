#ifndef BRAIN_HPP
#define BRAIN_HPP

class Brain
{
private:
	
public:
	Brain();
	Brain(const Brain& copy);
	virtual ~Brain();

	Brain &operator=(const Brain &src);

protected:
	std::string ideas[100];
};

#endif
