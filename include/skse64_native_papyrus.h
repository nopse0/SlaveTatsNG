#pragma once

namespace skse64_native_papyrus
{
	uint32_t		  GetLength(RE::BSFixedString theString);
	RE::BSFixedString GetNthChar(RE::BSFixedString theString, uint32_t index);
	bool              IsUppercase(RE::BSFixedString s);
	bool              IsLowercase(RE::BSFixedString s);
	bool              IsLetter(RE::BSFixedString s);
	bool              IsDigit(RE::BSFixedString s);
	bool              IsPunctuation(RE::BSFixedString s);
	bool              IsPrintable(RE::BSFixedString s);
	RE::BSFixedString ToUpper(RE::BSFixedString s);
	RE::BSFixedString ToLower(RE::BSFixedString s);
	uint32_t          AsOrd(RE::BSFixedString s);
	RE::BSFixedString AsChar(uint32_t c);
	int32_t           Find(RE::BSFixedString theString, RE::BSFixedString toFind, uint32_t startIndex = 0);
	RE::BSFixedString SubString(RE::BSFixedString theString, uint32_t startIndex, uint32_t len = 0);
	std::vector<RE::BSFixedString> Split(RE::BSFixedString theString, RE::BSFixedString theDelimiter);
}
