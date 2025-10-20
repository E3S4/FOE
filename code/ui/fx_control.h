#pragma once
#include <QWidget>
#include <QFormLayout>
#include <QSlider>
#include <QLabel>
#include "core/add_fx.h"

class FxControl : public QWidget {
    Q_OBJECT
public:
    explicit FxControl(QWidget *parent = nullptr);
    void loadEffectControls(const QString &effectName);

signals:
    void paramsChanged(const FXParams &params);

private:
    FXParams currentParams;
};

