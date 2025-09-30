#include "timeline.h"
#include <QSlider>
#include <QVBoxLayout>
#include <QLabel>

Timeline::Timeline(QWidget *p): QWidget(p) {
    auto *layout = new QVBoxLayout(this);
    auto *label = new QLabel("Frame: 0");
    auto *scrub = new QSlider(Qt::Horizontal);
    scrub->setRange(0,1000);
    connect(scrub,&QSlider::valueChanged,
            label,[label](int v){ label->setText(QString("Frame: %1").arg(v)); });
    layout->addWidget(scrub);
    layout->addWidget(label);
    scrub->setFixedHeight(20);
    scrub->setStyleSheet(R"(
                        QSlider::groove:horizontal { height:6px; background:#505050; }
                        QSlider::handle:horizontal { background:#aaa; width:12px; margin:-5px 0; border-radius:6px; }
)");
    int frameRate = 24;
connect(scrub, &QSlider::valueChanged, label, [label, frameRate](int frame){
    int totalSeconds = frame / frameRate;
    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;
    int frames = frame % frameRate;
    label->setText(QString("%1:%2:%3")
                   .arg(minutes,2,10,QChar('0'))
                   .arg(seconds,2,10,QChar('0'))
                   .arg(frames,2,10,QChar('0')));
});

}

