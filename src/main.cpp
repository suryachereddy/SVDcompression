#include <iostream>
#include <opencv2/opencv.hpp>
int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Usage: " << argv[0] << " <image path>" << std::endl;
        return -1;
    }
    cv::Mat image;
    std::string image_path = argv[1];
    image = cv::imread(image_path);

    // display image
    cv::imshow("Image", image);
    cv::waitKey(0);
    return 0;
}