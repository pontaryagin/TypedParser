#include <bits/stdc++.h>
#include <string>
using namespace std::string_literals;
using String = std::string;
#include <charconv>

namespace tp{

template<typename T, char Sep>
struct Vec
{
	using ret_type = std::vector<T>;
};

template<typename T, char Sep>
requires requires (T) { typename T::ret_type; }
struct Vec<T, Sep>
{
	using ret_type = std::vector<typename T::ret_type>;
};



// template<typename T, typename Sep>
// struct Pair
// {
// 	using ret_type = std::pair<T>;
// };

template<char separator>
struct Sep
{
	static constexpr char value = separator;
};

template<typename T>
struct Parser{};


template<>
struct Parser<double>
{
	static double parse(char* start, char* end) 
	{
		// double value;
    // if (auto [ptr, ec] = std::from_chars(start, end, value); ec == std::errc{}) {
    //   std::cout << value << std::endl;
    // }
    // else {
    //   throw std::invalid_argument("Invalid format for double : "s + start);
    // }
		// return value;

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
		size_t cnt = 0;
		for (auto it = start; it < end; ++it)
		{
			if (*it == separator)
			{
				++cnt;
			}
		}
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

#include <memory>
template<typename T>
auto parse(const String& str)
{
	auto s = std::make_unique<char[]>(str.size()+1);
	str.copy(s.get(), str.size());
	return Parser<T>::parse(s.get(), s.get() + str.size());
}
}

int main() {
	using T= tp::Vec<tp::Vec<int,':'>, ';'>;

	String s = "12:23;124:34";
	auto d = tp::parse<T>(s);
	
	return 0;
}