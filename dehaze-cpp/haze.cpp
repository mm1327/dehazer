#include "haze.h"
#include <vector>


Haze::Haze()
{
    percent = 0.01;
    minTrans = 0.25;
    guidedKernel = 10;
    darkKernel = 3;
    guidedE = 0.000001;
}

void Haze::dehaze( cv::Mat &src_image, cv::Mat &dehaze_image )
{
    float scale = 1/255.0;
    float atom_mean = 0.0;
    cv::Mat img_gray;

    cv::cvtColor( src_image, img_gray, cv::COLOR_BGR2GRAY );

    get_atmo( img_gray, atom_mean, percent );

    cv::Mat image_f;

    src_image.convertTo( image_f, CV_32FC3 );
    image_f = image_f * scale;
    cv::Mat image_trans;

    get_trans( image_f, image_trans, atom_mean );

    //std::cout << "image_trans" << std::endl;
    //std::cout << image_trans << std::endl;
    cv::Mat gray_f32;
    cv::Mat trans_guided;

    img_gray.convertTo( gray_f32, CV_32FC1 );
    gray_f32 = gray_f32 * scale;
    //std::cout << "gray_f32" << std::endl;
    //std::cout << gray_f32 << std::endl;

    guided_filter( image_trans, gray_f32, trans_guided, guidedKernel, guidedE );

    trans_guided = cv::max( trans_guided, minTrans );

    dehaze_image = cv::Mat::zeros( src_image.rows, src_image.cols, CV_8UC3 );

    int i;
    int j;
    uchar *line_de = nullptr;
    uchar *line_src = nullptr;
    float *line_guid = nullptr;
    float pix_channel;
    float guid_pix;
    int cp_v_b;
    int cp_v_g;
    int cp_v_r;
    for( i = 0; i < dehaze_image.rows; ++i )
    {
        line_de = dehaze_image.ptr<uchar>(i);
        line_src = src_image.ptr<uchar>(i);
        line_guid = trans_guided.ptr<float>(i);
        for( j  = 0; j < dehaze_image.cols; ++j )
        {
            guid_pix = line_guid[ j ];
            pix_channel = line_src[ j * 3     ] * scale;
            cp_v_b = MIN( ( int )( ( ( pix_channel - atom_mean ) / guid_pix + atom_mean ) * 255.0 ), 255 );
            cp_v_b = MAX( cp_v_b, 0 );
            line_de[ j * 3     ] = cp_v_b;

            pix_channel = line_src[ j * 3 + 1 ] * scale;
            cp_v_g = MIN( ( int )( ( ( pix_channel - atom_mean ) / guid_pix + atom_mean ) * 255.0 ), 255 );
            cp_v_g = MAX( cp_v_g, 0 );
            line_de[ j * 3 + 1 ] = cp_v_g;

            pix_channel = line_src[ j * 3 + 2 ] * scale;
            cp_v_r = MIN( ( int )( ( ( pix_channel - atom_mean ) / guid_pix + atom_mean ) * 255.0 ), 255 );
            cp_v_r = MAX( cp_v_r, 0 );
            line_de[ j * 3 + 2 ] = cp_v_r;
        }
    }
}

void Haze::set_param( float st_percent, float min_trans, int guide_kernel, int dark_kernel, float e )
{
    percent = st_percent;
    minTrans = min_trans;
    guidedKernel = guide_kernel;
    darkKernel = dark_kernel;
    guidedE = e;
}

void Haze::dark_channel(cv::Mat &image, cv::Mat &dc_img, int kernel_size )
{
    if( !image.empty() && 3 == image.channels() )
    {
        std::vector< cv::Mat > bgr_split;
        cv::Mat min_c_image;

        cv::split(image, bgr_split);
        min_c_image = cv::min(bgr_split[0], cv::min(bgr_split[1], bgr_split[2]));
        cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(kernel_size, kernel_size), cv::Point(-1, -1));
        cv::erode( min_c_image, dc_img, kernel, cv::Point(-1, -1) );
    }
}

void Haze::get_atmo(cv::Mat &gray_image, float &atmo_mena, float percent)
{
    cv::Mat hist;

    hist_gray( gray_image, hist );
    float stit_size = gray_image.cols * gray_image.rows * percent;

    float pix_size = 0;
    float bus_value = 0;
    int cur_pix_size;
    for( int pix_index = 255; pix_index > 1; --pix_index )
    {
        cur_pix_size = hist.at<int>(pix_index);
        pix_size += cur_pix_size;
        bus_value += cur_pix_size * pix_index;
        if( pix_size > stit_size )
        {
            break;
        }
    }
    atmo_mena = bus_value / ( pix_size * 255.0 );
}

void Haze::get_trans( cv::Mat &image, cv::Mat &image_t, float atom, float w )
{
    float per_atom = 1.0/atom;
    cv::Mat image_x = image * per_atom;
    cv::Mat dc_image;
    dark_channel( image_x, dc_image, darkKernel );
    cv::Mat w_dc_image = dc_image * w;

    image_t = 1.0 - w_dc_image;
}

void Haze::guided_filter(cv::Mat &trans_image, cv::Mat &guidance_image, cv::Mat &filter_image, int kernel_r, float e )
{
    cv::Mat mean_i;
    cv::Mat mean_p;
    cv::Mat corr_i;
    cv::Mat corr_ip;
    cv::Size kernel_size(kernel_r, kernel_r);

    cv::boxFilter( guidance_image, mean_i, CV_32F, kernel_size );
    //std::cout << "mean_i" << std::endl;
    //std::cout << mean_i << std::endl;
    cv::boxFilter( trans_image, mean_p, CV_32F, kernel_size );


    cv::Mat i_mul_i = guidance_image.mul( guidance_image );
    cv::boxFilter( i_mul_i, corr_i, CV_32F, kernel_size );


    cv::Mat i_mul_p = guidance_image.mul( trans_image );
    cv::boxFilter( i_mul_p, corr_ip, CV_32F, kernel_size );

    cv::Mat mi_mul_mi = mean_i.mul( mean_i );
    cv::Mat var_i = ( corr_i - mi_mul_mi ) + e;
    //std::cout << "var_i" << std::endl;
    //std::cout << var_i << std::endl;
    cv::Mat mi_mul_mp = mean_i.mul( mean_p );
    cv::Mat cov_ip = corr_ip - mi_mul_mp;
    cv::Mat a, b;

    cv::divide( cov_ip, var_i, a );
    b = mean_p - a.mul( mean_i );
    //std::cout << "b" << std::endl;
    //std::cout << b << std::endl;
    cv::Mat mean_a;
    cv::Mat mean_b;
    //std::cout << "a" << std::endl;
    //std::cout << a << std::endl;
    cv::boxFilter( a, mean_a, CV_32F, kernel_size );
    cv::boxFilter( b, mean_b, CV_32F, kernel_size );

    filter_image = mean_a.mul( guidance_image ) + mean_b;

}

void Haze::hist_gray( const cv::Mat &gray_image, cv::Mat &hist )
{
    int i;
    int j;
    const uchar *gray_line = nullptr;
    hist= cv::Mat::zeros( 256, 1, CV_32SC1 );

    int *his_line = hist.ptr<int>(0);

    for( i = 0; i < gray_image.rows; ++i )
    {
        gray_line = gray_image.ptr<uchar>(i);
        for( j = 0 ; j < gray_image.cols; ++j )
        {
            ++his_line[ gray_line[ j ] ];
        }
    }
}








