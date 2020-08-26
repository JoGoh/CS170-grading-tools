#include <iostream>
#include <string>
#include <cstdlib>
int main(int argc, char **argv) {
	std::string app, app2, app3;
	std::cin >> app, app2, app3;
	int a = atoi(app.c_str()), b = atoi(app2.c_str()), c = atoi(app3.c_str());
	// std::getline(std::cin, app, '\n');
	std::cin >> app;
	if(argc != 2) {
		std::cout << "test: " << (a == b == c == 0 ? "all clear" : "not clear") << "\n";
	} else {
		std::cout << "test " << argv[1] << ": " << (a == b == c == 0 ? "clear" : "not clear") << "\n";
	}
	return 0;
}