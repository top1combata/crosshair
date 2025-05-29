#pragma once

#include <QMainWindow>
#include "crosshair/manager.h"


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
};
