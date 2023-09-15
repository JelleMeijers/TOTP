#pragma once
#include <vector>

#include "Cryptography.h"

namespace HMAC
{
	std::vector<unsigned char> HMAC(std::vector<unsigned char> _key, std::vector<unsigned char> _msg, HashFunc _hash, size_t _block);
	
	inline std::vector<unsigned char> HMAC_SHA1(std::vector<unsigned char> _key, std::vector<unsigned char> _msg) { return HMAC(_key, _msg, Cryptography::SHA1, 64); }
};

