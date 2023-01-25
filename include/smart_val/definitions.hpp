//
// Created by bobini on 24.01.23.
//

#ifndef SMART_VAL_DEFINITIONS_HPP
#define SMART_VAL_DEFINITIONS_HPP
#include <type_traits>
#define SMART_VAL_MOV(...) \
  static_cast<typename std::remove_reference<decltype(__VA_ARGS__)>::type&&>( \
      __VA_ARGS__)
#define SMART_VAL_FWD(...) static_cast<decltype(__VA_ARGS__)&&>(__VA_ARGS__)
#include <functional>
#include <iosfwd>
#if ((defined(_MSVC_LANG) && _MSVC_LANG >= 201402L) || __cplusplus >= 201402L)
#  define SMART_VAL_CONSTEXPR14 constexpr
#else
#  define SMART_VAL_CONSTEXPR14
#endif
#if ((defined(_MSVC_LANG) && _MSVC_LANG >= 201703L) || __cplusplus >= 201703L)
#  define SMART_VAL_NODISCARD [[nodiscard]]
#else
#  define SMART_VAL_NODISCARD
#endif

namespace smart_val
{
namespace detail
{
template<class F, class... Args>
inline auto invoke(F&& function, Args&&... args)
    -> decltype(SMART_VAL_FWD(function)(SMART_VAL_FWD(args)...))
{
  return SMART_VAL_FWD(function)(SMART_VAL_FWD(args)...);
}

template<class Base, class T, class Derived>
inline auto invoke(T Base::*pmd, Derived&& ref)
    -> decltype(SMART_VAL_FWD(ref).*pmd)
{
  return SMART_VAL_FWD(ref).*pmd;
}
}  // namespace detail
}  // namespace smart_val
#endif  // SMART_VAL_DEFINITIONS_HPP
