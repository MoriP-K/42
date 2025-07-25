#include "../inc/MateriaSource.hpp"

MateriaSource::MateriaSource()
{
	std::cout << "MateariSource: Default Constructor called" << std::endl;
	this->initTemplate();
}

MateriaSource::MateriaSource(const MateriaSource& copy)
{
	std::cout << "MateriaSource: Copy constructor called" << std::endl;
	this->initTemplate();
	this->copyTemplates(src);
}

MateriaSource::~MateriaSource()
{
	std::cout << "MateriaSource: Destructor called" << std::endl;
	clearTemplates();
}



void MateriaSource::clearTemplates(void)
{
	for (int i = 0; i < slot; i++)
	{
		if (this->templates[i] != nullptr)
		{
			delete this->templates[i];
			this->templates[i] = nullptr;
		}
	}
}

void MateriaSource::copyTemplates(const MateriaSource &src)
{
	for (int i = 0; i < slot; i++)
	{
		if (src.templates[i] != nullptr)
		{
			this->initInventory[i] = src.templates[i]->clone();
		}
		else
		{
			this->templates[i] = nullptr;
		}
	}
}

void MateriaSource::initTemplate(void)
{
	for (int i = 0; i < slot; i++)
	{
		this->templates[i] = nullptr;
	}
}
