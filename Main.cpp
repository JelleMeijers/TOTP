#include <iostream>
#include <string>

#include "Cryptography.h"

int main() {
	std::string msg;
	std::cout << "Msg: ";
	std::getline(std::cin, msg);

	std::vector<unsigned char> input(msg.begin(), msg.end());
	auto hash = Cryptography::SHA1(input);

	std::cout << "Hash: " << std::hex;
	for (const uint32_t h : hash) {
		std::cout << h;
	}
	std::cout << std::endl;

	return 0;
}