#ifndef MATERIA_HPP
#define MATERIA_HPP

#include "IMateriaSource.hpp"
#include "AMateria.hpp"

class MateriaSource: public IMateriaSource
{
public:
	static const int slot = 4;

private:
	AMateria* templates[slot];

public:
	MateriaSource();
	MateriaSource(const MateriaSource& copy);
	virtual ~MateriaSource();
	MateriaSource &operator=(const MateriaSource &src);

	virtual void learnMateria(AMateria* m);
	virtual AMateria* createMateria(std::string const & type);

private:
	void clearTemplates(void);
	void copyTemplates(const MateriaSource &src);
	void initTemplate(void);
};

#endif