#pragma once

#include <cstdint>


struct Vector2i {
    int32_t x, y;

    bool operator==(Vector2i another) const {
        return x == another.x && y == another.y;
    }
};


struct Vector2iHasher {
    uint64_t operator()(Vector2i vec) const {
        return (static_cast<uint64_t>(vec.x) << 32) + static_cast<uint64_t>(vec.y);
    }
};
