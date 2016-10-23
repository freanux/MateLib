#ifndef _MATELIB_UTF8_HPP_
#define _MATELIB_UTF8_HPP_

#include <stdint.h>
#include <cstdlib>

namespace Mate {
    // Copyright (c) 2008-2010 Bjoern Hoehrmann <bjoern@hoehrmann.de>
    // See http://bjoern.hoehrmann.de/utf-8/decoder/dfa/ for details.

    static const int UTF8_ACCEPT = 0;
    static const int UTF8_REJECT = 12;

    static const uint8_t _utf8d[] = {
        // The first part of the table maps bytes to character classes that
        // to reduce the size of the transition table and create bitmasks.
         0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
         0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
         0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
         0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
         1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,  9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
         7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
         8,8,2,2,2,2,2,2,2,2,2,2,2,2,2,2,  2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
        10,3,3,3,3,3,3,3,3,3,3,3,3,4,3,3, 11,6,6,6,5,8,8,8,8,8,8,8,8,8,8,8,

        // The second part is a transition table that maps a combination
        // of a state of the automaton and a character class to a state.
         0,12,24,36,60,96,84,12,12,12,48,72, 12,12,12,12,12,12,12,12,12,12,12,12,
        12, 0,12,12,12,12,12, 0,12, 0,12,12, 12,24,12,12,12,12,12,24,12,24,12,12,
        12,12,12,12,12,12,12,24,12,12,12,12, 12,24,12,12,12,12,12,12,12,24,12,12,
        12,12,12,12,12,12,12,36,12,36,12,12, 12,36,12,12,12,12,12,36,12,36,12,12,
        12,36,12,12,12,12,12,12,12,12,12,12,
    };

    inline uint32_t _utf8_decode(const uint32_t byte, uint32_t& state, uint32_t& codep) {
        uint32_t type = _utf8d[byte];
        codep = (state != UTF8_ACCEPT) ? (byte & 0x3fu) | (codep << 6) : (0xff >> type) & (byte);
        state = _utf8d[256 + state + type];

        return state;
    }

    template<typename T> inline bool fast_mbstowcs(T *out, const char *s, size_t len) {
        uint32_t state = UTF8_ACCEPT;

        for (uint32_t codepoint; len; ++s) {
            if (!_utf8_decode(*reinterpret_cast<const unsigned char *>(s), state, codepoint)) {
                *out++ = codepoint;
                len--;
            }
            if (!*s) {
                break;
            }
        }

        return (state == UTF8_ACCEPT);
    }

    template<typename T> inline bool fast_mbtowc(T& out, const char s) {
        return fast_mbstowcs(&out, &s, 1);
    }

}

#endif