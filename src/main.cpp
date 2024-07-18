#include "common.h"


int main(int argc, char* argv[]) {
	sb::init();
	sb::run();
	sb::terminate();

	std::cout << "end main();" << std::endl;
	system("pause");
	return 0;
}