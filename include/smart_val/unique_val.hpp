//
// Created by bobini on 24.01.23.
//

#ifndef SMART_VAL_UNIQUE_VAL_HPP
#define SMART_VAL_UNIQUE_VAL_HPP
#include "definitions.hpp"

namespace smart_val
{
template<typename T, typename Deleter = void>
class unique_val
{
public:
  template<typename... Args>
  SMART_VAL_CONSTEXPR14 explicit unique_val(Args&&... args) noexcept(
      noexcept(T(SMART_VAL_FWD(args)...)))
      : m_val(SMART_VAL_FWD(args)...)
  {
  }
  template<typename OtherDeleter>
  SMART_VAL_CONSTEXPR14 auto
  operator=(unique_val<T, OtherDeleter>&& other) noexcept(
      std::is_nothrow_move_assignable<T>::value) -> unique_val&
  {
    m_val = SMART_VAL_MOV(other.val);
    return *this;
  }
  template<typename OtherDeleter>
  SMART_VAL_CONSTEXPR14 explicit unique_val(
      unique_val<T, OtherDeleter>&&
          other) noexcept(std::is_nothrow_move_constructible<T>::value)
      : m_val(SMART_VAL_MOV(other.val))
      , m_deleter(SMART_VAL_MOV(other.m_deleter))
  {
  }
  SMART_VAL_CONSTEXPR20 ~unique_val() noexcept
  {
    detail::invoke(m_deleter, m_val);
  }
  auto operator=(const unique_val& other) -> unique_val& = delete;
  unique_val(const unique_val& other) = delete;

  SMART_VAL_CONSTEXPR14 SMART_VAL_NODISCARD auto get() noexcept -> T&
  {
    return m_val;
  }
  SMART_VAL_CONSTEXPR14 SMART_VAL_NODISCARD auto get() const noexcept
      -> const T&
  {
    return m_val;
  }
  SMART_VAL_CONSTEXPR14 SMART_VAL_NODISCARD auto operator*() noexcept -> T&
  {
    return m_val;
  }
  SMART_VAL_CONSTEXPR14 SMART_VAL_NODISCARD auto operator*() const noexcept
      -> const T&
  {
    return m_val;
  }
  SMART_VAL_CONSTEXPR14 auto operator->() noexcept -> T* { return &m_val; }
  SMART_VAL_CONSTEXPR14 auto operator->() const noexcept -> const T*
  {
    return &m_val;
  }

private:
  T m_val;
  Deleter m_deleter;
};

template<typename T>
class unique_val<T, void>
{
public:
  template<typename... Args>
  SMART_VAL_CONSTEXPR14 explicit unique_val(Args&&... args) noexcept(
      noexcept(T(SMART_VAL_FWD(args)...)))
      : m_val(SMART_VAL_FWD(args)...)
  {
  }
  template<typename OtherDeleter>
  SMART_VAL_CONSTEXPR14 auto
  operator=(unique_val<T, OtherDeleter>&& other) noexcept(
      std::is_nothrow_move_assignable<T>::value) -> unique_val&
  {
    m_val = SMART_VAL_MOV(other.m_val);
    return *this;
  }
  SMART_VAL_CONSTEXPR14 unique_val(unique_val<T>&& other) noexcept(
      std::is_nothrow_move_constructible<T>::value)
      : m_val(SMART_VAL_MOV(other.m_val))
  {
  }
  auto operator=(const unique_val& other) -> unique_val& = delete;
  unique_val(const unique_val& other) = delete;

  SMART_VAL_CONSTEXPR14 SMART_VAL_NODISCARD auto get() noexcept -> T&
  {
    return m_val;
  }
  SMART_VAL_CONSTEXPR14 SMART_VAL_NODISCARD auto get() const noexcept
      -> const T&
  {
    return m_val;
  }
  SMART_VAL_CONSTEXPR14 SMART_VAL_NODISCARD auto operator*() noexcept -> T&
  {
    return m_val;
  }
  SMART_VAL_CONSTEXPR14 SMART_VAL_NODISCARD auto operator*() const noexcept
      -> const T&
  {
    return m_val;
  }
  SMART_VAL_CONSTEXPR14 auto operator->() noexcept -> T* { return &m_val; }
  SMART_VAL_CONSTEXPR14 auto operator->() const noexcept -> const T*
  {
    return &m_val;
  }

private:
  T m_val;
};

template<typename CharT, typename Traits, typename T, typename Deleter>
auto operator<<(std::basic_ostream<CharT, Traits>& os,
                const unique_val<T, Deleter>& p) noexcept(noexcept(os
                                                                   << p.get()))
    -> std::basic_ostream<CharT, Traits>&
{
  return os << p.get();
}

template<typename T, typename... Args>
SMART_VAL_CONSTEXPR14 SMART_VAL_NODISCARD auto make_unique_val(
    Args&&... args) noexcept(noexcept(unique_val<T>(SMART_VAL_FWD(args)...)))
    -> unique_val<T>
{
  return unique_val<T>(SMART_VAL_FWD(args)...);
}

}  // namespace smart_val

namespace std
{
template<typename T, typename Deleter>
struct hash<smart_val::unique_val<T, Deleter>>
{
  SMART_VAL_NODISCARD auto operator()(
      const smart_val::unique_val<T, Deleter>& item) const
      noexcept(noexcept(hash<T>()(item.get()))) -> size_t
  {
    return hash<T>()(item.get());
  }
};
}  // namespace std

#endif  // SMART_VAL_UNIQUE_VAL_HPP
