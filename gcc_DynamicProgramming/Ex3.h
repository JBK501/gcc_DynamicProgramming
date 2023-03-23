#pragma once

#include <vector>

namespace EX3
{
	// 피보나치
	// F(n) = F(n-1) + F(n-2)
	// F(0) = 0, F(1) = 1

	// 시간복잡도 O(n)
	// 공간복잡도 O(n)	

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
	// M x n의 영역에서 좌상단 -> 우하단으로 이동하는 모든 경우의 수
	// 이동은 오른쪽이나 아래쪽으로만 할 수 있습니다.

	// 시간복잡도 O(m*n)
	// 공간복잡도 O(m*n)	

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

	// 정수의 배열 numbers에서 숫자들을 조합하여 sum을 만들어낼 수 있는지 확인하는 함수
	// numbers : 양수의 집합
	// sum을 만들기 위해 numbers의 동일한 원소를 여러번 사용가능
	// ex_
	// CanAccumulate(8, {2,3,5})
	// 출력 : 참

	// sum을 m이라하고 배열의 크기를 n이라고 하면
	// 시간복잡도 : O(m * n) 
	// 공간복잡도 : O(m)

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

	// 정수의 배열 numbers에서 숫자들을 조합하여 sum을 만들어낼 수 있는 숫자 집합을 반환
	// numbers : 양수의 집합
	// sum을 만들기 위해 numbers의 동일한 원소를 여러번 사용가능
	// ex)
	// HowAccumulate(8, {2,3,5})
	// 출력 : {2,2,2,2} 또는 {3,5} 또는 {2,3,3}
	// HowAccumulate(7, {2,4})
	// 출력 : nullptr
	// HowAccumulate(0, {2,4})
	// 출력 : {}

	// 시간복잡도 : O(m^2 * n) 
	// 공간복잡도 : O(m^2)

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

	// 정수의 배열 numbers에서 숫자들을 조합하여 sum을 만들어낼 수 있는 숫자 집합들 중에 원소가 가장 적은 결과
	// numbers : 양수의 집합
	// sum을 만들기 위해 numbers의 동일한 원소를 여러번 사용가능
	// ex)
	// MinAccumulate(8, {2,3,5})
	// 출력 : {3,5}
	// MinAccumulate(7, {2,4})
	// 출력 : nullptr
	// MinAccumulate(0, {1,5})
	// 출력 : {}

	// 시간복잡도 : O(m^2*n)
	// 공간복잡도 : O(m^2)

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

}