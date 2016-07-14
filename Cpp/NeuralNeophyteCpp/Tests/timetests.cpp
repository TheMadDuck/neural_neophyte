#include "timetests.h"
#include <random>
TimeTests::TimeTests()
{
    // Test 1:
    std::chrono::high_resolution_clock::time_point t1_start =
            std::chrono::high_resolution_clock::now();
    randomGeneratorTest();
    std::chrono::high_resolution_clock::time_point t1_end
            = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(t1_end - t1_start).count();

    std::cout << std::endl;

    // Test 2:
    std::chrono::high_resolution_clock::time_point t2_start =
            std::chrono::high_resolution_clock::now();
    randomGeneratorTest2();
    std::chrono::high_resolution_clock::time_point t2_end
            = std::chrono::high_resolution_clock::now();

    auto duration2 = std::chrono::duration_cast<std::chrono::nanoseconds>(t2_end - t2_start).count();

    std::cout << std::endl;
    std::cout << "test1: " << duration << std::endl;
    std::cout << "test2: " << duration2 << std::endl;
    std::cout << "test1 / test2: " << (float) duration/(float) duration2 << std::endl;
    std::cout << "test2 / test1: " << (float) duration2/(float) duration << std::endl;
}


//increment Test
////////////////////////////////////////////

void TimeTests::increment()
{
    long number = 0;
    for (int var = 0; var < 1000000; ++var) {
        number += 7;
    }
}

// random generator test
////////////////////////////////////////////
void TimeTests::randomGeneratorTest()
{
    std::mt19937 rd(23);
    std::uniform_int_distribution<int> rdist(0,123);
    for (int var = 0; var < 10; ++var) {
        int i = rdist(rd);
        std::cout << i;
    }
}

void TimeTests::randomGeneratorTest2()
{
    std::random_device a;
    std::uniform_int_distribution<int> rdist(0,123);
    for (int var = 0; var < 10; ++var) {
        int i = rdist(a);
        std::cout << i;
    }
}
/////////////////////////////////////////////
