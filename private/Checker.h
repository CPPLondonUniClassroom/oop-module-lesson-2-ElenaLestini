#pragma once
#include <string>
#include <type_traits>
#include <utility>

template <class T>
class Checker {
    using yes = std::true_type;
    using no = std::false_type;

    template <typename U, typename FnPtr, FnPtr> struct SFINAE {
        using type = void;
    };

    template <class C> static typename SFINAE<C, C&(C::*)(const std::string&), &C::LogInfo>::type HasLogInfo(std::nullptr_t) {}
    template <class C> static no HasLogInfo(...) { return {}; }
    template <class C> static typename SFINAE<C, C&(C::*)(const std::string&), &C::LogError>::type HasLogError(std::nullptr_t) {}
    template <class C> static no HasLogError(...) { return {}; }
    template <class C> static typename SFINAE<C, const std::string&(C::*)() const, &C::GetLastError>::type HasGetLastError(std::nullptr_t) {}
    template <class C> static no HasGetLastError(...) { return {}; }

    template <class C> static std::enable_if_t<std::is_same_v<C, decltype(C{*static_cast<std::ostream*>(nullptr)})>> HasConstructor(std::nullptr_t) {}
    template <class C> static no HasConstructor(...) { return {}; }

public:
    static constexpr bool has_loginfo = std::is_same_v<void, decltype(HasLogInfo<T>(nullptr))>;
    static constexpr bool has_logerror = std::is_same_v<void, decltype(HasLogError<T>(nullptr))>;
    static constexpr bool has_getlasterror = std::is_same_v<void, decltype(HasGetLastError<T>(nullptr))>;

    static constexpr bool has_constructor = std::is_same_v<void, decltype(HasConstructor<T>(nullptr))>;
};