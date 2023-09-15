#pragma once
#include <vector>

typedef std::vector<unsigned char>(*HashFunc)(std::vector<unsigned char> _msg);

namespace Cryptography
{
	std::vector<unsigned char> SHA1(std::vector<unsigned char> _msg);
};

