//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// UNSUPPORTED: c++03, c++11, c++14, c++17, c++20

// <flat_set>

// size_type count(const key_type& x) const;

#include <cassert>
#include <deque>
#include <flat_set>
#include <functional>
#include <utility>

#include "MinSequenceContainer.h"
#include "test_macros.h"
#include "min_allocator.h"

template <class KeyContainer>
constexpr void test_one() {
  using Key = typename KeyContainer::value_type;
  using S   = typename KeyContainer::size_type;

  {
    using M = std::flat_set<Key, std::less<>, KeyContainer>;
    M m     = {1, 2, 4, 5, 8};
    ASSERT_SAME_TYPE(decltype(m.count(0)), S);
    assert(m.count(0) == 0);
    assert(m.count(1) == 1);
    assert(m.count(2) == 1);
    assert(m.count(3) == 0);
    assert(m.count(4) == 1);
    assert(m.count(5) == 1);
    assert(m.count(6) == 0);
    assert(m.count(7) == 0);
    assert(std::as_const(m).count(8) == 1);
    assert(std::as_const(m).count(9) == 0);
  }
  {
    using M = std::flat_set<Key, std::greater<int>, KeyContainer>;
    M m     = {1, 2, 4, 5, 8};
    ASSERT_SAME_TYPE(decltype(m.count(0)), S);
    assert(m.count(0) == 0);
    assert(m.count(1) == 1);
    assert(m.count(2) == 1);
    assert(m.count(3) == 0);
    assert(m.count(4) == 1);
    assert(m.count(5) == 1);
    assert(m.count(6) == 0);
    assert(m.count(7) == 0);
    assert(std::as_const(m).count(8) == 1);
    assert(std::as_const(m).count(9) == 0);
  }
  {
    // empty
    using M = std::flat_set<Key, std::less<>, KeyContainer>;
    M m;
    assert(m.count(0) == 0);
    assert(m.count(1) == 0);
  }
}

constexpr bool test() {
  test_one<std::vector<int>>();
#ifndef __cpp_lib_constexpr_deque
  if (!TEST_IS_CONSTANT_EVALUATED)
#endif
    test_one<std::deque<int>>();
  test_one<MinSequenceContainer<int>>();
  test_one<std::vector<int, min_allocator<int>>>();

  return true;
}

int main(int, char**) {
  test();
#if TEST_STD_VER >= 26
  static_assert(test());
#endif

  return 0;
}
