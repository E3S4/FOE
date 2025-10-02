#include "add_fx.h"
#include <opencv2/opencv.hpp>

namespace FX {
cv::Mat translate(const cv::Mat &frame, int dx, int dy) {
    cv::Mat out;
    cv::Mat transMat = (cv::Mat_<double>(2,3) << 1,0,dx, 0,1,dy);
    cv::warpAffine(frame, out, transMat, frame.size());
    return out;
}
cv::Mat colorCorrection(const cv::Mat &frame, double alpha, int beta) {
    cv::Mat out;
    frame.convertTo(out, -1, alpha, beta);
    return out;
}
cv::Mat glow(const cv::Mat &frame, double intensity) {
    cv::Mat blurred, out;
    cv::GaussianBlur(frame, blurred, cv::Size(15,15), 0);
    cv::addWeighted(frame, 1.0, blurred, intensity, 0, out);
    return out;
}

} // namespace FX

