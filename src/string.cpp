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
    buf = new char[String::strlen(s.buf) + 1];
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
        cout << "Error:Index out of bounds" << endl;
    }
    return buf[index];
}

char &String::operator[](int index) {
    cout << "Accessing index " << index << " in string of size " << strlen(buf) << endl;
    if (index < 0 || index >= strlen(buf)) {
        cout << "Error:Index out of bounds in String::operator[]" << endl;
    }
    return buf[index];
}


String String::reverse() const{
    int length = strlen(buf); //potential bug
    String reversal(length+1);
    String::reverse_cpy(reversal.buf, buf);
    return reversal;                        
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



void String::read(std::istream &in) {
    std::string temp;
    in >> temp;
    delete[] buf;
    buf = new char[temp.length() + 1];
    strcpy(buf, temp.c_str());
}

std::ostream &operator <<(std::ostream &out, const String s){
    s.print(out);
    return out;
}

std::istream &operator>>(std::istream &in, String &s) {
    s.read(in);
    return in;
}

void String::print(std::ostream &out) const {
    out << buf;
}

int String::indexOf(char c) const{
    // Use the static strchr function to find 'c' in 'buf'
    const char* found = strchr(buf, c);
    if (found) {
        // If found, calculate the index
        return found - buf;
    } else {
        // Return -1 if the character is not found
        return -1;
    }
}

// Find the first occurrence of a String in the string
int String::indexOf(String s) const{
    // Use the static strstr function to find 's' in 'buf'
    const char* found = strstr(buf, s.buf);
    if (found) {
        // If found, calculate the index
        return found - buf;
    } else {
        // Return -1 if the substring is not found
        return -1;
    }
}

// Concatenation operator
String String::operator+(const String &s) const {
    int newLength = strlen(buf) + strlen(s.buf); // Calculate total length
    String newString(newLength); // Create a new string with enough space
    strcpy(newString.buf, buf); // Copy current string to new string
    strcat(newString.buf, s.buf); // Concatenate the argument string
    return newString; // Return the concatenated string
}

String &String::operator+=(const String &s) {
    int newLength = strlen(buf) + strlen(s.buf);
    char* newBuf = new char[newLength + 1]; // Allocate new buffer
    strcpy(newBuf, buf); // Copy current content to new buffer
    strcat(newBuf, s.buf); // Append argument content
    delete[] buf; // Free old buffer
    buf = newBuf; // Replace with new buffer
    return *this; // Return the current object
}

//private constructor
String::String(int length) {
    buf = new char[length + 1];
    buf[length] = '\0';  // Ensure the string is null-terminated
}

