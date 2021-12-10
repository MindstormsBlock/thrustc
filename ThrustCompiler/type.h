#pragma once

#include <string>

#include <vector>

#include <iostream>
#include <fstream>

#if defined(_WIN32) || defined(__linux__) || defined(__APPLE__)
#define MODERN_DESKTOP
#if defined(_WIN64) || defined(__x86_64__) || defined(__ppc4__)
#define X64_PLATFORM
#endif
#endif

#ifdef MODERN_DESKTOP
using uint64 = unsigned long long int;
using int64 = signed long long int;
using uint32 = unsigned long int;
using int32 = signed long long int;
using uint16 = unsigned short int;
using int16 = signed short int;
using uint8 = unsigned char;
using int8 = signed char;
using uintp = uint32;
using intp = int32;

using float64 = double;
using float32 = float;
using floatp = float32;

#ifdef X64_PLATFORM
using sizep = uint64;
#else
using sizep = uint32;
#endif

#define ARGC int
#define MAINRET int

using char16 = wchar_t;
using char8 = char;

using String8 = std::string;
using String16 = std::wstring;

#endif

#ifdef _UNICODE
using charp = char16;
using String = String16;
using IFStream = std::wifstream;

#define MAIN wmain
#define ARGV wchar_t

#define strVal(x) L## x
#define charVal(x) L## x
#define sout std::wcout
#else
using charp = char8;
using String = String8;
using IFStream = std::ifstream;

#define MAIN main
#define ARGV char

#define strVal(x) x
#define charVal(x) x
#define sout std::cout
#endif