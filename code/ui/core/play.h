#pragma once
#include <QObject>
#include <QImage>
#include "framebuffer.h"

class PlayEngine : public QObject {
    Q_OBJECT
public:
    explicit PlayEngine(QObject *parent = nullptr);

    void loadClip(const VideoClip &clip);
    void seekToFrame(int frame);

signals:
    void frameDisplayed(const QImage &img);

private:
    VideoClip currentClip;
};

