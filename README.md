# dehaze

Realizing Kaiming He's paper 'Single Image Haze Removal Using Dark Channel Prior'

- 使用向导滤波算法精确计算透光率
- 改进原算法对大气光强计算算法
- 优化参数提升暗通道精度
- 优化参数提升透光率精度
- C++ 代码实现 1440X1080 分辨率下 tx2平台 cpu 耗时120ms

去雾前 | 去雾后 | 优化后
------------- | ------------- | -------------
![原图](http://192.168.7.163:3000/dww/dehaze/raw/branch/master/dehaze-python/image/haze.png)| ![结果](http://192.168.7.163:3000/dww/dehaze/raw/branch/master/dehaze-python/result/haze.png)| ![优化](http://192.168.7.163:3000/dww/dehaze/raw/branch/master/dehaze-python/result02/haze.png)
![原图](http://192.168.7.163:3000/dww/dehaze/raw/branch/master/dehaze-python/image/haze_06.png)| ![结果](http://192.168.7.163:3000/dww/dehaze/raw/branch/master/dehaze-python/result/haze_06.png)| ![优化](http://192.168.7.163:3000/dww/dehaze/raw/branch/master/dehaze-python/result02/haze_06.png)
![原图](http://192.168.7.163:3000/dww/dehaze/raw/branch/master/dehaze-python/image/haze_02.jpg)| ![结果](http://192.168.7.163:3000/dww/dehaze/raw/branch/master/dehaze-python/result/haze_02.jpg) | ![优化](http://192.168.7.163:3000/dww/dehaze/raw/branch/master/dehaze-python/result02/haze_02.jpg)
![原图](http://192.168.7.163:3000/dww/dehaze/raw/branch/master/dehaze-python/image/haze_02.png)| ![结果](http://192.168.7.163:3000/dww/dehaze/raw/branch/master/dehaze-python/result/haze_02.png) | ![优化](http://192.168.7.163:3000/dww/dehaze/raw/branch/master/dehaze-python/result02/haze_02.png)
![原图](http://192.168.7.163:3000/dww/dehaze/raw/branch/master/dehaze-python/image/haze_05.png)| ![结果](http://192.168.7.163:3000/dww/dehaze/raw/branch/master/dehaze-python/result/haze_05.png) | ![优化](http://192.168.7.163:3000/dww/dehaze/raw/branch/master/dehaze-python/result02/haze_05.png)
![原图](http://192.168.7.163:3000/dww/dehaze/raw/branch/master/dehaze-python/image/haze_04.jpg)| ![结果](http://192.168.7.163:3000/dww/dehaze/raw/branch/master/dehaze-python/result/haze_04.jpg) | ![优化](http://192.168.7.163:3000/dww/dehaze/raw/branch/master/dehaze-python/result02/haze_04.jpg)
![原图](http://192.168.7.163:3000/dww/dehaze/raw/branch/master/dehaze-python/image/channel_01.jpg)| ![结果](http://192.168.7.163:3000/dww/dehaze/raw/branch/master/dehaze-python/result/channel_01.jpg) | ![优化](http://192.168.7.163:3000/dww/dehaze/raw/branch/master/dehaze-python/result02/channel_01.jpg)
![原图](http://192.168.7.163:3000/dww/dehaze/raw/branch/master/dehaze-python/image/haze_16.png)| ![结果](http://192.168.7.163:3000/dww/dehaze/raw/branch/master/dehaze-python/result/haze_16.png) | ![优化](http://192.168.7.163:3000/dww/dehaze/raw/branch/master/dehaze-python/result02/haze_16.png)
![原图](http://192.168.7.163:3000/dww/dehaze/raw/branch/master/dehaze-python/image/haze_05.jpg)| ![结果](http://192.168.7.163:3000/dww/dehaze/raw/branch/master/dehaze-python/result/haze_05.jpg) | ![优化](http://192.168.7.163:3000/dww/dehaze/raw/branch/master/dehaze-python/result02/haze_05.jpg)