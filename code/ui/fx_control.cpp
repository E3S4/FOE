#include "fx_control.h"

FxControl::FxControl(QWidget *parent) : QWidget(parent) {
    auto *form = new QFormLayout(this);
    setLayout(form);
}

void FxControl::loadEffectControls(const QString &name) {
    auto *form = qobject_cast<QFormLayout*>(layout());

    //remove old contro;
    QLayoutItem *child;
    while ((child = form->takeAt(0))) {
        if (child->widget()) delete child->widget();
        delete child;
    }

    // Add title
    form->addRow(new QLabel("<b>" + name + "</b>"));

    // pos x
    QSlider *xSlider = new QSlider(Qt::Horizontal);
    xSlider->setRange(-200, 200);
    form->addRow("Position X", xSlider);
    connect(xSlider, &QSlider::valueChanged, this, [this](int v) {
        this->currentParams.posX = v;
        emit paramsChanged(this->currentParams);
    });

    // [pos y]
    QSlider *ySlider = new QSlider(Qt::Horizontal);
    ySlider->setRange(-200, 200);
    form->addRow("Position Y", ySlider);
    connect(ySlider, &QSlider::valueChanged, this, [this](int v) {
        this->currentParams.posY = v;
        emit paramsChanged(this->currentParams);
    });

    // hueShift
    QSlider *hueSlider = new QSlider(Qt::Horizontal);
    hueSlider->setRange(0, 180);
    form->addRow("Hue Shift", hueSlider);
    connect(hueSlider, &QSlider::valueChanged, this, [this](int v) {
        this->currentParams.hueShift = v;
        emit paramsChanged(this->currentParams);
    });

    //brightSlider-
    QSlider *brightSlider = new QSlider(Qt::Horizontal);
    brightSlider->setRange(0, 200);
    brightSlider->setValue(100);
    form->addRow("Brightness", brightSlider);
    connect(brightSlider, &QSlider::valueChanged, this, [this](int v) {
        this->currentParams.brightness = v / 100.0f;
        emit paramsChanged(this->currentParams);
    });

    //contrastSlider-
    QSlider *contrastSlider = new QSlider(Qt::Horizontal);
    contrastSlider->setRange(50, 200);
    contrastSlider->setValue(100);
    form->addRow("Contrast", contrastSlider);
    connect(contrastSlider, &QSlider::valueChanged, this, [this](int v) {
        this->currentParams.contrast = v / 100.0f;
        emit paramsChanged(this->currentParams);
    });

    // 
    // glow
    QSlider *glowSlider = new QSlider(Qt::Horizontal);
    glowSlider->setRange(0, 1);
    form->addRow("Glow", glowSlider);
    connect(glowSlider, &QSlider::valueChanged, this, [this](int v) {
        this->currentParams.glow = (v != 0);
        emit paramsChanged(this->currentParams);
    });
}

