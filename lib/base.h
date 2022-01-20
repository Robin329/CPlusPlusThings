//
// Created by renbin jiang on 2021/8/30.
//

#ifndef GOOGLETEST_DISTRIBUTION_BASE_H
#define GOOGLETEST_DISTRIBUTION_BASE_H

#include <stdlib.h>
#include <string.h>
#include <sys/syscall.h>
#include <unistd.h>

#include <chrono>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using namespace std;
namespace base {
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

#define getpid() syscall(SYS_thread_selfid)

typedef struct coor_t {
    float x;
    float y;
} coor;

typedef struct pointCoordinate {
    int S16X;
    int S16Y;
} point;
static int dbgLevel = 0;
#define DBG_LEVEL dbgLevel
#define COOR_T_LOG(tag, var, line, column)                                               \
    {                                                                                    \
        if (DBG_LEVEL) {                                                                 \
            do {                                                                         \
                printf("%s[%d] %s:\n", __FUNCTION__, __LINE__, tag);                     \
                for (int i = 0; i < column; i++) {                                       \
                    for (int j = 0; j < line; j++) {                                     \
                        printf(" [%d][%d] = (%d, %d) ", j, i, var[j][i].x, var[j][i].y); \
                    }                                                                    \
                    printf("\n");                                                        \
                }                                                                        \
            } while (0);                                                                 \
        }                                                                                \
    }

#define POINT_LOG(tag, var, line, column)                                                      \
    {                                                                                          \
        if (DBG_LEVEL) {                                                                       \
            do {                                                                               \
                printf("%s[%d] %s:\n", __FUNCTION__, __LINE__, tag);                           \
                for (int i = 0; i < line; i++) {                                               \
                    for (int j = 0; j < column; j++) {                                         \
                        printf(" [%d][%d] = (%d, %d) ", i, j, var[i][j].S16X, var[i][j].S16Y); \
                    }                                                                          \
                    printf("\n");                                                              \
                }                                                                              \
            } while (0);                                                                       \
        }                                                                                      \
    }

class Timer {
public:
    class boot_clock {
    public:
        typedef std::chrono::nanoseconds duration;

        typedef std::chrono::time_point<boot_clock, duration> time_point;

        static time_point now() {
            timespec ts;
            clock_gettime(_CLOCK_REALTIME, &ts);
            return boot_clock::time_point(std::chrono::seconds(ts.tv_sec) +
                                          std::chrono::nanoseconds(ts.tv_nsec));
        }
    };

    Timer() : start_(boot_clock::now()) {}

    std::chrono::milliseconds duration() const {
        return std::chrono::duration_cast<std::chrono::milliseconds>(boot_clock::now() - start_);
    }

private:
    boot_clock::time_point start_;
};

std::vector<std::string> Split(const std::string &s, const std::string &delimiters);

// Joins a container of things into a single string, using the given separator.
template <typename ContainerT, typename SeparatorT>
std::string Join(const ContainerT &things, SeparatorT separator) {
    if (things.empty()) {
        return "";
    }

    std::ostringstream result;
    result << *things.begin();
    for (auto it = std::next(things.begin()); it != things.end(); ++it) {
        result << separator << *it;
    }
    return result.str();
}

std::string Trim(const std::string &s);

// We instantiate the common cases in strings.cpp.
extern template std::string Join(const std::vector<std::string> &, char);

extern template std::string Join(const std::vector<const char *> &, char);

extern template std::string Join(const std::vector<std::string> &, const std::string &);

extern template std::string Join(const std::vector<const char *> &, const std::string &);

// Tests whether 's' starts with 'prefix'.
bool StartsWith(std::string_view s, std::string_view prefix);

bool StartsWith(std::string_view s, char prefix);

bool StartsWithIgnoreCase(std::string_view s, std::string_view prefix);

// Tests whether 's' ends with 'suffix'.
bool EndsWith(std::string_view s, std::string_view suffix);

bool EndsWith(std::string_view s, char suffix);

bool EndsWithIgnoreCase(std::string_view s, std::string_view suffix);

// Tests whether 'lhs' equals 'rhs', ignoring case.
bool EqualsIgnoreCase(std::string_view lhs, std::string_view rhs);

// Removes `prefix` from the start of the given string and returns true (if
// it was present), false otherwise.
inline bool ConsumePrefix(std::string_view *s, std::string_view prefix) {
    if (!StartsWith(*s, prefix)) return false;
    s->remove_prefix(prefix.size());
    return true;
}

// Removes `suffix` from the end of the given string and returns true (if
// it was present), false otherwise.
inline bool ConsumeSuffix(std::string_view *s, std::string_view suffix) {
    if (!EndsWith(*s, suffix)) return false;
    s->remove_suffix(suffix.size());
    return true;
}

// Replaces `from` with `to` in `s`, once if `all == false`, or as many times as
// there are matches if `all == true`.
[[nodiscard]] std::string StringReplace(std::string_view s, std::string_view from,
                                        std::string_view to, bool all);
} // namespace base
#endif // GOOGLETEST_DISTRIBUTION_BASE_H
