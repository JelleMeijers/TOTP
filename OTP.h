#pragma once
#include <stdint.h>
#include <vector>

namespace OTP
{
	int HOTP(std::vector<unsigned char> _key, uint64_t _c, int _digits = 6);
	int TOTP(std::vector<unsigned char> _key, int _T1 = 30, int _digits = 6);
};

