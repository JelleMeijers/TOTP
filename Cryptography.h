#pragma once
#include <array>
#include <vector>

namespace Cryptography
{
	std::array<uint32_t, 5> SHA1(std::vector<unsigned char> _msg);
};

