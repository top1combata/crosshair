#pragma once

#include <mutex>
#include <memory>
#include "crosshair.h"


class CrosshairManager {
public:
    CrosshairManager();
    ~CrosshairManager();

    CrosshairManager(const CrosshairManager&) = delete;
    CrosshairManager& operator=(const CrosshairManager&) = delete;

    void setCrosshair(const Crosshair& crosshair);
    const Crosshair& getCrosshair() const;

    bool isVisible() const;
    void setVisible(bool state = true);

    bool render();

private:
    static constexpr char* WINDOW_CLASS_NAME = "wnd";
    static constexpr char* WINDOW_NAME = "wnd";

    void* hwnd_;
    Crosshair crosshair_;
    bool isVisible_ = false;

private:
    void initWindow();
    void redraw();
};
