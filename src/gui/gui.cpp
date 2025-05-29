#include "gui.h"
#include "ui_gui.h"
#include <thread>


CrosshairGui::CrosshairGui(QWidget* parent) :
    QMainWindow(parent),
    gui_(new Ui::CrosshairGui) 
{
    gui_->setupUi(this);
    std::thread t(
        [this]() {
            while (crosshairManager_.render()) {
            }
        }
    );
    t.detach();
}


CrosshairGui::~CrosshairGui() {
    delete gui_;
}
