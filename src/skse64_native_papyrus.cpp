#include <algorithm>
#include <locale>
#include "../include/skse64_native_papyrus.h" 

// Copied from skse64 2.0.6 sources

namespace skse64_native_papyrus 
{

	uint32_t GetLength(RE::BSFixedString theString)
	{
		return (uint32_t)strlen(theString.data());
	}

	struct SingleCharStar
	{
		char m_c[2];
		SingleCharStar(char c)
		{
			m_c[0] = c;
			m_c[1] = '\0';
		}
		SingleCharStar& operator=(char c)
		{
			m_c[0] = c;
			return *this;
		}
		const char* c_str() { return m_c; }
	};

	RE::BSFixedString GetNthChar(RE::BSFixedString theString, uint32_t index)
	{
		if (index < 0 || index >= strlen(theString.data()))
			return NULL;
		return SingleCharStar(theString.data()[index]).c_str();
	}

	bool IsUppercase(RE::BSFixedString s)
	{
		if (!s.data())
			return false;
		return (isupper(s.data()[0])) ? true : false;
	}

	bool IsLowercase(RE::BSFixedString s)
	{
		if (!s.data())
			return false;
		return islower(s.data()[0]) ? true : false;
	}

	bool IsLetter(RE::BSFixedString s)
	{
		if (!s.data())
			return false;
		return isalpha(s.data()[0]) ? true : false;
	}
	bool IsDigit(RE::BSFixedString s)
	{
		if (!s.data())
			return false;
		return isdigit(s.data()[0]) ? true : false;
	}
	bool IsPunctuation(RE::BSFixedString s)
	{
		if (!s.data())
			return false;
		return ispunct(s.data()[0]) ? true : false;
	}
	bool IsPrintable(RE::BSFixedString s)
	{
		if (!s.data())
			return false;
		return isprint(s.data()[0]) ? true : false;
	}
	RE::BSFixedString ToUpper(RE::BSFixedString s)
	{
		if (!s.data())
			return NULL;

		return SingleCharStar((char)toupper(s.data()[0])).c_str();
	}

	RE::BSFixedString ToLower(RE::BSFixedString s)
	{
		if (!s.data())
			return NULL;
		return SingleCharStar((char)tolower(s.data()[0])).c_str();
	}

	uint32_t AsOrd(RE::BSFixedString s)
	{
		return s.data()[0];
	}

	RE::BSFixedString AsChar(uint32_t c)
	{
		if (c > 255)
			return NULL;
		return SingleCharStar((char)c).c_str();
	}

	int32_t Find(RE::BSFixedString theString, RE::BSFixedString toFind, uint32_t startIndex)
	{
		if (startIndex < 0)
			startIndex = 0;

		std::string s(theString.data());
		if (startIndex >= s.length())
			return -1;

		std::transform(s.begin(), s.end(), s.begin(), (char (*)(char))::toupper);

		std::string f(toFind.data());
		std::transform(f.begin(), f.end(), f.begin(), (char (*)(char))::toupper);

		std::string::size_type pos = s.find(f, startIndex);
		return (pos == std::string::npos) ? -1 : (int32_t)pos;
	}

	RE::BSFixedString SubString(RE::BSFixedString theString, uint32_t startIndex, uint32_t len)
	{
		if (startIndex < 0)
			return NULL;

		std::string tmpStr(theString.data());
		if (startIndex >= tmpStr.length())
			return NULL;

		std::string sub = (len) ? tmpStr.substr(startIndex, len) : tmpStr.substr(startIndex);
		return sub.c_str();
	}

	std::vector<RE::BSFixedString> Split(RE::BSFixedString theString, RE::BSFixedString theDelimiter)
	{
		std::vector<RE::BSFixedString> result;

		std::string str(theString.data());
		std::string delimiters(theDelimiter.data());

		std::string f(str);  // Eliminate case sensitivity during find
		std::transform(f.begin(), f.end(), f.begin(), (char (*)(char))::toupper);
		std::transform(delimiters.begin(), delimiters.end(), delimiters.begin(), (char (*)(char))::toupper);

		std::string::size_type lastPos = f.find_first_not_of(delimiters, 0);
		std::string::size_type pos = f.find_first_of(delimiters, lastPos);

		while (std::string::npos != pos || std::string::npos != lastPos) {
			std::string token = str.substr(lastPos, pos - lastPos);  // Pull from original string
			result.push_back(RE::BSFixedString(token.c_str()));
			lastPos = f.find_first_not_of(delimiters, pos);
			pos = f.find_first_of(delimiters, lastPos);
		}

		return result;
	}
}
