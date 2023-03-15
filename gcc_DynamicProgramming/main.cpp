#include <iostream>
#include <string>
#include <map>

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

int main()
{
    //std::cout << Fibonacci(50) << std::endl;

    /*std::map<int, int64_t> h;
    std::cout << FibonacciOPT(50, h) << std::endl;*/

    //std::cout << FindPath(20,20) << std::endl;

    path_history h;
    std::cout << FindPathOPT(20, 20, h)<<std::endl;
}

