#include <iostream>
#include <string>
#include <fstream>

std::string ft_replace(std::string buffer, const std::string search, const std::string replace)
{
	if (search.empty())
		return (buffer);

	size_t erase_len = search.length();
	size_t replace_len = replace.length();
	size_t pos_search = 0;

	pos_search = buffer.find(search);
	while (pos_search != std::string::npos)
	{
		buffer.erase(pos_search, erase_len);
		buffer.insert(pos_search, replace);
		pos_search = buffer.find(search, pos_search + replace_len);
	}
	return (buffer);
}

int main(int ac, char const *av[])
{
	if (ac != 4)
	{
		std::cout << "Invalid Argument." << std::endl;
		return 1;
	}
	else
	{
		const std::string filename = av[1];
		const std::string search = av[2];
		const std::string replace = av[3];
		std::string buffer;
		std::ifstream infile;
		std::ofstream outfile;

		if (search.empty())
		{
			std::cerr << "Error: search string cannot be empty" << std::endl;
			return (1);
		}

		infile.open(av[1]);
		if (infile.is_open() == true)
		{
			outfile.open((filename + ".replace").c_str());
			if (outfile.is_open() == true)
			{
				while (std::getline(infile, buffer))
				{
					buffer = ft_replace(buffer, search, replace);
					outfile << buffer;
					if (infile.peek() != EOF)
						outfile << std::endl;
				}
				outfile.close();
			}
			else
			{
				std::perror("Outfile Error");
				infile.close();
				return (1);
			}
			infile.close();
		}
		else
		{
			std::perror("Infile Error");
			std::cerr << "Outfile not created or truncated." << std::endl;
			return (1);
		}
		std::cout << "File processed successfully. Output: " << filename << ".replace" << std::endl;
		return (0);
	}
	return (1);
}
