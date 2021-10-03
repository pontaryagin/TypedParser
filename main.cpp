#include <bits/stdc++.h>
#include <string>
using namespace std::string_literals;
using String = std::string;
#include <cassert>

namespace tp{

template<typename T, typename = void>
struct RetTypeImpl{
	using type = T; 
};

template<typename T>
struct RetTypeImpl<T, std::void_t<typename T::ret_type>>{
	using type = typename T::ret_type; 
};

template<typename T>
using RetType = typename RetTypeImpl<T>::type;

template<typename T, char Sep>
struct Vec
{
	using ret_type = std::vector<RetType<T>>;
};

template<typename S, typename T, char sep>
struct Pair
{
	using ret_type = std::pair<RetType<S>, RetType<T>>;
};

template<typename T>
struct Parser{};

template<>
struct Parser<double>
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
		*end = last_char;
		return parsed;
	}
};

template<>
struct Parser<int>
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
		*end = last_char;
		return parsed;
	}
};

template<>
struct Parser<String>
{
	static String parse(char* start, char* end)
	{
		auto last_char = *end;
		*end = '\0';
		auto parsed = String(start);
		*end = last_char;
		return parsed;
	}
};

template<typename T, char Sep>
struct Parser<Vec<T, Sep>>
{
	using _wholeType = Vec<T, Sep>;
	static typename _wholeType::ret_type parse(char* start, char* end)
	{
		// constexpr auto separator = Sep::value;
		constexpr auto separator = Sep;
		size_t cnt = std::count(start, end, Sep);
		typename _wholeType::ret_type parsed;
		parsed.reserve(cnt + 1);
		auto curr_start = start;
		for (auto it = start; it <= end; ++it)
		{
			if (*it == separator || it == end)
			{
				auto val = Parser<T>::parse(curr_start, it);
				parsed.push_back(val);
				curr_start = it + 1;
			}
		}
		return parsed;
	}
};

template<typename S, typename T, char Sep>
struct Parser<Pair<S, T, Sep>>
{
	using _wholeType = Pair<S, T, Sep>;
	static typename _wholeType::ret_type parse(char* start, char* end)
	{
		size_t cnt = std::count(start, end, Sep);
		auto pos = std::find(start, end, Sep);
		if (cnt != 1)
		{
			throw std::invalid_argument("Invalid format for Pair : "s + start);
		}
		return {Parser<S>::parse(start, pos), Parser<T>::parse(pos+1, end)};
	}
};

template<typename T>
auto parse(const String& str)
{
	auto s = std::make_unique<char[]>(str.size()+1);
	str.copy(s.get(), str.size());
	return Parser<T>::parse(s.get(), s.get() + str.size());
}

template<typename T>
auto parse(const char* str)
{
	auto len = std::strlen(str);
	auto s = std::make_unique<char[]>(len+1);
	std::strcpy(s.get(), str);
	return Parser<T>::parse(s.get(), s.get() + len);
}

}

// template <unsigned N>
// struct String_ {
//   char data[N];
// 	constexpr String_() = default;
// 	constexpr String_(const char (&val)[N]) {
// 		std::copy_n(val, N, data);
// 	}
// };

// template<std::size_t ...Len>
// constexpr auto cat(const char (&...strings)[Len]) {
//   constexpr std::size_t N = (... + Len) - sizeof...(Len);
//   String_<N + 1> result = {};
//   result.data[N] = '\0';

//   char* dst = result.data;
//   for (const char* src : {strings...}) {
//     for (; *src != '\0'; src++, dst++) {
//       *dst = *src;
//     }
//   }
//   return result;
// }

// template<String_ str>
// template <String_ chars>
// struct TypeTable
// {
// };


// template<> 
// struct 
// TypeTable<"AAA">
// {
// 	using type = int;
// };

// template<> 
// struct 
// TypeTable<"BBB">
// {
// 	using type = float;
// };

using namespace std;
int main() {

	auto s = "12:23;124:34";
	using T= tp::Vec<tp::Pair<String, int,':'>, ';'>;
	auto d = tp::parse<T>(s);
	assert((d[0] == std::pair<String, int>{"12", 23}));
	assert((d[1] == std::pair<String, int>{"124", 34}));

	return 0;
}	