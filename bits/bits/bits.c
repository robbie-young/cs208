/*
    bits.c
    Authors: Robbie Young, 24 January 2022
    Credits: Original stubs created by Jeff Ondich, 19 January 2022
    Use: For use in Carleton's CS208 2022 Course
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "bits.h"

void to_upper(char *s) {
    if (s != NULL) {
        for (int i = 0; i < strlen(s) ; i++) {
            if (96 < s[i] && s[i] < 123) {
                s[i] = (char) s[i] & 0xDF;
            }
        }
    }
}   

void to_lower(char *s) {
    if (s != NULL) {
        for (int i = 0; i < strlen(s) ; i++) {
            if (64 < s[i] && s[i] < 91) {
                s[i] = (char) s[i] | 0x20;
            }
        }
    }
}

int middle_bits(int n, int bit_index, int bit_count) {
    if (n >= 0
    && bit_index >= 0 && bit_index <= 31
    && bit_count >= 1 && bit_count <= 31 - bit_index)
    {
        int p = 1;
        while (bit_count > 0) { // calculates which bits to turn off
            p = p * 2;
            bit_count--;
        }
        n = (n >> bit_index) & (p - 1); // shifts then turns all bits but ones wanted
    }
    return n;
}

bool to_utf8(int codepoint, char *utf8_buffer) {
    if (utf8_buffer != NULL
    && codepoint >= 0
    && codepoint <= 0x10FFFF) {
        if (codepoint <= 0x007F) 
        {
            utf8_buffer[0] = (char) codepoint;
            utf8_buffer[1] = 0;
        }
        else if (codepoint <= 0x07FF)
        {
            utf8_buffer[0] = (char) (middle_bits(codepoint, 6, 5) | 0xC0);
            utf8_buffer[1] = (char) (middle_bits(codepoint, 0, 6) | 0x80);
            utf8_buffer[2] = 0;
        }
        else if (codepoint <= 0xFFFF)
        {
            utf8_buffer[0] = (char) (middle_bits(codepoint, 12, 4) | 0xE0);
            utf8_buffer[1] = (char) (middle_bits(codepoint, 6, 6) | 0x80);
            utf8_buffer[2] = (char) (middle_bits(codepoint, 0, 6) | 0x80);
            utf8_buffer[3] = 0;
        }
        else if (codepoint <= 0x10FFFF)
        {
            utf8_buffer[0] = (char) (middle_bits(codepoint, 18, 3) | 0xF0);
            utf8_buffer[1] = (char) (middle_bits(codepoint, 12, 6) | 0x80);
            utf8_buffer[2] = (char) (middle_bits(codepoint, 6, 6) | 0x80);
            utf8_buffer[3] = (char) (middle_bits(codepoint, 0, 6) | 0x80);
            utf8_buffer[4] = 0;
        }
        return true;
    }
    return false;
}

int from_utf8(char *utf8_buffer) {
    if (utf8_buffer != NULL) {
        int byte_count = 0;
        while (utf8_buffer[byte_count] != 0) {
            byte_count++;
        }

        // 1 byte
        if (byte_count == 1
        && utf8_buffer[0] >> 7 == 0)
        {
            return (int) utf8_buffer[0];
        }
        
        // 2 bytes
        if (byte_count == 2
        && (unsigned char) utf8_buffer[0] >> 5 == 0x6
        && (unsigned char) utf8_buffer[1] >> 6 == 0x2)
        {
            int byte_1 = utf8_buffer[0] & 0x1F;
            int byte_2 = utf8_buffer[1] & 0x3F;
            return (byte_1 << 6) | byte_2; // concatenates bytes
        }
        
        // 3 bytes
        if (byte_count == 3
        && (unsigned char) utf8_buffer[0] >> 4 == 0xE
        && (unsigned char) utf8_buffer[1] >> 6 == 0x2
        && (unsigned char) utf8_buffer[2] >> 6 == 0x2)
        {
            int byte_1 = utf8_buffer[0] & 0xF;
            int byte_2 = utf8_buffer[1] & 0x3F;
            int byte_3 = utf8_buffer[2] & 0x3F;
            return (((byte_1 << 6) | byte_2) << 6) | byte_3; // concatenates bytes
        }
        
        // 4 bytes
        if (byte_count == 4
        && (unsigned char) utf8_buffer[0] >> 3 == 0x1E
        && (unsigned char) utf8_buffer[1] >> 6 == 0x2
        && (unsigned char) utf8_buffer[2] >> 6 == 0x2
        && (unsigned char) utf8_buffer[3] >> 6 == 0x2)
        {
            int byte_1 = utf8_buffer[0] & 0x7;
            int byte_2 = utf8_buffer[1] & 0x3F;
            int byte_3 = utf8_buffer[2] & 0x3F;
            int byte_4 = utf8_buffer[3] & 0x3F;
            return (((((byte_1 << 6) | byte_2) << 6) | byte_3) << 6 ) | byte_4; // concatenates bytes
        } 
    }
    return -1;
}