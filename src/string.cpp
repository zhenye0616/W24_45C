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
    int i;
    for (i = 0; i < n && src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    dest[i] = '\0'; // Ensure null-termination

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

int String::size() const{
    return strlen(buf);
    }

void String::print(std::ostream &out) const {
    out << buf;
}

void String::read(std::istream &in) {
    char temp[MAXLEN];
    in.getline(temp, MAXLEN);
    temp[MAXLEN - 1] = '\0';
    String::strncpy(buf, temp, MAXLEN);
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

void String::reverse_cpy(char* dest, const char* src) {
        int length = String::strlen(src); //potential bug
        for (int i = 0; i < length; ++i) {
            dest[length - i - 1] = src[i];
        }
        dest[length] = '\0'; // Null-terminate the resulting string
    }

String String::reverse() const{
    String reversed; 
    int length = String::strlen(buf);
    int maxLength = length < MAXLEN ? length : MAXLEN - 1;
    for (int i = 0; i < maxLength; ++i) {
        reversed.buf[i] = buf[length - 1 - i]; // Copy characters in reverse order
    }
    reversed.buf[maxLength] = '\0'; // Null-terminate the reversed string

    return reversed;
}

// Assignment operator
String &String::operator=(const String &s) {
    if (this != &s) { // Check for self-assignment
        String::strcpy(buf, s.buf);
    }
    return *this;
}

// Subscript operator for non-const Strings
char &String::operator[](int index) {
    if (!in_bound(index)) {
        // Handle the error, e.g., throw an exception or terminate the program
        throw std::out_of_range("Index out of bounds");
    }
    return buf[index];
}

// Comparison operators
bool String::operator==(const String &s) const {
    return String::strcmp(buf, s.buf) == 0;
}

bool String::operator!=(const String &s) const {
    return String::strcmp(buf, s.buf) != 0;
}

bool String::operator>(const String &s) const {
    return String::strcmp(buf, s.buf) > 0;
}

bool String::operator<(const String &s) const {
    return String::strcmp(buf, s.buf) < 0;
}

bool String::operator<=(const String &s) const {
    return String::strcmp(buf, s.buf) <= 0;
}

bool String::operator>=(const String &s) const {
    return String::strcmp(buf, s.buf) >= 0;
}

// Concatenation operator
String String::operator+(const String &s) const{
    String newString;
    String::strcpy(newString.buf, buf); // Copy the current string
    String::strncat(newString.buf, s.buf, MAXLEN - String::strlen(newString.buf) - 1); // Concatenate the parameter string
    return newString;
}

// Concatenation-assignment operator
String &String::operator+=(const String &s) {
    if (this == &s) {
        char *temp = new char[String::strlen(s.buf) + 1];
        String::strcpy(temp, s.buf);

        String::strncat(buf, temp, MAXLEN - String::strlen(buf) - 1);
        delete[] temp;
    } else {
        String::strncat(buf, s.buf, MAXLEN - String::strlen(buf) - 1);
    }
    
    return *this;
}

std::ostream &operator <<(std::ostream &out, const String &s){
    s.print(out);
    return out;
}

std::istream &operator>>(std::istream &in, String &s) {
    s.read(in);
    return in;
}

int String::indexOf(char c) const{
    // Use the static strchr function to find 'c' in 'buf'
    const char* found = String::strchr(buf, c);
    if (found) {
        // If found, calculate the index
        return found - buf;
    } else {
        // Return -1 if the character is not found
        return -1;
    }
}

// Find the first occurrence of a String in the string
int String::indexOf(const String &s) const{
    // Use the static strstr function to find 's' in 'buf'
    const char* found = String::strstr(buf, s.buf);
    if (found) {
        // If found, calculate the index
        return found - buf;
    } else {
        // Return -1 if the substring is not found
        return -1;
    }
}