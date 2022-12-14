#include "Filter.h"

Filter::Filter(bool addToList, int contrast, Filter::FilterType filterType) : Command(addToList){
    this->clarity = contrast;
    this->filterType = filterType;
}

Filter::~Filter() {

}

void Filter::operator()() {

}

void Filter::operator()(cv::Mat* mat) {
    if (clarity < 50) {
        cv::GaussianBlur(*mat, *mat, cv::Size(), ((double)50 - clarity) / 20.0f);
    }
    else if(clarity > 50) {
        cv::Mat blurred;
        cv::GaussianBlur(*mat, blurred, cv::Size(), ((double)clarity - 50) / 20.f);
        *mat = 2.0f * (*mat) - 1.0f * blurred;
    }

    if (filterType != FilterType::NONE) {
        cv::Mat hsv;
        cv::cvtColor(*mat, hsv, cv::COLOR_BGR2HSV);

        cv::Mat hsvSplit[3];
        split(hsv, hsvSplit);
        if (filterType == FilterType::GRAY) {
            cv::cvtColor(*mat, *mat, cv::COLOR_BGR2GRAY);
            cv::cvtColor(*mat, *mat, cv::COLOR_GRAY2BGR);
            return;
        }
        else if (filterType == FilterType::WARM) {
            hsvSplit[0] -= 10;
            hsvSplit[2] += 10;
        }
        else if (filterType == FilterType::COOL) {
            hsvSplit[0] += 60;
            hsvSplit[2] -= 20;
        }
        else if (filterType == FilterType::BRIGHT) {
            hsvSplit[0] += 5;
            hsvSplit[2] += 30;
        }
        cv::merge(hsvSplit, 3, hsv);
        cv::cvtColor(hsv, *mat, cv::COLOR_HSV2BGR);
    }
}