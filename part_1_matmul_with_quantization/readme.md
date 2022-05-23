# matmul with quantization
使用量化技术加速矩阵乘
通过大白话AI公众号讲解的相关量化的基础知识，进行一个矩阵乘法的demo，程序主要的要求是：
输入两个矩阵的维度，不需要设计防呆，一边用float32直接进行运算，另一边使用INT8量化运算。矩阵内数值可以设置范围内随机，左右边界也支持自定义输入。
最终结果对比要包括误差和计算时间。

摘取一些重点的知识：
![image text](https://github.com/coswindywang/Quantization/blob/main/part_1_matmul_with_quantization/1.png)
![image text](https://github.com/coswindywang/Quantization/blob/main/part_1_matmul_with_quantization/2.png)

但实际复现时存在S3 Z3以及乘之后数据类型搞得比较紊乱（所以参考下面的补充链接重新进行了复现）

补充： [知乎](https://zhuanlan.zhihu.com/p/437857388)