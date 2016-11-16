/*   Copyright (C) 2016 by Daniel M.H. Noll                                *
 *   Author: Daniel Noll                                                   *
 *                                                                         *
 *   Email: sport.mann@gmx.de                                              *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 * Redistribution and use in source and binary forms, with or without      *
 * modification, are permitted provided that the following conditions are  *
 *  met:                                                                   *
 *                                                                         *
 *     * Redistributions of source code must retain the above copyright    *
 *       notice, this list of conditions and the following disclaimer.     *
 *     * Redistributions in binary form must reproduce the above copyright *
 *       notice, this list of conditions and the following disclaimer in   *
 *       the documentation and/or other materials provided with            *
 *       the distribution.                                                 *
 *     * Neither the name of the author nor the names of its contributors  *
 *       may be used to endorse or promote products derived from this      *
 *       software without specific prior written permission.               *
 *                                                                         *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS     *
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT       *
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR   *
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT    *
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,   *
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT        *
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,   *
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY   *
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT     *
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE   *
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.    *
 ***************************************************************************/

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
