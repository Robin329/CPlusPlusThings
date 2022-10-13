/*
** The crc hash is licensed under the Apache License, Version 2.0, and a copy of the license is included in this file.
**
**Author:Wang Yaofu voipman@qq.com
**Description: The source file of class CrcHash.
*/

#include "crc16.h"
#include "crc32.h"
#include "crc64.h"
#include "crchash.h"
namespace common {
uint16_t Hash16(const std::string& key) {
    return crc16(key.c_str(), key.size());
}
uint16_t Hash16(const char* cpKey, const int iKeyLen) {
    return crc16(cpKey, iKeyLen);
}

uint32_t Hash32(const std::string& key) {
    return crc32(key.c_str(), key.size());
}
uint32_t Hash32(const char* cpKey, const int iKeyLen) {
    return crc32(cpKey, iKeyLen);
}

uint64_t Hash64(const std::string& key) {
    return crc64(key.c_str(), key.size());
}
uint64_t Hash64(const char* cpKey, const int iKeyLen) {
    return crc64(cpKey, iKeyLen);
}
} // namespace common
