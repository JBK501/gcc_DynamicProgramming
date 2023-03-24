#pragma once

#include <vector>
#include <string>

namespace EX3
{
	// �Ǻ���ġ
	// F(n) = F(n-1) + F(n-2)
	// F(0) = 0, F(1) = 1

	// �ð����⵵ O(n)
	// �������⵵ O(n)	

	int64_t Fibonacci(int n)
	{
		if (n == 0)
			return 0;

		std::vector<int64_t> table(n + 1);

		// like : base case
		table[0] = 0;
		table[1] = 1;

		// like : recursive case
		for (int i = 0; i <= n; i++)
		{
			if (i + 1 <= n)
			{
				table[i + 1] += table[i];
			}
			if (i + 2 <= n)
			{
				table[i + 2] += table[i];
			}
		}

		return table[n];
	}

	// Find Path
	// M x n�� �������� �»�� -> ���ϴ����� �̵��ϴ� ��� ����� ��
	// �̵��� �������̳� �Ʒ������θ� �� �� �ֽ��ϴ�.

	// �ð����⵵ O(m*n)
	// �������⵵ O(m*n)	

	int FindPath(int m, int n)
	{
		std::vector<std::vector<int>> table(m + 1, std::vector<int>(n + 1, 0));

		table[1][1] = 1;
		for (int row = 0; row <= m; row++)
		{
			for (int col = 0; col <= n; col++)
			{
				if (row + 1 <= m)
					table[row + 1][col] += table[row][col];

				if (col + 1 <= n)
					table[row][col + 1] += table[row][col];;
			}
		}
		return table[m][n];
	}

	// ������ �迭 numbers���� ���ڵ��� �����Ͽ� sum�� ���� �� �ִ��� Ȯ���ϴ� �Լ�
	// numbers : ����� ����
	// sum�� ����� ���� numbers�� ������ ���Ҹ� ������ ��밡��
	// ex_
	// CanAccumulate(8, {2,3,5})
	// ��� : ��

	// sum�� m�̶��ϰ� �迭�� ũ�⸦ n�̶�� �ϸ�
	// �ð����⵵ : O(m * n) 
	// �������⵵ : O(m)

	using integers = std::vector<int>;

	bool CanAccumulate(int sum, const integers& numbers)
	{
		std::vector<bool> table(sum + 1, false);

		table[0] = true;

		for (int i = 0; i <= sum; i++)
		{
			if (table[i] == true)
			{
				for (const auto& e : numbers)
				{
					if (i + e <= sum)
						table[i + e] = true;
				}
			}
		}
		return table[sum];
	}

	// ������ �迭 numbers���� ���ڵ��� �����Ͽ� sum�� ���� �� �ִ� ���� ������ ��ȯ
	// numbers : ����� ����
	// sum�� ����� ���� numbers�� ������ ���Ҹ� ������ ��밡��
	// ex)
	// HowAccumulate(8, {2,3,5})
	// ��� : {2,2,2,2} �Ǵ� {3,5} �Ǵ� {2,3,3}
	// HowAccumulate(7, {2,4})
	// ��� : nullptr
	// HowAccumulate(0, {2,4})
	// ��� : {}

	// �ð����⵵ : O(m^2 * n) 
	// �������⵵ : O(m^2)

	std::shared_ptr<integers> HowAccumulate(int sum, const integers& numbers)
	{
		std::vector<std::shared_ptr<integers>> table(sum + 1, nullptr);

		table[0] = std::make_shared<integers>(0);

		for (int i = 0; i <= sum; i++)
		{
			if (table[i] != nullptr)
			{
				for (const auto& e : numbers)
				{
					if (i + e <= sum)
					{
						table[i + e] = std::make_shared<integers>(*table[i]);
						table[i + e]->push_back(e);
					}
				}
			}
		}
		return table[sum];
	}

	// ������ �迭 numbers���� ���ڵ��� �����Ͽ� sum�� ���� �� �ִ� ���� ���յ� �߿� ���Ұ� ���� ���� ���
	// numbers : ����� ����
	// sum�� ����� ���� numbers�� ������ ���Ҹ� ������ ��밡��
	// ex)
	// MinAccumulate(8, {2,3,5})
	// ��� : {3,5}
	// MinAccumulate(7, {2,4})
	// ��� : nullptr
	// MinAccumulate(0, {1,5})
	// ��� : {}

	// �ð����⵵ : O(m^2*n)
	// �������⵵ : O(m^2)

	std::shared_ptr<integers> MinAccumulate(int sum, const integers& numbers)
	{
		std::vector<std::shared_ptr<integers>> table(sum + 1, nullptr);

		table[0] = std::make_shared<integers>(0);

		for (int i = 0; i <= sum; i++)
		{
			if (table[i])
			{
				for (const auto& e : numbers)
				{
					if (i + e <= sum)
					{
						if (table[i + e] == nullptr || table[i + e]->size() - 1 > table[i]->size())
						{
							table[i + e] = std::make_shared<integers>(*table[i]);
							table[i + e]->push_back(e);
						}
					}
				}
			}
		}
		return table[sum];
	}

	// �־��� ���ڿ��� ���� stringlist���� target ���ڿ��� ���� �� �ִ°�?
	// target�� ����� ���� ������ ���Ҹ� ������ ����ص� �˴ϴ�.
	// target�� �� ���ڿ��̸� �ƹ��͵� �������� �ʴ� ����̹Ƿ� ���Դϴ�. 

	// "abcdef" { "ab", "abc", "cd", "def", "abcd"}

	// target�� ���� : m, list ���� ���� : n
	// �ð����⵵ : O(m^2 * n)
	// �������⵵ :	O(m)

	using strings = std::vector<std::string>;

	bool CanGenerate(const std::string target, const strings& list)
	{
		std::vector<bool> table(target.size() + 1, false);

		table[0] = true;

		for (unsigned int i = 0; i <= target.length(); i++)
		{
			if (table[i] == true)
			{
				for (const auto& e : list)
				{
					if (i + e.length() <= target.length())
					{
						if (target.substr(i, e.length()) == e)
						{
							table[i + e.length()] = true;
						}
					}
				}
			}
		}

		return table[target.length()];
	}


	// �־��� ���ڿ��� ���� stringlist���� target ���ڿ��� ���� �� �ִ� ��� ����� ���� ��ȯ
	// target�� ����� ���� ������ ���Ҹ� ������ ����ص� �˴ϴ�.
	// target�� �� ���ڿ��̸� �ƹ��͵� �������� �ʴ� ����̹Ƿ� ���Դϴ�. 

	// "abcdef" { "ab", "abc", "cd", "def", "abcd"}
	// output : 1

	// �ð����⵵ : O(m^2*n)
	// �������⵵ : O(m)

	int HowManyGenereate(const std::string target, const strings& list)
	{
		std::vector<int> table(target.length() + 1);

		table[0] = 1;

		for (size_t i = 0; i <= target.length(); i++)
		{
			if (table[i] > 0)
			{
				for (const auto& e : list)
				{
					if (i + e.length() <= target.length())
					{
						if (target.substr(i, e.length()) == e)
						{
							table[i + e.length()] += table[i];
						}
					}
				}
			}
		}
		return table[target.length()];
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
	// �ð����⵵ : O(n^m)
	// �������⵵ : O(m^2*n)

	using listlist = std::list<std::list<std::string>>;

	listlist FindGenerateAll(std::string target, const strings& list)
	{
		std::vector<listlist> table(target.length() + 1);

		table[0] = listlist{ {} };

		for (size_t i = 0; i <= target.length(); i++)
		{
			if (table[i].size() > 0)
			{
				for (const auto& e : list)
				{
					if (target.substr(i, e.length())== e)
					{
						for (auto e2 : table[i])
						{
							if (i + e.length() <= target.length())
							{
								e2.push_back(e);
								table[i + e.length()].push_back(e2);
							}
						}
					}
				}
				
			}
		}
		return table[target.length()];
	}
}