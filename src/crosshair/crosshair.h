#pragma once

#include <unordered_map>
#include "utils/vector2i.h"



struct Color {
    uint8_t red, green, blue;
    uint8_t alpha = 255;
};


struct CrosshairProperties {
    int32_t size;
    int32_t gap;
    int32_t thickness;
    int32_t outlineThickness;
    Color color;
    Color outlineColor;
    bool dot;
};


class Crosshair {
public:
    Crosshair() = default;

    void setPixel(Vector2i position, Color color);
    void setRectangle(Vector2i topLeft, Vector2i bottomRight, Color color);
    Color getPixelColor(Vector2i vec) const;


    auto begin() const {
        return positionToColor_.begin();
    }

    auto end() const {
        return positionToColor_.end();
    }

    static Crosshair fromProperties(const CrosshairProperties& properties);

private:
    std::unordered_map<Vector2i, Color, Vector2iHasher> positionToColor_; 
};
