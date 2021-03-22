#include <initializer_list>

void freeze_up()
{
	auto bad_var = {1, 2, 3};
}

int main() {
	freeze_up();
	
	return 0;
}
