#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;

int main()
{
    // Load the image from file
    auto filename = "C:\\Users\\Maureen\\Downloads\\greenApple.jpg";
    cv::Mat image = cv::imread(filename, cv::IMREAD_COLOR);

    // Check if the image was successfully loaded
    if (image.empty()) 
    {
        std::cout << "Failed to load image!" << std::endl;
        return -1;
    }

    // Convert the image to HSV color space
    cv::Mat hsvImage;
    cv::cvtColor(image, hsvImage, cv::COLOR_BGR2HSV);

    // Define the range of green color in HSV color space
    cv::Scalar lowerGreen(40, 40, 40);
    cv::Scalar upperGreen(70, 255, 255);

    // Threshold the image using the green color range
    cv::Mat mask;
    cv::inRange(hsvImage, lowerGreen, upperGreen, mask);

    // Clean up the binary mask using morphological operations
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5));
    cv::morphologyEx(mask, mask, cv::MORPH_OPEN, kernel);
    cv::morphologyEx(mask, mask, cv::MORPH_CLOSE, kernel);

    // Apply the mask to the original image to segment the green objects
    cv::Mat result;
    image.copyTo(result, mask);

    // Create a window to display the result image
    cv::namedWindow("Color Segmentation Result", cv::WINDOW_NORMAL);
    cv::imshow("Color Segmentation Result", result);

    // Wait for the user to press a key
    cv::waitKey(0);

    return 0;
}
