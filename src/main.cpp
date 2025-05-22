#include <QApplication>
#include <gui/gui.h>


int main(int argc, char** argv) {
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);

    QApplication app(argc, argv);
    CrosshairGui gui;
    gui.show();
    app.exec();

    return 0;
}
