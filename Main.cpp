#include <iostream>
#include <string>

#include "HMAC.h"

int main() {
	std::string msg = "The quick brown fox jumps over the lazy dog";
	//std::cout << "Msg: ";
	//std::getline(std::cin, msg);

	std::string key = "key";
	//std::cout << "Key: ";
	//std::getline(std::cin, key);

	std::vector<unsigned char> msgBytes(msg.begin(), msg.end());
	std::vector<unsigned char> keyBytes(key.begin(), key.end());

	auto hmac = HMAC::HMAC_SHA1(keyBytes, msgBytes);

	std::cout << "Expected HMAC: \tde7c9b85b8b78aa6bc8a7a36f70a90701c9db4d9" << std::endl;
	std::cout << "HMAC: \t\t" << std::hex;
	for (const auto b : hmac) {
		if (b < 0x10)
			std::cout << "0";
		std::cout << (int)b;
	}
	std::cout << std::endl;

	return 0;
}