/**
 * @file classic_practice.cpp
 * @brief g++ -o classic_practice classic_practice.cpp -std=c++11
 * @author 光城
 * @version v1
 * @date 2019-08-07
 */

#include <dlfcn.h>

#include <iostream>

using namespace std;
/**
 * @brief namespace解决作用域不受限
 */
namespace Color {
enum Type { RED = 15, YELLOW, BLUE };
};

/**
 * @brief 上述如果 using namespace Color 后，前缀还可以省去，使得代码简化。
 * 不过，因为命名空间是可以随后被扩充内容的，所以它提供的作用域封闭性不高。
 * 在大项目中，还是有可能不同人给不同的东西起同样的枚举类型名。
 * 更“有效”的办法是用一个类或结构体来限定其作用域。
 *
 * 定义新变量的方法和上面命名空间的相同。
 * 不过这样就不用担心类在别处被修改内容。
 * 这里用结构体而非类，一是因为本身希望这些常量可以公开访问，
 * 二是因为它只包含数据没有成员函数。
 */
struct Color1 {
    enum Type { RED = 102, YELLOW, BLUE };
};

/**
 * @brief C++11的枚举类
 * 下面等价于enum class Color2:int
 */
enum class Color2 { RED = 2, YELLOW, BLUE };

enum class Color3 : char; // 前向声明

// 定义
enum class Color3 : char { RED = 'r', BLUE };
//===========================================
#include <cxxabi.h>   // for __cxa_demangle
#include <dlfcn.h>    // for dladdr
#include <execinfo.h> // for backtrace

#include <sstream>
#include <string>

// This function produces a stack backtrace with demangled function & method
// names.
std::string Backtrace(int skip = 1) {
    void *callstack[128];
    const int nMaxFrames = sizeof(callstack) / sizeof(callstack[0]);
    char buf[1024];
    int nFrames = backtrace(callstack, nMaxFrames);
    char **symbols = backtrace_symbols(callstack, nFrames);

    std::ostringstream trace_buf;
    for (int i = skip; i < nFrames; i++) {
        Dl_info info;
        if (dladdr(callstack[i], &info)) {
            char *demangled = NULL;
            int status;
            demangled = abi::__cxa_demangle(info.dli_sname, NULL, 0, &status);
            snprintf(buf, sizeof(buf), "%-3d %*0p %s + %zd\n", i, 2 + sizeof(void *) * 2, callstack[i],
                     status == 0 ? demangled : info.dli_sname, (char *)callstack[i] - (char *)info.dli_saddr);
            free(demangled);
        } else {
            snprintf(buf, sizeof(buf), "%-3d %*0p\n", i, 2 + sizeof(void *) * 2, callstack[i]);
        }
        trace_buf << buf;

        snprintf(buf, sizeof(buf), "%s\n", symbols[i]);
        trace_buf << buf;
    }
    free(symbols);
    if (nFrames == nMaxFrames) trace_buf << "[truncated]\n";
    return trace_buf.str();
}
//===========================================

//===========================================
#include <execinfo.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void handler(int sig) {
    void *array[10];
    size_t size;

    // get void*'s for all entries on the stack
    size = backtrace(array, 10);

    // print out all the frames to stderr
    fprintf(stderr, "Error: signal %d:\n", sig);
    backtrace_symbols_fd(array, size, STDERR_FILENO);
    exit(1);
}

//===========================================

//===============================================
#include <cxxabi.h>
#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>

/** Print a demangled stack backtrace of the caller function to FILE* out. */
static inline void print_stacktrace(FILE *out = stderr, unsigned int max_frames = 63) {
    fprintf(out, "stack trace:\n");

    // storage array for stack trace address data
    void *addrlist[max_frames + 1];

    // retrieve current stack addresses
    int addrlen = backtrace(addrlist, sizeof(addrlist) / sizeof(void *));

    if (addrlen == 0) {
        fprintf(out, "  <empty, possibly corrupt>\n");
        return;
    }

    // resolve addresses into strings containing "filename(function+address)",
    // this array must be free()-ed
    char **symbollist = backtrace_symbols(addrlist, addrlen);

    // allocate string which will be filled with the demangled function name
    size_t funcnamesize = 256;
    char *funcname = (char *)malloc(funcnamesize);

    // iterate over the returned symbol lines. skip the first, it is the
    // address of this function.
    for (int i = 1; i < addrlen; i++) {
        char *begin_name = 0, *begin_offset = 0, *end_offset = 0;

        // find parentheses and +address offset surrounding the mangled name:
        // ./module(function+0x15c) [0x8048a6d]
        for (char *p = symbollist[i]; *p; ++p) {
            if (*p == '(')
                begin_name = p;
            else if (*p == '+')
                begin_offset = p;
            else if (*p == ')' && begin_offset) {
                end_offset = p;
                break;
            }
        }

        if (begin_name && begin_offset && end_offset && begin_name < begin_offset) {
            *begin_name++ = '\0';
            *begin_offset++ = '\0';
            *end_offset = '\0';

            // mangled name is now in [begin_name, begin_offset) and caller
            // offset in [begin_offset, end_offset). now apply
            // __cxa_demangle():

            int status;
            char *ret = abi::__cxa_demangle(begin_name, funcname, &funcnamesize, &status);
            if (status == 0) {
                funcname = ret; // use possibly realloc()-ed string
                fprintf(out, "  %s : %s+%s\n", symbollist[i], funcname, begin_offset);
            } else {
                // demangling failed. Output function name as a C function with
                // no arguments.
                fprintf(out, "  %s : %s()+%s\n", symbollist[i], begin_name, begin_offset);
            }
        } else {
            // couldn't parse the line? print the whole line.
            fprintf(out, "  %s\n", symbollist[i]);
        }
    }

    free(funcname);
    free(symbollist);
}

//===============================================
int func1(void) {
    cout << "this func1" << endl;
    print_stacktrace();
    //    cout << Backtrace();
    return 0;
}

void func2(void) {
    cout << "this func2" << endl;
    func1();
    // cout << Backtrace();
    return;
}

int main() {
    // 定义新的枚举变量
    Color::Type c = Color::RED;
    cout << c << endl;
    /**
     * 上述的另一种方法：
     * using namespace Color; // 定义新的枚举变量
     * Type c = RED;
     */
    Color1 c1;
    cout << c1.RED << endl;

    Color1::Type c11 = Color1::BLUE;
    cout << c11 << endl;

    Color2 c2 = Color2::RED;
    cout << static_cast<int>(c2) << endl;

    char c3 = static_cast<char>(Color3::RED);
    cout << c3 << endl;
    func1();
    //    cout << Backtrace();
    func2();
    system("ls -al");
    return 0;
}
