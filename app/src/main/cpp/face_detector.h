//
// Created by Lightweh on 2018/11/21.
//

#ifndef FACEDETECTION_FACE_DETECTOR_H
#define FACEDETECTION_FACE_DETECTOR_H


#include <vector>
#include <opencv2/opencv.hpp>
#include <dlib/opencv/cv_image.h>
#include <dlib/image_processing/frontal_face_detector.h>


class FaceDetector {
private:

    dlib::frontal_face_detector face_detector;
    std::vector<dlib::rectangle> det_rects;

public:

    FaceDetector();

    int Detect(const cv::Mat &image);

    std::vector<dlib::rectangle> getDetResultRects();
};


#endif //FACEDETECTION_FACE_DETECTOR_H
