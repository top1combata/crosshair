#pragma once

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

    bool isVisibleInAds() const;
    void setVisibleInAds(bool state = true);
    
    bool isEnabled() const;
    void setEnabled(bool state = true);

    bool render();

private:
    void* hwnd_;
    Crosshair crosshair_;
    bool isVisible_ = false;
    bool isEnabled_ = false;
    bool isVisibleInAds_ = false;

private:
    void initWindow();
    void redraw();
};
