#ifndef HAZE_H
#define HAZE_H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>



class Haze
{
public:
    Haze();
    /*******************
     * param:
     *      src_image  input src image
     *      dehaze_image  output remove haze image
     ******************/
    void dehaze( cv::Mat &src_image, cv::Mat &dehaze_image );
    /*******************
     * param:
     *      st_percent 0.01~0.5
     *      min_trans  0.01~0.5
     *      guide_kernel 3 ~ 40
     *      dark_kernel  3 ~ 20
     *      e            0.0~0.00001
     ******************/
    void set_param( float st_percent, float min_trans, int guide_kernel, int dark_kernel, float e );

private:
    float percent;
    float minTrans;
    int guidedKernel;
    int darkKernel;
    float guidedE;

protected:
    void dark_channel( cv::Mat &image, cv::Mat &dc_img, int kernel_size = 5 );
    void get_atmo(cv::Mat &gray_image, float &atmo_mena, float percent = 0.01 );
    void get_trans( cv::Mat &image, cv::Mat &image_t, float atom, float w = 0.95 );
    void guided_filter(cv::Mat &trans_image, cv::Mat &guidance_image, cv::Mat &filter_image, int kernel_r, float e );
    void hist_gray( const cv::Mat &gray_image, cv::Mat &hist );
};

#endif // HAZE_H
