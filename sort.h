#pragma once

#include <constexpr_map.h>

#include <type_traits>
#include <sys/types.h>

template <class K, class V, int S>
constexpr auto Sort(ConstexprMap<K, V, S> map) {
    ssize_t sz = map.Size();
    if (sz == 0) {
        return map;
    }
    if (std::is_integral_v<K>) {
        bool flag = true;
        while (flag) {
            flag = false;
            for (ssize_t i = 0; i < sz - 1; ++i) {
                if (!(map.GetByIndex(i) > map.GetByIndex(i + 1))) {
                    std::swap(map.GetByIndex(i), map.GetByIndex(i + 1));
                    flag = true;
                }
            }
            --sz;
        }
    } else {
        bool flag = true;
        while (flag) {
            flag = false;
            for (ssize_t i = 0; i < sz - 1; ++i) {
                if (map.GetByIndex(i) > map.GetByIndex(i + 1)) {
                    std::swap(map.GetByIndex(i), map.GetByIndex(i + 1));
                    flag = true;
                }
            }
            --sz;
        }
    }

    return map;
}
