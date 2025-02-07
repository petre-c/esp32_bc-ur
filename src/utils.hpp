//
//  utils.hpp
//
//  Copyright © 2020 by Blockchain Commons, LLC
//  Licensed under the "BSD-2-Clause Plus Patent License"
//

#ifndef UTILS_HPP
#define UTILS_HPP

#include <stdint.h>
#include <vector>
#include <utility>
#include <string>
#include <array>
#include <assert.h>

#include "psram-allocator.hpp"

namespace ur {

typedef std::vector<uint8_t, PSRAMAllocator<uint8_t>> ByteVector;
typedef std::vector<ByteVector, PSRAMAllocator<ByteVector>> ByteVectorVector;
typedef std::vector<std::string, PSRAMAllocator<std::string>> StringVector;

ByteVector sha256(const ByteVector &buf);
ByteVector crc32_bytes(const ByteVector &buf);
uint32_t crc32_int(const ByteVector &buf);

ByteVector string_to_bytes(const std::string& s);

std::string data_to_hex(const ByteVector& in);
std::string data_to_hex(uint32_t n);

ByteVector int_to_bytes(uint32_t n);
uint32_t bytes_to_int(const ByteVector& in);

std::string join(const StringVector &strings, const std::string &separator);
StringVector split(const std::string& s, char separator);

StringVector partition(const std::string& string, size_t size);

std::string take_first(const std::string &s, size_t count);
std::string drop_first(const std::string &s, size_t count);

template<typename T, typename A>
void append(std::vector<T, A>& target, const std::vector<T, A>& source) {
    target.insert(target.end(), source.begin(), source.end());
}

template<typename T, typename A, size_t N>
void append(std::vector<T, A>& target, const std::array<T, N>& source) {
    target.insert(target.end(), source.begin(), source.end());
}

template<typename T, typename A1, typename A2>
std::vector<T, A1> join(const std::vector<std::vector<T, A1>, A2>& parts) {
    std::vector<T, A1> result;
    for(auto part: parts) { append(result, part); }
    return result;
}

template<typename T, typename A>
std::pair<std::vector<T, A>, std::vector<T, A>> split(const std::vector<T, A>& buf, size_t count) {
    auto first = buf.begin();
    auto c = std::min(buf.size(), count);
    auto last = first + c;
    auto a = std::vector<T, A>(first, last);
    auto b = std::vector<T, A>(last, buf.end());
    return std::make_pair(a, b);
}

template<typename T, typename A>
std::vector<T, A> take_first(const std::vector<T, A> &buf, size_t count) {
    auto first = buf.begin();
    auto c = std::min(buf.size(), count);
    auto last = first + c;
    return std::vector<T, A>(first, last);
}

void xor_into(ByteVector& target, const ByteVector& source);
ByteVector xor_with(const ByteVector& a, const ByteVector& b);

bool is_ur_type(char c);
bool is_ur_type(const std::string& s);

std::string to_lowercase(const std::string& s);
bool has_prefix(const std::string& s, const std::string& prefix);

}

#endif // UTILS_HPP
