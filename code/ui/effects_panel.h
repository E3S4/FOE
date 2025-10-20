#pragma once
#include <QWidget>

class EffectsPanel : public QWidget {
    Q_OBJECT
public:
    explicit EffectsPanel(QWidget *parent=nullptr);
signals:
    void effectDropped(const QString&);
};

