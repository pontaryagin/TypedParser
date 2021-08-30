#include <bits/stdc++.h>
#include <string>
using namespace std::string_literals;
using String = std::string;

namespace tp{
template<typename T, typename Sep>
struct Vec
{
	using rettype = std::vector<T>;
	static rettype parse(String s)
	{

	}

};



template<char separator>
struct Sep
{
	static constexpr char value = separator;
};

template<typename T>
struct parser{};


template<>
struct parser<double>
{
	static double parse(char* start, char* end) 
	{
		auto last_char = *end;
		*end = '\0';
		char* check;
		auto parsed = strtod(start, &check);
		if (check != end)
		{
			*end = last_char;
			throw std::invalid_argument("Invalid format for double : "s + start);
		}
		return parsed;
	}
};

template<>
struct parser<int>
{
	static int parse(char* start, char* end)
	{
		auto last_char = *end;
		*end = '\0';
		char* check;
		auto parsed = static_cast<int>(strtol(start, &check, 10));
		if (check != end)
		{
			*end = last_char;
			throw std::invalid_argument("Invalid format for double : "s + start);
		}
		return parsed;
	}
};

template<template<typename...> typename Vec, typename T, typename Sep>
struct parser<Vec<T, Sep>>
{
	using _wholeType = Vec<T, Sep>;
	static typename _wholeType::rettype parse(char* start, char* end)
	{
		constexpr auto separator = Sep::value;
		size_t cnt = 0;
		for (auto it = start; it < end; ++it)
		{
			if (*it == separator)
			{
				++cnt;
			}
		}
		typename _wholeType::rettype parsed;
		parsed.reserve(cnt + 1);
		auto curr_start = start;
		for (auto it = start; it <= end; ++it)
		{
			if (*it == separator || it == end)
			{
				auto val = parser<T>::parse(curr_start, it);
				parsed.push_back(val);
				curr_start = it + 1;
			}
		}
		return parsed;
	}
};
}

int main() {
	String s = "12";
	auto d = tp::parser<int>::parse(s.data(), s.data() + 2);
	std::cout << d << std::endl;
	String t = "12;2;3";
	auto vec = tp::parser<tp::Vec<int, tp::Sep<';'>>>::parse(t.data(), t.data() + t.size());
  auto vec2 = tp::parser<tp::Sep<

	return 0;
}