#include <catch2/catch.hpp>

#include "smart_val/unique_val.hpp"

static constexpr auto precision = 0.0001;

namespace sv = smart_val;
TEST_CASE("unique_val can be constructed", "[library]")
{
  auto val = sv::unique_val<int>();
  auto val2 = sv::make_unique_val<int>();
}

TEST_CASE("unique_val's value can be accessed", "[library]")
{
  auto val = sv::unique_val<int>(42);
  REQUIRE(val.get() == 42);
  REQUIRE(*val == 42);
  REQUIRE(val.operator->() == &val.get());
}

TEST_CASE("unique_val is not assignable or copiable", "[library]")
{
  STATIC_REQUIRE(
      !std::is_assignable<sv::unique_val<int>&, sv::unique_val<int>&>::value);
  STATIC_REQUIRE(!std::is_copy_constructible<sv::unique_val<int>>::value);
}

TEST_CASE("unique_val can be moved", "[library]")
{
  auto val = sv::unique_val<int>(42);
  auto val2 = std::move(val);
  REQUIRE(val2.get() == 42);

  auto val3 = sv::unique_val<int>();
  val3 = std::move(val2);

  REQUIRE(val3.get() == 42);
}

TEST_CASE("unique_val can be moved to another type", "[library]")
{
  auto val = sv::unique_val<int>(42);
  auto val2 = sv::unique_val<double>(std::move(val));
  REQUIRE_THAT(val2.get(), Catch::Matchers::WithinRel(42.0, precision));
}
