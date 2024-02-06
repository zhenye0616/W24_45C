#include <iostream>
#include "string.hpp"
#include <stdexcept> 
using namespace std;


// note explicit and default for parameter s below are gone

String::~String() {
    delete[] buf; // Deallocate the dynamically allocated memory
    cout << "destructing";
}

String::String(const char *s) {
    buf = new char[String::strlen(s) + 1]; // +1 for null-terminator
    strcpy(buf, s);
}

String::String(const String &s) {
    strcpy(buf, s.buf);
}

int String::size() const{
    return strlen(buf);
}

void String::swap(String &s) {
    std::swap(buf, s.buf);
}

String &String::operator=(String s) {
    swap(s); 
    return *this; 
}


const char &String::operator[](int index) const {
    if (!in_bounds(index)) {
        throw std::out_of_range("Index out of bounds");
    }
    return buf[index];
}



//static methods:

int String::strlen(const char *s) {
    int len=0;
    while (s[len] != '\0')
        ++len;
    return len;
}


char *String::strcpy( char * dest, const char * src )
{
      int i;
      for ( i = 0; src[i] != '\0'; ++i)  
      {
	    dest[i] = src[i];
      }
      dest[i]  = '\0';
      return dest;
}

char *String::strncpy(char *dest, const char *src, int n) {
    int i;
    for (i = 0; i < n && src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    dest[i] = '\0'; // Ensure null-termination

    return dest;
}

char *String::strdup(const char *src) {
    int length = strlen(src);
    char *duplicate = new char[length + 1];
    strcpy(duplicate, src);
    return duplicate;
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

int String::strcmp(const char* left, const char* right) {
        while (*left != '\0' && *right != '\0' && *left == *right) {
            ++left;
            ++right;
        }

        return (*left - *right);
    }


int String::strncmp(const char* left, const char* right, int n) {
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

void String::reverse_cpy(char* dest, const char* src) {
        int length = String::strlen(src);
        for (int i = 0; i < length; ++i) {
            dest[length - i - 1] = src[i];
        }
        dest[length] = '\0'; // Null-terminate the resulting string
    }


const char* String::strchr(const char* s, char c) {
    do {
        if (*s == c) {
            return s;
        }
    } while (*s++); 
    return nullptr;
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







