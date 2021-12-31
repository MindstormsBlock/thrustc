/*
 * Header file for common types
 */

#pragma once

//#define USE_STL_MODULES // - Does not suppot syntax highlighting
#pragma region includes

#ifdef USE_STL_MODULES
import <string>;

import <iostream>;
import <fstream>;

import <memory>;
#else
#include <string>

#include <iostream>
#include <fstream>

#include <memory>
#endif

#pragma endregion

//Definitions for compatibility
#pragma region platformDefs

//Definitions for Windows, GNU/Linux, macOS
#if defined(_WIN32) || defined(__linux__) || defined(__APPLE__)
#define MODERN_DESKTOP
//Definition for X64 platform
#if defined(_WIN64) || defined(__x86_64__) || defined(__ppc4__)
#define X64_PLATFORM
#endif
#endif

#pragma endregion

//Type definitions for modern desktop OSes
//p means "preferred" and is used to get the type most native to a platform, or a general preferred version of a type
#pragma region modernDesktopTypes

#ifdef MODERN_DESKTOP
//Integral types
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

//Floating-point types
using float64 = double;
using float32 = float;
using floatp = float32;

//Size type, used mainly in for-loops
#ifdef X64_PLATFORM
using sizep = uint64;
#else
using sizep = uint32;
#endif

//Character types
using wchar = wchar_t;
using nchar = char;

//String types
using NString = std::string;
using WString = std::wstring;

//Types for main
//Definitions used by main, and ONLY in main
#define ARGC int
#define MAINRET int

#endif

#pragma endregion

//Gets the preffered char/string type based on platform
#pragma region unicodeTypes

#ifdef _WIN32
//Basic types, for character and byte manipulation
using charp = wchar;
using String = WString;

using IFStream = std::wifstream;
using OFStream = std::wofstream;
using OStream = std::wostream;

inline OStream& sout = std::wcout;
inline OStream& serr = std::wcerr;

//Main and character definitions
//Definitions used by main, and ONLY in main
#define MAIN wmain
#define ARGV wchar_t

//Definitions for string literal creation and logging
//DO NOT USE PLAIN STRING/CHAR LITERALS
//DO NOT USE PLAIN LOGGING
#define strVal(x) L## x // - not limited to string, however separating str and char makes debugging easier
#define charVal(x) L## x
//#define sout std::wcout
//#define serr std::wcerr
#else
//Basic types, for character and byte manipulation
using charp = nchar;
using String = NString;

using IFStream = std::ifstream;
using OFStream = std::ofstream;
using OStream = std::ostream;

inline OStream& sout = std::cout;
inline OStream& serr = std::cerr;

//Main and character definitions
//Definitions used by main, and ONLY in main
#define MAIN main
#define ARGV char

//Definitions for string literal creation and logging
//DO NOT USE PLAIN STRING/CHAR LITERALS
#define strVal(x) x //not limited to string, however separating str and char makes debugging easier
#define charVal(x) x
//#define sout std::cout
//#define serr std::cerr
#endif

#pragma endregion

//Definitions for new lines
#pragma region lineBreaks

#ifdef _WIN32
#define newLine strVal("\r\n")
#elif defined(__APPLE__)
#define newLine strVal("\r")
#else
#define newLine strVal("\n")
#endif

#pragma endregion

//Smart pointer types
#pragma region smartPointerTypes

template<typename T>
using ptr = std::unique_ptr<T>;
template<typename T>
using sptr = std::shared_ptr<T>;
template<typename T>
using wptr = std::weak_ptr<T>;

#pragma endregion