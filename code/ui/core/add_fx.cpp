#include "add_fx.h"

cv::Mat AddFX::apply(const cv::Mat &input, const FXParams &params) {
    cv::Mat output;
    input.copyTo(output);

    //pos-scale
    if(params.posX != 0 || params.posY != 0 || params.scale != 1.0f){
        cv::Mat tmp;
        cv::resize(output, tmp, cv::Size(), params.scale, params.scale);
        output = cv::Mat::zeros(output.size(), output.type());
        int x = std::min(std::max(params.posX, 0), output.cols - tmp.cols);
        int y = std::min(std::max(params.posY, 0), output.rows - tmp.rows);
        tmp.copyTo(output(cv::Rect(x, y, tmp.cols, tmp.rows)));
    }

    // cc
    cv::Mat hsv;
    cv::cvtColor(output, hsv, cv::COLOR_BGR2HSV);
    std::vector<cv::Mat> channels;
    cv::split(hsv, channels);

    //hue shift
    channels[0] = (channels[0] + params.hueShift) % 180;

    //mege bakc
    cv::merge(channels, hsv);
    cv::cvtColor(hsv, output, cv::COLOR_HSV2BGR);

    //brightness
    output.convertTo(output, -1, params.contrast, params.brightness*50);

    // glow   
    if(params.glow){
        cv::Mat blur;
        cv::GaussianBlur(output, blur, cv::Size(15,15), 0);
        cv::addWeighted(output, 0.7, blur, 0.3, 0, output);
    }

    return output;
}

