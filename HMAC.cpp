#include "HMAC.h"
#include <iostream>

std::vector<unsigned char> XORVector(std::vector<unsigned char> _vec, unsigned char _operand) {
	for (auto it = _vec.begin(); it != _vec.end(); it++) {
		*it ^= _operand;
	}
	return _vec;
}

std::vector<unsigned char> HMAC::HMAC(std::vector<unsigned char> _key, std::vector<unsigned char> _msg, HashFunc _hash, size_t _block)
{
	//Generate block key
	auto blockKey = _key.size() > _block ? _hash(_key) : _key;
	blockKey.resize(_block, 0);

	//Generate opad and ipad
	auto opad = XORVector(blockKey, 0x5C);
	auto ipad = XORVector(blockKey, 0x36);

	ipad.insert(ipad.end(), _msg.begin(), _msg.end());
	ipad = _hash(ipad);
	opad.insert(opad.end(), ipad.begin(), ipad.end());
	return _hash(opad);
}
