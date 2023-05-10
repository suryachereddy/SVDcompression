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
    Eigen::BDCSVD<Eigen::MatrixXd> svdb(eb, Eigen::ComputeFullU | Eigen::ComputeFullV);

    std::cout << std::endl
              << "Calculating SVD for green channel" << std::endl;
    Eigen::BDCSVD<Eigen::MatrixXd> svdg(eg, Eigen::ComputeFullU | Eigen::ComputeFullV);

    std::cout << std::endl
              << "Calculating SVD for red channel" << std::endl;
    Eigen::BDCSVD<Eigen::MatrixXd> svdr(er, Eigen::ComputeFullU | Eigen::ComputeFullV);

    // reconstructing image using first 10 singular values
    std::cout << std::endl
              << "Reconstructing image" << std::endl;
    // blue channel
    Eigen::MatrixXd reconb = svdb.matrixU().leftCols(10) * svdb.singularValues().head(10).asDiagonal() * svdb.matrixV().leftCols(10).transpose();
    // green channel
    Eigen::MatrixXd recong = svdg.matrixU().leftCols(10) * svdg.singularValues().head(10).asDiagonal() * svdg.matrixV().leftCols(10).transpose();
    // red channel
    Eigen::MatrixXd reconr = svdr.matrixU().leftCols(10) * svdr.singularValues().head(10).asDiagonal() * svdr.matrixV().leftCols(10).transpose();

    // eigen to cv
    cv::Mat reconb_cv, recong_cv, reconr_cv;
    cv::eigen2cv(reconb, reconb_cv);
    cv::eigen2cv(recong, recong_cv);
    cv::eigen2cv(reconr, reconr_cv);

    // merge channels
    std::vector<cv::Mat> channels;
    channels.push_back(reconb_cv);
    channels.push_back(recong_cv);
    channels.push_back(reconr_cv);
    cv::Mat recon;
    cv::merge(channels, recon);
    // normalize pixel values to [0, 255]
    cv::normalize(recon, recon, 0, 255, cv::NORM_MINMAX);

    // convert to 8-bit unsigned integers
    cv::Mat recon_8u;
    recon.convertTo(recon_8u, CV_8U);
    // display image
    cv::imshow("Reconstructed Image", recon_8u);
    cv::waitKey(0);
    std::cout << "reconb rows: " << reconb.rows() << std::endl
              << "reconb cols: " << reconb.cols() << std::endl;

    return 0;
}