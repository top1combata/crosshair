#include "manager.h"

#include <windows.h>


CrosshairManager::CrosshairManager() {
    initWindow();
    crosshair_ = Crosshair::fromProperties({
        .size = 10,
        .gap = 7,
        .thickness = 2,
        .outlineThickness = 2,
        .color = {255, 0, 0},
        .outlineColor = {1, 0, 0},
        .dot = true
    });
    setVisible();
}


CrosshairManager::~CrosshairManager() {
    DestroyWindow(static_cast<HWND>(hwnd_));
    UnregisterClassA(WINDOW_CLASS_NAME, GetModuleHandleA(NULL));
}


LRESULT WINAPI windowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

void CrosshairManager::initWindow() {
    WNDCLASSA windowClass = {};
    windowClass.lpszClassName = WINDOW_CLASS_NAME;
    windowClass.hInstance = GetModuleHandleA(NULL);
    windowClass.lpfnWndProc = &windowProcedure;

    if (!RegisterClassA(&windowClass)) {
        throw std::runtime_error("Failed to register window class");
    }

    hwnd_ = CreateWindowExA(
        WS_EX_LAYERED | WS_EX_TOPMOST | WS_EX_TOOLWINDOW | WS_EX_TRANSPARENT,
        WINDOW_CLASS_NAME, WINDOW_NAME,
        WS_POPUP,
        0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
        NULL, NULL, GetModuleHandleA(NULL),
        static_cast<void*>(this) // Pass this in lParam in window procedure
    );

    if (!hwnd_) {
        throw std::runtime_error("Failed to create a window");
    }

    SetLayeredWindowAttributes(static_cast<HWND>(hwnd_), 0, 0, LWA_COLORKEY);

    ShowWindow(static_cast<HWND>(hwnd_), SW_SHOW);
}


bool CrosshairManager::render() {
    MSG msg;
    while (PeekMessageA(&msg, static_cast<HWND>(hwnd_), 0, 0, PM_REMOVE)) {
        if (msg.message == WM_QUIT) {
            return false;
        }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return true;
}


void CrosshairManager::redraw() {
    InvalidateRect(static_cast<HWND>(hwnd_), nullptr, TRUE);
}


void CrosshairManager::setCrosshair(const Crosshair& crosshair) {
    crosshair_ = crosshair;
}


const Crosshair& CrosshairManager::getCrosshair() const {
    return crosshair_;
}


bool CrosshairManager::isVisible() const {
    return isVisible_;
}


void CrosshairManager::setVisible(bool state) {
    if (state != isVisible_) {
        isVisible_ = state;
        redraw();
    }
}


LRESULT WINAPI windowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_NCCREATE: {
            // Getting pointer to CrosshairManager passed from window creation
            CrosshairManager* crosshairManagerPtr = reinterpret_cast<CrosshairManager*>(
                reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams
            );

            SetWindowLongPtrA(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(crosshairManagerPtr));
        }

        case WM_PAINT: {
            PAINTSTRUCT paintstruct;
            HDC hdc = BeginPaint(hwnd, &paintstruct);

            // Transparent background
            RECT rc;
            GetClientRect(hwnd, &rc);
            FillRect(hdc, &rc, static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH)));

            const auto& crosshairManager = (
                *reinterpret_cast<CrosshairManager*>(GetWindowLongPtrA(hwnd, GWLP_USERDATA))
            );

            if (crosshairManager.isVisible()) {
                Vector2i screenCenter = {
                    GetSystemMetrics(SM_CXSCREEN) / 2,
                    GetSystemMetrics(SM_CYSCREEN) / 2
                };

                for (auto [position, color] : crosshairManager.getCrosshair()) {
                    SetPixel(
                        hdc, 
                        screenCenter.x + position.x, 
                        screenCenter.y + position.y, 
                        RGB(color.red, color.green, color.blue)
                    );
                }
            }

            EndPaint(hwnd, &paintstruct);
        }

        case WM_ERASEBKGND: {
            return 1;
        }

        case WM_DESTROY: {
            PostQuitMessage(0);
            return 0;
        }
    }

    return DefWindowProcA(hwnd, msg, wParam, lParam);
}
