#ifndef STRING_HPP
#define STRING_HPP

#include <iosfwd>

class String {
public:
    // constructs this string from a C string, defaults to empty string
    explicit String(const char *s = ""); //done

    // construct this string as a copy of string s
    String(const String &s); //done

    // construct this string by moving from string s
    // String(String &&s);
    // swap buf between this string and s using std::swap, explained later
    void swap(String &s);//done

    // assignment operator from one string, s, to this string
    String &operator=(String s);//done

    // assign to this string by moving from string s
    // String &operator=(String &&s);
    // allow indexing this string with notation s[i]
    char &operator[](int index);

    // allow const indexing
    const char &operator[](int index) const;//done

    // returns the logical length of this string (# of chars up to '\0')
    int size() const;//done

    // returns a reversal of this string, does not modify this string
    String reverse() const;//done

    // returns index into this string for first occurrence of c
    int indexOf(char c) const;

    // returns index into this string for first occurrence of s
    int indexOf(String s) const;

    // relational operators for comparing this strings to another string
    bool operator==(const String &s) const; //done
    bool operator!=(const String &s) const; //done
    bool operator>(const String &s) const;  //done
    bool operator<(const String &s) const;  //done
    bool operator<=(const String &s) const; //done
    bool operator>=(const String &s) const; //done

    // concatenate this and s to form a return string
    String operator+(const String &s) const;

    // concatenate s onto the end of this string
    String &operator+=(const String &s);

    // print this string, hint: use operator << to send buf to out
    void print(std::ostream &out) const;

    // read next word into this string
    // hint: use operator >> to read from in into buf
    void read(std::istream &in);

    // destructor for this string
    ~String();//done

    bool in_bounds(int i) const {
        return i >= 0 && i < strlen(buf);
    }

    // These static helper methods will ultimately be changed to private,
    // but are made public so that you (and the autograder) can test them.
    static int strlen(const char *s);//done
    static char *strcpy(char *dest, const char *src);//done
    static char *strdup(const char *src);
    static char *strncpy(char *dest, const char *src, int n);//done
    static char *strcat(char *dest, const char *src);//done
    static char *strncat(char *dest, const char *src, int n);//done
    static int strcmp(const char *left, const char *right);//done
    static int strncmp(const char *left, const char *right, int n);//done
    static void reverse_cpy(char *dest, const char *src);//done
    static const char *strchr(const char *str, char c);//done
    static const char *strstr(const char *haystack, const char *needle);//done

private:
    char *buf;  // array for the characters in this String
                // DO NOT add any data members - use the null terminator

    // construct string with a buffer of given length
    // Note: private constructors are used when you want to construct
    // an instance of a class that doesn't satisfy the invariants of the class
    // (for example without null-terminator).
    // Useful for implementing reverse() and operator +()
    explicit String(int length);
};

std::ostream &operator<<(std::ostream &out, const String&s);
std::istream &operator>>(std::istream &in, String &s);
#endif
