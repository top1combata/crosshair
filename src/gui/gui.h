#pragma once

#include <crosshair/manager.h>
#include <QMainWindow>


namespace Ui {
class CrosshairGui;
}

class CrosshairGui : public QMainWindow
{
    Q_OBJECT

public:
    explicit CrosshairGui(QWidget* parent = nullptr);
    ~CrosshairGui();

private:
    Ui::CrosshairGui* gui_;
    CrosshairManager crosshairManager_;
    CrosshairProperties crosshairProperties_ = {};

private:
    void initWidgets();
};
