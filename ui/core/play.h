#pragma once
#include "framebuffer.h"
#include <QObject>
#include <QTimer>
#include <QImage>
#include <functional>

class PlayEngine : public QObject {
    Q_OBJECT
public:
    PlayEngine(QObject *parent = nullptr);

    void startPreview(const VideoClip &clip, std::function<void(const QImage&)> frameCallback = nullptr);
    void stopPreview();

private slots:
    void advanceFrame();

private:
    VideoClip currentClip;
    int currentFrame = 0;
    QTimer timer;
    std::function<void(const QImage&)> frameCallback;
};

