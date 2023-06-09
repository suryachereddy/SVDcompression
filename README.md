# SVDcompression

Goal: 
1. Compress an image using Singular Value Decomposition (SVD) and compare the results with the original image.
2. Learn C++, CMake, OpenCV and Eigen3 in the process.


Done:
1. Load image in CV and split into RGB channels.
2. Convert CV::Mat to Eigen::Matrix and compute SVD for each channel.
3. Reconstruct image from SVD.

To Do:
1. Write a function to compute the compression ratio.


## Dependencies
1. OpenCV
2. Eigen3
3. CMake

## Build Instructions
1. Clone the repo.
2. Create a build directory and cd into it.
3. Run `cmake ..` and then `make`.
4. Run `./SVDcompression` to run the program.

## Run Instructions
Run `./svd <image-file> <singular-values>` to run the program.

Example: `./svd example.jpg 50`