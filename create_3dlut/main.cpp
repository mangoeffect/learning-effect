/**
 * @file main.cpp
 * @author mango (2321544362@qq.com)
 * @brief 
 * @version 0.1
 * @date 2023-09-03
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "opencv2/opencv.hpp"

void Create3Dlut(cv::Mat& lut)
{
    lut = cv::Mat::zeros(cv::Size(512, 512), CV_8UC4);

    //外层8x8 64 方块
    for(int bx = 0; bx < 8; bx++)
    {
        for(int by = 0; by < 8; by++)
        {
            //内层一块方块的储存,64个像素点
            for(int g = 0; g < 64; g++)
            {
                for(int r = 0; r < 64; r++)
                {
                    uint8_t rr = (int)(r * 255.0 / 63.0 + 0.5); //r通道压缩[256 ->64]
                    uint8_t gg = (int)(g * 255.0 / 63.0 + 0.5); //g通道压缩[256 ->64]
                    uint8_t bb = (int)((bx + by * 8) * 255.0 / 63.0 + 0.5);  //g通道压缩[256 ->64]
                    uint8_t aa = 255;
                    int x = r + bx * 64;
                    int y = g + by * 64;
                    lut.at<cv::Vec4b>(y, x) = cv::Vec4b(bb, gg, rr, aa);
                }
            }
        }
    }
}

int main(int argc, char** argv)
{
    cv::Mat lut;
    Create3Dlut(lut);

    cv::imshow("crreate-3d-lut", lut);
    cv::waitKey(0);

    return 0;
}

