#ifndef STRING_HPP
#define STRING_HPP

#include <iosfwd>

constexpr int MAXLEN = 1024;

class String{
public:

	explicit String(const char *s =""); //done

	String(const String&s);//done

	String &operator=(const String&s);

	char &operator[](int index);

	int size(); //done

	String reverse();

	int indexOf(char c);

	int indexOf(const String &s);

	bool operator==(const String &s) const; 
	bool operator!=(const String &s) const;
	bool operator>(const String &s) const; 
	bool operator<(const String &s) const;
	bool operator<=(const String &s) const; 
	bool operator>=(const String &s) const;

	String operator+(const String &s);

	String &operator+=(const String &s);

	void print(std::ostream &out) const; //done

	void read(std::istream &in);//done

	~String();//done

	bool in_bound( int i){
		return i >= 0 && i < strlen(buf);
	}


	static int strlen(const char *s);//done
	static char *strcpy(char *dest, const char *src);//done
	static char *strncpy(char *dest, const char *src, int n);//done
	static char *strcat(char *dest, const char *src);//done
	static char *strncat(char *dest, const char *src, int n);//done
	static int strcmp(const char *left, char *right);//done
	static int strncmp(const char *left, char *right, int n);//done
	static void reverse_cpy(char *dest, const char *src);//done
	static const char *strchr(const char *srt, char c);//done
	static const char *strstr(const char *haystack, const char *needle);//done

private:
	char buf[MAXLEN];

};

std::ostream &operator <<(std::ostream &out, const String &s); //done
std::istream &operator>>(std::istream &in, String &s);
#endif 


