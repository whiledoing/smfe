smfe (sensor motion features extroactor)
===============================================================================

## Introduction

该计算库主要用来提取运动传感器信号的特征.

一个典型的运动传感器包含三个主要部分:

1.  加速度传感器
2.  磁通传感器
3.  陀螺仪传感器

包含整个三个传感器的控制单元一般也被叫做IMU(inertia measurement unit)单元.

计算的特征主要包含几个部分

1.  运动传感基本特征(加速度,速度,位移,旋转角度,角速度等)
2.  统计特征
3.  时域特征
4.  频域特征
5.  时间-频率特征

## 安装 && 编译

Git clone之后, 调用下面命令编译和测试库(debug版本):

    1. git submodule update --init --recursive
    2. mkdir build.debug
    3. cd build.debug
    4. cmake .. -G"NMake Makefiles" -DBOOST_ROOT=/your/boost/root/path
    5. nmake
    6. ctest

对于release版本, 2~4步改为:

    2. mkdir build.release
    3. cd build.release
    4. cmake .. -G"NMake Makefiles" -DCMAKE_BUILD_TYPE=Release -DBOOST_ROOT=/your/boost/root/path

Linux上将"NMake Makefiles"和nmake改为对应的工具链即可.

## 关于第三方库的说明

本库依赖于下面几个第三方库:

1.  [boost](http://www.boost.org/) 主要几个子模块为 `unit_test filesystem property_tree accumulators`
2.  [armadillo](http://arma.sourceforge.net/) 线性代数C++计算库
3.  [aquila](http://aquila-dsp.org/) 信号处理C++库
4.  [wavelet1d](https://code.google.com/p/wavelet1d/) 离散小波变换
5.  [fftw](http://www.fftw.org/) 傅里叶变换计算库

`armadillo`和`aquila`已经编译好(visual C++ 2012)放置在了`3rd`目录中,也可以自己编译将编译好的结果放置到`3rd`目录中即可

需要注意的是,aquila编译好的library需要根据`BUILD_TYPE`放置不同的目录下(可以参考`cmake/modules/support_aquila.cmake`模块):

1.  debug模式的lib: 放置在 `Debug/Aquila.lib`
2.  relase模式的lib: 放置在 `Release/Aquila.lib`

`wavelet1d`使用直接包含源码的方式加入到smfe_lib中.

`fftw`已经将编译好的(visual C++ 2012)放置在`3rd/fftw`中, 如果自己需要重新编译, 参考`3rd/fftw/README.md`

## 说明

1.  本库的基本类型定义在`include/smfe/global.h`文件中

2.  可以参考`test`目录下的测试代码作为example

## 说明

1.  本库的基本类型定义在`include/smfe/global.h`文件中

2.  可以参考`test`目录下的测试代码作为example

## 使用本库

1.  制定boost目录
2.  制定`SMFE_DIR`变量指示`smfe library`所在的根目录, 其中`${SMFE_LIB}/include`保存了
smfe的头文件, `${SMFE_LIB}/lib/debug(release)`保存了smfe编译好的lib或者.a文件.
3.  将`SMFE_DIR`中的`support_smfe.cmake`加入到`CMAKE_MODULE_PATH`中
4.  使用`support_smfe(${target})`命令在target工程中加入本库

具体可以参考目录`test_using_smfe`中的示例性使用代码

## TODO

1.  将计算信号的特征变得完全可配置
