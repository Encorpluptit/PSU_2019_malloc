//
// Created by dbernard on 2/8/20.
//

#include "memory.h"

size_t align(size_t sz) {
    for (size_t i = 0; i != 32; ++i)
        if (1 << i > sz)
            return 1 << i;
    return sz;
}
