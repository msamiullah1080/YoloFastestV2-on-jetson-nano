#ifndef CAMERAPROCESSING_HPP_INCLUDED
#define CAMERAPROCESSING_HPP_INCLUDED

#include <iostream>
#include <stdio.h>
#include <vector>
#include <chrono>
#include <thread>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


#include "yolo-fastestv2.h"
#include "FrameBuffer.hpp" // Include the header for FrameBuffer class
#include "AnnotateObjects.hpp"  // Include the header for AnnotateObjects class

void videoCreation(FrameBuffer& frameBuffer, const std::string &recording) {
    frameBuffer.generateVideo(recording);
}

void cameraProcessing(const std::string &rtspUrl, const std::string &cameraID, yoloFastestv2 &yoloF2) {

    float f;
    float FPS[16];
    int i, Fcnt = 0;

    cv::Mat frame;
    std::chrono::steady_clock::time_point Tbegin, Tend;

    for (i = 0; i < 16; i++) FPS[i] = 0.0;

    cv::VideoCapture cap(rtspUrl);


    if (!cap.isOpened()) {
        std::cerr << "ERROR: Unable to open " << cameraID << std::endl;
        return;
    }

    std::cout << "Start grabbing from "<< cameraID<< ", press ESC on Live window to terminate" << std::endl;

    // Buffer initializations
    double fps = static_cast<double>(cap.get(cv::CAP_PROP_FPS));
    int videoDurationInSeconds = 40;
    int bufferSize = static_cast<int>(videoDurationInSeconds * fps);

    FrameBuffer frameBuffer(bufferSize, fps);

    char key = 0;
    bool recordMode = false;
    bool recordStarted = false;

    std::chrono::steady_clock::time_point recordStartTime;

    while (key != 27) { // esc key
        cap >> frame;
        if (frame.empty()) {
            std::cerr << "ERROR: Unable to grab from " << cameraID << std::endl;
            break;
        }

        Tbegin = std::chrono::steady_clock::now();

        std::vector<TargetBox> boxes;
        yoloF2.detection(frame, boxes);
        AnnotateObjects(frame, boxes);
        Tend = std::chrono::steady_clock::now();

        f = std::chrono::duration_cast<std::chrono::milliseconds>(Tend - Tbegin).count();
        if (f > 0.0) FPS[((Fcnt++) & 0x0F)] = 1000.0 / f;
        for (f = 0.0, i = 0; i < 16; i++) { f += FPS[i]; }
        putText(frame, cv::format("FPS %0.2f", f / 16), cv::Point(10, 20), cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(0, 0, 255));
        cv::imshow(cameraID, frame);


        frameBuffer.addFrame(frame);


        if (recordMode) {
            if (!recordStarted) {
                recordStarted = true;
                recordStartTime = std::chrono::steady_clock::now();
            }

            // str1.append(str2);
            const std::string recording = cameraID + " Recording.avi";
            // Check if recording duration is reached
            auto elapsedSeconds = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - recordStartTime).count();
            if (elapsedSeconds >= videoDurationInSeconds / 2) {

                std::thread videogeneration(videoCreation, std::ref(frameBuffer), recording);
                videogeneration.detach();

                recordMode = false;
                recordStarted = false;
            }
        }

        key = cv::waitKey(5);

        if (key == 'r') { // Press 'r' to start recording mode
            recordMode = true;
            std::cout << "R pressed. "<< cameraID << " waiting for remaining frames..." << std::endl;
        }

    }
}

#endif // CAMERAPROCESSING_HPP_INCLUDED
