#include <iostream>
#include <iomanip>
#include <string>

#include "OTP.h"

std::vector<unsigned char> key = { 0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x21, 0xDE, 0xAD, 0xBE, 0xEF };

int main() {
	std::cout << "Code: " << std::setfill('0') << std::setw(6) << OTP::TOTP(key) << std::endl;

	return 0;
}