#include "play.h"
#include <opencv2/opencv.hpp>
#include <QDebug>

PlayEngine::PlayEngine(QObject *parent): QObject(parent) {
    connect(&timer, &QTimer::timeout, this, &PlayEngine::advanceFrame);
}

void PlayEngine::startPreview(const VideoClip &clip, std::function<void(const QImage&)> callback) {
    currentClip = clip;
    currentFrame = 0;
    frameCallback = callback;
    if(currentClip.totalFrames > 0)
        timer.start(1000 / currentClip.frameRate);
}

void PlayEngine::stopPreview() {
    timer.stop();
}

void PlayEngine::advanceFrame() {
    if(currentFrame >= currentClip.totalFrames) {
        timer.stop();
        return;
    }

    cv::Mat frame = currentClip.frames[currentFrame];

    // Convert BGR -> RGB for Qt
    cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);
    QImage qimg(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);

    if(frameCallback) frameCallback(qimg);

    currentFrame++;
}

