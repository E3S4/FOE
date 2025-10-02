#pragma once
#include <QWidget>

class Timeline : public QWidget {
    Q_OBJECT
public:
    explicit Timeline(QWidget *parent=nullptr);

signals:
    void frameChanged(int frame);
};

