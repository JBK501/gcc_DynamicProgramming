#pragma once

#include <string>
#include <vector>
#include <map>
#include <list>

namespace EX2
{
// 주어진 문자열의 집합 stringlist에서 target 문자열을 만들 수 있는가?
// target을 만들기 위해 동일한 원소를 여러번 사용해도 됩니다.
// target이 빈 문자열이면 아무것도 선택하지 않는 경우이므로 참입니다. 

// "abcdef" { "ab", "abc", "cd", "def", "abcd"}

// target의 길이 : m, list 원소 개수 : n
// 시간복잡도 : O(n^m * m)
// 공간복잡도 :	O(m^2)

using strings = std::vector<std::string>;

bool CanGenerate(std::string target, const strings& list)
{
	// base case
	if (target == "")
	{
		return true;
	}

	// recursive case
	for (const auto& e : list)
	{
		// target	e		result
		// abcdef	abc	->	def

		if (target.find(e) == 0)
		{
			const std::string result = target.substr(e.length());
			if (CanGenerate(result, list))
			{
				return true;
			}
		}
	}
	return false;
}

// 시간복잡도 : O(m^2*n)
// 공간복잡도 : O(m^2)

using gen_history = std::map<std::string, bool>;
bool CanGenerateOPT(std::string target, const strings& list, gen_history& h)
{
	if (h.count(target) == 1)
		return h[target];

	if (target == "")
		return true;

	for (const auto& e : list)
	{
		if (target.find(e) == 0)
		{
			const std::string result = target.substr(e.length());
			if (CanGenerateOPT(result, list, h))
			{
				h[target] = true;
				return h[target];
			}			
		}
	}
	h[target] = false;
	return h[target];
}

// 주어진 문자열의 집합 stringlist에서 target 문자열을 만들 수 있는 모든 경우의 수를 반환
// target을 만들기 위해 동일한 원소를 여러번 사용해도 됩니다.
// target이 빈 문자열이면 아무것도 선택하지 않는 경우이므로 참입니다. 

// "abcdef" { "ab", "abc", "cd", "def", "abcd"}

// 시간복잡도 : O(m^2*n)
// 공간복잡도 : O(m^2)

using gen_history2 = std::map<std::string, int>;

int HowManyGenerate(std::string target, const strings& list, gen_history2& h)
{
	if (h.count(target) == 1)
		return h[target];

	if (target == "")
		return 1;

	int count{};

	for (const auto& e : list)
	{
		if (target.find(e) == 0)
		{
			count += HowManyGenerate(target.substr(e.length()), list, h);
		}
	}

	h[target] = count;
	return h[target];
}

// 주어진 문자열의 집합 stringlist에서 target 문자열을 만들 수 있는 모든 경우의 수(배열)를 배열로 반환
// target을 만들기 위해 동일한 원소를 여러번 사용해도 됩니다.
// target이 빈 문자열이면 아무것도 선택하지 않는 경우이므로 참입니다. 

// "hello" {"he","h","e","llo"}
// {
//	 {"he", "llo"}
//	 {"h" "e" "llo"}
// }

// "abcdef" { "ab", "abc", "cd", "def", "abcd"}
// {"abc","def}

// "hello" {"a","b","c"}
// {}

// ""	{"a","b","c"}
// {
//	{}
// }

// m : target 길이, n : 집합의 크기
// 시간복잡도 : O(n^m*m) -> O(n^m)
// 공간복잡도 : O(m^2 + m * n) ->O(m^2)

using listlist = std::list<std::list<std::string>>;

listlist FindGenerateAll(std::string target, const strings& list)
{
	if (target == "")
		return listlist{ {} };

	listlist result; 

	for (const auto& e : list)
	{
		if (target.find(e) == 0)
		{
			auto ret = FindGenerateAll(target.substr(e.length()), list);

			for (auto e2 : ret)
			{
				e2.push_front(e);

				result.push_front(e2);
			}
		}
	}
	return result;
}

// 시간복잡도 : O(n^m)
// 공간복잡도 : O(m^2)

using gen_history3 = std::map<std::string, listlist>;
listlist FindGenerateOPT(std::string target, const strings&list, gen_history3 & h)
{
	if (h.count(target) == 1)
		return h[target];

	if (target == "")
		return listlist{ {} };

	listlist result;
	for (const auto& e : list)
	{
		if (target.find(e) == 0)
		{
			auto ret = FindGenerateOPT(target.substr(e.length()), list, h);
			for (auto e2 : ret)
			{
				e2.push_front(e);
				result.push_front(e2);
			}
		}
	}

	h[target] = result;
	return h[target];
}

}

