#include "Zombie.hpp"

int main(void)
{
	std::cout << "=== Testing randomChump (Stack allocation) ===" << std::endl;
    // スタック割り当て - 関数終了時に自動的に破棄される
    randomChump("StackZombie");
    std::cout << "randomChump function ended" << std::endl;
    
    std::cout << "\n=== Testing newZombie (Heap allocation) ===" << std::endl;
    // ヒープ割り当て - 手動でdeleteするまで存続
    Zombie* heapZombie = newZombie("HeapZombie");
    heapZombie->announce();
    
    std::cout << "About to delete heap zombie..." << std::endl;
    delete heapZombie;  // ヒープに割り当てられたオブジェクトは手動でdeleteが必要
    
    std::cout << "\n=== Testing scope example ===" << std::endl;
    {
        Zombie localZombie("LocalZombie");
        localZombie.announce();
        // スコープを出る時にデストラクタが自動的に呼ばれる
    }
    std::cout << "Left scope" << std::endl;
	return 0;
}
