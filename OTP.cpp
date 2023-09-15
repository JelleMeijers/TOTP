#include "OTP.h"
#include <chrono>

#include "HMAC.h"

int OTP::HOTP(std::vector<unsigned char> _key, uint64_t _c, int _digits)
{
    std::vector<unsigned char> msg(8);
    for (int i = 0; i < 8; i++) {
        msg[i] = _c >> 56;
        _c <<= 8;
    }
    auto hmac = HMAC::HMAC_SHA1(_key, msg);
    int offset = *hmac.rbegin() & 0x0F;
    int code = ((hmac[offset] & 0x7F) << 24) | (hmac[offset + 1] << 16) | (hmac[offset + 2] << 8) | hmac[offset + 3];
    return code % (int)pow(10, _digits);
}

int OTP::TOTP(std::vector<unsigned char> _key, int _T1, int _digits)
{
    uint64_t c = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count() / _T1;
    return HOTP(_key, c, _digits);
}
