#include "fx_control.h"
#include <QFormLayout>
#include <QSlider>
#include <QLabel>

FxControl::FxControl(QWidget *p): QWidget(p) {
    auto *form = new QFormLayout(this);
    setLayout(form);
}

void FxControl::loadEffectControls(const QString &name) {
    auto *form = qobject_cast<QFormLayout*>(layout());
    QLayoutItem *child;
    while ((child = form->takeAt(0))) { delete child->widget(); delete child; }
    form->addRow(new QLabel("<b>"+name+"</b>"));
    for(int i=0;i<3;i++){
        auto *s = new QSlider(Qt::Horizontal);
        form->addRow(QString("Param %1").arg(i+1), s);
    }
}

