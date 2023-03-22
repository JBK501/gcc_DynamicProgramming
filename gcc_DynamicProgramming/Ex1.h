#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>

// �Ǻ���ġ
// ù��°�� �ι�°�� �׻� 1�̰�, �� ���Ĵ� ���� �� ���ڸ� ���� ��

// F(1) = 1
// F(2) = 1
// F(3) = 1 + 1 = 2
// F(4) = 1 + 2 = 3

// �ð����⵵ : O(2^n)
// �������⵵ : O(n)
int Fibonacci(int n)
{
    if (n <= 2)
        return 1;

    return Fibonacci(n - 1) + Fibonacci(n - 2);
}


// �ð����⵵ : O(n)
// �������⵵ : O(n)
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
// M x n�� �������� �»�� -> ���ϴ����� �̵��ϴ� ��� ����� ��
// �̵��� �������̳� �Ʒ������θ� �� �� �ֽ��ϴ�.

// �ð����⵵ : O(2^(m+n))
// �������⵵ : O(m+n)
int FindPath(int m, int n)
{
    // base
    if (m == 0 || n == 0)
        return 0;

    if (m == 1 && n == 1)
        return 1;

    return FindPath(m - 1, n) + FindPath(m, n - 1);
}

// ���� ����
// <string, int(����)> : "m,n"

// �ð����⵵ : O(m x n)
// �������⵵  : O(m + n)
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

// ������ �迭 numbers���� ���ڵ��� �����Ͽ� sum�� ���� �� �ִ��� Ȯ���ϴ� �Լ�
// numbers : ����� ����
// sum�� ����� ���� numbers�� ������ ���Ҹ� ������ ��밡��
// ex_
// CanAccumulate(8, {2,3,5})
// ��� : ��

// sum�� m�̶��ϰ� �迭�� ũ�⸦ n�̶�� �ϸ�
// �ð����⵵ : O(n^m) 
// �������⵵ : O(m + n)

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


// �ð����⵵ : O(m*n)
// �������⵵ : O(m + n + m*n) -> O(m) ������ �ʴ� ���� ������ �� �ִ�.(���⼭�� �迭�� ���� ������ ����)

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

// ������ �迭 numbers���� ���ڵ��� �����Ͽ� sum�� ���� �� �ִ� ���� ������ ��ȯ
// numbers : ����� ����
// sum�� ����� ���� numbers�� ������ ���Ҹ� ������ ��밡��
// ex)
// HowAccumulate(8, {2,3,5})
// ��� : {2,2,2,2} �Ǵ� {3,5} �Ǵ� {2,3,3}
// HowAccumulate(7, {2,4})
// ��� : {}

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

// �ð����⵵ : O(m * n)
// �������⵵ : O(m^2)

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

// ������ �迭 numbers���� ���ڵ��� �����Ͽ� sum�� ���� �� �ִ� ���� ���յ� �߿� ���Ұ� ���� ���� ���
// numbers : ����� ����
// sum�� ����� ���� numbers�� ������ ���Ҹ� ������ ��밡��
// ex)
// MinAccumulate(8, {2,3,5})
// ��� : {3,5}
// MinAccumulate(7, {2,4})
// ��� : {}

// �ð����⵵ : O(m*n)
// �������⵵ : O(m^2 * n)

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


