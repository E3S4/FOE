#pragma once
#include <opencv2/opencv.hpp>
extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
}
#include <string>
#include <vector>
struct VideoClip {
    int width = 0;
    int height = 0;
    int frameRate = 24;
    int totalFrames = 0;
    int streamIndex = 0;
    std::vector<cv::Mat> frames;
    AVFormatContext *fmtCtx = nullptr;
    AVCodecContext  *codecCtx = nullptr;
    std::string filePath;
};

