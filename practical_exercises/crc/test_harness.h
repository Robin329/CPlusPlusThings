#pragma once
#include <stdio.h>
#include <stdlib.h>

#include <sstream>

namespace common {
namespace test {
extern int errCount;
// Run some of the tests registered by the TEST() macro.  If the
// environment variable "LEVELDB_TESTS" is not set, runs all tests.
// Otherwise, runs only the tests whose name contains the value of
// "LEVELDB_TESTS" as a substring.  E.g., suppose the tests are:
//    TEST(Foo, Hello) { ... }
//    TEST(Foo, World) { ... }
// LEVELDB_TESTS=Hello will run the first test
// LEVELDB_TESTS=o     will run both tests
// LEVELDB_TESTS=Junk  will run no tests
//
// Returns 0 if all tests pass.
// Dies or returns a non-zero value if some test fails.
extern int RunAllTests(const char* matcher);

// Return the directory to use for temporary storage.
extern std::string TmpDir();

// Return a randomization seed for this run.  Typically returns the
// same number on repeated invocations of this binary, but automated
// runs may be able to vary the seed.
extern int RandomSeed();

// An instance of Tester is allocated to hold temporary state during
// the execution of an assertion.
class Tester {
private:
    bool ok_;
    const char* fname_;
    int line_;
    std::stringstream ss_;

public:
    Tester(const char* f, int l) : ok_(true), fname_(f), line_(l) {}

    ~Tester() {
        if (!ok_) {
            fprintf(stderr, "\033[0;31m[ ERROR    ] ==== %s:%d:%s\n", fname_, line_, ss_.str().c_str());
            fprintf(stderr, "\033[0m");
            errCount++;
            // exit(1);
        }
    }

    Tester& Is(bool b, const char* msg) {
        if (!b) {
            ss_ << " Assertion failure " << msg;
            ok_ = false;
        }
        return *this;
    }

#define BINARY_OP(name, op)                                                    \
    template <class X, class Y>                                                \
    Tester& name(const X& x, const Y& y) {                                     \
        if (!(x op y)) {                                                       \
            ss_ << " failed: Expect:" << x << (" " #op " ") << "Actual:" << y; \
            ok_ = false;                                                       \
        }                                                                      \
        return *this;                                                          \
    }

    BINARY_OP(IsEq, ==)
    BINARY_OP(IsNe, !=)
    BINARY_OP(IsGe, >=)
    BINARY_OP(IsGt, >)
    BINARY_OP(IsLe, <=)
    BINARY_OP(IsLt, <)
#undef BINARY_OP
#define DOUBLE_OP(name, op)                                                    \
    template <class X, class Y>                                                \
    Tester& name(const X& x, const Y& y) {                                     \
        if (!(x - y > -0.000001 && x - y < 0.000001)) {                        \
            ss_ << " failed: Expect:" << x << (" " #op " ") << "Actual:" << y; \
            ok_ = false;                                                       \
        }                                                                      \
        return *this;                                                          \
    }
    DOUBLE_OP(IsDoubleEq, ==)
#undef DOUBLE_OP

    // Attach the specified value to the error message if an error has occurred
    template <class V>
    Tester& operator<<(const V& value) {
        if (!ok_) {
            ss_ << " " << value;
        }
        return *this;
    }
};

#define ASSERT_TRUE(c)         ::common::test::Tester(__FILE__, __LINE__).Is((c), #c)
#define ASSERT_FALSE(c)        ::common::test::Tester(__FILE__, __LINE__).Is(!(c), #c)
#define ASSERT_EQ(a, b)        ::common::test::Tester(__FILE__, __LINE__).IsEq((a), (b))
#define ASSERT_NE(a, b)        ::common::test::Tester(__FILE__, __LINE__).IsNe((a), (b))
#define ASSERT_GE(a, b)        ::common::test::Tester(__FILE__, __LINE__).IsGe((a), (b))
#define ASSERT_GT(a, b)        ::common::test::Tester(__FILE__, __LINE__).IsGt((a), (b))
#define ASSERT_LE(a, b)        ::common::test::Tester(__FILE__, __LINE__).IsLe((a), (b))
#define ASSERT_LT(a, b)        ::common::test::Tester(__FILE__, __LINE__).IsLt((a), (b))
#define EXPECT_GT(a, b)        ::common::test::Tester(__FILE__, __LINE__).IsLt((a), (b))
#define EXPECT_LT(a, b)        ::common::test::Tester(__FILE__, __LINE__).IsLt((a), (b))
#define EXPECT_EQ(a, b)        ::common::test::Tester(__FILE__, __LINE__).IsEq((a), (b))
#define EXPECT_NE(a, b)        ::common::test::Tester(__FILE__, __LINE__).IsNe((a), (b))
#define EXPECT_DOUBLE_EQ(a, b) ::common::test::Tester(__FILE__, __LINE__).IsDoubleEq((a), (b))
#define EXPECT_TRUE(a)         ::common::test::Tester(__FILE__, __LINE__).IsEq((a), (true))
#define EXPECT_FALSE(a)        ::common::test::Tester(__FILE__, __LINE__).IsEq((a), (false))
#define EXPECT_THROW(a, exceptions) \
    try {                           \
        a;                          \
    } catch (exceptions e) {        \
        EXPECT_TRUE(true);          \
    } catch (...) {                 \
        EXPECT_TRUE(false);         \
    }
#define EXPECT_ANY_THROW(a) \
    try {                   \
        a;                  \
    } catch (...) {         \
        EXPECT_TRUE(true);  \
    }
#define TCONCAT(a, b)  TCONCAT1(a, b)
#define TCONCAT1(a, b) a##b

#define TEST(base, name)                                                                      \
    class TCONCAT(_Test_, base##name) : public ::common::test::TestBase {                     \
    public:                                                                                   \
        void _Run();                                                                          \
        static void _RunIt() {                                                                \
            TCONCAT(_Test_, base##name) t;                                                    \
            t._Run();                                                                         \
        }                                                                                     \
    };                                                                                        \
    bool TCONCAT(_Test_ignored_, base##name) =                                                \
            ::common::test::RegisterTest(#base, #name, &TCONCAT(_Test_, base##name)::_RunIt); \
    void TCONCAT(_Test_, base##name)::_Run()

// Register the specified test.  Typically not used directly, but
// invoked via the macro expansion of TEST.
extern bool RegisterTest(const char* base, const char* name, void (*func)());

class TestBase {};

class TestPerfomence {
public:
    TestPerfomence();
    TestPerfomence(int size);
    ~TestPerfomence();
    long NowMs();

private:
    long startMs_;
};
#define TEST_PERF(a, size) ::common::test::TestPerfomence a(size);
} // namespace test
} // namespace common
