#include "console.h"

int main() {
	try {
		workWithExpression W;
		W.Expression();
		std::cout << std::endl;
		std::cout << (1 + 2) + 5 * (3 * (3 + 0)) * sinf(10) + (7);
		//(a+b)+5*(3*(3+0))*sin(x)+(7))
	}
	catch (const char* str) {
		std::cout << str;
	}
	return 0;
}