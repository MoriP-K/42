#include "../inc/MateriaSource.hpp"

MateriaSource::MateriaSource()
{
	// std::cout << "MateriaSource: Default Constructor called" << std::endl;
	this->initTemplate();
}

MateriaSource::MateriaSource(const MateriaSource &copy)
{
	// std::cout << "MateriaSource: Copy constructor called" << std::endl;
	this->initTemplate();
	this->copyTemplates(copy);
}

MateriaSource::~MateriaSource()
{
	// std::cout << "MateriaSource: Destructor called" << std::endl;
	clearTemplates();
}

MateriaSource& MateriaSource::operator=(const MateriaSource &src)
{
	// std::cout << "MateriaSource: Copy assignment operator called" << std::endl;
	if (this != &src)
	{
		clearTemplates();
		copyTemplates(src);
	}
	return (*this);
}

void MateriaSource::learnMateria(AMateria* m)
{
	if (!m)
	{
		// std::cout << "Cannot laern null materia" << std::endl;
		return ;
	}
	for (int i = 0; i < slot; i++)
	{
		if (this->templates[i] == NULL)
		{
			this->templates[i] = m->clone();
			delete m;
			// std::cout << "MateriaSource learned " << m->getType() << " in slot " << i << std::endl;
			return ;
		}
	}
	// std::cout << "MateriaSource is full, cannot learn " << m->getType() << std::endl;
}

AMateria* MateriaSource::createMateria(std::string const & type)
{
	for (int i = 0; i < slot; i++)
	{
		if (this->templates[i] && this->templates[i]->getType() == type)
		{
			// std::cout << "MateriaSource creating " << type << " from template" << std::endl;
			return (this->templates[i]->clone());
		}
	}
	// std::cout << "MateriaSource: unknown type " << type << std::endl;
	return (NULL);
}

void MateriaSource::clearTemplates(void)
{
	for (int i = 0; i < slot; i++)
	{
		if (this->templates[i])
		{
			delete this->templates[i];
			this->templates[i] = NULL;
		}
	}
}

void MateriaSource::copyTemplates(const MateriaSource &src)
{
	for (int i = 0; i < slot; i++)
	{
		if (src.templates[i])
		{
			this->templates[i] = src.templates[i]->clone();
		}
		else
		{
			this->templates[i] = NULL;
		}
	}
}

void MateriaSource::initTemplate(void)
{
	for (int i = 0; i < slot; i++)
	{
		this->templates[i] = NULL;
	}
}
