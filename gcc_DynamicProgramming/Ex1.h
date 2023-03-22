#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>

// 피보나치
// 첫번째와 두번째는 항상 1이고, 그 이후는 앞의 두 숫자를 더한 것

// F(1) = 1
// F(2) = 1
// F(3) = 1 + 1 = 2
// F(4) = 1 + 2 = 3

// 시간복잡도 : O(2^n)
// 공간복잡도 : O(n)
int Fibonacci(int n)
{
    if (n <= 2)
        return 1;

    return Fibonacci(n - 1) + Fibonacci(n - 2);
}


// 시간복잡도 : O(n)
// 공간복잡도 : O(n)
int64_t FibonacciOPT(int n, std::map<int, int64_t>& history)
{
    if (history.count(n) == 1)
        return history[n];

    if (n <= 2)
        return 1;

    history[n] = FibonacciOPT(n - 1, history) + FibonacciOPT(n - 2, history);
    return history[n];
}

// Find Path
// M x n의 영역에서 좌상단 -> 우하단으로 이동하는 모든 경우의 수
// 이동은 오른쪽이나 아래쪽으로만 할 수 있습니다.

// 시간복잡도 : O(2^(m+n))
// 공간복잡도 : O(m+n)
int FindPath(int m, int n)
{
    // base
    if (m == 0 || n == 0)
        return 0;

    if (m == 1 && n == 1)
        return 1;

    return FindPath(m - 1, n) + FindPath(m, n - 1);
}

// 정답 저장
// <string, int(정답)> : "m,n"

// 시간복잡도 : O(m x n)
// 공간복잡도  : O(m + n)
using path_history = std::map<std::string, int>;
int FindPathOPT(int m, int n, path_history& h)
{
    const std::string key = std::to_string(m) + "," + std::to_string(n);
    if (h.count(key) == 1)
        return h[key];

    const std::string rkey = std::to_string(n) + "," + std::to_string(m);
    if (h.count(rkey) == 1)
        return h[rkey];

    // base
    if (m == 0 || n == 0)
        return 0;

    if (m == 1 && n == 1)
        return 1;

    h[key] = FindPathOPT(m - 1, n, h) + FindPathOPT(m, n - 1, h);
    return h[key];
}

// 정수의 배열 numbers에서 숫자들을 조합하여 sum을 만들어낼 수 있는지 확인하는 함수
// numbers : 양수의 집합
// sum을 만들기 위해 numbers의 동일한 원소를 여러번 사용가능
// ex_
// CanAccumulate(8, {2,3,5})
// 출력 : 참

// sum을 m이라하고 배열의 크기를 n이라고 하면
// 시간복잡도 : O(n^m) 
// 공간복잡도 : O(m + n)

using integers = std::vector<int>;
bool CanAccumulate(int sum, integers numbers)
{
    // base 
    if (sum == 0)
        return true;
    if (sum < 0)
        return false;

    // recursive
    for (const auto& e : numbers)
    {
        if (CanAccumulate(sum - e, numbers) == true)
            return true;
    }

    return false;
}


// 시간복잡도 : O(m*n)
// 공간복잡도 : O(m + n + m*n) -> O(m) 변하지 않는 값은 제거할 수 있다.(여기서는 배열의 값은 변하지 않음)

using accum_history = std::map<int, bool>;
bool CanAccumulateOPT(int sum, integers numbers, accum_history& h)
{
    if (h.count(sum) == 1)
        return h[sum];

    if(sum == 0)
        return true;
    if (sum < 0)
        return false;

    for (const auto& e : numbers)
    {
        if (CanAccumulateOPT(sum - e, numbers, h))
        {
            h[sum] = true;
            return h[sum];
        }
    }

    h[sum] = false;
    return h[sum];
}

// 정수의 배열 numbers에서 숫자들을 조합하여 sum을 만들어낼 수 있는 숫자 집합을 반환
// numbers : 양수의 집합
// sum을 만들기 위해 numbers의 동일한 원소를 여러번 사용가능
// ex)
// HowAccumulate(8, {2,3,5})
// 출력 : {2,2,2,2} 또는 {3,5} 또는 {2,3,3}
// HowAccumulate(7, {2,4})
// 출력 : {}

std::shared_ptr<integers> HowAccumulate(int sum, integers numbers)
{
    if (sum == 0)
        return std::make_shared<integers>();
    
    if (sum < 0)
        return nullptr;

    for (const auto& e : numbers)
    {
        auto ret = HowAccumulate(sum - e, numbers);
        if (ret != nullptr)
        {
            ret->push_back(e);
            return ret;
        }
    }
    return nullptr;
}

// 시간복잡도 : O(m * n)
// 공간복잡도 : O(m^2)

using how_accum_history = std::map<int, std::shared_ptr<integers>>;
std::shared_ptr<integers> HowAccumulateOPT(int sum, integers numbers,how_accum_history& h)
{
    if (h.count(sum) == 1)
        return h[sum];

    if (sum == 0)
        return std::make_shared<integers>();

    if (sum < 0)
        return nullptr;

    for (const auto& e : numbers)
    {
        auto ret = HowAccumulateOPT(sum - e, numbers,h);
        if (ret != nullptr)
        {
            ret->push_back(e);
            h[sum] = ret;
            return h[sum];
        }
    }

    h[sum] = nullptr;
    return h[sum];
}

// 정수의 배열 numbers에서 숫자들을 조합하여 sum을 만들어낼 수 있는 숫자 집합들 중에 원소가 가장 적은 결과
// numbers : 양수의 집합
// sum을 만들기 위해 numbers의 동일한 원소를 여러번 사용가능
// ex)
// MinAccumulate(8, {2,3,5})
// 출력 : {3,5}
// MinAccumulate(7, {2,4})
// 출력 : {}

// 시간복잡도 : O(m*n)
// 공간복잡도 : O(m^2 * n)

std::shared_ptr<integers> MinAccumulate(int sum, integers numbers, how_accum_history& h)
{
    if (h.count(sum) == 1)
        return h[sum];

    if (sum == 0)
        return std::make_shared<integers>();

    if (sum < 0)
        return nullptr;

    std::shared_ptr<integers> min{};

    for (const auto& e : numbers)
    {
        auto ret = MinAccumulate(sum - e, numbers, h);

        if (ret != nullptr)
        {
            std::shared_ptr<integers> v = std::make_shared<integers>();
            v->resize(ret->size());
            std::copy(ret->begin(), ret->end(), v->begin());
            v->push_back(e);
            
            if (min == nullptr || v->size() < min->size())
                min = v;
        }
    }

    h[sum] = min;
    return h[sum];
}


