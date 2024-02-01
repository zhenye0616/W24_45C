#include <iostream>
#include "string.hpp"
using namespace std;


// note explicit and default for parameter s below are gone

String::String(const char *s) {
    strncpy(buf, s, MAXLEN-1);
}

String::~String() {
    cout << "destructing";
}

String::String(const String &s) {
    strcpy(buf, s.buf);
}


char *String::strncpy(char *dest, const char *src, int n) {
    for (int i = 0; i < n; i++) {
        if (*(src + i) != '\0') {
            dest[i] = src[i]; 
        } else {
            for (; i < n; i++) {
                dest[i] = '\0';
            }
            break;
        }
    }
    return dest;
}


char *String::strcpy( char * dest, const char * src )
{
      int i = 0;
      for ( i = 0; src[i] != '\0'; ++i)  
      {
	    dest[i] = src[i];
      }
      dest[i]  = '\0';
      return dest;
}


int String::strlen(const char *s) {
    int len=0;
    while (s[len] != '\0')
        ++len;
    return len;
}

int String::size() {
    return strlen(buf);
    }

void String::print(std::ostream &out) const {
    out << buf;
}

void String::read(std::istream &in) {
    in.getline(buf, MAXLEN);
}

std::ostream &operator <<(std::ostream &out, const String &s){
    s.print(out);
    return out;
}


char* String::strcat(char* dest, const char* src) {
        char* result = dest; // Save the original 'dest' pointer
        while (*dest) {
            ++dest; // Move 'dest' to the end of the string
        }
        while (*src) {
            *dest++ = *src++; // Copy characters from 'src' to 'dest'
        }
        *dest = '\0'; // Null-terminate the resulting string
        return result;
    }


char* String::strncat(char* dest, const char* src, int n) {
        char* result = dest; // Save the original 'dest' pointer
        while (*dest) {
            ++dest; // Move 'dest' to the end of the string
        }
        while (*src && n-- > 0) {
            *dest++ = *src++; // Copy at most 'n' characters from 'src' to 'dest'
        }
        *dest = '\0'; // Null-terminate the resulting string
        return result;
    }

int String::strcmp(const char* left, char* right) {
        while (*left != '\0' && *right != '\0' && *left == *right) {
            ++left;
            ++right;
        }

        return (*left - *right);
    }


int String::strncmp(const char* left, char* right, int n) {
        while (*left != '\0' && *right != '\0' && n > 0 && *left == *right) {
            ++left;
            ++right;
            --n;
        }

        if (n == 0) {
            return 0; // The first n characters are equal
        }

        return (*left - *right);
    }


const char* String::strchr(const char* s, char c) {
        while (*s) {
            if (*s == c) {
                return s;
            }
            ++s;
        }
        return nullptr; // Character not found
    }


    // Implementation of strstr
const char* String::strstr(const char* haystack, const char* needle) {
        while (*haystack) {
            const char* h = haystack;
            const char* n = needle;
            
            while (*h && *n && (*h == *n)) {
                ++h;
                ++n;
            }

            if (!*n) {
                return haystack; // Found the substring
            }

            ++haystack;
        }

        return nullptr; // Substring not found
    }

void String::reverse_cpy(char* dest, const char* src) {
        int length = String::strlen(src); //potential bug
        for (int i = 0; i < length; ++i) {
            dest[length - i - 1] = src[i];
        }
        dest[length] = '\0'; // Null-terminate the resulting string
    }