//
// Created by renbin jiang on 2021/8/30.
//
#include "base.h"

#include <gtest/gtest.h>

#include <set>
#include <unordered_set>

using namespace base;

TEST(strings, split_empty) {
    std::vector<std::string> parts = base::Split("", ",");
    ASSERT_EQ(1U, parts.size());
    ASSERT_EQ("", parts[0]);
}

TEST(strings, split_single) {
    std::vector<std::string> parts = base::Split("foo", ",");
    ASSERT_EQ(1U, parts.size());
    ASSERT_EQ("foo", parts[0]);
}

TEST(strings, split_simple) {
    std::vector<std::string> parts = base::Split("foo,bar,baz", ",");
    ASSERT_EQ(3U, parts.size());
    ASSERT_EQ("foo", parts[0]);
    ASSERT_EQ("bar", parts[1]);
    ASSERT_EQ("baz", parts[2]);
}

TEST(strings, split_with_empty_part) {
    std::vector<std::string> parts = base::Split("foo,,bar", ",");
    ASSERT_EQ(3U, parts.size());
    ASSERT_EQ("foo", parts[0]);
    ASSERT_EQ("", parts[1]);
    ASSERT_EQ("bar", parts[2]);
}

TEST(strings, split_with_trailing_empty_part) {
    std::vector<std::string> parts = base::Split("foo,bar,", ",");
    ASSERT_EQ(3U, parts.size());
    ASSERT_EQ("foo", parts[0]);
    ASSERT_EQ("bar", parts[1]);
    ASSERT_EQ("", parts[2]);
}

TEST(strings, split_null_char) {
    std::vector<std::string> parts = base::Split(std::string("foo\0bar", 7), std::string("\0", 1));
    ASSERT_EQ(2U, parts.size());
    ASSERT_EQ("foo", parts[0]);
    ASSERT_EQ("bar", parts[1]);
}

TEST(strings, split_any) {
    std::vector<std::string> parts = base::Split("foo:bar,baz", ",:");
    ASSERT_EQ(3U, parts.size());
    ASSERT_EQ("foo", parts[0]);
    ASSERT_EQ("bar", parts[1]);
    ASSERT_EQ("baz", parts[2]);
}

TEST(strings, split_any_with_empty_part) {
    std::vector<std::string> parts = base::Split("foo:,bar", ",:");
    ASSERT_EQ(3U, parts.size());
    ASSERT_EQ("foo", parts[0]);
    ASSERT_EQ("", parts[1]);
    ASSERT_EQ("bar", parts[2]);
}

TEST(strings, trim_empty) {
    ASSERT_EQ("", base::Trim(""));
}

TEST(strings, trim_already_trimmed) {
    ASSERT_EQ("foo", base::Trim("foo"));
}

TEST(strings, trim_left) {
    ASSERT_EQ("foo", base::Trim(" foo"));
}

TEST(strings, trim_right) {
    ASSERT_EQ("foo", base::Trim("foo "));
}

TEST(strings, trim_both) {
    ASSERT_EQ("foo", base::Trim(" foo "));
}

TEST(strings, trim_no_trim_middle) {
    ASSERT_EQ("foo bar", base::Trim("foo bar"));
}

TEST(strings, trim_other_whitespace) {
    ASSERT_EQ("foo", base::Trim("\v\tfoo\n\f"));
}

TEST(strings, join_nothing) {
    std::vector<std::string> list = {};
    ASSERT_EQ("", base::Join(list, ','));
}

TEST(strings, join_single) {
    std::vector<std::string> list = {"foo"};
    ASSERT_EQ("foo", base::Join(list, ','));
}

TEST(strings, join_simple) {
    std::vector<std::string> list = {"foo", "bar", "baz"};
    ASSERT_EQ("foo,bar,baz", base::Join(list, ','));
}

TEST(strings, join_separator_in_vector) {
    std::vector<std::string> list = {",", ","};
    ASSERT_EQ(",,,", base::Join(list, ','));
}

TEST(strings, join_simple_ints) {
    std::set<int> list = {1, 2, 3};
    ASSERT_EQ("1,2,3", base::Join(list, ','));
}

TEST(strings, join_unordered_set) {
    std::unordered_set<int> list = {1, 2};
    ASSERT_TRUE("1,2" == base::Join(list, ',') || "2,1" == base::Join(list, ','));
}

TEST(strings, StartsWith_empty) {
    ASSERT_FALSE(base::StartsWith("", "foo"));
    ASSERT_TRUE(base::StartsWith("", ""));
}

TEST(strings, StartsWithIgnoreCase_empty) {
    ASSERT_FALSE(base::StartsWithIgnoreCase("", "foo"));
    ASSERT_TRUE(base::StartsWithIgnoreCase("", ""));
}

TEST(strings, StartsWith_simple) {
    ASSERT_TRUE(base::StartsWith("foo", ""));
    ASSERT_TRUE(base::StartsWith("foo", "f"));
    ASSERT_TRUE(base::StartsWith("foo", "fo"));
    ASSERT_TRUE(base::StartsWith("foo", "foo"));
}

TEST(strings, StartsWithIgnoreCase_simple) {
    ASSERT_TRUE(base::StartsWithIgnoreCase("foo", ""));
    ASSERT_TRUE(base::StartsWithIgnoreCase("foo", "f"));
    ASSERT_TRUE(base::StartsWithIgnoreCase("foo", "F"));
    ASSERT_TRUE(base::StartsWithIgnoreCase("foo", "fo"));
    ASSERT_TRUE(base::StartsWithIgnoreCase("foo", "fO"));
    ASSERT_TRUE(base::StartsWithIgnoreCase("foo", "Fo"));
    ASSERT_TRUE(base::StartsWithIgnoreCase("foo", "FO"));
    ASSERT_TRUE(base::StartsWithIgnoreCase("foo", "foo"));
    ASSERT_TRUE(base::StartsWithIgnoreCase("foo", "foO"));
    ASSERT_TRUE(base::StartsWithIgnoreCase("foo", "fOo"));
    ASSERT_TRUE(base::StartsWithIgnoreCase("foo", "fOO"));
    ASSERT_TRUE(base::StartsWithIgnoreCase("foo", "Foo"));
    ASSERT_TRUE(base::StartsWithIgnoreCase("foo", "FoO"));
    ASSERT_TRUE(base::StartsWithIgnoreCase("foo", "FOo"));
    ASSERT_TRUE(base::StartsWithIgnoreCase("foo", "FOO"));
}

TEST(strings, StartsWith_prefix_too_long) {
    ASSERT_FALSE(base::StartsWith("foo", "foobar"));
}

TEST(strings, StartsWithIgnoreCase_prefix_too_long) {
    ASSERT_FALSE(base::StartsWithIgnoreCase("foo", "foobar"));
    ASSERT_FALSE(base::StartsWithIgnoreCase("foo", "FOOBAR"));
}

TEST(strings, StartsWith_contains_prefix) {
    ASSERT_FALSE(base::StartsWith("foobar", "oba"));
    ASSERT_FALSE(base::StartsWith("foobar", "bar"));
}

TEST(strings, StartsWithIgnoreCase_contains_prefix) {
    ASSERT_FALSE(base::StartsWithIgnoreCase("foobar", "oba"));
    ASSERT_FALSE(base::StartsWithIgnoreCase("foobar", "OBA"));
    ASSERT_FALSE(base::StartsWithIgnoreCase("foobar", "bar"));
    ASSERT_FALSE(base::StartsWithIgnoreCase("foobar", "BAR"));
}

TEST(strings, StartsWith_char) {
    ASSERT_FALSE(base::StartsWith("", 'f'));
    ASSERT_TRUE(base::StartsWith("foo", 'f'));
    ASSERT_FALSE(base::StartsWith("foo", 'o'));
}

TEST(strings, EndsWith_empty) {
    ASSERT_FALSE(base::EndsWith("", "foo"));
    ASSERT_TRUE(base::EndsWith("", ""));
}

TEST(strings, EndsWithIgnoreCase_empty) {
    ASSERT_FALSE(base::EndsWithIgnoreCase("", "foo"));
    ASSERT_FALSE(base::EndsWithIgnoreCase("", "FOO"));
    ASSERT_TRUE(base::EndsWithIgnoreCase("", ""));
}

TEST(strings, EndsWith_simple) {
    ASSERT_TRUE(base::EndsWith("foo", ""));
    ASSERT_TRUE(base::EndsWith("foo", "o"));
    ASSERT_TRUE(base::EndsWith("foo", "oo"));
    ASSERT_TRUE(base::EndsWith("foo", "foo"));
}

TEST(strings, EndsWithIgnoreCase_simple) {
    ASSERT_TRUE(base::EndsWithIgnoreCase("foo", ""));
    ASSERT_TRUE(base::EndsWithIgnoreCase("foo", "o"));
    ASSERT_TRUE(base::EndsWithIgnoreCase("foo", "O"));
    ASSERT_TRUE(base::EndsWithIgnoreCase("foo", "oo"));
    ASSERT_TRUE(base::EndsWithIgnoreCase("foo", "oO"));
    ASSERT_TRUE(base::EndsWithIgnoreCase("foo", "Oo"));
    ASSERT_TRUE(base::EndsWithIgnoreCase("foo", "OO"));
    ASSERT_TRUE(base::EndsWithIgnoreCase("foo", "foo"));
    ASSERT_TRUE(base::EndsWithIgnoreCase("foo", "foO"));
    ASSERT_TRUE(base::EndsWithIgnoreCase("foo", "fOo"));
    ASSERT_TRUE(base::EndsWithIgnoreCase("foo", "fOO"));
    ASSERT_TRUE(base::EndsWithIgnoreCase("foo", "Foo"));
    ASSERT_TRUE(base::EndsWithIgnoreCase("foo", "FoO"));
    ASSERT_TRUE(base::EndsWithIgnoreCase("foo", "FOo"));
    ASSERT_TRUE(base::EndsWithIgnoreCase("foo", "FOO"));
}

TEST(strings, EndsWith_prefix_too_long) {
    ASSERT_FALSE(base::EndsWith("foo", "foobar"));
}

TEST(strings, EndsWithIgnoreCase_prefix_too_long) {
    ASSERT_FALSE(base::EndsWithIgnoreCase("foo", "foobar"));
    ASSERT_FALSE(base::EndsWithIgnoreCase("foo", "FOOBAR"));
}

TEST(strings, EndsWith_contains_prefix) {
    ASSERT_FALSE(base::EndsWith("foobar", "oba"));
    ASSERT_FALSE(base::EndsWith("foobar", "foo"));
}

TEST(strings, EndsWithIgnoreCase_contains_prefix) {
    ASSERT_FALSE(base::EndsWithIgnoreCase("foobar", "OBA"));
    ASSERT_FALSE(base::EndsWithIgnoreCase("foobar", "FOO"));
}

TEST(strings, StartsWith_std_string) {
    ASSERT_TRUE(base::StartsWith("hello", std::string{"hell"}));
    ASSERT_FALSE(base::StartsWith("goodbye", std::string{"hell"}));
}

TEST(strings, StartsWithIgnoreCase_std_string) {
    ASSERT_TRUE(base::StartsWithIgnoreCase("HeLlO", std::string{"hell"}));
    ASSERT_FALSE(base::StartsWithIgnoreCase("GoOdByE", std::string{"hell"}));
}

TEST(strings, EndsWith_std_string) {
    ASSERT_TRUE(base::EndsWith("hello", std::string{"lo"}));
    ASSERT_FALSE(base::EndsWith("goodbye", std::string{"lo"}));
}

TEST(strings, EndsWithIgnoreCase_std_string) {
    ASSERT_TRUE(base::EndsWithIgnoreCase("HeLlO", std::string{"lo"}));
    ASSERT_FALSE(base::EndsWithIgnoreCase("GoOdByE", std::string{"lo"}));
}

TEST(strings, EndsWith_char) {
    ASSERT_FALSE(base::EndsWith("", 'o'));
    ASSERT_TRUE(base::EndsWith("foo", 'o'));
    ASSERT_FALSE(base::EndsWith("foo", "f"));
}

TEST(strings, EqualsIgnoreCase) {
    ASSERT_TRUE(base::EqualsIgnoreCase("foo", "FOO"));
    ASSERT_TRUE(base::EqualsIgnoreCase("FOO", "foo"));
    ASSERT_FALSE(base::EqualsIgnoreCase("foo", "bar"));
    ASSERT_FALSE(base::EqualsIgnoreCase("foo", "fool"));
}

TEST(strings, ubsan_28729303) {
    base::Split("/dev/null", ":");
}

TEST(strings, ConsumePrefix) {
    std::string_view s{"foo.bar"};
    ASSERT_FALSE(base::ConsumePrefix(&s, "bar."));
    ASSERT_EQ("foo.bar", s);
    ASSERT_TRUE(base::ConsumePrefix(&s, "foo."));
    ASSERT_EQ("bar", s);
}

TEST(strings, ConsumeSuffix) {
    std::string_view s{"foo.bar"};
    ASSERT_FALSE(base::ConsumeSuffix(&s, ".foo"));
    ASSERT_EQ("foo.bar", s);
    ASSERT_TRUE(base::ConsumeSuffix(&s, ".bar"));
    ASSERT_EQ("foo", s);
}

TEST(strings, StringReplace_false) {
    // No change.
    ASSERT_EQ("abcabc", base::StringReplace("abcabc", "z", "Z", false));
    ASSERT_EQ("", base::StringReplace("", "z", "Z", false));
    ASSERT_EQ("abcabc", base::StringReplace("abcabc", "", "Z", false));

    // Equal lengths.
    ASSERT_EQ("Abcabc", base::StringReplace("abcabc", "a", "A", false));
    ASSERT_EQ("aBcabc", base::StringReplace("abcabc", "b", "B", false));
    ASSERT_EQ("abCabc", base::StringReplace("abcabc", "c", "C", false));

    // Longer replacement.
    ASSERT_EQ("foobcabc", base::StringReplace("abcabc", "a", "foo", false));
    ASSERT_EQ("afoocabc", base::StringReplace("abcabc", "b", "foo", false));
    ASSERT_EQ("abfooabc", base::StringReplace("abcabc", "c", "foo", false));

    // Shorter replacement.
    ASSERT_EQ("xxyz", base::StringReplace("abcxyz", "abc", "x", false));
    ASSERT_EQ("axyz", base::StringReplace("abcxyz", "bcx", "x", false));
    ASSERT_EQ("abcx", base::StringReplace("abcxyz", "xyz", "x", false));
}

TEST(strings, StringReplace_true) {
    // No change.
    ASSERT_EQ("abcabc", base::StringReplace("abcabc", "z", "Z", true));
    ASSERT_EQ("", base::StringReplace("", "z", "Z", true));
    ASSERT_EQ("abcabc", base::StringReplace("abcabc", "", "Z", true));

    // Equal lengths.
    ASSERT_EQ("AbcAbc", base::StringReplace("abcabc", "a", "A", true));
    ASSERT_EQ("aBcaBc", base::StringReplace("abcabc", "b", "B", true));
    ASSERT_EQ("abCabC", base::StringReplace("abcabc", "c", "C", true));

    // Longer replacement.
    ASSERT_EQ("foobcfoobc", base::StringReplace("abcabc", "a", "foo", true));
    ASSERT_EQ("afoocafooc", base::StringReplace("abcabc", "b", "foo", true));
    ASSERT_EQ("abfooabfoo", base::StringReplace("abcabc", "c", "foo", true));

    // Shorter replacement.
    ASSERT_EQ("xxyzx", base::StringReplace("abcxyzabc", "abc", "x", true));
    ASSERT_EQ("<xx>", base::StringReplace("<abcabc>", "abc", "x", true));
}
