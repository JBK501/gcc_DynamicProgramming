#include "Ex1.h"
#include "Ex2.h"

using namespace std;

void Print(std::shared_ptr<integers> result)
{
    if (result == nullptr)
    {
        std::cout << "nullptr" << std::endl;
        return;
    }

    std::cout << "{";
    for (const auto& e : *result)
    {
        std::cout << e << ", ";
    }
    std::cout << "}" << std::endl;
}

void Print(const EX2::listlist & result)
{
    std::cout << "{" << std::endl;

    for (const auto& e1 : result)
    {
        cout << "\t{";

        for (const auto& e2 : e1)
        {
            cout << e2 << ", ";
        }

        cout << "}," << endl;
    }

    std::cout << "}" << std::endl;
}

int main()
{
    //std::cout << Fibonacci(50) << std::endl;

    /*std::map<int, int64_t> h;
    std::cout << FibonacciOPT(50, h) << std::endl;*/

    //std::cout << FindPath(20,20) << std::endl;

    /*path_history h;
    std::cout << FindPathOPT(20, 20, h)<<std::endl;*/

    //std::cout << CanAccumulate(7, { 2,4 }) << std::endl;

    //accum_history h;
    //std::cout << CanAccumulateOPT(8, { 2,3,5 }, h) << std::endl;

    /*Print(HowAccumulate(8, { 2,3,5 }));
    Print(HowAccumulate(7, { 2,4 }));*/

    //how_accum_history h;
    //Print(HowAccumulateOPT(8, { 2,3,5 }, h));
    //h.clear();
    //Print(HowAccumulateOPT(7, { 2,4 }, h));

    //h.clear();
    //Print(MinAccumulate(8, { 2,3,5 }, h));

    //h.clear();
    //Print(MinAccumulate(7, { 2,4 }, h));

    //h.clear();
    //Print(MinAccumulate(720, { 500,100,50,10 }, h));

   /* std::cout<<EX2::CanGenerate("abcdef", { "ab","abc","cd","def","abcd" })<<std::endl;
    std::cout << EX2::CanGenerate("abcd", { "a","b","c","d"}) << std::endl;
    std::cout << EX2::CanGenerate("hello", { "a","b","c","d" }) << std::endl;

    EX2::gen_history h;
    std::cout << EX2::CanGenerateOPT("abcdef", { "ab","abc","cd","def","abcd" },h) << std::endl;
    h.clear();
    std::cout << EX2::CanGenerateOPT("abcd", { "a","b","c","d" },h) << std::endl;
    h.clear();
    std::cout << EX2::CanGenerateOPT("hello", { "a","b","c","d" },h) << std::endl;*/

    /*EX2::gen_history2 h;
    std::cout << EX2::HowManyGenerate("abcdef", { "ab", "abc", "cd", "def", "abcd" }, h) << std::endl;
    h.clear();
    std::cout << EX2::HowManyGenerate("abcd", { "a","b","c","d" }, h) << std::endl;
    h.clear();
    std::cout << EX2::HowManyGenerate("hello", { "a","b","c","d" }, h) << std::endl;*/


    Print(EX2::FindGenerateAll("hello", { "h","e","he","llo","hll" }));

    EX2::gen_history3 h;
    Print(EX2::FindGenerateOPT("hello", { "h","e","he","llo","hll" },h));

}


