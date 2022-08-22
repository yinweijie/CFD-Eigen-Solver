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

如果流动是**从左到右**，左边的对流项可以写为：

$$
F_{r} T_{P}-F_{l} T_{L}=D_{r} A_{r}\left(T_{R}-T_{P}\right)-D_{l} A_{l}\left(T_{P}-T_{L}\right)+\bar{S} V
$$

![](https://md-pic-1259272405.cos.ap-guangzhou.myqcloud.com/img/20200727161942.png)

归并同类项得到：

$$
T_{P} \underbrace{\left[D_{l} A_{l}+F_{l}+D_{r} A_{r}+\left(F_{r}-F_{l}\right)\right]}_{a_{p}}=T_{L} \underbrace{\left[D_{l} A_{l}+F_{l}\right]}_{a_{L}}+T_{R} \underbrace{\left[D_{r} A_{r}\right]}_{a_{R}}+\underbrace{\bar{S}_{V}}_{S_{u}}
$$

如果流动**从右到左**：

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

简写为：

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

## 一阶迎风格式的再推导

- 内部点

对于上面迎风格式推导Link Coefficient的方式，有些繁琐，其实理解了原理以后，可以有更简便的推导方式，这里为了突出重点，先忽略扩散项：

$$
F_r T_R - F_l T_L = \\ 
\left[T_P \max(F_r, 0) - T_R \max(-F_r, 0)\right] - \left[T_L \max(F_l, 0) - T_P \max(-F_l, 0)\right] = 0 \\
\Downarrow\\
T_P\underbrace{\left[\max(F_r, 0) + \max(-F_l, 0)\right]}_{a_P} = T_L \underbrace{\max(F_l, 0)}_{a_L} + T_R \underbrace{\max(-F_r, 0)}_{a_R}
$$

可以看到$a_P$和$a_R, \, a_L$有一定关系，即：

$$
\max(F_r, 0) + \max(-F_l, 0) = [\max(-F_r, 0) + F_r] + [\max(F_l, 0) - F_l] \\
a_P = (a_R + F_r) + (a_L - F_l)
$$

这里利用到了[Co-Located SIMPLE.md](./Co-Located SIMPLE.md)中“对流项一阶迎风的另一种表达”中给出的关系。

- 左边界

$$
F_r T_R - F_l T_L = \\ 
\left[T_P \max(F_r, 0) - T_R \max(-F_r, 0)\right] - \left[T_A \max(F_l, 0) - T_P \max(-F_l, 0)\right] = 0 \\
\Downarrow\\
T_P\underbrace{\left[\max(F_r, 0) + \max(-F_l, 0)\right]}_{a_P} = T_A \max(F_l, 0) + T_R \underbrace{\max(-F_r, 0)}_{a_R}
$$

由于$T_L$被边界值$T_A$取代了，$a_L=0$，$a_P$和$a_R, \, a_L$的关系可以表示为：

$$
a_P = (a_R + F_r) + (\max(F_l, 0) - F_l) \\
= (a_R + F_r) + (\underbrace{a_L}_{=0} - F_l) \underbrace{-S_p}_{=\max(F_l, 0)}
$$

其中：

$$
-S_p = \max(F_l, 0)
$$

写成这种形式是为了和内部点形式保持一致。

- 右边界

$$
F_r T_R - F_l T_L = \\
\left[T_P \max(F_r, 0) - T_B \max(-F_r, 0)\right] - \left[T_L \max(F_l, 0) - T_P \max(-F_l, 0)\right] = 0 \\
\Downarrow\\
T_P\underbrace{[\max(F_r, 0) + \max(-F_l, 0)]}_{a_P} = T_L \underbrace{\max(F_l, 0)}_{a_L} + T_B \max(-F_r, 0)
$$

于是：

$$
a_P = (\max(-F_r, 0) + F_r) + (a_L - F_l) \\
= (\underbrace{a_R}_{=0} + F_r) + (a_L - F_l) \underbrace{-S_p}_{=\max(-F_r, 0)}
$$

其中：

$$
-S_p = \max(-F_r, 0)
$$

## 一阶迎风格式用于动量方程边界

- 左边界

在处理动量方程边界条件的时候，和标量输运方程有些区别，对于$x$方向速度动量方程，仿照上面的推导方式有：

$$
F_r u_R - F_l u_L = \\ 
\left[u_P \max(F_r, 0) - u_R \max(-F_r, 0)\right] - \rho u_{in}u_{in} = 0 \\
\Downarrow\\
u_P\underbrace{\max(F_r, 0)}_{a_P} = \rho u_{in}u_{in} + u_R \underbrace{\max(-F_r, 0)}_{a_R}
$$

因此：

$$
a_P = a_R + F_r + \underbrace{a_L}_{=0} - \underbrace{F_l}_{=0}
$$

可以看到动量边界并不会写成$F_l u_L = [u_A \max(F_l, 0) - u_P \max(-F_l, 0)]$这种形式，而是直接根据边界条件给定的。

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

- 方程离散

$$
0=\nabla \cdot(k \nabla T)+S \\
0=\frac{\partial}{\partial x}\left(k \frac{\partial T}{\partial x}\right)+\frac{\partial}{\partial y}\left(k \frac{\partial T}{\partial y}\right)+S \\
0=\int_{V}\left[\frac{\partial}{\partial x}\left(k \frac{\partial T}{\partial x}\right)+\frac{\partial}{\partial y}\left(k \frac{\partial T}{\partial y}\right)\right] \mathrm{d} V+\bar{S} V\\
0=\left(k A \frac{\partial T}{\partial x}\right)_{r}-\left(k A \frac{\partial T}{\partial x}\right)_{l}+\left(k A \frac{\partial T}{\partial y}\right)_{t}-\left(k A \frac{\partial T}{\partial y}\right)_{b}+\bar{S} V
$$

- 系数总结

二维扩散，两种边界条件的系数如下：

**Dirichlet Boundary Condition (2D)**:

$$
\begin{array}{lcccccc} 
\hline
& a_{L} & a_{R} & a_{B} & a_{T} & S_{p} & S_{u} \\
\hline 
\text { Interior } & D_{L} A_{L} & D_{R} A_{R} & D_{B} A_{B} & D_{T} A_{T} & 0 & \bar{S} V \\
\text { Boundary }(\mathrm{L}) & 0 & D_{R} A_{R} & D_{B} A_{B} & D_{T} A_{T} & -2 D_{L} A_{L} & T_{\text {wall }}\left(2 D_{L} A_{L}\right)+\bar{S} V \\
\text { Boundary }(\mathrm{R}) & D_{L} A_{L} & 0 & D_{B} A_{B} & D_{T} A_{T} & -2 D_{R} A_{R} & T_{\text {wall }}\left(2 D_{R} A_{R}\right)+\bar{S} V \\
\text { Boundary }(\mathrm{B}) & D_{L} A_{L} & D_{R} A_{R} & 0 & D_{T} A_{T} & -2 D_{B} A_{B} & T_{\text {wall }}\left(2 D_{B} A_{B}\right)+\bar{S} V \\
\text { Boundary }(\mathrm{T}) & D_{L} A_{L} & D_{R} A_{R} & D_{T} A_{T} & 0 & -2 D_{T} A_{T} & T_{\text {wall }}\left(2 D_{T} A_{T}\right)+\bar{S} V \\
\hline
\end{array}
$$

**Neumann Boundary Condition (2D)**:

$$
\begin{array}{lcccccc} 
\hline
& a_{L} & a_{R} & a_{B} & a_{T} & S_{p} & S_{u} \\
\hline 
\text { Interior } & D_{L} A_{L} & D_{R} A_{R} & D_{B} A_{B} & D_{T} A_{T} & 0 & \bar{S} V \\
\text { Boundary }(\mathrm{L}) & 0 & D_{R} A_{R} & D_{B} A_{B} & D_{T} A_{T} & 0 & -q_{\text {wall }} A_{l}+\bar{S} V \\
\text { Boundary }(\mathrm{R}) & D_{L} A_{L} & 0 & D_{B} A_{B} & D_{T} A_{T} & 0 & -q_{\text {wall }} A_{r}+\bar{S} V \\
\text { Boundary }(\mathrm{B}) & D_{L} A_{L} & D_{R} A_{R} & 0 & D_{T} A_{T} & 0 & -q_{\text {wall }} A_{B}+\bar{S} V \\
\text { Boundary }(\mathrm{T}) & D_{L} A_{L} & D_{R} A_{R} & D_{T} A_{T} & 0 & 0 & -q_{\text {wall }} A_{T}+\bar{S} V \\
\hline
\end{array}
$$

$$
a_{p}=a_{L}+a_{R}+a_{T}+a_{B}-S_{p}
$$

**Summation Notation**:

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

为了对比说明，将前面一维对流-扩散也放在这里：

$$
\begin{array}{cccc} 
\hline
& a_{L} & a_{R} & S_{p} & S_{u} \\
\hline \text { Left } & 0 & D_{r} A_{r} & -\left(2 D_{l} A_{l}\right. & T_{A}\left(2 D_{l} A_{l}\right. \\
& & +\max \left(-F_{r}, 0\right) & \left.+\max \left(F_{l}, 0\right)\right) & \left.+\max \left(F_{l}, 0\right)\right)+\bar{S} V \\
\hline \text { Interior } & D_{l} A_{l} & D_{r} A_{r} & 0 & \bar{S} V \\
& +\max \left(F_{l}, 0\right) & +\max \left(-F_{r}, 0\right) & \\
\hline \text { Right } & D_{l} A_{l}+ & 0 & -\left(2 D_{r} A_{r}\right. & T_{B}\left(2 D_{r} A_{r}\right. \\
& \max \left(0, F_{l}\right) & & \left.+\max \left(-F_{r}, 0\right)\right) & \left.+\max \left(-F_{r}, 0\right)\right)+\bar{S} V \\
\hline
\end{array}
$$

$$
a_{P}=a_{L}+a_{R}+\left(F_{r}-F_{l}\right)-S_{p}
$$

系数矩阵形式如下：

![](https://md-pic-1259272405.cos.ap-guangzhou.myqcloud.com/img/20200813155844.png)

- 编程实现

从上面表格中可以总结这样一个规律：

内部点只会引入系数$a_P和a_N$，**对流项**引入$a_N$为$\max(F, 0)$相关系数，引入$a_P=a_{L}+a_{R}+...\left(F_{r}-F_{l}\right)+$ $...-S_p$，**扩散项**引入$a_N$的为$DA$相关系数，引入$a_{p}=a_{L}+a_{R}+...-S_p$；

狄拉克边界不会引入$a_N$，**对流项**会引入$S_P=-\max(F,0)$相关量，$S_u=T_N(\max(F,0))$相关量，**扩散项**会引入$S_P=-2DA$和$S_u=T_N(2DA)$。也就是说，对于壁面网格，靠壁面那一侧的$a_N$系数为$0$，被替换为$-S_p$，并且还会引入源项$S_u$，最终对流项和扩散项的$a_P$与内部点形式相同，只需要注意边界那一侧的$a_N=0$，$-S_p$被额外引入；

黎曼边界同样也不会引入$a_N$，同时也不会引入$S_p$，只会额外引入源项$S_u$；

源项只会引入$S_u$。

由于紧邻壁面的网格需要特殊处理，因此程序中`Mesh`类里封装了一些函数如`is_at_left_boundary`等用来判断网格是否为边壁网格；还分装了如`bottom_of`用来返回当前网格周围网格的编号。

在`MatrixCoeff`类中，封装了三个成员函数`addConvectionTerm`、`addDiffusionTerm`和`addSourceTerm`将方程的对流、扩散和源项分别处理，这样可以只引入需要考虑的项。

- 算例

![](https://md-pic-1259272405.cos.ap-guangzhou.myqcloud.com/img/20200811154409.png)

![](https://md-pic-1259272405.cos.ap-guangzhou.myqcloud.com/img/20200811154435.png)

**注意**，我的程序中，y坐标是向上的，因此Top和Bottom与这里的正好相反，因此`Inputs`中`top`为150℃，`bottom`为250℃。

## 类封装

至此，二维稳态对流扩散代码基本实现，最后一步是完善矩阵迭代求解器。之前一直是使用稠密矩阵`MatrixXd`来存储，并且使用矩阵直接求解法求解矩阵，效率不高，内存消耗也比较大。

- 迭代求解简单案例

`Eigen`库中自带有系数矩阵类`SparseMatrix<T>`，以及迭代求解器，例如`BiCGSTAB`，因此可以用稀疏矩阵去保存系数，并采用迭代求解器求解，下面给出一个简单的`Eigen`库迭代求解稀疏矩阵的例子：

```cpp
#include <Eigen/Sparse>
#include <Eigen/IterativeLinearSolvers>
#include <vector>
#include <iostream>

using Eigen::SparseMatrix;
using Eigen::VectorXd;
using Eigen::VectorXi;
using Eigen::BiCGSTAB;

int main(int argc, char** argv)
{

    int n = 5;
    VectorXd x(n), b(n);
    SparseMatrix<double> A(n,n); // default is column major

    /******* fill A and b ******/ 
    /*
    A matrix:
    [ 30.5  -9.5   0.    0.    0. ]
    [-10.5  20.   -9.5   0.    0. ]
    [  0.  -10.5  20.   -9.5   0. ]
    [  0.    0.  -10.5  20.   -9.5]
    [  0.    0.    0.  -10.5  29.5]

    B vector
    [2200.  100.  100.  100. 3900.]
    */
    A.reserve(VectorXi::Constant(n, 3));

    for(int i = 0; i < 5; i++)
    {
        if(i == 0)
        {
            A.insert(i, i) = 30.5;
            A.insert(i, i+1) = -9.5;
            b[i] = 2200;
        }
        else if(i == 4)
        {
            A.insert(i, i-1) = -10.5;
            A.insert(i, i) = 29.5;
            b[i] = 3900;
        }
        else
        {
            A.insert(i, i-1) = -10.5;                    // alternative: mat.coeffRef(i,j) += v_ij;
            A.insert(i, i) = 20;
            A.insert(i, i+1) = -9.5;
            b[i] = 100;
        }
    }

    A.makeCompressed();                        // optional

    /* ^^^^ fill A and b ^^^^ */ 

    BiCGSTAB<SparseMatrix<double>, Eigen::IdentityPreconditioner> solver;
    solver.compute(A);
    x = solver.solve(b);

    std::cout << "#iterations:     " << solver.iterations() << std::endl;
    std::cout << "estimated error: " << solver.error()      << std::endl;

    std::cout << "x: " << std::endl << x << std::endl;

    return 0;
}
```

- CFD求解器中实现迭代求解

为了方便Debug操作，依旧保留之前的稠密矩阵类的求解过程，重新定义一个新的稀疏矩阵求解过程，而这两个过程在初始化矩阵的的步骤有大量相同操作，为了将这部分代码抽象出来，定义了一个抽象接口类`MatrixInterface`，定义在`MatrixInterface.h`中，以及两个封装类`DenseMatrixWrapper`和`SparseMatrixWrapper`定义在`MatrixWrapper.h`中，这两个封装类会implement这个接口，用于实现往矩阵中插入数字的过程。

初始化矩阵在函数`initDenseMatrix`、`initSparseMatrix`以及`init`中，求解矩阵在函数`DebugSolve`和`Solve`函数中。

# Sandip Mazumder - CFD Lectures

同位网格SIMPLE算法，参考Sandip的CFD课程：[Link](https://www.youtube.com/watch?v=JUbHKZRupnE&list=PLVuuXJfoPgT4gJcBAAFPW7uMwjFKB9aqT)

课程中的方程符号和Fluid 101中不太一样，这里统一一下。

## 动量方程简化

二维动量方程（$X$方向和$Y$方向）完整形式为：

$$
\frac{\partial(\rho u)}{\partial t}+\frac{\partial(\rho u u)}{\partial x}+\frac{\partial(\rho v u)}{\partial y}=-\frac{\partial p}{\partial x}+\frac{\partial}{\partial x}\left(2 \mu \frac{\partial u}{\partial x}+\lambda \nabla \cdot \bar{u}\right)+\frac{\partial}{\partial y}\left[\mu\left(\frac{\partial u}{\partial y}+\frac{\partial v}{\partial x}\right)\right] \\
\frac{\partial(\rho v)}{\partial t}+\frac{\partial(\rho u v)}{\partial x}+\frac{\partial(\rho v v)}{\partial y}=-\frac{\partial p}{\partial y}+\frac{\partial}{\partial x}\left[\mu\left(\frac{\partial u}{\partial y}+\frac{\partial v}{\partial x}\right)\right]+\frac{\partial}{\partial y}\left(2 \mu \frac{\partial v}{\partial y}+\lambda \nabla \cdot \bar{u}\right)
$$

将等号右侧提取出扩散项：

$$
\begin{aligned}
\rho\left(\frac{\partial u}{\partial t}+u \frac{\partial u}{\partial x}+v \frac{\partial u}{\partial y}\right)=& \\
-\frac{\partial p}{\partial x}+\frac{\partial}{\partial x}\left(\mu \frac{\partial u}{\partial x}\right)&
+\frac{\partial}{\partial y}\left(\mu \frac{\partial u}{\partial y}\right)+\left[\frac{\partial}{\partial x}\left(\mu \frac{\partial u}{\partial x}\right)+\frac{\partial}{\partial y}\left(\mu \frac{\partial v}{\partial x}\right)\right]+\frac{\partial}{\partial x}(\lambda \nabla \cdot \bar{u}) \\


\rho\left(\frac{\partial v}{\partial t}+u \frac{\partial v}{\partial x}+v \frac{\partial v}{\partial y}\right)=& \\
-\frac{\partial p}{\partial y}+\frac{\partial}{\partial x}\left(\mu \frac{\partial v}{\partial x}\right)&
+\frac{\partial}{\partial y}\left(\mu \frac{\partial v}{\partial y}\right)+\left[\frac{\partial}{\partial y}\left(\mu \frac{\partial v}{\partial y}\right)+\frac{\partial}{\partial x}\left(\mu \frac{\partial u}{\partial y}\right)\right]+\frac{\partial}{\partial y}(\lambda \nabla \cdot \bar{u})

\end{aligned}
$$

考虑流体不可压，有连续性方程：

$$
\frac{\partial u}{\partial x} + \frac{\partial v}{\partial y} = 0
$$

最终可以将动量方程简化为： 

$$
\frac{\partial(\rho u)}{\partial t}+\nabla \cdot(\rho \bar{u} u)=-\frac{\partial p}{\partial x}+\nabla \cdot(\mu \nabla u)+S x \\
\frac{\partial(\rho v)}{\partial t}+\nabla \cdot(\rho \bar{u} v)=-\frac{\partial p}{\partial y}+\nabla \cdot(\mu \nabla v)+S y
$$

这里将分离出来的粘性项以外的项，视为源项$S_x, S_y$，这里取$0$。

## 输运方程统一形式

可以看到，实际上动量方程可以看作是特殊的标量输运方程，输运对象是速度$u$和$v$，如果用统一形式来描述$X$方向动量方程、$Y$方向动量方程，能量输运方程，可以写成：

$$
\begin{aligned}
\frac{\partial (\rho u \phi^u)}{\partial x} + \frac{\partial (\rho v \phi^u)}{\partial y} &= \frac{\partial}{\partial x}\left( \mu \frac{\partial \phi^u}{\partial x} \right) + \frac{\partial}{\partial y}\left( \mu \frac{\partial \phi^u}{\partial y} \right) + S^u \\

\frac{\partial (\rho u \phi^v)}{\partial x} + \frac{\partial (\rho v \phi^v)}{\partial y} &= \frac{\partial}{\partial x}\left( \mu \frac{\partial \phi^v}{\partial x} \right) + \frac{\partial}{\partial y}\left( \mu \frac{\partial \phi^v}{\partial y} \right) + S^v \\

\frac{\partial (\rho c_p u \phi^T)}{\partial x} + \frac{\partial (\rho c_p v \phi^T)}{\partial y} &= \frac{\partial}{\partial x}\left( k \frac{\partial \phi^T}{\partial x} \right) + \frac{\partial}{\partial y}\left( k \frac{\partial \phi^T}{\partial y} \right) + S^T

\end{aligned}
$$

其中：

$$
\begin{aligned}
S^u &= -\frac{\partial p}{\partial x} \\
S^v &= -\frac{\partial p}{\partial y} \\
S^T &= \bar{S}V
\end{aligned}
$$

## 输运方程离散

将输运方程写成有限体积通量形式：

$$
\begin{aligned}

\left(J_{e}^{u} A_e - J_{w}^{u} A_w\right) +\left(J_{n}^{u} A_n - J_{s}^{u} A_s\right) &=-\left(p_{e} A_e - p_{w} A_w\right) \\

\left(J_{e}^{v} A_e - J_{w}^{v} A_w\right) +\left(J_{n}^{v} A_n - J_{s}^{v} A_s\right) &=-\left(p_{n} A_n - p_{s} A_s\right) \\

\left(J_{e}^{T} A_e - J_{w}^{T} A_w\right) +\left(J_{n}^{T} A_n - J_{s}^{T} A_s\right) &=\bar{S}V \\
\end{aligned}
$$

- $X$方向动量方程

$$
\begin{aligned}

J_{e}^{u} &=\rho_{e} u_{e} \phi^u_{e}-\left.\mu_{e} \frac{\partial \phi^u}{\partial x}\right|_{e}\\
J_{w}^{u} &=\rho_{w} u_{w} \phi^u_{w}-\left.\mu_{w} \frac{\partial \phi^u}{\partial x}\right|_{w}\\
J_{n}^{u} &=\rho_{n} v_{n} \phi^u_{n}-\left.\mu_{n} \frac{\partial \phi^u}{\partial y}\right|_{n}\\
J_{s}^{u} &=\rho_{s} v_{s} \phi^u_{s}-\left.\mu_{s} \frac{\partial \phi^u}{\partial y}\right|_{s}

\end{aligned}
$$

离散形式：

$$
\begin{aligned}
&\left[\phi_{O}^u \max \left(\rho_e u_e, 0\right)-\phi_{E}^u \max \left(-\rho_e u_e, 0\right)-\mu_{e} \frac{\phi_{E}^u-\phi_{O}^u}{\Delta x}\right] A_x\\
-&\left[\phi_{W}^u \max \left(\rho_w u_w, 0\right)-\phi_{O}^u \max \left(-\rho_w u_w, 0\right)-\mu_{w} \frac{\phi_{O}^u-\phi_{W}^u}{\Delta x}\right] A_x\\
+&\left[\phi_{O}^u \max \left(\rho_n v_n, 0\right)-\phi_{N}^u \max \left(-\rho_n v_n, 0\right)-\mu_{n} \frac{\phi_{N}^u-\phi_{O}^u}{\Delta y}\right] A_y\\
-&\left[\phi_{S}^u \max \left(\rho_s v_s, 0\right)-\phi_{O}^u \max \left(-\rho_s v_s, 0\right)-\mu_{s} \frac{\phi_{O}^u-\phi_{S}^u}{\Delta y}\right] A_y=-\left(p_{e}-p_{w}\right) A_x = \frac{1}{2}\left(p_{W}-p_{E}\right) A_x
\end{aligned}
$$

写成Link coefficient形式：

$$
a_O \phi_O^u = a_E \phi_E^u + a_W \phi_W^u + a_N \phi_N^u + a_S \phi_S^u + S^u
$$

其中：

$$
\begin{aligned}
a_{E} &=\max \left(-\rho_e u_e, 0\right) A_x+\frac{\mu_{e}}{\Delta x} A_x = \max(-F_e, 0) + DA_e\\
a_{W} &=\max \left(\rho_w u_w, 0\right) A_x+\frac{\mu_{w}}{\Delta x} A_x = \max(F_w, 0) + DA_w\\
a_{N} &=\max \left(-\rho_n v_n, 0\right) A_y+\frac{\mu_{n}}{\Delta y} A_y = \max(-F_n, 0) + DA_n \\
a_{S} &=\max \left(\rho_s v_s, 0\right)A_y+\frac{\mu_{s}}{\Delta y} A_y = \max(F_s, 0) + DA_s\\
a_{O} &=a_E+a_W+a_N+a_S+\left[F_e - F_w + F_n - F_s\right] \\
S^{u} &=\frac{1}{2}\left(p_{W}-p_{E}\right) A_x \\
\end{aligned}
$$

- $Y$方向动量方程

Link coefficient形式

$$
a_O \phi_O^v = a_E \phi_E^v + a_W \phi_W^v + a_N \phi_N^v + a_S \phi_S^v + S^v
$$

其中：

$$
\begin{aligned}
a_{E} &=\max \left(-\rho_e u_e, 0\right) A_x+\frac{\mu_{e}}{\Delta x} A_x = \max(-F_e, 0) + DA_e\\
a_{W} &=\max \left(\rho_w u_w, 0\right) A_x+\frac{\mu_{w}}{\Delta x} A_x = \max(F_w, 0) + DA_w\\
a_{N} &=\max \left(-\rho_n v_n, 0\right) A_y+\frac{\mu_{n}}{\Delta y} A_y = \max(-F_n, 0) + DA_n \\
a_{S} &=\max \left(\rho_s v_s, 0\right)A_y+\frac{\mu_{s}}{\Delta y} A_y = \max(F_s, 0) + DA_s\\
a_{O} &=a_E+a_W+a_N+a_S+\left[F_e - F_w + F_n - F_s\right] \\
S^{v} &=\frac{1}{2}\left(p_{S}-p_{N}\right) A_y
\end{aligned}
$$

- 能量方程

Link coefficient形式：

$$
a_O \phi_O^T = a_E \phi_E^T + a_W \phi_W^T + a_N \phi_N^T + a_S \phi_S^T + S^T
$$

其中：

$$
\begin{aligned}
a_{E} &=\max \left(-\rho_e c_p u_e, 0\right) A_x+\frac{k_{e}}{\Delta x} A_x = \max(-F_e, 0) + DA_e \\
a_{W} &=\max \left(\rho_w c_p u_w, 0\right) A_x+\frac{k_{w}}{\Delta x} A_x = \max(F_w, 0) + DA_w \\
a_{N} &=\max \left(-\rho_n c_p v_n, 0\right) A_y+\frac{k_{n}}{\Delta y} A_y = \max(-F_n, 0) + DA_n \\
a_{S} &=\max \left(\rho_s c_p v_s, 0\right)A_y+\frac{k_{s}}{\Delta y} A_y = \max(F_s, 0) + DA_s\\
a_{O} &=a_E+a_W+a_N+a_S+\left[F_e - F_w + F_n - F_s\right] \\
S^{T} &= \bar{S}V
\end{aligned}
$$

可以看到，输运方程的形式基本是一样的（动量方程只有压力项有区别），不同的只是输运对象。

## PWIM差值

计算对流项的时候，需要知道网格面上的法向速度，在同位网格SIMPLE算法中，这个法向速度不能直接用网格中心点的平均值表示，否则会出现“棋盘问题”，需要用到PWIM差值得到法向速度。

$X$方向法向速度：

$$
\begin{aligned}
\hat{u}_{e} &=\frac{1}{2}\left(\hat{u}_{O}+\hat{u}_{E}\right)+\frac{1}{2} \frac{\left(p_{E}^{(k)}-p_{W}^{(k)}\right)}{\left.2 a_{O}\right|_{O}} A_x+\frac{1}{2} \frac{\left(p_{E E}^{(k)}-p_{O}^{(k)}\right)}{\left.2 a_{O}\right|_{E}} A_x-\left[\frac{1}{\left.a_{O}\right|_{E}}+\frac{1}{\left.a_{O}\right|_{O}}\right] \frac{\left(p_{E}^{(k)}-p_{O}^{(k)}\right)}{2} A_x \\
\end{aligned}
$$

或：

$$
\hat{u}_{e}=\frac{1}{2}\left(\hat{u}_{O}+\hat{u}_{E}\right)+\frac{1}{2} \Delta x \Delta y\left[\left.\frac{1}{\left.A_{O}\right|_{O}} \frac{\partial p^{(k)}}{\partial x}\right|_{O}+\left.\frac{1}{\left.A_{O}\right|_{E}} \frac{\partial p^{(k)}}{\partial x}\right|_{E}-\left.\left(\frac{1}{\left.A_{O}\right|_{E}}+\frac{1}{\left.A_{O}\right|_{O}}\right) \frac{\partial p^{(k)}}{\partial x}\right|_{e}\right]
$$

$Y$方向法向速度：

$$
\begin{aligned}
\hat{v}_{n} &=\frac{1}{2}\left(\hat{v}_{O}+\hat{v}_{N}\right)+\frac{1}{2} \frac{\left(p_{N}^{(k)}-p_{S}^{(k)}\right)}{\left.2 a_{O}\right|_{O}} A_y+\frac{1}{2} \frac{\left(p_{N N}^{(k)}-p_{O}^{(k)}\right)}{\left.2 a_{O}\right|_{N}} A_y-\left[\frac{1}{\left.a_{O}\right|_{N}}+\frac{1}{\left.a_{O}\right|_{O}}\right] \frac{\left(p_{N}^{(k)}-p_{O}^{(k)}\right)}{2} A_y\\
\end{aligned}
$$

或：

$$
\hat{v}_{n}=\frac{1}{2}\left(\hat{v}_{O}+\hat{v}_{N}\right)+\frac{1}{2} \Delta x \Delta y\left[\left.\frac{1}{\left.A_{O}\right|_{O}} \frac{\partial p^{(k)}}{\partial y}\right|_{O}+\left.\frac{1}{\left.A_{O}\right|_{N}} \frac{\partial p^{(k)}}{\partial y}\right|_{N}-\left.\left(\frac{1}{\left.A_{O}\right|_{N}}+\frac{1}{\left.A_{O}\right|_{O}}\right) \frac{\partial p^{(k)}}{\partial y}\right|_{n}\right]
$$

## 压力、速度修正

由于SIMPLE算法需要对方程组的解反复修正，需要求解压力修正方程：

$$
a_{O}^{p} p_{O}^{\prime} = a_{E}^{p} p_{E}^{\prime}+a_{W}^{p} p_{W}^{\prime}+a_{N}^{p} p_{N}^{\prime}+a_{S}^{p} p_{S}^{\prime} + S^{p}
$$

其中：

$$
\begin{aligned}
a_{E}^{p} &=\frac{\rho_{e}(A_x)^{2}}{2}\left[\frac{1}{\left.a_{O}\right|_{E}}+\frac{1}{\left.a_{O}\right|_{O}}\right], \quad 
a_{W}^{p} =\frac{\rho_{w}(A_x)^{2}}{2}\left[\frac{1}{\left.a_{O}\right|_{W}}+\frac{1}{\left.a_{O}\right|_{O}}\right] \\
a_{N}^{p} &=\frac{\rho_{n}(A_y)^{2}}{2}\left[\frac{1}{\left.a_{O}\right|_{N}}+\frac{1}{\left.a_{O}\right|_{O}}\right], \quad
a_{S}^{p}=\frac{\rho_{s}(A_y)^{2}}{2}\left[\frac{1}{\left.a_{O}\right|_{S}}+\frac{1}{\left.a_{O}\right|_{O}}\right] \\
a_O^p &= a_E^p + a_W^p + a_N^p + a_S^p \\
S^{p} &=-\left[\left(\rho_{e} \hat{u}_{e}-\rho_{w} \hat{u}_{w}\right) A_x+\left(\rho_{n} \hat{v}_{n}-\rho_{s} \hat{v}_{s}\right) A_y\right]=-\dot{m}_\text{imbalance}
\end{aligned}
$$

得到压力修正量以后，可以分别修正速度cell value和face value：

- cell value修正

$$
u_{O}^{\prime}=\frac{\left(p_{W}^{\prime}-p_{E}^{\prime}\right)}{\left.2 a_{O}\right|_{O}} A_x \quad \text { and } \quad v_{O}^{\prime}=\frac{\left(p_{S}^{\prime}-p_{N}^{\prime}\right)}{\left.2 a_{O}\right|_{O}} A_y
$$

  于是下一个outer iteration的值为：

$$
p_{O}^{(k+1)}=p_{O}^{(k)}+\omega_{p} p_{O}^{\prime} \\

  u_{O}^{(k+1)}=\hat{u}_{O}+\omega_{u v} u_{O}^{\prime}=\hat{u}_{O}+\omega_{u w} \frac{\left(p_{W}^{\prime}-p_{E}^{\prime}\right)}{\left.2 a_{O}\right|_{O}} A_x \\

  v_{O}^{(k+1)}=\hat{v}_{O}+\omega_{u v} v_{O}^{\prime}=\hat{v}_{O}+\omega_{u w} \frac{\left(p_{S}^{\prime}-p_{N}^{\prime}\right)}{\left.2 a_{O}\right|_{O}} A_y
$$

- face value修正

$$
u_{e}^{\prime}=\left[\frac{1}{\left.a_{O}\right|_{E}}+\frac{1}{\left.a_{O}\right|_{O}}\right] \frac{\left(p_{O}^{\prime}-p_{E}^{\prime}\right)}{2} A_x \\
  v_{n}^{\prime}=\left[\frac{1}{\left.a_{O}\right|_{N}}+\frac{1}{\left.a_{O}\right|_{O}}\right] \frac{\left(p_{O}^{\prime}-p_{N}^{\prime}\right)}{2} A_y
$$

  于是，下一个outer iteration的值为：

$$
u_{e}^{(k+1)}=\hat{u}_{e}+\omega_{uv} u_{e}^{\prime}=\hat{u}_{e}+\omega_{uv}\left[\frac{1}{\left.a_{O}\right|_{E}}+\frac{1}{\left.a_{O}\right|_{O}}\right] \frac{\left(p_{O}^{\prime}-p_{E}^{\prime}\right)}{2} A_x \\

  v_{n}^{(k+1)}=\hat{v}_{n}+\omega_{uv} v_{n}^{\prime}=\hat{v}_{n}+\omega_{uv}\left[\frac{1}{\left.a_{O}\right|_{N}}+\frac{1}{\left.a_{O}\right|_{O}}\right] \frac{\left(p_{O}^{\prime}-p_{N}^{\prime}\right)}{2} A_y
$$

## 动量方程边界

### Walls (No Slip)

- $X$方向动量方程

通量原始形式：

$$
\begin{aligned}

\left(J_{e}^{u} A_e - J_{w}^{u} A_w\right) +\left(J_{n}^{u} A_n - J_{s}^{u} A_s\right) &=-\left(p_{e} A_e - p_{w} A_w\right) \\

\left(J_{e}^{v} A_e - J_{w}^{v} A_w\right) +\left(J_{n}^{v} A_n - J_{s}^{v} A_s\right) &=-\left(p_{n} A_n - p_{s} A_s\right) \\

\end{aligned}
$$

考虑东、西、北、南四个方向壁面的通量（$\phi^u = u$）：

$$
\begin{aligned}

J_{e}^{u} &=\rho_{e} u_{e} \phi^u_{e}-\left.\mu_{e} \frac{\partial \phi^u}{\partial x}\right|_{e} = 0 - \left.\mu_{e} \frac{\partial \phi^u}{\partial x}\right|_{e} \approx -\mu_e\frac{-9 u_{O}+u_{W}+8 u_{e}}{3 \Delta x}=-\mu_e\frac{-9 u_{O}+u_{W}}{3 \Delta x} \\

J_{w}^{u} &=\rho_{w} u_{w} \phi^u_{w}-\left.\mu_{w} \frac{\partial \phi^u}{\partial x}\right|_{w} = 0 - \left.\mu_{w} \frac{\partial \phi^u}{\partial x}\right|_{w} \approx -\mu_w\frac{9 u_{O}-u_{E}-8 u_{w}}{3 \Delta x}=-\mu_w\frac{9 u_{O}-u_{E}}{3 \Delta x}\\

J_{n}^{u} &=\rho_{n} v_{n} \phi^u_{n}-\left.\mu_{n} \frac{\partial \phi^u}{\partial y}\right|_{n} = 0 - \left.\mu_{n} \frac{\partial \phi^u}{\partial y}\right|_{n} \approx -\mu_n\frac{-9 u_{O}+u_{S}+8 u_{n}}{3 \Delta y}=-\mu_n\frac{-9 u_{O}+u_{S}}{3 \Delta y}\\

J_{s}^{u} &=\rho_{s} v_{s} \phi^u_{s}-\left.\mu_{s} \frac{\partial \phi^u}{\partial y}\right|_{s} = 0 - \left.\mu_{s} \frac{\partial \phi^u}{\partial y}\right|_{s} \approx -\mu_s\frac{9 u_{O}-u_{N}-8 u_{s}}{3 \Delta y}=-\mu_s\frac{9 u_{O}-u_{N}}{3 \Delta y}

\end{aligned}
$$

壁面方向压力，粘度：

$$
p_e \approx p_O, \quad \mu_e \approx \mu_O \\
p_w \approx p_O, \quad \mu_w \approx \mu_O \\
p_n \approx p_O, \quad \mu_n \approx \mu_O \\
p_s \approx p_O, \quad \mu_s \approx \mu_O \\
$$

Link coefficient形式：

$$
\text{East wall:}\quad a_E = 0, \quad F_e = 0, \quad -S_O = \frac{3\mu_O}{\Delta x}A_x, \quad -S_W = \frac{\mu_O}{3\Delta x}A_x, \quad S_u = 0\\

\text{West wall:}\quad a_W = 0, \quad F_w = 0, \quad -S_O = \frac{3\mu_O}{\Delta x}A_x, \quad -S_E = \frac{\mu_O}{3\Delta x}A_x, \quad S_u = 0\\

\text{North wall:}\quad a_N = 0, \quad F_n = 0, \quad -S_O = \frac{3\mu_O}{\Delta y}A_y, \quad -S_S = \frac{\mu_O}{3\Delta y}A_y, \quad S_u = 0\\

\text{South wall:}\quad a_S = 0, \quad F_s = 0, \quad -S_O = \frac{3\mu_O}{\Delta y}A_y, \quad -S_N = \frac{\mu_O}{3\Delta y}A_y, \quad S_u = 0\\

a_O = a_E + a_W + a_N + a_S +\left[F_e - F_w + F_n - F_s\right] - S_O\\
a_O u_O = (a_E-S_E) u_E + (a_W-S_W) u_W + (a_N-S_N) u_N + (a_S-S_S) u_S + S^u + S_u \\

\text{East wall:}\quad S^u = \left(\frac{p_W + p_O}{2} - p_O \right)A_x = \left(\frac{p_W - p_O}{2} \right)A_x\\
\text{West wall:}\quad S^u = \left(p_O - \frac{p_O + p_E}{2} \right)A_x = \left(\frac{p_O - p_E}{2} \right)A_x
$$

**注意**：边界系数有叠加效果，例如，某个网格左侧和顶部都是壁面，则这个网格的$a_W = 0, a_N = 0$，其他系数也会叠加。

- $Y$方向动量方程

Link Coefficient形式（$\phi^v = v$）：

$$
\text{East wall:}\quad a_E = 0, \quad F_e = 0, \quad -S_O = \frac{3\mu_O}{\Delta x}A_x, \quad -S_W = \frac{\mu_O}{3\Delta x}A_x, \quad S_u = 0\\

\text{West wall:}\quad a_W = 0, \quad F_w = 0, \quad -S_O = \frac{3\mu_O}{\Delta x}A_x, \quad -S_E = \frac{\mu_O}{3\Delta x}A_x, \quad S_u = 0\\

\text{North wall:}\quad a_N = 0, \quad F_n = 0, \quad -S_O = \frac{3\mu_O}{\Delta y}A_y, \quad -S_S = \frac{\mu_O}{3\Delta y}A_y, \quad S_u = 0\\

\text{South wall:}\quad a_S = 0, \quad F_s = 0, \quad -S_O = \frac{3\mu_O}{\Delta y}A_y, \quad -S_N = \frac{\mu_O}{3\Delta y}A_y, \quad S_u = 0\\

a_O = a_E + a_W + a_N + a_S +\left[F_e - F_w + F_n - F_s\right] - S_O\\
a_O v_O = (a_E-S_E) v_E + (a_W-S_W) v_W + (a_N-S_N) v_N + (a_S-S_S) v_S + S^v + S_u \\

\text{North wall:}\quad S^v = \left(\frac{p_S + p_O}{2} - p_O \right)A_y = \left(\frac{p_S - p_O}{2} \right)A_y\\
\text{South wall:}\quad S^v = \left( p_O - \frac{p_O + p_N}{2} \right)A_y = \left(\frac{p_O - p_N}{2} \right)A_y
$$

求解$X$方向动量方程与$Y$方向动量方程，唯一的区别就是压力项，其他的系数都是一样的。

### Inlet (Fixed Velocity)

- $X$方向动量方程

与上面类似，考虑东、西、北、南四个方向入口的通量（$\phi^u = u$）：

$$
\begin{aligned}

J_{e}^{u} &=\rho_{e} u_{e} \phi^u_{e}-\left.\mu_{e} \frac{\partial \phi^u}{\partial x}\right|_{e} = \rho_{in}u_{in}u_{in} - \left.\mu_{e} \frac{\partial \phi^u}{\partial x}\right|_{e} \\
&\approx \rho_{in}u_{in}u_{in}-\mu_e\frac{-9 u_{O}+u_{W}+8 u_{e}}{3 \Delta x}=\rho_{in}u_{in}u_{in}-\mu_e\frac{-9 u_{O}+u_{W} + 8u_{in}}{3 \Delta x} \\

J_{w}^{u} &=\rho_{w} u_{w} \phi^u_{w}-\left.\mu_{w} \frac{\partial \phi^u}{\partial x}\right|_{w} = \rho_{in}u_{in}u_{in} - \left.\mu_{w} \frac{\partial \phi^u}{\partial x}\right|_{w} \\
&\approx \rho_{in}u_{in}u_{in} -\mu_w\frac{9 u_{O}-u_{E}-8 u_{w}}{3 \Delta x}=\rho_{in}u_{in}u_{in}-\mu_w\frac{9 u_{O}-u_{E}-8u_{in}}{3 \Delta x}\\

J_{n}^{u} &=\rho_{n} v_{n} \phi^u_{n}-\left.\mu_{n} \frac{\partial \phi^u}{\partial y}\right|_{n} = \rho_{in}v_{in}u_{in} - \left.\mu_{n} \frac{\partial \phi^u}{\partial y}\right|_{n} \\
&\approx \rho_{in}v_{in}u_{in}-\mu_n\frac{-9 u_{O}+u_{S}+8 u_{n}}{3 \Delta y}=\rho_{in}v_{in}u_{in}-\mu_n\frac{-9 u_{O}+u_{S}+8u_{in}}{3 \Delta y}\\

J_{s}^{u} &=\rho_{s} v_{s} \phi^u_{s}-\left.\mu_{s} \frac{\partial \phi^u}{\partial y}\right|_{s} = \rho_{in}v_{in}u_{in} - \left.\mu_{s} \frac{\partial \phi^u}{\partial y}\right|_{s} \\
&\approx \rho_{in}v_{in}u_{in}-\mu_s\frac{9 u_{O}-u_{N}-8 u_{s}}{3 \Delta y}=\rho_{in}v_{in}u_{in}-\mu_s\frac{9 u_{O}-u_{N}-8u_{in}}{3 \Delta y}

\end{aligned}
$$

速度入口压力、粘度：

$$
p_e \approx p_O, \quad \mu_e \approx \mu_O \\
p_w \approx p_O, \quad \mu_w \approx \mu_O \\
p_n \approx p_O, \quad \mu_n \approx \mu_O \\
p_s \approx p_O, \quad \mu_s \approx \mu_O \\
$$

Link coefficient形式：

$$
\text{East in:}\quad a_E = 0, \quad F_e = 0, \quad -S_O = \frac{3\mu_O}{\Delta x}A_x, \quad -S_W = \frac{\mu_O}{3\Delta x}A_x, \quad S_u = -\rho_{in}u_{in}u_{in} + \frac{8\mu_O u_{in}}{3\Delta x}A_x\\

\text{West in:}\quad a_W = 0, \quad F_w = 0, \quad -S_O = \frac{3\mu_O}{\Delta x}A_x, \quad -S_E = \frac{\mu_O}{3\Delta x}A_x, \quad S_u = \rho_{in}u_{in}u_{in} + \frac{8\mu_O u_{in}}{3\Delta x}A_x\\

\text{North in:}\quad a_N = 0, \quad F_n = 0, \quad -S_O = \frac{3\mu_O}{\Delta y}A_y, \quad -S_S = \frac{\mu_O}{3\Delta y}A_y, \quad S_u = -\rho_{in}v_{in}u_{in} + \frac{8\mu_O u_{in}}{3\Delta x}A_y\\

\text{South in:}\quad a_S = 0, \quad F_s = 0, \quad -S_O = \frac{3\mu_O}{\Delta y}A_y, \quad -S_N = \frac{\mu_O}{3\Delta y}A_y, \quad S_u = \rho_{in}v_{in}u_{in} + \frac{8\mu_O u_{in}}{3\Delta x}A_y\\

a_O = a_E + a_W + a_N + a_S +\left[F_e - F_w + F_n - F_s\right] - S_O\\
a_O u_O = (a_E-S_E) u_E + (a_W-S_W) u_W + (a_N-S_N) u_N + (a_S-S_S) u_S + S^u + S_u \\

\text{East in:}\quad S^u = \left(\frac{p_W + p_O}{2} - p_O \right)A_x = \left(\frac{p_W - p_O}{2} \right)A_x\\
\text{West in:}\quad S^u = \left(p_O - \frac{p_O + p_E}{2} \right)A_x = \left(\frac{p_W - p_O}{2} \right)A_x
$$

- $Y$方向动量方程

Link Coefficient形式（$\phi^v = v$）：

$$
\text{East in:}\quad a_E = 0, \quad F_e = 0, \quad -S_O = \frac{3\mu_O}{\Delta x}A_x, \quad -S_W = \frac{\mu_O}{3\Delta x}A_x, \quad S_u = -\rho_{in}u_{in}v_{in} + \frac{8\mu_O v_{in}}{3\Delta x}A_x\\

\text{West in:}\quad a_W = 0, \quad F_w = 0, \quad -S_O = \frac{3\mu_O}{\Delta x}A_x, \quad -S_E = \frac{\mu_O}{3\Delta x}A_x, \quad S_u = \rho_{in}u_{in}v_{in} + \frac{8\mu_O v_{in}}{3\Delta x}A_x\\

\text{North in:}\quad a_N = 0, \quad F_n = 0, \quad -S_O = \frac{3\mu_O}{\Delta y}A_y, \quad -S_S = \frac{\mu_O}{3\Delta y}A_y, \quad S_u = -\rho_{in}v_{in}v_{in} + \frac{8\mu_O v_{in}}{3\Delta x}A_y\\

\text{South in:}\quad a_S = 0, \quad F_s = 0, \quad -S_O = \frac{3\mu_O}{\Delta y}A_y, \quad -S_N = \frac{\mu_O}{3\Delta y}A_y, \quad S_u = \rho_{in}v_{in}v_{in} + \frac{8\mu_O v_{in}}{3\Delta x}A_y\\

a_O = a_E + a_W + a_N + a_S +\left[F_e - F_w + F_n - F_s\right] - S_O\\
a_O v_O = (a_E-S_E) v_E + (a_W-S_W) v_W + (a_N-S_N) v_N + (a_S-S_S) v_S + S^v + S_u \\

\text{North in:}\quad S^v = \left(\frac{p_S + p_O}{2} - p_O \right)A_y = \left(\frac{p_S - p_O}{2} \right)A_y\\
\text{South in:}\quad S^v = \left( p_O - \frac{p_O + p_N}{2} \right)A_y = \left(\frac{p_O - p_N}{2} \right)A_y
$$

### Inlet (Fixed Pressure)

- $X$方向动量方程

考虑东、西、北、南四个方向压力入口的通量（$\phi^u = u$）：

$$
\begin{aligned}

J_{e}^{u} &=\rho_{e} u_{e} \phi^u_{e}-\left.\mu_{e} \frac{\partial \phi^u}{\partial x}\right|_{e} = \rho_{O}u_{O}u_{O} - \left.\mu_{e} \frac{\partial \phi^u}{\partial x}\right|_{e} \\
&\approx \rho_{O}u_{O}u_{O}-\mu_e\frac{-9 u_{O}+u_{W}+8 u_{e}}{3 \Delta x}=\rho_{O}u_{O}u_{O}-\mu_e\frac{-9 u_{O}+u_{W} + 8u_{O}}{3 \Delta x} \\

J_{w}^{u} &=\rho_{w} u_{w} \phi^u_{w}-\left.\mu_{w} \frac{\partial \phi^u}{\partial x}\right|_{w} = \rho_{O}u_{O}u_{O} - \left.\mu_{w} \frac{\partial \phi^u}{\partial x}\right|_{w} \\
&\approx \rho_{O}u_{O}u_{O} -\mu_w\frac{9 u_{O}-u_{E}-8 u_{w}}{3 \Delta x}=\rho_{O}u_{O}u_{O}-\mu_w\frac{9 u_{O}-u_{E}-8u_{O}}{3 \Delta x}\\

J_{n}^{u} &=\rho_{n} v_{n} \phi^u_{n}-\left.\mu_{n} \frac{\partial \phi^u}{\partial y}\right|_{n} = \rho_{O}v_{O}u_{O} - \left.\mu_{n} \frac{\partial \phi^u}{\partial y}\right|_{n} \\
&\approx \rho_{O}v_{O}u_{O}-\mu_n\frac{-9 u_{O}+u_{S}+8 u_{n}}{3 \Delta y}=\rho_{O}v_{O}u_{O}-\mu_n\frac{-9 u_{O}+u_{S}+8u_{O}}{3 \Delta y}\\

J_{s}^{u} &=\rho_{s} v_{s} \phi^u_{s}-\left.\mu_{s} \frac{\partial \phi^u}{\partial y}\right|_{s} = \rho_{O}v_{O}u_{O} - \left.\mu_{s} \frac{\partial \phi^u}{\partial y}\right|_{s} \\
&\approx \rho_{O}v_{O}u_{O}-\mu_s\frac{9 u_{O}-u_{N}-8 u_{s}}{3 \Delta y}=\rho_{O}v_{O}u_{O}-\mu_s\frac{9 u_{O}-u_{N}-8u_{O}}{3 \Delta y}

\end{aligned}
$$

由于压力入口并没有给定速度，因此入口速度需要通过差值得到，这里入口边界速度采用一阶近似。

压力入口压力、粘度：

$$
p_e = p_{in}, \quad \mu_e \approx \mu_O \\
p_w = p_{in}, \quad \mu_w \approx \mu_O \\
p_n = p_{in}, \quad \mu_n \approx \mu_O \\
p_s = p_{in}, \quad \mu_s \approx \mu_O \\
$$

Link coefficient形式：

$$
\text{East in:}\quad a_E = 0, \quad F_e = 0, \quad -S_O = \left(\rho_O u_O + \frac{\mu_O}{3\Delta x}\right)A_x, \quad -S_W = \frac{\mu_O}{3\Delta x}A_x, \quad S_u = 0\\

\text{West in:}\quad a_W = 0, \quad F_w = 0, \quad -S_O = \left(-\rho_O u_O + \frac{\mu_O}{3\Delta x}\right)A_x, \quad -S_E = \frac{\mu_O}{3\Delta x}A_x, \quad S_u = 0\\

\text{North in:}\quad a_N = 0, \quad F_n = 0, \quad -S_O = \left(\rho_O v_O + \frac{\mu_O}{3\Delta y}\right)A_y, \quad -S_S = \frac{\mu_O}{3\Delta y}A_y, \quad S_u = 0\\

\text{South in:}\quad a_S = 0, \quad F_s = 0, \quad -S_O = \left(-\rho_O v_O + \frac{\mu_O}{3\Delta y}\right)A_y, \quad -S_N = \frac{\mu_O}{3\Delta y}A_y, \quad S_u = 0\\

a_O = a_E + a_W + a_N + a_S +\left[F_e - F_w + F_n - F_s\right] - S_O\\
a_O u_O = (a_E-S_E) u_E + (a_W-S_W) u_W + (a_N-S_N) u_N + (a_S-S_S) u_S + S^u + S_u \\

\text{East in:}\quad S^u = \left(\frac{p_W + p_O}{2} - p_{in} \right)A_x \\
\text{West in:}\quad S^u = \left(p_{in} - \frac{p_O + p_E}{2} \right)A_x
$$

- $Y$方向动量方程

Link coefficient形式（$\phi^v = v$）：

$$
\text{East in:}\quad a_E = 0, \quad F_e = 0, \quad -S_O = \left(\rho_O u_O + \frac{\mu_O}{3\Delta x}\right)A_x, \quad -S_W = \frac{\mu_O}{3\Delta x}A_x, \quad S_u = 0\\

\text{West in:}\quad a_W = 0, \quad F_w = 0, \quad -S_O = \left(-\rho_O u_O + \frac{\mu_O}{3\Delta x}\right)A_x, \quad -S_E = \frac{\mu_O}{3\Delta x}A_x, \quad S_u = 0\\

\text{North in:}\quad a_N = 0, \quad F_n = 0, \quad -S_O = \left(\rho_O v_O + \frac{\mu_O}{3\Delta y}\right)A_y, \quad -S_S = \frac{\mu_O}{3\Delta y}A_y, \quad S_u = 0\\

\text{South in:}\quad a_S = 0, \quad F_s = 0, \quad -S_O = \left(-\rho_O v_O + \frac{\mu_O}{3\Delta y}\right)A_y, \quad -S_N = \frac{\mu_O}{3\Delta y}A_y, \quad S_u = 0\\

a_O = a_E + a_W + a_N + a_S +\left[F_e - F_w + F_n - F_s\right] - S_O\\
a_O v_O = (a_E-S_E) v_E + (a_W-S_W) v_W + (a_N-S_N) v_N + (a_S-S_S) v_S + S^v + S_u \\

\text{North in:}\quad S^v = \left(\frac{p_S + p_O}{2} - p_{in} \right)A_y \\
\text{South in:}\quad S^v = \left(p_{in} - \frac{p_O + p_N}{2} \right)A_y
$$

### Outlet (Fixed Pressure)

- $X$方向动量方程：

考虑东、西、北、南四个方向压力出口的通量（$\phi^u = u$）：

$$
\begin{aligned}

J_{e}^{u} &=\rho_{e} u_{e} \phi^u_{e}-\left.\mu_{e} \frac{\partial \phi^u}{\partial x}\right|_{e} = \rho_{O}u_{O}u_{O} - \left.\mu_{e} \frac{\partial \phi^u}{\partial x}\right|_{e}\approx \rho_{O}u_{O}u_{O} \\

J_{w}^{u} &=\rho_{w} u_{w} \phi^u_{w}-\left.\mu_{w} \frac{\partial \phi^u}{\partial x}\right|_{w} = \rho_{O}u_{O}u_{O} - \left.\mu_{w} \frac{\partial \phi^u}{\partial x}\right|_{w}\approx \rho_{O}u_{O}u_{O}\\

J_{n}^{u} &=\rho_{n} v_{n} \phi^u_{n}-\left.\mu_{n} \frac{\partial \phi^u}{\partial y}\right|_{n} = \rho_{O}v_{O}u_{O} - \left.\mu_{n} \frac{\partial \phi^u}{\partial y}\right|_{n} \approx \rho_{O}v_{O}u_{O}\\

J_{s}^{u} &=\rho_{s} v_{s} \phi^u_{s}-\left.\mu_{s} \frac{\partial \phi^u}{\partial y}\right|_{s} = \rho_{O}v_{O}u_{O} - \left.\mu_{s} \frac{\partial \phi^u}{\partial y}\right|_{s}\approx \rho_{O}v_{O}u_{O}

\end{aligned}
$$

忽略出口的粘性作用，并将出口速度近似为网格速度。

出口压力：

$$
p_e = p_{out} \\
p_w = p_{out} \\
p_n = p_{out} \\
p_s = p_{out} 
$$

Link coefficient形式：

$$
\text{East in:}\quad a_E = 0, \quad F_e = 0, \quad -S_O = \rho_O u_O A_x, \quad -S_W = 0, \quad S_u = 0\\

\text{West in:}\quad a_W = 0, \quad F_w = 0, \quad -S_O = -\rho_O u_O A_x, \quad -S_E = 0, \quad S_u = 0\\

\text{North in:}\quad a_N = 0, \quad F_n = 0, \quad -S_O = \rho_O v_O A_y, \quad -S_S = 0, \quad S_u = 0\\

\text{South in:}\quad a_S = 0, \quad F_s = 0, \quad -S_O = -\rho_O v_O A_y, \quad -S_N = 0, \quad S_u = 0\\

a_O = a_E + a_W + a_N + a_S +\left[F_e - F_w + F_n - F_s\right] - S_O\\
a_O u_O = (a_E-S_E) u_E + (a_W-S_W) u_W + (a_N-S_N) u_N + (a_S-S_S) u_S + S^u + S_u \\

\text{East out:}\quad S^u = \left(\frac{p_W + p_O}{2} - p_{out} \right)A_x \\
\text{West out:}\quad S^u = \left(p_{out} - \frac{p_O + p_E}{2} \right)A_x
$$

- $Y$方向动量方程

Link coefficient形式：

$$
\text{East in:}\quad a_E = 0, \quad -S_O = \rho_O u_O A_x, \quad -S_W = 0, \quad S_u = 0\\

\text{West in:}\quad a_W = 0, \quad -S_O = -\rho_O u_O A_x, \quad -S_E = 0, \quad S_u = 0\\

\text{North in:}\quad a_N = 0, \quad -S_O = \rho_O v_O A_y, \quad -S_S = 0, \quad S_u = 0\\

\text{South in:}\quad a_S = 0, \quad -S_O = -\rho_O v_O A_y, \quad -S_N = 0, \quad S_u = 0\\

a_O = a_E + a_W + a_N + a_S +\left[F_e - F_w + F_n - F_s\right] - S_O\\
a_O u_O = (a_E-S_E) u_E + (a_W-S_W) u_W + (a_N-S_N) u_N + (a_S-S_S) u_S + S^u + S_u \\

\text{North out:}\quad S^v = \left(\frac{p_S + p_O}{2} - p_{out} \right)A_x \\
\text{South out:}\quad S^v = \left(p_{out} - \frac{p_O + p_N}{2} \right)A_x
$$

## 压力修正方程边界

### Walls (No Slip)

对于西边界：

$$
\begin{aligned}
a_{E}^{p} &=\frac{\rho_{e}(A_x)^{2}}{2}\left[\frac{1}{\left.a_{O}\right|_{E}}+\frac{1}{\left.a_{O}\right|_{O}}\right], \quad 
a_{W}^{p} =0 \\
a_{N}^{p} &=\frac{\rho_{n}(A_y)^{2}}{2}\left[\frac{1}{\left.a_{O}\right|_{N}}+\frac{1}{\left.a_{O}\right|_{O}}\right], \quad
a_{S}^{p}=\frac{\rho_{s}(A_y)^{2}}{2}\left[\frac{1}{\left.a_{O}\right|_{S}}+\frac{1}{\left.a_{O}\right|_{O}}\right] \\
a_O^p &= a_E^p + a_W^p + a_N^p + a_S^p \\
S^{p} &=-\left[\left(\rho_{e} \hat{u}_{e}\right) A_x+\left(\rho_{n} \hat{v}_{n}-\rho_{s} \hat{v}_{s}\right) A_y\right]=-\dot{m}_\text{imbalance} \\
a_{O}^{p} &p_{O}^{\prime} = a_{E}^{p} p_{E}^{\prime}+a_{W}^{p} p_{W}^{\prime}+a_{N}^{p} p_{N}^{\prime}+a_{S}^{p} p_{S}^{\prime} + S^{p}
\end{aligned}
$$

其他边界类似，需要改变的是$a^p$和$S^p$。

### Inlet (Prescribed Velocity)

对于西边界：

$$
\begin{aligned}
a_{E}^{p} &=\frac{\rho_{e}(A_x)^{2}}{2}\left[\frac{1}{\left.a_{O}\right|_{E}}+\frac{1}{\left.a_{O}\right|_{O}}\right], \quad 
a_{W}^{p} =0 \\
a_{N}^{p} &=\frac{\rho_{n}(A_y)^{2}}{2}\left[\frac{1}{\left.a_{O}\right|_{N}}+\frac{1}{\left.a_{O}\right|_{O}}\right], \quad
a_{S}^{p}=\frac{\rho_{s}(A_y)^{2}}{2}\left[\frac{1}{\left.a_{O}\right|_{S}}+\frac{1}{\left.a_{O}\right|_{O}}\right] \\
a_O^p &= a_E^p + a_W^p + a_N^p + a_S^p \\
S^{p} &=-\left[\left(\rho_{e} \hat{u}_{e}-\rho_{in}u_{in}\right) A_x+\left(\rho_{n} \hat{v}_{n}-\rho_{s} \hat{v}_{s}\right) A_y\right]=-\dot{m}_\text{imbalance} \\
a_{O}^{p} &p_{O}^{\prime} = a_{E}^{p} p_{E}^{\prime}+a_{W}^{p} p_{W}^{\prime}+a_{N}^{p} p_{N}^{\prime}+a_{S}^{p} p_{S}^{\prime} + S^{p}
\end{aligned}
$$

其他边界类似，和上面壁面边界不同的是，$S^p$中边界速度由$0$变为$u_{in}$。

### Outlet (Fixed Pressure)

对于东边界：

$$
\begin{aligned}
a_{E}^{p} &=0, \quad 
a_{W}^{p} =\frac{\rho_{w}(A_x)^{2}}{2}\left[\frac{1}{\left.A_{O}\right|_{W}}+\frac{1}{\left.A_{O}\right|_{O}}\right] \\
a_{N}^{p} &=\frac{\rho_{n}(A_y)^{2}}{2}\left[\frac{1}{\left.a_{O}\right|_{N}}+\frac{1}{\left.a_{O}\right|_{O}}\right], \quad
a_{S}^{p}=\frac{\rho_{s}(A_y)^{2}}{2}\left[\frac{1}{\left.a_{O}\right|_{S}}+\frac{1}{\left.a_{O}\right|_{O}}\right] \\
a_O^p &= a_E^p + a_W^p + a_N^p + a_S^p - S_O\\
S^{p} &=-\left[\left(\rho_{e} \hat{u}_{e}-\rho_{w}\hat{u}_{w}\right) A_x+\left(\rho_{n} \hat{v}_{n}-\rho_{s} \hat{v}_{s}\right) A_y\right]=-\dot{m}_\text{imbalance} \\
-S_W &= -\frac{\rho_{O}(A_x)^{2}}{\left.2 A_{O}\right|_{O}},\quad -S_E=0, \quad -S_N=0, \quad -S_S=0\\
-S_O &= \frac{\rho_{O}(A_x)^{2}}{\left.2 A_{O}\right|_{O}}\\
a_{O}^{p} &p_{O}^{\prime} = (a_{E}^{p}-S_E) p_{E}^{\prime}+(a_{W}^{p}-S_W) p_{W}^{\prime}+(a_{N}^{p}-S_N) p_{N}^{\prime}+(a_{S}^{p}-S_S) p_{S}^{\prime} + S^{p}
\end{aligned}
$$

其他方向类似。

## 边界处PWIM修正

边界网格的PWIM格式需要特殊处理。

### Inlet / Wall

对于左侧速度入口 / 壁面：

$$
\begin{array}{ll}
\text { Inlet: } & \hat{u}_{w}=u_{i n} \\
\text { Wall: } & \hat{u}_{w}=0
\end{array}
$$

此时右侧速度PWIM差值需要特殊处理：

$$
\hat{u}_{e}=\frac{1}{2}\left(\hat{u}_{O}+\hat{u}_{E}\right)+\frac{1}{2} \Delta x \Delta y\left[\left.\frac{1}{\left.A_{O}\right|_{O}} \frac{\partial p}{\partial x}\right|_{O}+\left.\frac{1}{\left.A_{O}\right|_{E}} \frac{\partial p}{\partial x}\right|_{E}-\left.\left(\frac{1}{\left.A_{O}\right|_{E}}+\frac{1}{\left.A_{O}\right|_{O}}\right) \frac{\partial p}{\partial x}\right|_{e}\right] \\
\left.\frac{\partial p}{\partial x}\right|_{O}=\frac{p_{e}-p_{w}}{\Delta x}=\frac{1}{\Delta x}\left[\frac{p_{E}+p_{O}}{2}-p_{w}\right]
$$

### Outlet

对于右侧出口：

$$
\hat{u}_{e}=\hat{u}_{O}
$$

此时左侧的PWIM差值为：

$$
\hat{u}_{w}=\frac{1}{2}\left(\hat{u}_{O}+\hat{u}_{W}\right)+\frac{1}{2} \Delta x \Delta y\left[\left.\frac{1}{\left.A_{O}\right|_{O}} \frac{\partial p}{\partial x}\right|_{O}+\left.\frac{1}{\left.A_{O}\right|_{W}} \frac{\partial p}{\partial x}\right|_{W}-\left.\left(\frac{1}{\left.A_{O}\right|_{W}}+\frac{1}{\left.A_{O}\right|_{O}}\right) \frac{\partial p}{\partial x}\right|_{w}\right]\\
\left.\frac{\partial p}{\partial x}\right|_{O}=\frac{p_{e}-p_{w}}{\Delta x}=\frac{1}{\Delta x}\left[p_{{out}}-\frac{p_{W}+p_{O}}{2}\right]
$$

## 算例

### Driven Cavity

$$
\begin{aligned}
&0 \leq x \leq 1\\
&0 \leq y \leq 1\\
&\text{Let density} = 1 \, \mathrm{kg/m^3}; \\

&\text{dynamic viscosity} = 0.01 \, \mathrm{kg/m s}\\
&\text{North side moves left-to-right at } 1 \, \mathrm{m/s}.\\
&\text{Results in a Reynolds number of } 100.
\end{aligned}
$$

### Backward Facing Step Problem

![](https://md-pic-1259272405.cos.ap-guangzhou.myqcloud.com/img/20200823152548.png)

![](https://md-pic-1259272405.cos.ap-guangzhou.myqcloud.com/img/20200823153443.png)