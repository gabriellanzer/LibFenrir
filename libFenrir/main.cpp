#include "App.h"
#include <ctime>

int main() {
	std::srand(std::time(0));
	App::init(800,640,"LibFenrir", false);
	App::run();
	App::end();
	return 0;
}