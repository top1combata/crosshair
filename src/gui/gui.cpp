#include "gui.h"
#include "ui_gui.h"


CrosshairGui::CrosshairGui(QWidget *parent) :
    QMainWindow(parent),
    gui_(new Ui::CrosshairGui) 
{
    gui_->setupUi(this);
}


CrosshairGui::~CrosshairGui() {
    delete gui_;
}
