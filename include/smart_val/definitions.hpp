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
#if ((defined(_MSVC_LANG) && _MSVC_LANG >= 202002L) || __cplusplus >= 202002L)
#  define SMART_VAL_CONSTEXPR20 constexpr
#else
#  define SMART_VAL_CONSTEXPR20
#endif

namespace smart_val
{

struct default_destruct_t
{
  template<typename T>
  void operator()(const T& val) const
  {
    (void)val;
  }
};

static constexpr auto default_destruct = default_destruct_t {};

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

template<typename F, typename... Args>
struct is_invocable
    : std::is_constructible<
          std::function<void(Args...)>,
          std::reference_wrapper<typename std::remove_reference<F>::type> >
{
};

template<typename R, typename F, typename... Args>
struct is_invocable_r
    : std::is_constructible<
          std::function<R(Args...)>,
          std::reference_wrapper<typename std::remove_reference<F>::type> >
{
};
}  // namespace detail
}  // namespace smart_val
#endif  // SMART_VAL_DEFINITIONS_HPP
