#include "crosshair.h"


void Crosshair::setPixel(Vector2i position, Color color) {
    positionToColor_[position] = color;
}


void Crosshair::setRectangle(Vector2i topLeft, Vector2i bottomRight, Color color) {
    for (int x = topLeft.x; x <= bottomRight.x; x++) {
        for (int y = topLeft.y; y <= bottomRight.y; y++) {
            setPixel({x, y}, color);
        }
    }
}


Color Crosshair::getPixelColor(Vector2i vec) const {
    return positionToColor_.at(vec);
}


Crosshair Crosshair::fromProperties(const CrosshairProperties& properties) {
    Crosshair crosshair;

    auto [size, gap, thickness, outlineThickness, color, outlineColor, dot] = properties;

    auto setOutlinedRectangle = [&](Vector2i topLeft, Vector2i bottomRight) {
        crosshair.setRectangle(topLeft, bottomRight, properties.color);
        if (outlineThickness) {
            
            crosshair.setRectangle(
                {topLeft.x - outlineThickness, topLeft.y - outlineThickness},
                {bottomRight.x, topLeft.y - 1},
                outlineColor
            );

            crosshair.setRectangle(
                {bottomRight.x + 1, topLeft.y - outlineThickness},
                {bottomRight.x + outlineThickness, bottomRight.y},
                outlineColor
            );

            crosshair.setRectangle(
                {topLeft.x, bottomRight.y + 1},
                {bottomRight.x + outlineThickness, bottomRight.y + outlineThickness},
                outlineColor
            );

            crosshair.setRectangle(
                {topLeft.x - outlineThickness, topLeft.y},
                {topLeft.x - 1, bottomRight.y + outlineThickness},
                outlineColor
            );
        }
    };

    // Dot
    if (dot) {
        setOutlinedRectangle(
            {-thickness / 2, -thickness / 2},
            {thickness - thickness / 2, thickness - thickness / 2}
        );
    }

    // Left
    setOutlinedRectangle(
        {-gap - size, -thickness / 2},
        {-gap - 1, thickness - thickness / 2}
    );

    // Right
    setOutlinedRectangle(
        {gap + 1, -thickness / 2},
        {gap + size, thickness - thickness / 2}
    );

    // Top
    setOutlinedRectangle(
        {-thickness / 2, -gap - size},
        {thickness - thickness / 2, -gap - 1}
    );

    // Bottom
    setOutlinedRectangle(
        {-thickness / 2, gap + 1},
        {thickness - thickness / 2, gap + size}
    );

    return crosshair;
}
