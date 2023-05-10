#include <iostream>
#include <opencv2/opencv.hpp>
#include <eigen3/Eigen/SVD>
#include <opencv2/core/eigen.hpp>

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
    cv::imshow("Image Selected", image);
    cv::waitKey(0);

    // eigen3 matrices for rgb
    Eigen::MatrixXd eb, eg, er;

    // split cv channels
    cv::Mat cb, cg, cr;
    cv::extractChannel(image, cb, 0);
    cv::extractChannel(image, cg, 1);
    cv::extractChannel(image, cr, 2);

    // cv to eigen
    cv::cv2eigen(cb, eb);
    cv::cv2eigen(cg, eg);
    cv::cv2eigen(cr, er);
    std::cout << std::endl
              << "Calculating SVD for blue channel" << std::endl;
    Eigen::BDCSVD<Eigen::MatrixXd> svdb(eb, Eigen::ComputeThinU | Eigen::ComputeThinV);

    std::cout << std::endl
              << "Calculating SVD for green channel" << std::endl;
    Eigen::BDCSVD<Eigen::MatrixXd> svdg(eg, Eigen::ComputeThinU | Eigen::ComputeThinV);

    std::cout << std::endl
              << "Calculating SVD for red channel" << std::endl;
    Eigen::BDCSVD<Eigen::MatrixXd> svdr(er, Eigen::ComputeThinU | Eigen::ComputeThinV);
    return 0;
}