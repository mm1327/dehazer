# dehaze 暗通道去雾 C++
## 简介
- 代码采用Qt框架编写核心代码不依赖Qt任何库
- 去雾代码注意为 haze.h haze.cpp 部分

## 接口

- 保护 haze.h 头文件
创建对象 Haze haze

调用函数 

~~~ C
/*******************
 * 去雾函数
* param:
*      src_image  input src image
*      dehaze_image  output remove haze image
******************/
void dehaze( cv::Mat &src_image, cv::Mat &dehaze_image );

/*******************
 * 参数设置
* param:
*      st_percent 0.01~0.5
*      min_trans  0.01~0.5
*      guide_kernel 3 ~ 40
*      dark_kernel  3 ~ 20
*      e            0.0~0.00001
******************/
void set_param( float st_percent, float min_trans, int guide_kernel, int dark_kernel, float e );

~~~
