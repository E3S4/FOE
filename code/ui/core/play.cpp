#include "play.h"
#include <opencv2/opencv.hpp>

PlayEngine::PlayEngine(QObject *parent) : QObject(parent) {}

void PlayEngine::loadClip(const VideoClip &clip) {
    currentClip = clip;
}

void PlayEngine::seekToFrame(int frame) {
    if (frame < 0 || frame >= currentClip.frames.size()) return;

    const cv::Mat &mat = currentClip.frames[frame];
    if (!mat.empty()) {
        QImage img(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_BGR888);
        emit frameDisplayed(img.copy());
    }
}

