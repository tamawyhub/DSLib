#include "AVLTree.hpp"
int main() {
	unsigned long long seed=time(0);
	//unsigned long long seed = 1679878882;
	srand(seed);
	std::cout << "random seed : " << seed << "\n";
	int x=rand()%1000;
	AVLTree<int> t(x);
	int c=x;
	for (int i = 1; i < 10; i++){
		x=rand()%1000;
		t.insert(x);
	}
	t.print();
	std::cout << t.getHeight() << "\n";
	std::cout << "value to be removed: " << c << "\n";
	std::cout << "------------------------\n";
	t.remove(c);
	t.print();
	std::cout << t.getHeight() << "\n";
	return 0;
}
