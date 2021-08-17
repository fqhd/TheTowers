#include "Program.hpp"
#include <iostream>

int main(){

	//Seeding the random function to be completely random each time
	srand(time(0));

	Program p;
	p.run();

	return 0;
}
