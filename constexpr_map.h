#pragma once

#include <array>
#include <stdexcept>

template <class K, class V, int MaxSize = 8>
class ConstexprMap {
public:
    constexpr ConstexprMap() {
    }

    constexpr V& operator[](const K& key) {
        if (sz_ >= MaxSize) {
            throw std::runtime_error("Incorrect index");
        }
        for (auto& elem : data_) {
            if (elem.first == key) {
                return elem.second;
            }
        }
        data_[sz_].first = key;
        return data_[sz_++].second;
    }

    constexpr const V& operator[](const K& key) const {
        for (const auto& elem : data_) {
            if (elem.first == key) {
                return elem.second;
            }
        }
        throw std::runtime_error("didn't find key");
    }

    constexpr bool Erase(const K& key) {
        for (std::size_t i = 0; i < sz_; ++i) {
            if (data_[i].first == key) {
                --sz_;
                for (size_t j = i; j < sz_; ++j) {
                    data_[j] = data_[j + 1];
                }
                return true;
            }
        }
        return false;
    }

    constexpr bool Find(const K& key) const {
        for (const auto& elem : data_) {
            if (elem.first == key) {
                return true;
            }
        }
        return false;
    }

    constexpr std::size_t Size() const {
        return sz_;
    }

    constexpr std::pair<K, V>& GetByIndex(std::size_t pos) {
        if (pos > sz_) {
            throw std::runtime_error("lol");
        }
        return data_[pos];
    }

    constexpr const std::pair<K, V>& GetByIndex(std::size_t pos) const {
        if (pos > sz_) {
            throw std::runtime_error("lol");
        }
        return data_[pos];
    }

private:
    std::size_t sz_ = 0;
    std::array<std::pair<K, V>, MaxSize> data_;
};
