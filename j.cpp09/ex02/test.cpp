#include "PmergeMe.hpp"

void PmergeMe::MergeInsertionSort(std::vector<size_t> chain, int depth)
{
	std::vector<size_t> mainChain;
	std::vector<size_t> pendChain;
	std::vector<size_t> stragglerGroup;
	size_t groupSize = 1;

	if (depth != 0)
	{
		for (int i = 0; i < depth; ++i)
			groupSize *= 2;
	}
	std::cout << "Depth: " << depth << ", GroupSize: " << groupSize
		<< ", ChainSize: " << chain.size() << std::endl;

	if (chain.size() < groupSize * 2)
	{
		for (size_t i = 0; i < chain.size(); ++i)
    {
		this->_sortedVec.push_back(this->_arr[chain[i]]);
    }
	}
		return ;

	for (size_t i = 0; i < chain.size(); i += groupSize * 2)
	{
		if (i + groupSize < chain.size())
		{
			size_t firstGroupEnd = i + groupSize - 1;
			size_t secondGroupStart = i + groupSize;
			size_t secondGroupEnd = std::min(i + groupSize * 2 - 1, chain.size() - 1);
			std::cout << "FG: " << firstGroupEnd << ", SG: " << secondGroupEnd << std::endl;
			// std::cout << "F[" << i << "]: " << _arr[chain[firstGroupEnd]]
			// 	<< ", S[" << i + groupSize << "]: " << _arr[chain[secondGroupEnd]] << std::endl;
			++this->_count;

			if (this->_arr[chain[firstGroupEnd]] > this->_arr[chain[secondGroupEnd]])
			{
				for (size_t j = i; j <= firstGroupEnd; ++j)
					mainChain.push_back(chain[j]);
				for (size_t j = secondGroupStart; j <= secondGroupEnd; ++j)
					pendChain.push_back(chain[j]);
			}
			else
			{
				for (size_t j = secondGroupStart; j <= secondGroupEnd; ++j)
					mainChain.push_back(chain[j]);
				for (size_t j = i; j <= firstGroupEnd; ++j)
					pendChain.push_back(chain[j]);
			}
		}
		else
		{
			for (size_t j = i; j < chain.size(); ++j)
				stragglerGroup.push_back(chain[j]);
		}	
	}

    std::cout << "mainChain: ";
    for (size_t i = 0; i < mainChain.size(); ++i)
        std::cout << mainChain[i] << "(" << this->_arr[mainChain[i]] << ") ";
    std::cout << std::endl;

    std::cout << "pendChain: ";
    for (size_t i = 0; i < pendChain.size(); ++i)
        std::cout << pendChain[i] << "(" << this->_arr[pendChain[i]] << ") ";
    std::cout << std::endl;

    if (!stragglerGroup.empty())
    {
        std::cout << "stragglerGroup: ";
        for (size_t i = 0; i < stragglerGroup.size(); ++i)
            std::cout << stragglerGroup[i] << "(" << this->_arr[stragglerGroup[i]] << ") ";
        std::cout << std::endl;
    }
	if (!mainChain.empty())
		this->MergeInsertionSort(mainChain, ++depth);

	if (!pendChain.empty())
	{
		size_t numPendGroup = pendChain.size() / groupSize;
		std::vector<int> jacob = this->generateJacobsthal(numPendGroup);
		std::vector<int> order = this->createInsertionOrder(jacob, numPendGroup);
		for (size_t i = 0; i < order.size(); ++i)
		{
			size_t groupIdx = order[i];
			size_t pendStart = groupIdx * groupSize;
			size_t pendEnd = std::min(pendStart + groupSize - 1, pendChain.size() - 1);
			size_t mainStart = groupIdx * groupSize;
			std::cout << "\nInserting pend group " << groupIdx 
				<< " (indices " << pendStart << ".." << pendEnd << ")" << std::endl;
			if (groupIdx == 0)
			{
				size_t mainValue = this->_arr[mainChain[mainStart]];
				size_t insertPos = 0;
				for (size_t j = 0; j < this->_sortedVec.size(); ++j)
				{
					if (this->_sortedVec[j] == mainValue)
					{
						insertPos = j;
						break;
					}
				}
				for (size_t j = pendStart; j <= pendEnd; ++j)
				{
					this->_sortedVec.insert(this->_sortedVec.begin() + insertPos, this->_arr[pendChain[j]]);
					insertPos++;
				}
			}
			else
			{
				size_t mainValue = this->_arr[mainChain[mainStart]];
                size_t upperLimit = 0;
                
                for (size_t j = 0; j < this->_sortedVec.size(); ++j)
                {
                    if (this->_sortedVec[j] == mainValue)
                    {
                        upperLimit = j;
                        break;
                    }
                }
				for (size_t j = pendStart; j <= pendEnd; ++j)
				{
					int pendValue = this->_arr[pendChain[j]];
					
					// 制限付き二分探索
					int insertPos = this->limitedBinarySearch(upperLimit, pendValue);
					
					std::cout << "  Inserting " << pendValue 
								<< " at position " << insertPos << std::endl;
					
					this->_sortedVec.insert(this->_sortedVec.begin() + insertPos, 
											pendValue);
					
					// upperLimit を更新
					upperLimit = insertPos + 1;
				}
			}
			
		}
	}
	if (!stragglerGroup.empty())
	{
		for (size_t i = 0; i < stragglerGroup.size(); ++i)
		{
			int value = this->_arr[stragglerGroup[i]];
			int pos = this->binarySearch(value);
			this->_sortedVec.insert(this->_sortedVec.begin() + pos, value);
		}
	}
}

