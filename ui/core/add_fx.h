#pragma once
#include "framebuffer.h"
#include <opencv2/opencv.hpp>
#include <string>
namespace FX {
cv::Mat translate(const cv::Mat &frame, int dx, int dy);
cv::Mat colorCorrection(const cv::Mat &frame, double alpha=1.0, int beta=0);
cv::Mat glow(const cv::Mat &frame, double intensity=0.5);

} 
