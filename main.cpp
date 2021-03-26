#include <initializer_list>
//#include <iostream>

void freeze_up()
{
	auto bad_var = {1, 2, 3};		// A breakpoint here will trigger the issue.
}									// A breakpoint here is fine.

int main() {
	//std::cout << "freeze test" << std::endl;

	freeze_up();
	
	return 0;
}
