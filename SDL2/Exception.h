#pragma once

#define throwRTExcept(desc) throw std::runtime_error(desc  "\n FILE: "   __FILE__  "\n LINE: " + std::to_string(__LINE__) + "\n");