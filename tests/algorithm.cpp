#include <core/algorithm.hpp>
#include <initializer_list>
#include <vector>

#include <unittest/unittest.hpp>

int main () {
  using namespace unittest;

  test("algorithm") = {
    task("all-of") = [] {
      auto result = core::all_of({ 1, 2, 3, 4, 5}, [](int v) { return v > 0; });
      assert::is_true(result);
    },

    task("any-of") = [] {
      auto result = core::any_of({ 1, 2, 3 }, [](int v) { return v % 2 == 0; });
      assert::is_true(result);
    },

    task("none-of") = [] {
      auto result = core::none_of({ 1, 2, 3 }, [](int v) { return v <= 0; });
      assert::is_true(result);
    },

    task("for-each") = [] {
      core::for_each({ 1, 2, 3 }, [](int v) { assert::greater(v, 0); });
    },

    task("count") = [] {
      assert::equal(core::count({ 1, 2, 1, 1 }, 1), 3);
    },

    task("count-if") = [] {
      auto result = core::count_if({ 1, 2, 1 }, [](int v) { return v % 2; });
      assert::equal(result, 2);
    },

    task("mismatch") = [] {
      auto value = std::string { "abcXYZcba" };
      auto expected = std::string { "abc" };
      auto result = core::mismatch(value, value.rbegin());
      assert::equal(std::string { value.begin(), result.first }, expected);
    },

    task("equal") = [] {
      auto value = std::string { "hello" };
      auto result = core::equal(value, ::std::begin(value));
      assert::is_true(result);
    },

    task("find") = [] {
      auto value = std::string { "find" };
      auto result = core::find(value, 'n');
      assert::not_equal(result, ::std::end(value));
    },

    task("find-if") = [] {
      auto value = std::string { "find-if" };
      auto res = core::find_if(value, [](int ch) {
        return not ::std::isalpha(ch);
      });
      assert::not_equal(res, ::std::end(value));
    },

    task("find-if-not") = [] {
      auto value = std::string { "find-if-not" };
      auto res = core::find_if_not(value,
        [] (int ch) { return ::std::isalpha(ch);
      });
      assert::not_equal(res, ::std::end(value));
    },

    task("find-end") = [] {
      auto value = std::vector<int> { 1, 2, 3, 4, 6, 7, 9, 8, 1, 2, 3 };
      auto subset = std::vector<int> { 1, 2, 3 };

      auto result = core::find_end(value, subset);
      assert::not_equal(result, ::std::end(value));
      assert::equal(::std::distance(::std::begin(value), result), 8);
    },

    task("find-first-of") = [] {
      auto value = std::string { "find-first-of" };
      auto subset = std::string { "o" };
      auto result = core::find_first_of(value, subset);
      assert::not_equal(result, ::std::end(value));
      assert::equal(::std::distance(::std::begin(value), result), 11);
    },

    task("adjacent-find") = [] {
      auto value = std::string { "adjacent-find" };
      auto result = core::adjacent_find(value);
      assert::equal(result, ::std::end(value));
    },

    task("search") = [] {
      auto value = std::string { "searching with the search function" };
      auto result = core::search(value, std::string { "the" });
      assert::not_equal(result, ::std::end(value));
    },

    task("search-n") = [] {
      auto value = std::string { "searching for consecutive letters" };
      auto result = core::search_n(value, 2, 't');
      assert::not_equal(result, ::std::end(value));
    },

    task("copy") = [] {
      std::vector<int> from { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
      std::vector<int> to { };
      std::ignore = core::copy(from, std::back_inserter(to));

      assert::equal(to[0], 0);
      assert::equal(to[1], 1);
      assert::equal(to[2], 2);
      assert::equal(to[3], 3);
      assert::equal(to[4], 4);
      assert::equal(to[5], 5);
      assert::equal(to[6], 6);
      assert::equal(to[7], 7);
      assert::equal(to[8], 8);
      assert::equal(to[9], 9);
    },

    task("copy-if") = [] {
      auto value = std::string { "copy-if" };
      std::string output { };
      std::ignore = core::copy_if(
        value,
        ::std::back_inserter(output),
        [] (char ch) { return ::std::isalpha(ch); }
      );
      assert::equal(output, std::string { "copyif" });
    },

    task("copy-backward") = [] {
      auto value = std::string { "copy-backward" };
      std::string output(value.size(), '\0');
      std::ignore = core::copy_backward(value, ::std::end(output));
      assert::equal(output, value);
    },

    task("move") = [] {
      auto value = std::vector<std::string> { "first", "second", "third" };
      std::vector<std::string> output { 3 };
      std::ignore = core::move(value, ::std::begin(output));

      assert::is_true(value[0].empty());
      assert::is_true(value[1].empty());
      assert::is_true(value[2].empty());

      assert::equal(output[0], std::string { "first" });
      assert::equal(output[1], std::string { "second" });
      assert::equal(output[2], std::string { "third" });
    },

    task("move-backward") = [] {
      auto value = std::vector<std::string> { "first", "second", "third" };
      std::vector<std::string> output { 3 };
      std::ignore = core::move_backward(value, ::std::end(output));

      assert::is_true(value[0].empty());
      assert::is_true(value[1].empty());
      assert::is_true(value[2].empty());

      assert::equal(output[2], std::string { "third" });
      assert::equal(output[1], std::string { "second" });
      assert::equal(output[0], std::string { "first" });
    },

    task("fill") = [] {
      std::vector<int> value { 1, 2, 3, 4, 5, 6, 7 };
      auto predicate = [](int v) { return v == -1; };
      assert::is_true(core::none_of(value, predicate));
      core::fill(value, -1);
      assert::is_true(core::all_of(value, predicate));
    },

    task("transform") = [] {
      std::vector<int> value { 1, 2, 3 };
      std::vector<std::string> output { 3 };
      core::transform(value, ::std::begin(output), [] (int v) -> std::string {
        return std::to_string(v);
      });
      assert::equal(output[0], std::string { "1" });
      assert::equal(output[1], std::string { "2" });
      assert::equal(output[2], std::string { "3" });
    },

    task("remove") = [] {
      std::string text { "words words words" };
      text.erase(core::remove(text, ' '), ::std::end(text));
      assert::equal(text, std::string { "wordswordswords" });
    },

    task("remove-if") = [] {
      std::string text { "remove-if" };
      text.erase(
        core::remove_if(text, [](char ch) { return not ::std::isalpha(ch); }),
        ::std::end(text)
      );
      assert::equal(text, std::string { "removeif" });
    },

    task("remove-copy") = [] {
      std::string text { "remove-copy" };
      std::string output { };
      std::ignore = core::remove_copy(text, ::std::back_inserter(output), '-');
      assert::equal(output, std::string { "removecopy" });
    },

    task("remove-copy-if") = [] {
      std::string text { "remove-copy-if" };
      std::string output { };
      std::ignore = core::remove_copy_if(
        text,
        ::std::back_inserter(output),
        [] (char ch) { return ::std::isalpha(ch); }
      );
      assert::equal(output, std::string { "--" });
    },

    task("replace") = [] { assert::fail(); },
    task("replace-if") = [] { assert::fail(); },
    task("replace-copy") = [] { assert::fail(); },
    task("replace-copy-if") = [] { assert::fail(); },
    task("swap-ranges") = [] { assert::fail(); },
    task("reverse") = [] { assert::fail(); },
    task("reverse-copy") = [] { assert::fail(); },
    task("rotate") = [] { assert::fail(); },
    task("rotate-copy") = [] { assert::fail(); },
    task("shuffle") = [] { assert::fail(); },
    task("unique") = [] { assert::fail(); },
    task("unique-copy") = [] { assert::fail(); }
  };

  monitor::run();
}