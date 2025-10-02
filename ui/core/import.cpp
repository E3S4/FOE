#include "import.h"
#include <opencv2/opencv.hpp>
#include <QDebug>
VideoClip importVideo(const QString &qpath) {
    VideoClip clip;
    std::string path = qpath.toStdString();
    cv::VideoCapture cap(path);
    if(!cap.isOpened()) {
        qWarning() << "Failed to open video:" << qpath;
        return clip;
    }
    clip.width  = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
    clip.height = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));
    clip.frameRate = static_cast<int>(cap.get(cv::CAP_PROP_FPS));
    clip.totalFrames = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_COUNT));
    clip.filePath = path;
    for(int i=0; i<clip.totalFrames; i++){
        cv::Mat frame;
        cap >> frame;
        if(frame.empty()) break;
        clip.frames.push_back(frame);
    }
    qDebug() << "Imported video:" << qpath
             << "FPS:" << clip.frameRate
             << "Frames:" << clip.totalFrames
             << "Resolution:" << clip.width << "x" << clip.height;
    return clip;
}

