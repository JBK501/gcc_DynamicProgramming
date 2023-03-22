#pragma once

#include <string>
#include <vector>
#include <map>
#include <list>

namespace EX2
{
// �־��� ���ڿ��� ���� stringlist���� target ���ڿ��� ���� �� �ִ°�?
// target�� ����� ���� ������ ���Ҹ� ������ ����ص� �˴ϴ�.
// target�� �� ���ڿ��̸� �ƹ��͵� �������� �ʴ� ����̹Ƿ� ���Դϴ�. 

// "abcdef" { "ab", "abc", "cd", "def", "abcd"}

// target�� ���� : m, list ���� ���� : n
// �ð����⵵ : O(n^m * m)
// �������⵵ :	O(m^2)

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

// �ð����⵵ : O(m^2*n)
// �������⵵ : O(m^2)

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

// �־��� ���ڿ��� ���� stringlist���� target ���ڿ��� ���� �� �ִ� ��� ����� ���� ��ȯ
// target�� ����� ���� ������ ���Ҹ� ������ ����ص� �˴ϴ�.
// target�� �� ���ڿ��̸� �ƹ��͵� �������� �ʴ� ����̹Ƿ� ���Դϴ�. 

// "abcdef" { "ab", "abc", "cd", "def", "abcd"}

// �ð����⵵ : O(m^2*n)
// �������⵵ : O(m^2)

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

// �־��� ���ڿ��� ���� stringlist���� target ���ڿ��� ���� �� �ִ� ��� ����� ��(�迭)�� �迭�� ��ȯ
// target�� ����� ���� ������ ���Ҹ� ������ ����ص� �˴ϴ�.
// target�� �� ���ڿ��̸� �ƹ��͵� �������� �ʴ� ����̹Ƿ� ���Դϴ�. 

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

// m : target ����, n : ������ ũ��
// �ð����⵵ : O(n^m*m) -> O(n^m)
// �������⵵ : O(m^2 + m * n) ->O(m^2)

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

// �ð����⵵ : O(n^m)
// �������⵵ : O(m^2)

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

