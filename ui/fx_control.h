#pragma once
#include <QWidget>

class FxControl : public QWidget {
    Q_OBJECT
public:
    explicit FxControl(QWidget *parent=nullptr);
    void loadEffectControls(const QString &effectName);
};

