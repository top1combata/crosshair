#pragma once

#include <crosshair/crosshair.h>


namespace Constants {

constexpr CrosshairProperties CROSSHAIR_PROPERTIES = {
    .size = 10,
    .gap = 7,
    .thickness = 2,
    .outlineThickness = 2,
    .color = {255, 0, 255},
    .outlineColor = {1, 0, 0},
    .dot = true
};

constexpr char WINDOW_CLASS_NAME[] = "crosshair_window_class";

constexpr char WINDOW_NAME[] = "crosshair_window";

}
