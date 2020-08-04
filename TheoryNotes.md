# Fluid 101

## 一维扩散

一维扩散过程可以用如下方程描述：
$$
\int_{V}\left[\frac{d}{d x}\left(k \frac{d T}{d x}\right)\right] \mathrm{d} V+\bar{S} \int_{V} \mathrm{d} V=0
$$
根据散度定理，可以将体积分转换为面积分：
$$
\int_{A}\left(k \frac{\mathrm{d} T}{\mathrm{d} x} n_{x}\right) \mathrm{d} A+\bar{S} V=0
$$
对于一个网格，需要知道右侧（$r$）网格面上的梯度和网左侧（$l$）格面上的梯度。直观理解就是，$e$面扩散出去的能量与$w$面扩散进入的能量之差，代表总的扩散引起的能量变化，平衡状态下，这部分应该刚好等于内部源项的产生：
$$
\left(k A \frac{d T}{d x}\right)_{r}-\left(k A \frac{d T}{d x}\right)_{l}+\bar{S} V=0
$$

- 内部点

对于内部点，面上的梯度，可以利用内部点的值进行线性差值得到：

![](https://md-pic-1259272405.cos.ap-guangzhou.myqcloud.com/img/20200720202136.png)

方程可进一步表示为：
$$
\left(k_{r} A_{r} \frac{T_{R}-T_{P}}{d_{P R}}\right)-\left(k_{l} A_{l} \frac{T_{P}-T_{L}}{d_{L P}}\right)+\bar{S} V=0
$$
这里，未知数为$T_R$，$T_P$，$T_L$，重新整理得到：
$$
T_{P}\left(\frac{k_{l} A_{l}}{d_{L P}}+\frac{k_{r} A_{r}}{d_{P R}}\right)=T_{L}\left(\frac{k_{l} A_{l}}{d_{L P}}\right)+T_{R}\left(\frac{k_{r} A_{r}}{d_{P R}}\right)+\bar{S} V
$$
为了方便书写，引入系数$D = k/d$，上式可简写为：
$$
T_{P}\left(D_{l} A_{l}+D_{r} A_{r}\right)=T_{L}\left(D_{l} A_{l}\right)+T_{R}\left(D_{r} A_{r}\right)+\bar{S} V
$$
需要注意的是，$k_l$是左侧面上的扩散系数，$d_{LP}$是左侧点与中心点的距离，$A_l$是左侧面的面积，$D_l = k_l/d_{LP}$。右侧类似。

系数用$a$来表示，源项用$S_u$来表示：
$$
a_{p} T_{P}=a_{L} T_{L}+a_{R} T_{R}+S_{u}\\
T_{P} \underbrace{\left(D_{l} A_{l}+D_{r} A_{r}+0\right)}_{a_{p}}=T_{L} \underbrace{\left(D_{l} A_{l}\right)}_{a_{L}}+T_{R} \underbrace{\left(D_{r} A_{r}\right)}_{a_{R}}+\underbrace{\bar{S} V}_{S_{u}}
$$
其中：
$$
\begin{array}{c}
a_{p}=a_{L}+a_{R}-S_{p} \quad a_{L}=D_{l} A_{l} \quad a_{R}=D_{r} A_{r} \\
S_{P}=0 \quad S_{u}=\bar{S} V
\end{array}
$$
可以发现中心点系数正好等于左右点系数之和，再额外考虑$S_p$的作用，这里$S_p$是边界条件引入的不规则系数，在后面会出现。

- 左边界

对于紧邻左侧边界的网格，计算左侧面梯度的时候需要特殊处理，不再使用左侧网格中心点（此时没有左侧网格了），而是用壁面处的给定值（$T_A$），距离也变为中心点到壁面距离（$d_{LP}/2$）：

![](https://md-pic-1259272405.cos.ap-guangzhou.myqcloud.com/img/20200720213325.png)

此时边界第一层网格的控制方程可以写成：
$$
\left(k_{r} A_{r} \frac{T_{R}-T_{P}}{d_{P R}}\right)-\left(k_{l} A_{l} \frac{T_{P}-T_{A}}{d_{L P} / 2}\right)+\bar{S} V=0
$$
将系数整理一下：
$$
a_{p} T_{P}=a_{L} T_{L}+a_{R} T_{R}+S_{u}\\
T_{P} \underbrace{\left(0+D_{r} A_{r}+2 D_{l} A_{l}\right)}_{a_{P}}=T_{L} \underbrace{(0)}_{a_{L}}+T_{R} \underbrace{\left(D_{r} A_{r}\right)}_{a_{R}}+\underbrace{T_{A}\left(2 D_{l} A_{l}\right)+\bar{S} V}_{S_{u}}
$$
其中：
$$
a_{L}=0 \quad a_{R}=D_{r} A_{r} \quad a_{p}=a_{L}+a_{R}-S_{p}\\
S_{P}=-2 D_{l} A_{l} \quad S_{u}=T_{A}\left(2 D_{l} A_{l}\right)+\bar{S} V
$$
将上面内部网格的形式放在这做对比：
$$
a_{p} T_{P}=a_{L} T_{L}+a_{R} T_{R}+S_{u}\\
T_{P} \underbrace{\left(D_{l} A_{l}+D_{r} A_{r}+0\right)}_{a_{p}}=T_{L} \underbrace{\left(D_{l} A_{l}\right)}_{a_{L}}+T_{R} \underbrace{\left(D_{r} A_{r}\right)}_{a_{R}}+\underbrace{\bar{S} V}_{S_{u}}
$$
和上面内网格形式对比可以发现，边界网格$T_P$的系数$a_L$消失了，多出来一个不规则项$-S_p$，源项也多出来一部分$T_{A}\left(2 D_{l} A_{l}\right)$。因此，边界条件的引入会改变$T_p$的系数，还会引入额外源项。

- 右边界

类似的，右侧边界的第一层网格也需要做额外处理：

![](https://md-pic-1259272405.cos.ap-guangzhou.myqcloud.com/img/20200720220053.png)

右边界网格的控制方程可以写成：
$$
\left(k_{r} A_{r} \frac{T_{B}-T_{P}}{d_{P R} / 2}\right)-\left(k_{l} A_{l} \frac{T_{P}-T_{L}}{d_{L P}}\right)+\bar{S} V=0
$$
整理系数后：
$$
a_{p} T_{p}=a_{L} T_{L}+a_{R} T_{R}+S_{u}\\
T_{P} \underbrace{\left(D_{l} A_{l}+0+2 D_{r} A_{r}\right)}_{a_{p}}=T_{L} \underbrace{\left(D_{l} A_{l}\right)}_{a_{L}}+T_{R} \underbrace{(0)}_{a_{R}}+\underbrace{T_{B}\left(2 D_{r} A_{r}\right)+\bar{S} V}_{S_{u}}
$$
其中：
$$
\begin{array}{c}
a_{L}=D_{l} A_{l} \quad a_{R}=0 \quad a_{p}=a_{L}+a_{R}-S_{p} \\
S_{P}=-2 D_{r} A_{r} \quad S_{u}=T_{B}\left(2 D_{r} A_{r}\right)+\bar{S} V
\end{array}
$$
可以发现$a_R$消失了，多出来$-S_p$，以及源项$T_{B}\left(2 D_{r} A_{r}\right)$。

系数可以总结为：
$$
\begin{array}{lccccc} 
\hline
& a_{L} & a_{R} & a_{P} & S_{p} & S_{u} \\
\hline 
\text { Boundary }(\mathrm{L}) & 0 & D_{R} A_{R} & a_{L}+a_{R}-S_{p} & -2 D_{L} A_{L} & T_{A}\left(2 D_{L} A_{L}\right)+\bar{S} V \\
\text { Interior } & D_{L} A_{L} & D_{R} A_{R} & a_{L}+a_{R}-S_{p} & 0 & \bar{S} V \\
\text { Boundary }(\mathrm{R}) & D_{L} A_{L} & 0 & a_{L}+a_{R}-S_{p} & -2 D_{R} A_{R} & T_{B}\left(2 D_{R} A_{R}\right)+\bar{S} V \\
\hline
\end{array}
$$
最终可以形成矩阵：
$$
\left[\begin{array}{ccccc}
a_{p 1} & -a_{r 1} & 0 & 0 & 0 \\
-a_{l 2} & a_{p 2} & -a_{r 2} & 0 & 0 \\
0 & -a_{l 3} & a_{p 3} & -a_{r 3} & 0 \\
0 & 0 & -a_{l 4} & a_{p 4} & -a_{r 4} \\
0 & 0 & 0 & -a_{15} & a_{p 5}
\end{array}\right]\left[\begin{array}{c}
T_{1} \\
T_{2} \\
T_{3} \\
T_{4} \\
T_{5}
\end{array}\right]=\left[\begin{array}{c}
S_{u 1} \\
S_{u 2} \\
S_{u 3} \\
S_{u 4} \\
S_{u 5}
\end{array}\right]
$$

- 代码重构

在实际编程的过程中，最有用的就是上面这张表，以及$a_P$、$a_R$、$a_L$在矩阵每一行的哪个位置。

在`main`函数中，主要分为创建网格、初始化系数矩阵以及求解矩阵三个步骤：

```cpp
int main()
{
    // 读取数据


    // 创建网格
    Mesh* mesh = new Mesh(Inputs::L, Inputs::N);

    // 初始化矩阵
    MatrixCoeff* MCoeff = new MatrixCoeff(mesh);

    // 获取矩阵
    MatrixXd& A_m = MCoeff->get_A_m();
    VectorXd& b_m = MCoeff->get_b_m();
    VectorXd& x = MCoeff->get_x();

    // 求解矩阵
    x = A_m.fullPivLu().solve(b_m);

    // 输出结果
    cout << "Solution: " << endl << x << endl;

    delete MCoeff;
    delete mesh;
}
```



`initMesh`被封装到`Mesh`类中，主要是根据传入的计算域长度和网格个数，计算出**每个网格**的中心点坐标以及表格中的$a_L$、$a_R$、$a_P$、$S_p$和$S_u$。

这里为了计算这些值，还需要计算$D_LA_L = k_lA_l/d_{LP}$、$D_R A_R = k_r A_r / d_{PR}$、$\bar{S}V$。

这里$k_l, k_r$分别是网格左/右表面处的传热系数，$A_l, A_r$分别是网格左/右表面的面积，$d_{LP}, d_{PR}$分别是网格中心与左/右相邻网格中心的距离，$\bar{S}$是单位体积的热源（$W/m^3$)，$V$是网格体积。



`initMatrix`被封装到`MatrixCoeff`类中，接收`Mesh`对象，并利用`Mesh`中的$a_L$、$a_R$、$a_P$、$S_p$和$S_u$去初始化系数矩阵，这里初始化的时候，边界处的网格未知数($T_1, T_5$)需要特殊处理。



代码见：`solver_cpp_archive\2.1DDiffusion_OOP`

- 算例

取自Fluid 101 Course 1，P23：

![](https://md-pic-1259272405.cos.ap-guangzhou.myqcloud.com/img/20200722161418.png)

## 一维对流-扩散

一维对流-扩散控制方程：
$$
\int_{V} \nabla \cdot\left(\rho c_{p} \boldsymbol{U} T\right) \mathrm{d} V=\int_{V} \nabla \cdot(k \nabla T) \mathrm{d} V+\int_{V} S \mathrm{d} V
$$

- 内部点

离散后有：
$$
\underbrace{\rho_{r} c_{p r} U_{r} T_{r} A_{r}-\rho_{l} c_{p l} U_{l} T_{l} A_{l}}_{\text {Convection }}=\underbrace{k_{r} A_{r} \frac{T_{R}-T_{P}}{d_{P R}}-k_{l} A_{l} \frac{T_{P}-T_{L}}{d_{L P}}+\bar{S} V}_{\text {Diffusion }}
$$
和前面类似，定义简化符号来代替网格相关的常量：
$$
\begin{array}{l}
D=k / d \quad\left[\mathrm{W} / \mathrm{m}^{2} \mathrm{K}\right] \\
F=\rho c_{p} U A \quad[\mathrm{W} / \mathrm{K}]
\end{array}
$$
上面的离散方程可以写成：
$$
F_{r} T_{r}-F_{l} T_{l}=D_{r} A_{r}\left(T_{R}-T_{P}\right)-D_{l} A_{l}\left(T_{P}-T_{L}\right)+\bar{S} V
$$
类似的，需要对网格面上的点进行差值：

![](https://md-pic-1259272405.cos.ap-guangzhou.myqcloud.com/img/20200724213855.png)

得到：
$$
\frac{F_{r}}{2}\left(T_{P}+T_{R}\right)-\frac{F_{l}}{2}\left(T_{L}+T_{P}\right)=D_{r} A_{r}\left(T_{R}-T_{P}\right)-D_{l} A_{l}\left(T_{P}-T_{L}\right)+\bar{S} V
$$
归并相同的项：
$$
\begin{array}{l}
T_{P}\underbrace{\left[\left(D_{l} A_{l}+\frac{F_{l}}{2}\right)+\left(D_{r} A_{r}-\frac{F_{r}}{2}\right)+\left(F_{r}-F_{l}\right)\right]}_{a_{p}}= \\
T_{L} \underbrace{\left[D_{l} A_{l}+\frac{F_{l}}{2}\right]}_{a_{L}}+
T_{R} \underbrace{\left[D_{r} A_{r}-\frac{F_{r}}{2}\right]}_{a_{R}}+\bar{S} V
\end{array}
$$

- 左边界

$$
\frac{F_{r}}{2}\left(T_{P}+T_{R}\right)-F_{l} T_{A}=D_{r} A_{r}\left(T_{R}-T_{P}\right)-2 D_{l} A_{l}\left(T_{P}-T_{A}\right)+\bar{S} V
$$

归并同类项：
$$
\begin{array}{l}
T_{P}\left[0+\left(D_{r} A_{r}-\frac{F_{r}}{2}\right)+\left(F_{r}-F_{l}\right)+\left(2 D_{l} A_{l}+F_{l}\right)\right]= \\
T_{L} \underbrace{[0]}_{a_{L}}+T_{R}[\underbrace{\left.D_{r} A_{r}-\frac{F_{r}}{2}\right]}_{a_{R}}+\underbrace{T_{A}\left[2 D_{l} A_{l}+F_{l}\right]+\bar{S} V}_{S_{u}}
\end{array}
$$

- 右边界

$$
F_{r} T_{B}-\frac{F_{l}}{2}\left(T_{L}+T_{P}\right)=2 D_{r} A_{r}\left(T_{B}-T_{P}\right)-D_{l} A_{l}\left(T_{P}-T_{L}\right)+\bar{S} V
$$

归并同类项：
$$
\begin{array}{l}
T_{P}\left[\left(D_{l} A_{l}+\frac{F_{l}}{2}\right)+0+\left(F_{r}-F_{l}\right)+\left(2 D_{r} A_{r}-F_{r}\right)\right]= \\
T_{L}[\underbrace{\left.D_{l} A_{l}+\frac{F_{l}}{2}\right]}_{a_{L}}+T_{R} \underbrace{[0]}_{a_{R}}+\underbrace{T_{B}\left[2 D_{r} A_{r}-F_{r}\right]+\bar{S} V}_{S_{u}}
\end{array}
$$
左右边界推导类似，只不过由于边界条件的存在，会引入不规则系数和源项，最终的系数如下表所示：
$$
\begin{array}{lcccc} 
\hline
& a_{L} & a_{R}  & S_{p} & S_{u} \\
\hline 
\text { Boundary }(\mathrm{L}) & 0 & D_{R} A_{R} - \frac{F_r}{2} & -(2 D_{L} A_{L} + F_l) & T_{A}\left(2 D_{L} A_{L} + F_l \right)+\bar{S} V \\
\text { Interior } & D_{L} A_{L} + \frac{F_l}{2}& D_{R} A_{R}- \frac{F_r}{2}  & 0 & \bar{S} V \\
\text { Boundary }(\mathrm{R}) & D_{L} A_{L} + \frac{F_l}{2}& 0  & -(2 D_{R} A_{R} - F_r) & T_{B}\left(2 D_{R} A_{R} - F_r\right)+\bar{S} V \\
\hline
\end{array}
$$

$$
a_{P}=a_{L}+a_{R}+\left(F_{r}-F_{l}\right)-S_{p}
$$

其中：
$$
D_LA_L = k_lA_l/d_{LP} \\
D_R A_R = k_r A_r / d_{PR} \\
F_l = \rho c_p U_l A_l \\
F_r = \rho c_p U_r A_r
$$
与扩散项相比，多出来了与$F$相关的量，这是对流通量引入的。

- 算例

取自Fluid 101 Course 1，P34：

![](https://md-pic-1259272405.cos.ap-guangzhou.myqcloud.com/img/20200803204948.png)

- 代码修改

代码部分只需要做微小的增加，在`Mesh`类和`MatrixCoeff`类中增加和`F`相关的量即可。

## 一阶迎风格式

一阶迎风格式在构造网格面的值的时候，只选取上游网格的值，因此在构造面值的时候，需要考虑流动方向，对于如下方程：
$$
F_{r} T_{r}-F_{l} T_{l}=D_{r} A_{r}\left(T_{R}-T_{P}\right)-D_{l} A_{l}\left(T_{P}-T_{l}\right)+\bar{S} V
$$

- 内部点

如果流动是从左到右，左边的对流项可以写为：
$$
F_{r} T_{P}-F_{l} T_{L}=D_{r} A_{r}\left(T_{R}-T_{P}\right)-D_{l} A_{l}\left(T_{P}-T_{L}\right)+\bar{S} V
$$
![](https://md-pic-1259272405.cos.ap-guangzhou.myqcloud.com/img/20200727161942.png)

归并同类项得到：
$$
T_{P} \underbrace{\left[D_{l} A_{l}+F_{l}+D_{r} A_{r}+\left(F_{r}-F_{l}\right)\right]}_{a_{p}}=T_{L} \underbrace{\left[D_{l} A_{l}+F_{l}\right]}_{a_{L}}+T_{R} \underbrace{\left[D_{r} A_{r}\right]}_{a_{R}}+\underbrace{\bar{S}_{V}}_{S_{u}}
$$
如果流动从右到左：
$$
T_{P} \underbrace{\left[D_{l} A_{l}+D_{r} A_{r}-F_{r}+\left(F_{r}-F_{l}\right)\right]}_{a_{P}}=T_{L} \underbrace{\left[D_{l} A_{l}\right]}_{a_{L}}+T_{R} \underbrace{\left[D_{l} A_{l}-F_{r}\right]}_{a_{R}}+\underbrace{\bar{S} V}_{S_{u}}
$$
写成通用形式：
$$
a_{P} T_{p}=a_{L} T_{L}+a_{R} T_{R}+S_{u}
$$
其中：
$$
\begin{aligned}
a_{L} &=D_{l} A_{l}+\max \left(F_{l}, 0\right) \\
a_{R} &=D_{R} A_{R}+\max \left(-F_{r}, 0\right) \\
a_{P} &=a_{L}+a_{R}+\left(F_{r}-F_{l}\right)-S_{p} \\
S_{P} &=0 \\
S_{u} &=\bar{S} V
\end{aligned}
$$
可以看到，流动对$a_L$和$a_R$的贡献只来自上游，对于$a_L$，只有流动从左到右（即$F_l>0$）才对其有贡献，对于$a_R$，只有流动从右到左（即$F_r<0$）才对其有贡献。

- 左边界

流动从左向右：
$$
F_{r} T_{P}-F_{l} T_{A}=D_{r} A_{r}\left(T_{R}-T_{P}\right)-2 D_{l} A_{l}\left(T_{P}-T_{A}\right)
$$
归并同类项：
$$
T_{P} \underbrace{\left[0+D_{r} A_{r}+\left(F_{r}-F_{l}\right)+2 D_{l} A_{l}+F_{l}\right]}_{a_{p}}=T_{L} \underbrace{[0]}_{a_{L}}+T_{R} \underbrace{\left[D_{r} A_{r}\right]}_{a_{R}}+\underbrace{T_{A}\left[2 D_{l} A_{l}+F_{l}\right]}_{S_{u}}
$$
![](https://md-pic-1259272405.cos.ap-guangzhou.myqcloud.com/img/20200727163110.png)

**对于左边界，如果流动从右向左，需要注意**，对流项中，不再有边界值的出现，边界值由上游值决定：
$$
F_{r} T_{R}-F_{l} T_{P}=D_{r} A_{r}\left(T_{R}-T_{P}\right)-2 D_{l} A_{l}\left(T_{P}-T_{A}\right)
$$
归并同类项：
$$
T_{P} \underbrace{\left[0+D_{r} A_{r}-F_{r}+\left(F_{r}-F_{l}\right)+2 D_{l} A_{l}\right]}_{a_{p}}=T_{L} \underbrace{[0]}_{a_{L}}+T_{R} \underbrace{\left[D_{r} A_{r}-F_{r}\right]}_{a_{R}}+\underbrace{T_{A}\left[2 D_{l} A_{l}\right]}_{S_{u}}
$$
![](https://md-pic-1259272405.cos.ap-guangzhou.myqcloud.com/img/20200727163414.png)

归并同类项：
$$
a_{P} T_{p}=a_{L} T_{L}+a_{R} T_{R}+S_{u}
$$
其中：
$$
\begin{array}{l}
a_{L}=0 \\
a_{R}=D_{r} A_{r}+\max \left(-F_{r}, 0\right) \\
a_{P}=a_{L}+a_{R}+\left(F_{r}-F_{l}\right)-S_{p} \\
S_{P}=-\left(2 D_{l} A_{l}+\max \left(F_{l}, 0\right)\right) \\
S_{u}=T_{A}\left(2 D_{l} A_{l}+\max \left(F_{l}, 0\right)\right)
\end{array}
$$

- 右边界

推导类似，最终结果总结到下表中。
$$
\begin{array}{cccc} 
\hline
& a_{L} & a_{R} & S_{p} & S_{u} \\
\hline \text { Left } & 0 & D_{R} A_{R} & -\left(2 D_{L} A_{L}\right. & T_{A}\left(2 D_{L} A_{L}\right. \\
& & +\max \left(-F_{r}, 0\right) & \left.+\max \left(F_{l}, 0\right)\right) & \left.+\max \left(F_{l}, 0\right)\right)+\bar{S} V \\
\hline \text { Interior } & D_{L} A_{L} & D_{R} A_{R} & 0 & \bar{S} V \\
& +\max \left(F_{l}, 0\right) & +\max \left(-F_{r}, 0\right) & \\
\hline \text { Right } & D_{L} A_{L}+ & 0 & -\left(2 D_{R} A_{R}\right. & T_{B}\left(2 D_{R} A_{R}\right. \\
& \max \left(0, F_{l}\right) & & \left.+\max \left(-F_{r}, 0\right)\right) & \left.+\max \left(-F_{r}, 0\right)\right)+\bar{S} V \\
\hline
\end{array}
$$

$$
a_{P}=a_{L}+a_{R}+\left(F_{r}-F_{l}\right)-S_{p}
$$

其中：
$$
D_LA_L = k_lA_l/d_{LP} \\
D_R A_R = k_r A_r / d_{PR} \\
F_l = \rho c_p U_l A_l \\
F_r = \rho c_p U_r A_r
$$

- 代码修改

只需要修改`MatrixCoeff`中的`aL`、`aR`、`Sp`和`Su`即可。

## 狄拉克边界与黎曼边界

前面使用的边界条件都是狄拉克边界条件，也即直接给定边界的值，黎曼边界条件则是给定梯度。

对于给定热流（即温度梯度）的这种情况，通常用于壁面边界，因此这里只考虑一维扩散过程。

- 内部点

回顾前面的内容，先给出内部点的离散方程：
$$
\left(k_{r} A_{r} \frac{T_{R}-T_{P}}{d_{P R}}\right)-\left(k_{l} A_{l} \frac{T_{P}-T_{L}}{d_{L P}}\right)+\bar{S} V=0
$$
归并同类项：
$$
\begin{array}{c}
a_{p} T_{P}=a_{L} T_{L}+a_{R} T_{R}+S_{u} \\
T_{P} \underbrace{\left(D_{l} A_{l}+D_{r} A_{r}+0\right)}_{a_{p}}=T_{L} \underbrace{\left(D_{l} A_{l}\right)}_{a_{L}}+T_{R} \underbrace{\left(D_{r} A_{r}\right)}_{a_{R}}+\underbrace{S V}_{S_{u}}
\end{array}
$$
写成通式：
$$
\begin{aligned}
a_{p} T_{P}=& \sum_{N} a_{N} T_{N}+S_{u} \\
a_{p}=\sum_{N} \frac{k_{N} A_{N}}{\left|\boldsymbol{d}_{P N}\right|}|\hat{\boldsymbol{n}}| \quad & a_{N}=\frac{k_{N} A_{N}}{\left|\boldsymbol{d}_{P N}\right|}|\hat{\boldsymbol{n}}| \quad S_{u}=\bar{S} V
\end{aligned}
$$
![](https://md-pic-1259272405.cos.ap-guangzhou.myqcloud.com/img/20200729205916.png)

注意前面推导的时候，由于网格是正交的，所以$|\hat{\boldsymbol{n}}| = 1$，但是如果网格非正交，绝对值就不一定是$1$了，因此通式中要保留这一项。

- 狄拉克边界

$$
T_{P} \underbrace{\left(0+D_{r} A_{r}+2 D_{l} A_{l}\right)}_{a_{P}}=T_{L} \underbrace{(0)}_{a_{L}}+T_{R} \underbrace{\left(D_{r} A_{r}\right)}_{a_{R}}+\underbrace{T_{w}\left(2 D_{l} A_{l}\right)+\bar{S} V}_{S_{u}}
$$

$$
\begin{array}{c}
a_{L}=0 \quad a_{R}=D_{r} A_{r} \quad a_{p}=a_{L}+a_{R}-S_{p} \\
S_{P}=-2 D_{l} A_{l} \quad S_{u}=\bar{S} V+T_{w}\left(2 D_{l} A_{l}\right)
\end{array}
$$

这里给出了左边界网格的离散形式，可以看到，边界条件对$a_p$和$S_u$都有影响。

通式为：

<img src="https://md-pic-1259272405.cos.ap-guangzhou.myqcloud.com/img/20200729211615.png" style="zoom: 50%;" />

**注意**：在这里，左边界网格的左侧没有网格，所以左侧$a_N=0$，对$a_P$中$\sum_N$那部分的贡献也为$0$，边界的贡献跑到不规则项即$S_p$和$S_u$中了。

- 黎曼边界

$$
\underbrace{\left(k A \frac{d T}{d x} n_{x}\right)_{r}}_{\text {Heat Flux Right Face }}+\underbrace{\left(k A \frac{d T}{d x} n_{x}\right)_{l}}_{\text {Heat Flux Left Face }}+\bar{S} V=0
$$

这里可以直接给出左边界的梯度：
$$
q=-k \frac{d T}{d x} n_{x} \quad\left[\mathrm{W} / \mathrm{m}^{2}\right]\\
k_{r} A_{r}\left(\frac{T_{R}-T_{P}}{d_{P R}}\right)-q_{w} A_{l}+\bar{S} V=0
$$
**注意**：当$q$为正值的时候，表示热量流出控制体。

归并同类项：
$$
\begin{aligned}
a_{p} T_{p} &=a_{L} T_{L}+a_{R} T_{R}+S_{u} \\
T_{P} \underbrace{\left(0+D_{r} A_{r}+0\right)}_{a_{P}} &=T_{L} \underbrace{(0)}_{a_{L}}+T_{R} \underbrace{\left(D_{r} A_{r}\right)}_{a_{R}}+\underbrace{-q_{w} A_{l}+\bar{S} V}_{S_{u}}
\end{aligned}
$$
其中：
$$
\begin{array}{c}
a_{L}=0 \quad a_{R}=D_{r} A_{r} \quad a_{p}=a_{L}+a_{R}-S_{p} \\
S_{P}=0 \quad S_{u}=\bar{S} V-q_{w} A_{l}
\end{array}
$$
写成通式：
$$
a_{p} T_{P}=\sum_{N} a_{N} T_{N}+S_{u} \\
a_{p}=\left(\sum_{N} \frac{k_{N} A_{N}}{\left|\boldsymbol{d}_{P N}\right|}|\hat{\boldsymbol{n}}|\right) \quad a_{N}=\frac{k_{N} A_{N}}{\left|\boldsymbol{d}_{P N}\right|}|\hat{\boldsymbol{n}}| \quad S_{u}=\bar{S} V-q_{w} A_{l}
$$
和前面相同的是，边界网格左侧的$a_N=0$，与前面不同的是，边界不再对$S_p$有影响，只对$S_u$有影响。

- 总结

**Dirichlet Boundary Condition**:
$$
\begin{array}{lccccc}
\hline
\text { Cell Type } & a_{L} & a_{R} & a_{P} & S_{p} & S_{u} \\
\hline \text { Boundary }(\mathrm{L}) & 0 & D_{R} A_{R} & a_{l}+a_{r}-S_{p} & -2 D_{L} A_{L} & T_{w}\left(2 D_{L} A_{L}\right)+\bar{S} V \\
\text { Interior } & D_{L} A_{L} & D_{R} A_{R} & a_{l}+a_{r}-S_{p} & 0 & \bar{S} V \\
\text { Boundary }(\mathrm{R}) & D_{L} A_{L} & 0 & a_{l}+a_{r}-S_{p} & -2 D_{R} A_{R} & T_{w}\left(2 D_{R} A_{R}\right)+\bar{S} V \\
\hline
\end{array}
$$
**Neumann Boundary Condition**:
$$
\begin{array}{lccccc}
\hline
\text { Cell Type } & a_{L} & a_{R} & a_{P} & S_{p} & S_{u} \\
\hline \text { Boundary }(\mathrm{L}) & 0 & D_{R} A_{R} & a_{l}+a_{r}-S_{p} & 0 & -q_{w} A_{l}+\bar{S} V \\
\text { Interior } & D_{L} A_{L} & D_{R} A_{R} & a_{l}+a_{r}-S_{p} & 0 & \bar{S} V \\
\text { Boundary }(\mathrm{R}) & D_{L} A_{l} & 0 & a_{l}+a_{r}-S_{p} & 0 & -q_{w} A_{r}+\bar{S} V \\
\hline
\end{array}
$$
**Summation**:
$$
\begin{array}{lccc}
\hline
\text { Face Type } & a_{P} & a_{N} & S_{u} \\
\hline \text { Interior } & \frac{k_{N} A_{N}}{\left|\boldsymbol{d}_{P N}\right|}|\hat{\boldsymbol{n}}| & \frac{k_{N} A_{N}}{\left|\boldsymbol{d}_{P N}\right|}|\hat{\boldsymbol{n}}| & 0 \\
\text { Dirichlet } & \frac{k_{w} A_{w}}{\left|\boldsymbol{d}_{L P}\right| / 2}|\hat{\boldsymbol{n}}| & 0 & T_{w}\left(\frac{k_{w} A_{w}}{\left|\boldsymbol{d}_{L P}\right| / 2}|\hat{\boldsymbol{n}}|\right) \\
\text { Neumann } & 0 & 0 & -q_{w} A_{w} \\
\hline
\end{array}
$$
总结起来就是：

1. 两种边界条件的引入都会使得边界那个方向的$a_N=0$
2. 狄拉克边界的引入会同时在$a_P$和$S_u$中引入不规则项
3. 黎曼边界条件只会在$S_u$中引入不规则项

- 算例

取自Fluid 101 Course 2，P17：

![](https://md-pic-1259272405.cos.ap-guangzhou.myqcloud.com/img/20200803205129.png)

- 代码修改

在前面对流扩散代码基础上做如下修改：

1. 在`Inputs.h`中将流速设置为$0$，这样对流相关的项就为$0$了，得到了上图(a)，即狄拉克边界条件的代码
2. 如果要修改左边界为黎曼边界条件，先在`Inputs.h`中增加左边界热流密度`q_w`
3. 再将`MatrixCoeff`中的`Sp`全部设置为$0$
4. 最后将左边界网格的`Su`改为$-q_{w} A_{r}+\bar{S} V$

## 二维扩散



