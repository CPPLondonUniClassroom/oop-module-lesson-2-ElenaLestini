#include <iostream>
#include <string>
#include <sstream>
#include "private/Checker.h"
#include "EXERCISE.h"

using namespace std::string_literals;
using chk = Checker<ILogger>;
using chk2 = Checker<StringLogger>;

bool part1err = false, part2err = false;


template<class T, T, class = std::bool_constant<false> >
struct has_virtual_function
        : std::true_type { };

template<class T, T X>
struct has_virtual_function<T, X, std::bool_constant<X != X> >
        : std::false_type { };

template<class T, T X>
constexpr bool has_virtual_function_v = has_virtual_function<T, X>::value;

template <typename T>
void TryImplLogInfo() {
    if constexpr (!has_virtual_function_v<decltype(&T::LogInfo), &T::LogInfo>) {
        std::cerr << "ERROR: ILogger does not have a virtual LogInfo()\n";
        part1err = true;
    }
}

template <typename T>
void TryImplLogError() {
    if constexpr (!has_virtual_function_v<decltype(&T::LogError), &T::LogError>) {
        std::cerr << "ERROR: ILogger does not have a virtual LogError()\n";
        part1err = true;
    }
}

template <typename T>
void TryImplGetLastError() {
    if constexpr (!has_virtual_function_v<decltype(&T::GetLastError), &T::GetLastError>) {
        std::cerr << "ERROR: ILogger does not have a virtual GetLastError()\n";
        part1err = true;
    }
}

template <typename T>
void TestStringLogger() {
    {
        std::ostringstream ss;
        T sl{ss};
        sl.LogInfo("Info msg");
        if (ss.str() != "INFO: Info msg") {
            std::cerr << "ERROR: StringLogger does not log the info message correctly\n";
            part2err = true;
        }
    }
    {
        std::ostringstream ss;
        T sl{ss};
        sl.LogError("Err msg");
        if (ss.str() != "ERROR: Err msg") {
            std::cerr << "ERROR: StringLogger does not log the error message correctly\n";
            part2err = true;
        }
        if (sl.GetLastError() != "Err msg") {
            std::cerr
                    << "ERROR: StringLogger does not return the last error message from GetLastError()\n";
            part2err = true;
        }
        if (sl.LogError("a").LogInfo("b").GetLastError() != "a") {
            std::cerr
                    << "ERROR: StringLogger does not replace the last error when a new one is written\n";
            part2err = true;
        }
    }
}

int main() {
    if constexpr (!std::is_abstract_v<ILogger>) {
        std::cerr << "ERROR: ILogger has at least one non-virtual function or none at all\n";
        part1err = true;
    } else {
        if constexpr (chk::has_loginfo)
            TryImplLogInfo<ILogger>();
        else {
            std::cerr << "ERROR: ILogger does not have LogInfo()\n";
            part1err = true;
        }
        if constexpr (chk::has_logerror)
            TryImplLogError<ILogger>();
        else {
            std::cerr << "ERROR: ILogger does not have LogError()\n";
            part1err = true;
        }
        if constexpr (chk::has_getlasterror)
            TryImplGetLastError<ILogger>();
        else {
            std::cerr << "ERROR: ILogger does not have GetLastError()\n";
            part1err = true;
        }
    }
    if constexpr (!std::has_virtual_destructor_v<ILogger>) {
        std::cerr << "ERROR: ILogger does not have a virtual destructor\n";
        part1err = true;
    }
    if (part1err)
        std::cerr << "Part 1 not passed. Part 2 will not be checked.\n";
    else {
        std::cout << "Part 1 passed!" << std::endl;
        if constexpr (!std::is_base_of_v<ILogger, StringLogger> || !std::is_convertible_v<StringLogger&, ILogger&>) {
            std::cerr << "ERROR: StringLogger does not (correctly) inherit from ILogger\n";
            part2err = true;
        } else {
            if constexpr (!std::is_abstract_v<StringLogger>) {
                if constexpr (!chk2::has_constructor) {
                    std::cerr << "ERROR: StringLogger does not have the correct constructor or none is defined\n";
                    part2err = true;
                } else {
                    TestStringLogger<StringLogger>();
                }
            } else {
                std::cerr << "ERROR: StringLogger does not implement all of ILogger\n";
                part2err = true;
            }
        }
        if (!part2err)
            std::cout << "Part 2 passed!" << std::endl;
    }
}