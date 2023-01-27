//
// Created by bobini on 24.01.23.
//

#ifndef SMART_VAL_UNIQUE_VAL_HPP
#define SMART_VAL_UNIQUE_VAL_HPP
#include "definitions.hpp"

namespace smart_val
{
template<typename T, typename Destruct = default_destruct_t>
class unique_val
{
  static_assert(detail::is_invocable<Destruct, T&>::value,
                "Destruct function must be invocable with T&");

public:
  template<typename... Args,
           typename = typename std::enable_if<
               std::is_constructible<T, Args...>::value>::type>
  constexpr explicit unique_val(Args&&... args) noexcept(
      noexcept(T(SMART_VAL_FWD(args)...)))
      : m_item(SMART_VAL_FWD(args)...)
      , m_destruct(default_destruct)
  {
  }
  template<typename OtherT, typename OtherDestruct>
  SMART_VAL_CONSTEXPR14 operator unique_val<OtherT, OtherDestruct>() && noexcept
  {
    return unique_val<OtherT, OtherDestruct>(std::move(get()),
                                             std::move(get_destruct()));
  }
  SMART_VAL_CONSTEXPR14 unique_val(unique_val&& other) noexcept(
      std::is_nothrow_move_constructible<T>::value&&
          std::is_nothrow_move_constructible<Destruct>::value)
      : m_item(SMART_VAL_MOV(other.get()))
      , m_destruct(SMART_VAL_MOV(other.get_destruct()))
  {
    other.m_is_moved_from = true;
  }
  template<typename OtherT, typename OtherDestruct>
  SMART_VAL_CONSTEXPR14
  unique_val(OtherT&& other_t, OtherDestruct&& other_destruct) noexcept(
      std::is_nothrow_move_constructible<T>::value&&
          std::is_nothrow_move_constructible<Destruct>::value)
      : m_item(static_cast<T>(SMART_VAL_FWD(other_t)))
      , m_destruct(static_cast<Destruct>(SMART_VAL_FWD(other_destruct)))
  {
  }
  SMART_VAL_CONSTEXPR14 auto operator=(unique_val&& other) noexcept(
      std::is_nothrow_move_assignable<T>::value&&
          std::is_nothrow_move_assignable<Destruct>::value) -> unique_val&
  {
    m_item = SMART_VAL_MOV(other.get());
    m_destruct = SMART_VAL_MOV(other.get_destruct());
    other.m_is_moved_from = true;
    return *this;
  }
  SMART_VAL_CONSTEXPR20 ~unique_val() noexcept
  {
    if (!m_is_moved_from) {
      detail::invoke(get_destruct(), get());
    }
  }
  auto operator=(const unique_val& other) -> unique_val& = delete;
  unique_val(const unique_val& other) = delete;

  SMART_VAL_CONSTEXPR14 SMART_VAL_NODISCARD auto get() noexcept -> T&
  {
    return m_item;
  }
  constexpr SMART_VAL_NODISCARD auto get() const noexcept -> const T&
  {
    return m_item;
  }
  SMART_VAL_CONSTEXPR14 SMART_VAL_NODISCARD auto get_destruct() noexcept
      -> Destruct&
  {
    return m_destruct;
  }
  constexpr SMART_VAL_NODISCARD auto get_destruct() const noexcept
      -> const Destruct&
  {
    return m_destruct;
  }
  SMART_VAL_CONSTEXPR14 SMART_VAL_NODISCARD auto operator*() noexcept -> T&
  {
    return get();
  }
  constexpr SMART_VAL_NODISCARD auto operator*() const noexcept -> const T&
  {
    return get();
  }
  SMART_VAL_CONSTEXPR14 auto operator->() noexcept -> T* { return &m_item; }
  constexpr auto operator->() const noexcept -> const T* { return &m_item; }

private:
  T m_item;
  Destruct m_destruct;
  bool m_is_moved_from = false;
};

template<typename T, typename... Args>
constexpr SMART_VAL_NODISCARD auto make_unique_val(Args&&... args) noexcept(
    noexcept(unique_val<T>(SMART_VAL_FWD(args)...))) -> unique_val<T>
{
  return unique_val<T>(SMART_VAL_FWD(args)...);
}

}  // namespace smart_val

#endif  // SMART_VAL_UNIQUE_VAL_HPP
