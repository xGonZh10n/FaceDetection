//
// Created by Lightweh on 2018/11/21.
//

#include "face_detector.h"

FaceDetector::FaceDetector() {
    face_detector = dlib::get_frontal_face_detector();
}

int FaceDetector::Detect(const cv::Mat &image) {

    if (image.empty())
        return 0;

    if (image.channels() == 1) {
        cv::cvtColor(image, image, CV_GRAY2BGR);
    }

    dlib::cv_image<dlib::bgr_pixel> dlib_image(image);

    det_rects.clear();

    det_rects = face_detector(dlib_image);

    return det_rects.size();
}

std::vector<dlib::rectangle> FaceDetector::getDetResultRects() {
    return det_rects;
}