#include "gui.h"
#include "ui_gui.h"
#include "utils/constants.h"
#include <QColorDialog>
#include <thread>


CrosshairGui::CrosshairGui(QWidget* parent) :
    QMainWindow(parent),
    gui_(new Ui::CrosshairGui),
    crosshairProperties_(Constants::CROSSHAIR_PROPERTIES)
{
    gui_->setupUi(this);
    initWidgets();
    setFixedSize(size());

    crosshairManager_.setCrosshair(Crosshair::fromProperties(crosshairProperties_));

    std::thread t(
        [this]() {
            while (crosshairManager_.render()) {
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        }
    );
    t.detach();
}


CrosshairGui::~CrosshairGui() {
    delete gui_;
}


void CrosshairGui::initWidgets() {
    gui_->sizeSlider->setValue(crosshairProperties_.size);
    QObject::connect(gui_->sizeSlider, &QSlider::valueChanged, [this](int newSize) {
        crosshairProperties_.size = newSize;
        crosshairManager_.setCrosshair(Crosshair::fromProperties(crosshairProperties_));
    });

    gui_->gapSlider->setValue(crosshairProperties_.gap);
    QObject::connect(gui_->gapSlider, &QSlider::valueChanged, [this](int newGap) {
        crosshairProperties_.gap = newGap;
        crosshairManager_.setCrosshair(Crosshair::fromProperties(crosshairProperties_));
    });

    gui_->thicknessSlider->setValue(crosshairProperties_.thickness);
    QObject::connect(gui_->thicknessSlider, &QSlider::valueChanged, [this](int newThickness) {
        crosshairProperties_.thickness = newThickness;
        crosshairManager_.setCrosshair(Crosshair::fromProperties(crosshairProperties_));
    });

    gui_->outlineThicknessSlider->setValue(crosshairProperties_.outlineThickness);
    QObject::connect(gui_->outlineThicknessSlider, &QSlider::valueChanged, [this](int newOutlineThickness) {
        crosshairProperties_.outlineThickness = newOutlineThickness;
        crosshairManager_.setCrosshair(Crosshair::fromProperties(crosshairProperties_));
    });

    gui_->dotCheckBox->setChecked(crosshairProperties_.dot);
    QObject::connect(gui_->dotCheckBox, &QCheckBox::stateChanged, [this](int checkState) {
        crosshairProperties_.dot = checkState;
        crosshairManager_.setCrosshair(Crosshair::fromProperties(crosshairProperties_));
    });

    gui_->dotCheckBox->setChecked(crosshairProperties_.dot);
    QObject::connect(gui_->toggleCheckBox, &QCheckBox::stateChanged, [this](int checkState) {
        crosshairManager_.setEnabled(checkState);
    });


    gui_->adsCheckBox->setChecked(crosshairManager_.isVisibleInAds());
    QObject::connect(gui_->adsCheckBox, &QCheckBox::stateChanged, [this](int checkState) {
        crosshairManager_.setVisibleInAds(checkState);
    });
    

    auto getColorFor = [&](Color& color) {
        return [&]() {
            Color initialColor = color;

            auto* colorDialog = new QColorDialog(
                QColor::fromRgb(color.red, color.green, color.blue), 
                this
            );
            colorDialog->setOption(QColorDialog::DontUseNativeDialog);
            colorDialog->setAttribute(Qt::WA_DeleteOnClose);

            auto setColor = [&](const QColor& newColor) {
                if (newColor.isValid()) {
                    QRgb rgb = newColor.rgb();
                    color = {
                        static_cast<uint8_t>(qRed(rgb)),
                        static_cast<uint8_t>(qGreen(rgb)),
                        static_cast<uint8_t>(qBlue(rgb))
                    };
                    crosshairManager_.setCrosshair(Crosshair::fromProperties(crosshairProperties_));
                }
            };

            QObject::connect(colorDialog, &QColorDialog::currentColorChanged, setColor);
            QObject::connect(colorDialog, &QColorDialog::colorSelected, setColor);
            QObject::connect(colorDialog, &QColorDialog::rejected, [this, initialColor, &color]() {
                color = initialColor;
                crosshairManager_.setCrosshair(Crosshair::fromProperties(crosshairProperties_));
            });

            colorDialog->show();
        };
    };

    QObject::connect(gui_->colorButton, &QPushButton::pressed, getColorFor(crosshairProperties_.color));
    QObject::connect(gui_->outlineColorButton, &QPushButton::pressed, getColorFor(crosshairProperties_.outlineColor));
}
