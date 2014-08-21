#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

class String
{
public:
	String(const char *str = NULL);
	String(const String &other);
	~String();
	String & operator=(const String &other);
	String operator+(const String &other);
	bool operator==(const String &other);
	char & operator[](unsigned int idx);
	size_t size();
public:
	friend ostream & operator<<(ostream &os, String &s);
	friend istream & operator>>(istream &is, String &s);
private:
	char *m_data;
};


String::String(const char *str)
{
	if (!str)
	{
		m_data = new char[1];
		*m_data = '\0';
	}
	else
	{
		m_data = new char[strlen(str) + 1];
		strcpy(m_data, str);
	}
}

String::String(const String &other)
{
	if (m_data)	
	{
		delete []m_data;
		m_data = NULL;
	}

	if (other.m_data)
	{
		m_data = new char[strlen(other.m_data) + 1];
		strcpy(m_data, other.m_data);	
	}
}

String::~String()
{
	if (m_data)
		delete []m_data;
}

String & String::operator=(const String &other)
{
	if (this != &other)
	{
		if (m_data)	
		{
			delete []m_data;
			m_data = NULL;
		}

		if (other.m_data)
		{
			m_data = new char[strlen(other.m_data) + 1];
			strcpy(m_data, other.m_data);	
		}
	}

	return *this;
}

String  String::operator+(const String &other)
{
	String newStr;

	if (!other.m_data)
	{
		newStr = *this;
	}

	if (!m_data)
	{
		newStr = other;
	}
	else
	{
		newStr.m_data = new char[strlen(m_data) + strlen(other.m_data) + 1];	
		strcpy(newStr.m_data, m_data);
		strcat(newStr.m_data, other.m_data);
	}

	return newStr;
}

bool String::operator==(const String &other)
{
	if (!m_data || !other.m_data)
		return false;

	return strcmp(m_data, other.m_data) ? false : true;
}

char & String::operator[](unsigned int idx)
{
	if (!m_data)
	{
		m_data = new char[1];
		m_data[0] = '\0';
		return m_data[0];
	}

	if (idx >= strlen(m_data))	
		return m_data[0];

	return m_data[idx];
}

size_t String::size()
{
	if (m_data)
		return strlen(m_data);
	else
		return 0;
}

ostream & operator<<(ostream &os, String &s)
{
	os << s.m_data;
	return os;
}

istream & operator>>(istream &is, String &s)
{
	char temp[255];
	is >> setw(255) >> temp;
	s = temp; 

	return is;
}

int main()
{
	String s;
	String t("world");
	s = "hello";

	cout << s << endl; 
	cout << t << endl;
	cout << s.size() << endl;

	String r = s + " " + t;
	cout << r << endl;

	return 0;
}








