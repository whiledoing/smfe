smfe features reference
===============================================================================

# 频率特征

## 主要的数据结构:

1.  cx_vec

    使用 `smfe_fft` 对原始信号计算得到的频谱信息.

    频谱是傅里叶变换结果的一种表现形式, 使用复数来表示频率的每一项. 复数的**长度**表示
    对应信号的**幅值**, 复数的**角度 = atan2(img, rel)**表示信号的**相位**. 每一个复数
    对应的信号频率和当前复数在频率中的**下标有关**, 计算公式为:

        /* i 表示下标, fs表示采样频率, size表示频谱的长度 */
        frequency = i * fs /size

    另外注意, 频谱是**对称**的, 频率向量的前半部分很后半部分关于中间对称. 所以一般不直接
    对频谱进行分析, 而是转换为**频率-幅值**信息进行分析

2.  fm_vec

    使用 `frequency_magnitude_vec` 或者 `sorted_frequency_magnitude_vec` 得到信号的
    **频率-幅值**信息.

    频率-幅值对应了经过fft变换之后的所有**频率(单位hz)和频率幅值的信息**.

    考虑信号:

        f(t) = 10 * f( 2*pi * 1000 * t) + 3 * f(2*pi * 2000 * t);

    如果使用fs = 6000来采样, 那么得到的频率幅值信息最大的两个就是:

        1.  mag : 10  fre : 1000
        2.  mag : 3   fre : 2000

    `frequency_magnitude_vec` 接口得到的结果按照**频率从小到大顺序存放**

    `sorted_frequency_magnitude_vec` 接口得到结果按照 **幅值从大到小顺序存放**

    下文中说明的排过序的逻辑统一为 :  **幅值从大到小**

## 特征和对应API

1.  频谱

    `smfe_fft` 输入时序信号, 输出频谱信号

2.  频率-幅值信息

    `frequency_magnitude_vec` 和 `sorted_frequency_magnitude_vec`, 输入原始信号, 得到频率幅值信号

3.  主频率

    `principal_frequency`, 输入的是**排过序之后**的的频率-幅值信息, 得到主频率, 也就是**幅值最大的频率**, @see `sorted_frequency_magnitude_vec`

4.  中值频率

    `median_frequency`, 输入的是**排过序之后**的的频率-幅值信息, 得到中值频率, @see `sorted_frequency_magnitude_vec`

5.  四分卫频率

    `first_quater_frequency` 和 `third_quater_frequency` 输入的是**排过序之后**的的频率-幅值信息, 得到 1/4 和 3/4 位置的频率, @see `sorted_frequency_magnitude_vec`

6.  前n大频率

    `first_n_frequency` 输入的是**排过序之后**的的频率-幅值信息, 得到幅值前n大的频率vector, @see `sorted_frequency_magnitude_vec`

6.  频谱能量

    `frequency_energy`  输入的是**无序**的频率-幅值信息(有序当然也可以), 得到所有幅值的平方和, 就是频谱能量.

7.  频率域信息熵

    `frequency_domain_entropy` 输入的fft分解之后信号的所有幅值向量或者fm_vec, 使用所有的幅值数据计算频率域的信息熵. 信息熵表示为数据分布的均匀度, 对应到这里, 如果频率分布的越不均匀, 熵越小, 越均匀, 熵越大.

# 小波特征

## 离散小波变换

1.  离散小波变换简称为dwt

2.  离散小波变换是将离散的时域信号分解为一些列的小波, 小波类似于傅里叶分解中的正弦和余弦波, 是一种有限长度范围的脉冲信号.

3.  经常使用的是haar小波, 和[Daubechies Wavelet](https://zh.wikipedia.org/wiki/%E5%A4%9A%E8%B4%9D%E8%A5%BF%E5%B0%8F%E6%B3%A2)

当前支持的小波类型名称有:

     haar, db1, db2, db3, db4, db5, db6, db7, db8, db9, db10, db11, db12, db13, db14, db15
     bior1.1, bio1.3, bior1.5, bior2.2, bior2.4,bior2.6,bior2.8 bior3.1, bior3.3, bior3.5, bior3.7, bior3.9, bior4 bior5.5, bior6.
     coif1, coif2, coif3, coif4, coif5.

db1表示一阶Daubechies Wavelet, db2表示二阶, etc...

[具体可以参考](http://code.google.com/p/wavelet1d/wiki/new1DDWTdemo)

小波变换是分层的, 在使用dwt计算的时候, 需要制定分解的层级, 假设分解层级为`wavelet_level`, 那么dwt分解之后会得到1个approximation系数, 和`wavelet_level`个
detail系数. (approximation可以理解为fft变换中的直流信号, detail表示为不同频率信号的信息), 最后这些向量被组装成一个向量, 包装方式如下:

    [A D[wavelet_level] D[wavelet_level-1] D[wavelet_level-2] ... D[1]]

其中A表示approximation系数, D[i]表示第i层的detail系数

Notes:

1.  这里的所有level相关的概念都是从**下标1**开始.
2.  小波变换层级不可以大于 \f$(int)(log_2^{N}) - 2\f$, 其中N表示数据的长度

## 主要数据结构

1.  wavelet_signal

    表示dwt变换之后的结果, 该向量将所有的detail和approximation系数进行了pack操作.

2.  time_signal

    表示时序信号.

3.  dwt_length_vec; /** dwt 离散小波变换后保存各个层级小波数据长度的向量类型 */

    dwt变换的返回值之一, 保存了不同小波变换层级的数据大小. 在别的接口中, 比如获取指定层级detail系数的方法 `dwt_detail_coeff`, 需要传入lenth的信息.

4.  dwt_flag_vec; /** dwt 离散小波变换后保存相关计算信息的向量类型 */

    dwt变换的返回值之一, 保存了dwt变换中的一些标志信息, 一般用不到, 只有在进行逆变换 `idwt` 的时候需要传入该数据.

## 特征和对应API

1.  小波特征

    `dwt` 输入时序信号, 使用的小波名称, 小波分解的层级, 返回离散小波变换之后的小波特征wavelet_signal, 该向量将所有的detail和approximation系数进行了pack操作. @ see 离散小波变换

2.  approximation 特征

    `dwt_approximation_coeff` 输入时序信号, 得到当前信号的approximation系数, 或者是从`dwt`返回的wavelet_signal中提取approximation系数.

3.  detail 特征

    `dwt_detail_coeff` 输入时序信号, 和需要得到的层级, 得到当前信号的指定层级detail系数, 或者是从`dwt`返回的wavelet_signal中提取detail系数.

4.  detail range 特征

    `dwt_detail_coeff_of_range` 得到一段层级上的detail特征, 按照层级顺序pack为一个vec返回. @note 层级区间左闭右开 [detail_coeff_start_level, detail_coeff_end_level)

5.  能量

    `dwt_energy` 这里的操作都是针对**detail**数据而言, 得到指定层级detail信号的能量.

6.  均方根 (rms)

    `dwt_rms` 得到指定层级**detail**数据的均方根.

7.  归一化的能量

    `dwt_normised_energy_using_signal_energy` 使用原始信号的能量对小波变换的能量进行归一化处理, 等价于调用 : `dwt_energy(time_signal) / energy(time_signal)`
