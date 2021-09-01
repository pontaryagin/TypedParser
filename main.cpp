#include <bits/stdc++.h>
#include <string>
using namespace std::string_literals;
using String = std::string;

namespace tp{
// template<typename T>
// RetType
// {
// 	using type = T;
// }

// template<typename T, char sep>
// RetType<Vec<T, sep>>
// {
// 	using type = 
// }

template<typename T, char Sep>
requires	requires(T){ T::ret_type; }
struct Vec
{
    using ret_type = std::vector<T::ret_type>;
};

// template<typename T, typename Sep>
// struct Pair
// {
// 	using rettype = std::pair<T>;
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
	static typename _wholeType::rettype parse(char* start, char* end)
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
		typename _wholeType::rettype parsed;
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

// template<typename T, typename Sep>
// struct Parser<Pair<T, Sep>>
// {
// 	using _wholeType = Pair<T, Sep>;
// 	static typename _wholeType::rettype parse(char* start, char* end)
// 	{
// 		constexpr auto separator = Sep::value;

// 		typename _wholeType::rettype parsed;
// 		parsed.reserve(cnt + 1);
// 		auto curr_start = start;
// 		for (auto it = start; it <= end; ++it)
// 		{
// 			if (*it == separator || it == end)
// 			{
// 				auto val = Parser<T>::parse(curr_start, it);
// 				parsed.push_back(val);
// 				curr_start = it + 1;
// 			}
// 		}
// 		return parsed;
// 	}
// };

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
	String s = "12:23;124:34";
	auto d = tp::parse<tp::Vec<tp::Vec<int,':'>, ':'>>(s);
	// std::cout << d << std::endl;
	String t = "12;2;3";
	
	return 0;
}