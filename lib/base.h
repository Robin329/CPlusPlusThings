//
// Created by renbin jiang on 2021/8/30.
//

#ifndef _BASE_H_
#define _BASE_H_

#include <stdlib.h>
#include <string.h>
#include <sys/syscall.h>
#include <sys/time.h>
#include <unistd.h>
#if defined(__APPLE__)
#include <pthread.h>
#elif defined(__linux__) && !defined(__ANDROID__)
#include <syscall.h>
#elif defined(_WIN32)
#include <windows.h>
#endif

#include <chrono>
#include <ctime>
#include <iostream>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <vector>

#include "dbg-macro/dbg.h"
#include "filesystem.h"

typedef int8_t S8;
typedef int16_t S16;
typedef int32_t S32;
typedef int64_t S64;

typedef uint8_t U8;
typedef uint16_t U16;
typedef uint32_t U32;
typedef uint64_t U64;

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

typedef ListNode Node;

ListNode *nodeInit() {
    ListNode *l;
    l = (ListNode *)malloc(sizeof(ListNode));
    l->next = nullptr;
    int x = 0, count = 0;
    while (scanf("%d", &x) != EOF) {
        cout << "count:" << count << " x:" << x << endl;
        ++count;

        ListNode *p;
        p = (ListNode *)malloc(sizeof(ListNode));
        p->val = x;
        p->next = l->next;
        l->next = p;
        if (count > 2) break;
    }
    return l;
}

bool printNode(Node *result) {
    Node *p = result->next;
    stack<int> s;
    while (result != NULL && p != NULL) //入栈
    {
        cout << "val:" << p->val << endl;
        s.push(p->val);
        p = p->next;
    }

    while (!s.empty()) //出栈
    {
        cout << s.top() << " ";
        s.pop();
    }
    return true;
}

#define GET_CUR_TIME_STRING(tag)                                                                   \
    do {                                                                                           \
        struct timespec ts;                                                                        \
        clock_gettime(CLOCK_MONOTONIC, &ts);                                                       \
        struct tm *pTm = localtime(&ts.tv_sec);                                                    \
        char timeStr[20] = {};                                                                     \
        sprintf(timeStr, "%.2d-%.2d %.2d:%.2d:%.2d.%.3ld %s ", tag, pTm->tm_mon + 1, pTm->tm_mday, \
                pTm->tm_hour, pTm->tm_min, pTm->tm_sec, ts.tv_nsec / 1000000);                     \
        std::cout << timeStr << " [" << __FUNCTION__ << "] " << std::endl;                         \
    } while (0)

#ifdef __apple__
#define getpid() syscall(SYS_thread_selfid)
#endif
#ifndef TAG
#define TAG "base"
#endif
#define ROBIN_DBG(format, ...)                                                           \
    printf("%d %d D %s : %s" #format "\n", (int)getpid(), (int)syscall(SYS_gettid), TAG, \
           __FUNCTION__, ##__VA_ARGS__)

typedef struct coor_t {
    float x;
    float y;
} coor;

typedef struct pointCoordinate {
    int S16X;
    int S16Y;
} point;

static int dbgLevel = 1;
#define DBG_LEVEL dbgLevel
#define COOR_T_LOG(tag, var, line, column)                                                \
    {                                                                                     \
        if (DBG_LEVEL) {                                                                  \
            do {                                                                          \
                printf("%s[%d] %s:\n", __FUNCTION__, __LINE__, tag);                      \
                for (int i = 0; i < column; i++) {                                        \
                    for (int j = 0; j < line; j++) {                                      \
                        printf(" [%d][%d] = (%f, %f)\n", j, i, var[j][i].x, var[j][i].y); \
                    }                                                                     \
                    printf("\n");                                                         \
                }                                                                         \
            } while (0);                                                                  \
        }                                                                                 \
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

class Time {
public:
    Time() {
        m_time_t = std::time(0);
        m_time = std::localtime(&m_time_t);
        assert(m_time);
        m_year = m_time->tm_year + 1900;
        m_min = m_time->tm_min;
        m_hour = m_time->tm_hour;
        m_day = m_time->tm_mday;
        m_mon = m_time->tm_mon + 1;
        m_wday = m_time->tm_wday;
        m_yday = m_time->tm_yday;
    }
    static Time *getTime() {
                if (!m_stTime) {
                    m_stTime = new Time();

                } return m_stTime;
//        static Time t;
//        return &t;
    }
    int getYear() { return m_year; }
    int getMon() { return m_mon; }
    int getHour() { return m_hour; }
    int getDay() { return m_day; }
    virtual ~Time() {
        //        if (m_stTime) delete m_stTime;
    }

private:
        static Time *m_stTime;
    std::time_t m_time_t;
    std::tm *m_time;
    int m_year;
    int m_min;
    int m_hour;
    int m_day;
    int m_mon;
    int m_wday;
    int m_yday;
};

class Timer1 {
public:
#define MILLION 1000000

    Timer1(std::string tag) {
        std::cout << "Timer()" << std::endl;

        m_tag = tag;

        if (m_tag.empty()) {
            m_tag = "GL";
        }

        clock_gettime(CLOCK_MONOTONIC, &tpStart);
    }

    ~Timer1() {
        std::cout << "~Timer()" << std::endl;

        clock_gettime(CLOCK_MONOTONIC, &tpEnd);

        timeCost = MILLION * (tpEnd.tv_sec - tpStart.tv_sec) +
                (tpEnd.tv_nsec - tpStart.tv_nsec) / 1000;

        std::cout << "[" << m_tag << "] cost: " << timeCost << " mS" << std::endl;

        m_tag = "";
    }

private:
    struct timespec tpStart;

    struct timespec tpEnd;

    float timeCost;

    std::string m_tag;
};

class Timer {
public:
    class boot_clock {
    public:
        typedef std::chrono::nanoseconds duration;

        typedef std::chrono::time_point<boot_clock, duration> time_point;

        static time_point now() {
            timespec ts;
#ifdef __apple__
            clock_gettime(_CLOCK_REALTIME, &ts);
#else
            clock_gettime(CLOCK_REALTIME, &ts);
#endif
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

uint64_t GetThreadId();

class TimerLog {
public:
    TimerLog(const std::string tag) { // 对象构造时候保存开始时间
        m_begin_ = std::chrono::high_resolution_clock::now();
        m_tag_ = tag;
    }

    void Reset() { m_begin_ = std::chrono::high_resolution_clock::now(); }

    long long Elapsed() {
        return static_cast<long long>(std::chrono::duration_cast<std::chrono::milliseconds>(
                                              std::chrono::high_resolution_clock::now() - m_begin_)
                                              .count());
    }

    ~TimerLog() { // 对象析构时候计算当前时间与对象构造时候的时间差就是对象存活的时间
        auto time = std::chrono::duration_cast<std::chrono::milliseconds>(
                            std::chrono::high_resolution_clock::now() - m_begin_)
                            .count();
        std::cout << "time cost:{ " << m_tag_ << " } " << static_cast<double>(time) << " ms"
                  << std::endl;
    }
    static std::chrono::time_point<std::chrono::high_resolution_clock> Now() {
        return std::chrono::high_resolution_clock::now();
    }

    static long long DiffUs(std::chrono::time_point<std::chrono::high_resolution_clock> before,
                            std::chrono::time_point<std::chrono::high_resolution_clock> after) {
        return static_cast<long long>(
                std::chrono::duration_cast<std::chrono::microseconds>(after - before).count());
    }

    static long long DiffMs(std::chrono::time_point<std::chrono::high_resolution_clock> before,
                            std::chrono::time_point<std::chrono::high_resolution_clock> after) {
        return static_cast<long long>(
                std::chrono::duration_cast<std::chrono::milliseconds>(after - before).count());
    }

    static long long GetCurrentMs() {
#if 0
        struct timeval time;
        gettimeofday(&time, NULL);
        return static_cast<long long>(time.tv_sec * 1000) +
                static_cast<long long>(time.tv_usec / 1000);
#else
        struct timespec curTime;
        clock_gettime(CLOCK_MONOTONIC, &curTime);
        return MILLION * curTime.tv_sec + curTime.tv_nsec / 1000;
#endif
    }

    static void ShowCurTime() {
        time_t now = time(0);
        char *dt = ctime(&now);
        std::cout << "cur time is " << dt << endl;
        std::cout << "cur ms is " << GetCurrentMs() << endl;
    }

    static struct timeval GetCurrentTimeofDay() {
        struct timeval time;
        gettimeofday(&time, NULL);
        return time;
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_begin_;
    std::string m_tag_;
};

#define CAL_TIME(x) TimerLog t(x)
#define CAL_TIME_BEGIN(x) auto begin_##x = TimerLog::Now();

#define CAL_TIME_END(x)                                                                        \
    std::cout << "time cost:{ " << #x << " } " << TimerLog::DiffMs(begin_##x, TimerLog::Now()) \
              << "ms" << endl;

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
#endif // _BASE_H_
