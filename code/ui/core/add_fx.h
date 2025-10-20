#pragma once
#include <opencv2/opencv.hpp>
#include <string>

struct FXParams {
    int posX = 0;
    int posY = 0;
    float scale = 1.0f;
    int hueShift = 0;       // cc
    float brightness = 1.0f;
    float contrast = 1.0f;
    bool glow = false;
};

class AddFX {
public:
    AddFX() = default;

    //it aplies fx to each frame 
     cv::Mat apply(const cv::Mat &input, const FXParams &params);
};

