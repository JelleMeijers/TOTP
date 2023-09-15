#include "Cryptography.h"
#include <iostream>
#include <array>

#define ROL(x, n) (((x) << (n)) | ((x) >> (sizeof(x)*8-(n))))

std::vector<unsigned char> Cryptography::SHA1(std::vector<unsigned char> _msg)
{
    //Initialize hash
    std::array<uint32_t, 5> hash = {0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476, 0xC3D2E1F0};

    //Get message length and calculate number of chunks
    size_t msgLen = _msg.size();
    size_t nChunks = ceil(((float)(msgLen + 9)) / 64);

    //Resize to multiple of 512 bits
    _msg.resize(nChunks * 64);

    //append a 1 bit
    _msg[msgLen] = 0x80;

    //Set last 64 bits to msg len
    uint64_t msgLenb = msgLen * 8;
    for (auto it = _msg.rbegin(); it != _msg.rbegin() + 8; it++) {
        *it = msgLenb & 0xFF;
        msgLenb >>= 8;
    }

    //Run compression on all chunks
    for (auto chunk = _msg.begin(); chunk != _msg.end(); chunk += 64)
    {
        //Generate words
        std::array<uint32_t, 80> w;
        for (int i = 0; i < 16; i++) {
            auto word = chunk + i * 4;
            w[i] = (*word << 24) | (*(word + 1) << 16) | (*(word + 2) << 8) | *(word + 3);
        }
        for (int i = 16; i < 80; i++) {
            w[i] = ROL(w[i - 3] ^ w[i - 8] ^ w[i - 14] ^ w[i - 16], 1);
        }

        std::array<uint32_t, 5> abcde = hash;

        for (int i = 0; i < 80; i++) {
            uint32_t f;
            uint32_t k;

            if (i < 20) {
                f = (abcde[1] & abcde[2]) | (~abcde[1] & abcde[3]);
                k = 0x5A827999;
            } else if (i < 40) {
                f = abcde[1] ^ abcde[2] ^ abcde[3];
                k = 0x6ED9EBA1;
            } else if (i < 60) {
                f = (abcde[1] & abcde[2]) | (abcde[1] & abcde[3]) | (abcde[2] & abcde[3]);
                k = 0x8F1BBCDC;
            } else {
                f = abcde[1] ^ abcde[2] ^ abcde[3];
                k = 0xCA62C1D6;
            }

            uint32_t temp = ROL(abcde[0], 5) + f + abcde[4] + k + w[i];
            abcde[4] = abcde[3];
            abcde[3] = abcde[2];
            abcde[2] = ROL(abcde[1], 30);
            abcde[1] = abcde[0];
            abcde[0] = temp;
        }

        for (int i = 0; i < 5; i++) {
            hash[i] += abcde[i];
        }
    }

    //Return the hash
    std::vector<unsigned char> retVal(20);
    for (int i = 0; i < 5; i++) {
        retVal[i*4] = (hash[i] >> 24) & 0xFF;
        retVal[i*4+1] = (hash[i] >> 16) & 0xFF;
        retVal[i*4+2] = (hash[i] >> 8) & 0xFF;
        retVal[i*4+3] = hash[i] & 0xFF;
    }

    return retVal;
}
