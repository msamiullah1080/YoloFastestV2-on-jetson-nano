#ifndef FRAMEBUFFER_HPP_INCLUDED
#define FRAMEBUFFER_HPP_INCLUDED

#include <deque>
#include <string>
#include <iostream>
#include <opencv2/opencv.hpp>


class FrameBuffer {
private:
    std::deque<cv::Mat> buffer;
    unsigned int bufferSize;
    double fps ;

public:
    FrameBuffer(int bufferSize, double fps) : bufferSize(bufferSize), fps(fps) {}

    void addFrame(const cv::Mat& frame) {
        if (buffer.size() >= bufferSize) {
            buffer.pop_front(); // Remove oldest frame if buffer is full
        }
        buffer.push_back(frame.clone());
    }

    void generateVideo(const std::string &filename) {
        if (buffer.empty()) {
            std::cerr << "Buffer is empty, cannot generate video." << std::endl;
            return;
        }

        cv::Size frameSize = buffer.front().size();
        cv::VideoWriter videoWriter(filename, cv::VideoWriter::fourcc('X', '2', '6', '4'), fps, frameSize);

        for (const auto& frame : buffer) {
            videoWriter.write(frame);
        }

        videoWriter.release();
        std::cout << "Video saved as " << filename << std::endl;
    }
};


#endif // FRAMEBUFFER_HPP_INCLUDED
