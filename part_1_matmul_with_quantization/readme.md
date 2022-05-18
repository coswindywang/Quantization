# matmul with quantization
使用量化技术加速矩阵乘
通过大白话AI公众号讲解的相关量化的基础知识，进行一个矩阵乘法的demo，程序主要的要求是：
输入两个矩阵的维度，不需要设计防呆，一边用float32直接进行运算，另一边使用INT8量化运算。矩阵内数值可以设置范围内随机，左右边界也支持自定义输入。
最终结果对比要包括误差和计算时间。

摘取一些重点的知识：
$r$ 表示一个32位浮点实数； $q$ 表示$r$量化后的定点整数。

浮点实数与量化定点整数之间的换算公式为：

$${r = S(q - Z) \choose q = round(r \div S + Z)}$$ 

$S$ 即scale 表示实数范围与整数范围之间的比例； $Z$ 即zero point 实数0量化后的整数

二者来自于：

$${S = r_max - r_min \div q_max - q_min  \choose Z = round(q_max - r_max \div S)}$$

round 舍入操作

在矩阵运算中，量化手段也是类似的，如推文中的推导所示，最后需要

$M = S_1