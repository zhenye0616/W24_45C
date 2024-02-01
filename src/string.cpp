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


