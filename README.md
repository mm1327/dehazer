# dehaze

Realizing Kaiming He's paper 'Single Image Haze Removal Using Dark Channel Prior'


- 使用向导滤波算法精确计算透光率
- 改进原算法对大气光强计算算法
- 优化参数提升暗通道精度
- 优化参数提升透光率精度
- 加入GAMMA亮度增强

去雾前 | 去雾后 | 优化后
------------- | ------------- | -------------
![原图](dehaze-python/image/haze.png)| ![结果](dehaze-python/result/haze.png)| ![优化](dehaze-python/result02/haze.png)
![原图](dehaze-python/image/haze_02.png)| ![结果](dehaze-python/result/haze_02.png)| ![优化](dehaze-python/result02/haze_02.png)
![原图](dehaze-python/image/haze_03.png)| ![结果](dehaze-python/result/haze_03.png)| ![优化](dehaze-python/result02/haze_03.png)
![原图](dehaze-python/image/haze_04.jpg)| ![结果](dehaze-python/result/haze_04.jpg)| ![优化](dehaze-python/result02/haze_04.jpg)
![原图](dehaze-python/image/haze_05.png)| ![结果](dehaze-python/result/haze_05.png)| ![优化](dehaze-python/result02/haze_05.png)
![原图](dehaze-python/image/haze_06.png)| ![结果](dehaze-python/result/haze_06.png)| ![优化](dehaze-python/result02/haze_06.png)
![原图](dehaze-python/image/haze_08.png)| ![结果](dehaze-python/result/haze_08.png)| ![优化](dehaze-python/result02/haze_08.png)
![原图](dehaze-python/image/haze_15.png)| ![结果](dehaze-python/result/haze_15.png)| ![优化](dehaze-python/result02/haze_15.png)


## 链接
[去雾算法](https://github.com/anhenghuang/dehaze/  "去雾算法")

[论文](http://mmlab.ie.cuhk.edu.hk/archive/2011/Haze.pdf  "论文")