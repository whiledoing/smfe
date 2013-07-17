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
5.  时间-频率特征 (TODO)

## 安装

本库依赖于下面几个第三方库:

1.  [boost](http://www.boost.org/) 主要几个子模块为 `unit_test filesystem property_tree accumulators`
2.  [armadillo](http://arma.sourceforge.net/) 线性代数C++计算库
3.  [aquila](http://aquila-dsp.org/) 信号处理C++库

`armadillo`和`aquila`已经编译好(visual C++ 2012)放置在了`3rd`目录中,也可以自己编译将编译好的结果放置到`3rd`目录中即可

需要注意的是,aquila编译好的library需要改为如下的命名(可以参考`cmake/modules/support_aquila.cmake`模块):

1.  debug模式的lib: Aquila_debug.lib
2.  relase模式的lib: Aquila_release.lib

boost查找有两个办法:

1.  设置`BOOST_ROOT`环境变量
2.  或者在调用cmake的时候设置`BOOST_DIR`的数值,比如`cmake ..  -DCMAKE_DIR="F/lib/boost/"`

配置好第三方库之后,调用下面命令编译本库:

    1.  mkdir build
    2.  cd build && cmake ..
    3.  make/nmake

## 说明

1.  本库的基本类型定义在`include/smfe/global.h`文件中

2.  计算特征的大部分方法都是模板类,可以放入一个向量作为输入参数,该向量类型需要符合
下面的要求:

    *   STL兼容的接口 (begin end operator[] size etc)
    *   一些方法中限定容器中的数据类型为value_t (参考globl.h)

3.  `std::vector`和`arma::vec`都可以作为有效的容器类型.

4.  可以参考`test`目录下的测试代码作为example

## TODO

1.  时间-频率特征
2.  将计算信号的特征变得完全可配置
