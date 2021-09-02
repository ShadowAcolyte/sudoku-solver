#pragma once

#include <iostream>
#include <cstdint>
#include <chrono>

class benchmark {
    std::uint64_t t_start, t_end;
public:
    benchmark() {
        t_start = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    }
    inline void reset() {
        t_end = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        std::cout << "\nTime taken : " << (t_end - t_start) / 1000.0f << "ms\n";
        t_start = t_end;
    }
};