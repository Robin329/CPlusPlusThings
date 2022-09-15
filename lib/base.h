//
// Created by renbin jiang on 2021/8/30.
//

#pragma once
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
#include <cassert>
#include <chrono>
#include <climits>
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

typedef int8_t  S8;
typedef int16_t S16;
typedef int32_t S32;
typedef int64_t S64;

typedef uint8_t  U8;
typedef uint16_t U16;
typedef uint32_t U32;
typedef uint64_t U64;

typedef S8  s8;
typedef U8  u8;
typedef S16 s16;
typedef U16 u16;
typedef S32 s32;
typedef U32 u32;
typedef S64 s64;
typedef U64 u64;

#define rb_normal   "\033[0m"
#define rb_black    "\033[30m"
#define rb_red      "\033[31m"
#define rb_green    "\033[32m"
#define rb_yellow   "\033[33m"
#define rb_blue     "\033[34m"
#define rb_magenta  "\033[35m"
#define rb_cyan     "\033[36m"
#define rb_white    "\033[37m"
#define rb_bblack   "\033[30;1m"
#define rb_bred     "\033[31;1m"
#define rb_bgreen   "\033[32;1m"
#define rb_byellow  "\033[33;1m"
#define rb_bblue    "\033[34;1m"
#define rb_bmagenta "\033[35;1m"
#define rb_bcyan    "\033[36;1m"
#define rb_bwhite   "\033[37;1m"

#define TRUE  1
#define FALSE 0
#define BOOL  bool
using namespace std;
namespace base {
class ListNode {
public:
    int       val;
    ListNode *next;

    ListNode() {}
    ListNode(int x) : val(x), next(NULL) {}
    ~ListNode() {}
    static ListNode *nodeInit() {
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

    static bool printNode(ListNode *result) {
        ListNode * p = result->next;
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
    class TreeNode {
    private:
        int       val;
        TreeNode *left;
        TreeNode *right;

    public:
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
        TreeNode() {}
        ~TreeNode() {}
    };
};

#define GET_CUR_TIME_STRING(tag)                                                                                 \
    do {                                                                                                         \
        struct timespec ts;                                                                                      \
        clock_gettime(CLOCK_MONOTONIC, &ts);                                                                     \
        struct tm *pTm = localtime(&ts.tv_sec);                                                                  \
        char       timeStr[20] = {};                                                                             \
        sprintf(timeStr, "%.2d-%.2d %.2d:%.2d:%.2d.%.3ld %s ", tag, pTm->tm_mon + 1, pTm->tm_mday, pTm->tm_hour, \
                pTm->tm_min, pTm->tm_sec, ts.tv_nsec / 1000000);                                                 \
        std::cout << timeStr << " [" << __FUNCTION__ << "] " << std::endl;                                       \
    } while (0)

#ifdef __apple__
#define getpid() syscall(SYS_thread_selfid)
#endif
#ifndef TAG
#define TAG "base"
#endif
#define ROBIN_DBG(format, ...) \
    printf("%d %d D %s : %s" #format "\n", (int)getpid(), (int)syscall(SYS_gettid), TAG, __FUNCTION__, ##__VA_ARGS__)

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

class Mutex;
class Condition {
public:
    enum { PRIVATE = 0, SHARED = 1 };

    enum WakeUpType { WAKE_UP_ONE = 0, WAKE_UP_ALL = 1 };

    Condition();
    explicit Condition(int type);
    inline ~Condition() { pthread_cond_destroy(&mCond); }
    // Wait on the condition variable.  Lock the mutex before calling.
    // Note that spurious wake-ups may happen.
    inline int32_t wait(Mutex &mutex);
    // same with relative timeout
    inline int32_t waitRelative(Mutex &mutex, int64_t reltime);

    // Signal the condition variable, allowing one thread to continue.
    inline void signal() { pthread_cond_signal(&mCond); }
    // Signal the condition variable, allowing one or all threads to continue.
    inline void signal(WakeUpType type) {
        if (type == WAKE_UP_ONE) {
            signal();
        } else {
            broadcast();
        }
    }
    // Signal the condition variable, allowing all threads to continue.
    inline void broadcast() { pthread_cond_broadcast(&mCond); }

private:
#if !defined(_WIN32)
    pthread_cond_t mCond;
#else
    void *mState;
#endif
};

class Mutex {
public:
    enum { PRIVATE = 0, SHARED = 1 };

    Mutex() { pthread_mutex_init(&mMutex, nullptr); }
    explicit Mutex(const char *name) { pthread_mutex_init(&mMutex, nullptr); }
    explicit Mutex(int type, const char *name = nullptr) {
        if (type == SHARED) {
            pthread_mutexattr_t attr;
            pthread_mutexattr_init(&attr);
            pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
            pthread_mutex_init(&mMutex, &attr);
            pthread_mutexattr_destroy(&attr);
        } else {
            pthread_mutex_init(&mMutex, nullptr);
        }
    }
    ~Mutex() { pthread_mutex_destroy(&mMutex); }

    // lock or unlock the mutex
    int32_t lock() { return -pthread_mutex_lock(&mMutex); }
    void    unlock() { pthread_mutex_unlock(&mMutex); }

    // lock if possible; returns 0 on success, error otherwise
    int32_t tryLock() { return -pthread_mutex_trylock(&mMutex); }

    // Manages the mutex automatically. It'll be locked when Autolock is
    // constructed and released when Autolock goes out of scope.
    class Autolock {
    public:
        inline explicit Autolock(Mutex &mutex) : mLock(mutex) { mLock.lock(); }
        inline explicit Autolock(Mutex *mutex) : mLock(*mutex) { mLock.lock(); }
        inline ~Autolock() { mLock.unlock(); }

    private:
        Mutex &mLock;
        // Cannot be copied or moved - declarations only
        Autolock(const Autolock &);
        Autolock &operator=(const Autolock &);
    };

private:
    friend class Condition;
    // A mutex cannot be copied
    Mutex(const Mutex &);
    Mutex &operator=(const Mutex &);
#if !defined(_WIN32)
    pthread_mutex_t mMutex;
#else
    void  _init();
    void *mState;
#endif
};
inline int32_t Condition::wait(Mutex &mutex) {
    return -pthread_cond_wait(&mCond, &mutex.mMutex);
}
inline int32_t Condition::waitRelative(Mutex &mutex, int64_t reltime) {
    struct timespec ts;
#if defined(__linux__)
    clock_gettime(CLOCK_MONOTONIC, &ts);
#else // __APPLE__
    // Apple doesn't support POSIX clocks.
    struct timeval t;
    gettimeofday(&t, nullptr);
    ts.tv_sec = t.tv_sec;
    ts.tv_nsec = t.tv_usec * 1000;
#endif

    // On 32-bit devices, tv_sec is 32-bit, but `reltime` is 64-bit.
    int64_t reltime_sec = reltime / 1000000000;

    ts.tv_nsec += static_cast<long>(reltime % 1000000000);
    if (reltime_sec < INT64_MAX && ts.tv_nsec >= 1000000000) {
        ts.tv_nsec -= 1000000000;
        ++reltime_sec;
    }

    int64_t time_sec = ts.tv_sec;
    if (time_sec > INT64_MAX - reltime_sec) {
        time_sec = INT64_MAX;
    } else {
        time_sec += reltime_sec;
    }

    ts.tv_sec = (time_sec > LONG_MAX) ? LONG_MAX : static_cast<long>(time_sec);

    return -pthread_cond_timedwait(&mCond, &mutex.mMutex, &ts);
}
// ---------------------------------------------------------------------------

/*
 * Automatic mutex.  Declare one of these at the top of a function.
 * When the function returns, it will go out of scope, and release the
 * mutex.
 */

typedef Mutex::Autolock AutoMutex;

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
        }
        return m_stTime;
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
    int64_t systemTime(int /*clock*/) {
        // Clock support varies widely across hosts. Mac OS doesn't support
        // posix clocks, older glibcs don't support CLOCK_BOOTTIME and Windows
        // is windows.
        struct timeval t;
        t.tv_sec = t.tv_usec = 0;
        gettimeofday(&t, NULL);
        return int64_t(t.tv_sec) * 1000000000LL + int64_t(t.tv_usec) * 1000LL;
    }

private:
    static Time *m_stTime;
    std::time_t  m_time_t;
    std::tm *    m_time;
    int          m_year;
    int          m_min;
    int          m_hour;
    int          m_day;
    int          m_mon;
    int          m_wday;
    int          m_yday;
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

        timeCost = MILLION * (tpEnd.tv_sec - tpStart.tv_sec) + (tpEnd.tv_nsec - tpStart.tv_nsec) / 1000;

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
            return boot_clock::time_point(std::chrono::seconds(ts.tv_sec) + std::chrono::nanoseconds(ts.tv_nsec));
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
        auto time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() -
                                                                          m_begin_)
                            .count();
        std::cout << "time cost:{ " << m_tag_ << " } " << static_cast<double>(time) << " ms" << std::endl;
    }
    static std::chrono::time_point<std::chrono::high_resolution_clock> Now() {
        return std::chrono::high_resolution_clock::now();
    }

    static long long DiffUs(std::chrono::time_point<std::chrono::high_resolution_clock> before,
                            std::chrono::time_point<std::chrono::high_resolution_clock> after) {
        return static_cast<long long>(std::chrono::duration_cast<std::chrono::microseconds>(after - before).count());
    }

    static long long DiffMs(std::chrono::time_point<std::chrono::high_resolution_clock> before,
                            std::chrono::time_point<std::chrono::high_resolution_clock> after) {
        return static_cast<long long>(std::chrono::duration_cast<std::chrono::milliseconds>(after - before).count());
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
        char * dt = ctime(&now);
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
    std::string                                                 m_tag_;
};

#define CAL_TIME(x) TimerLog t(x)
#define CAL_TIME_BEGIN(x) auto begin_##x = TimerLog::Now();

#define CAL_TIME_END(x) \
    std::cout << "time cost:{ " << #x << " } " << TimerLog::DiffMs(begin_##x, TimerLog::Now()) << "ms" << endl;

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
[[nodiscard]] std::string StringReplace(std::string_view s, std::string_view from, std::string_view to, bool all);
} // namespace base
#endif // _BASE_H_
