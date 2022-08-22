# 动量方程推导

## $X$方向动量方程

对于每个网格，$X$方向的动量方程通量形式为：

$$
\left(J_{e}^{X}-J_{w}^{X}\right) \Delta y+\left(J_{n}^{X}-J_{s}^{X}\right) \Delta x=-\int_{s}^{n} \int_{w}^{e} \frac{\partial p}{\partial x} d x d y
$$

其中：

$$
J_{e}^{X}=\rho_{e} u_{e} u_{e}-\left.\mu_{e} \frac{\partial u}{\partial x}\right|_{e}\\
J_{w}^{X}=\rho_{w} u_{w} u_{w}-\left.\mu_{w} \frac{\partial u}{\partial x}\right|_{w}\\
J_{n}^{X}=\rho_{n} v_{n} u_{n}-\left.\mu_{n} \frac{\partial u}{\partial y}\right|_{n}\\
J_{s}^{X}=\rho_{s} v_{s} u_{s}-\left.\mu_{s} \frac{\partial u}{\partial y}\right|_{s}
$$

将face value表示为cell value得到：

$$
\begin{aligned}
&\left[\frac{\left|(\rho u)_{e}\right|+(\rho u)_{e}}{2} u_{O}-\frac{\left|(\rho u)_{e}\right|-(\rho u)_{e}}{2} u_{E}-\mu_{e} \frac{u_{E}-u_{O}}{\Delta x}\right] \Delta y\\
-&\left[\frac{\left|(\rho u)_{w}\right|+(\rho u)_{w}}{2} u_{W}-\frac{\left|(\rho u)_{w}\right|-(\rho u)_{w}}{2} u_{O}-\mu_{w} \frac{u_{O}-u_{W}}{\Delta x}\right] \Delta y\\
+&\left[\frac{\left|(\rho v)_{n}\right|+(\rho v)_{n}}{2} u_{O}-\frac{\left|(\rho v)_{n}\right|-(\rho v)_{n}}{2} u_{N}-\mu_{n} \frac{u_{N}-u_{O}}{\Delta y}\right] \Delta x\\
-&\left[\frac{\left|(\rho v)_{s}\right|+(\rho v)_{s}}{2} u_{S}-\frac{\left|(\rho v)_{s}\right|-(\rho v)_{s}}{2} u_{O}-\mu_{s} \frac{u_{O}-u_{S}}{\Delta y}\right] \Delta x=-\left(p_{e}-p_{w}\right) \Delta y
\end{aligned}
$$

## 对流项一阶迎风的另一种表达

其中**对流项**用的是一阶迎风格式，还有**另一种表达形式**：

$$
\begin{align}
(\rho u \phi)_{e}&=\rho_e u_e \phi_{e}=\phi_{O} \max \left(\rho_e u_e, 0\right)-\phi_{E} \max \left(-\rho_e u_e, 0\right)\\
(\rho u \phi)_{w}&=\rho_w u_w \phi_{w}=\phi_{W} \max \left(\rho_w u_w, 0\right)-\phi_{O} \max \left(-\rho_w u_w, 0\right)\\
(\rho v \phi)_{n}&=\rho_n v_n \phi_{n}=\phi_{O} \max \left(\rho_n v_n, 0\right)-\phi_{N} \max \left(-\rho_n v_n, 0\right)\\
(\rho v \phi)_{s}&=\rho_s v_s \phi_{s}=\phi_{S} \max \left(\rho_s v_s, 0\right)-\phi_{O} \max \left(-\rho_s v_s, 0\right)
\end{align}
$$

因为：

$$
\max \left(\rho_e u_e, 0\right) = \frac{\left|(\rho u)_{e}\right|+(\rho u)_{e}}{2}\qquad
\max \left(-\rho_e u_e, 0\right) = \frac{\left|(\rho u)_{e}\right|-(\rho u)_{e}}{2}\\
\max \left(\rho_w u_w, 0\right) = \frac{\left|(\rho u)_{w}\right|+(\rho u)_{w}}{2} \qquad 
\max \left(-\rho_w u_w, 0\right) = \frac{\left|(\rho u)_{w}\right|-(\rho u)_{w}}{2} \\
\max \left(\rho_n v_n, 0\right) = \frac{\left|(\rho v)_{n}\right|+(\rho v)_{n}}{2} \qquad 
\max \left(-\rho_n v_n, 0\right) = \frac{\left|(\rho v)_{n}\right|-(\rho v)_{n}}{2}\\
\max \left(\rho_s v_s, 0\right) = \frac{\left|(\rho v)_{s}\right|+(\rho v)_{s}}{2} \qquad 
\max \left(-\rho_s v_s, 0\right) = \frac{\left|(\rho v)_{s}\right|-(\rho v)_{s}}{2}
$$

对于动量方程，只需要把$\phi$替换为$u$即可。

由上面的关系，可以容易得到如下关系：

$$
\rho_e u_e + \max(-\rho_e u_e, 0) = \max(\rho_e u_e, 0), \quad \max(\rho_e u_e, 0) - \rho_e u_e = max(-\rho_e u_e, 0) \\
\rho_w u_w + \max(-\rho_w u_w, 0) = \max(\rho_w u_w, 0), \quad \max(\rho_w u_w, 0) - \rho_w u_w = max(-\rho_w u_w, 0) \\
\vdots
$$

这个关系在下面推导Link Coefficient形式会用到。

## 标量输运与动量输运的异同

可以看到，动量输运方程实际上可以看成是特殊的标量输运方程，只不过输运对象为$u$，因此在做face value差值的时候，我们只对对流项（$\rho u u$）中其中一个$u$做差值，另一个$u$依旧保留face value，认为是已知的，这个默认已知的值，只在simple算法中的outer iteration中更新，后面会具体介绍。

## Link Coefficients形式

写成Link coefficients形式：

$$
A_{O} \phi_{O}+A_{E} \phi_{E}+A_{W} \phi_{W}+A_{N} \phi_{N}+A_{S} \phi_{S}=S\\
$$

其中：

$$
\begin{aligned}
A_{E} &=-\frac{\left|(\rho u)_{e}\right|-(\rho u)_{e}}{2} \Delta y-\frac{\mu_{e}}{\Delta x} \Delta y \\
A_{W} &=-\frac{\left|(\rho u)_{w}\right|+(\rho u)_{w}}{2} \Delta y-\frac{\mu_{w}}{\Delta x} \Delta y \\
A_{N} &=-\frac{\left|(\rho v)_{n}\right|-(\rho v)_{n}}{2} \Delta x-\frac{\mu_{n}}{\Delta y} \Delta x \\
A_{S} &=-\frac{\left|(\rho v)_{s}\right|+(\rho v)_{s}}{2}\Delta x-\frac{\mu_{s}}{\Delta y} \Delta x\\
A_{O}&=-(A_E+A_W+A_N+A_S)+\left[(\rho u)_e\Delta y - (\rho u)_w\Delta y + (\rho v)_n\Delta x - (\rho v)_s\Delta x\right]
\end{aligned}
\begin{array}{l}
S^{X}=\left(p_{w}-p_{e}\right) \Delta y \\
S^{Y}=\left(p_{s}-p_{n}\right) \Delta x
\end{array}
$$

**注意**：这里给出的是interior网格的形式，对于boundary网格，需要从最原始的通量形式重新推导，以免出现错误。

# SIMPLE算法步骤与推导

## step 1：猜测初值

猜测网格初值：$u^{k}, v^{k}, p^{k}$

## step 2：计算速度face value

用cell value速度差值face value法向速度：

- 当$k=1$的，依旧用distance-weighted interpolation（$u_{e}=\frac{u_{E}+u_{O}}{2} \text { etc. }$），因为此时的压力是猜测值，不宜用PWIM差值
- 当$k\neq1$时，用上一步PWIM差值计算得到的速度face value和velocity correction，得到这一步的速度face value

## step 3：计算速度Link coefficient

- 计算X方向和Y方向动量方程的Link coefficient（They are the same）

- 计算压力：
  
  $$
  S^{X}=\left(p_{w}-p_{e}\right) \Delta y=\left(\frac{p_{O}+p_{W}}{2}-\frac{p_{O}+p_{E}}{2}\right) \Delta y=\frac{1}{2}\left(p_{W}-p_{E}\right) \Delta y\\S^{Y}=\left(p_{s}-p_{n}\right) \Delta x=\frac{1}{2}\left(p_{S}-p_{N}\right) \Delta x
  $$

## step 4：迭代求解动量方程

迭代计算动量方程，得到$u, v$

**注意**：

- 这里不需要完全收敛
- 课程中求解的是correction form + inertial damping形式，需要自己写迭代算法，这里暂时使用迭代求解器

这里可以进一步写出速度的表达式，以供后面推导使用：

$$
\hat{u}_{O}=-\frac{1}{\left.A_{O}\right|_{O}} \sum_{n b} A_{n b}\bigg|_{O} \hat{u}_{n b}\bigg|_{O}+\frac{\left(p_{W}^{(k)}-p_{E}^{(k)}\right)}{\left.2 A_{O}\right|_{O}} \Delta y \tag{1}\\
\hat{v}_{O}=-\frac{1}{\left.A_{O}\right|_{O}} \sum_{n b} A_{n b}\bigg|_{O} \hat{v}_{n b}\bigg|_{O}+\frac{\left(p_{s}^{(k)}-p_{N}^{(k)}\right)}{\left.2 A_{O}\right|_{O}} \Delta x
$$

## step 5：PWIM差值计算速度face value

用上面的式子，表达east方向的中心速度：

$$
\hat{u}_{E}=-\frac{1}{\left.A_{O}\right|_{E}} \sum_{n b} A_{n b}\bigg|_{E} \hat{u}_{n b}\bigg|_{E}+\frac{\left(p_{O}^{(k)}-p_{E E}^{(k)}\right)}{\left.2 A_{O}\right|_{E}} \Delta y \tag{2}
$$

假设east方向的面上有一个速度，可以类似地表达为：

$$
\hat{u}_{e}=-\frac{1}{\left.A_{O}\right|_{e}} \sum_{n b} A_{n b}\bigg|_{e} \hat{u}_{n b}\bigg|_{e}+\frac{\left(p_{O}^{(k)}-p_{E}^{(k)}\right)}{\left.A_{O}\right|_{e}} \Delta y \tag{3}
$$

但是上式与面相关的值（如：$A_O\big|_e$）我们都不知道，因此可以用cell value做平均：

$$
\frac{1}{\left.A_{O}\right|_{e}} \sum_{n b} A_{n b}\bigg|_{e} \hat{u}_{n b}\bigg|_{e}=\frac{1}{2}\left[\frac{1}{\left.A_{O}\right|_{E}} \sum_{n b} A_{n b}\bigg|_{E} \hat{u}_{n b}\bigg|_{E}+\frac{1}{\left.A_{O}\right|_{O}} \sum_{n b} A_{n b}\bigg|_{O} \hat{u}_{n b}\bigg|_{O}\right] \tag{4}
$$

$$
\frac{1}{\left.A_{O}\right|_{e}}=\frac{1}{2}\left[\frac{1}{\left.A_{O}\right|_{E}}+\frac{1}{\left.A_{O}\right|_{O}}\right] \tag{5}
$$

$A_O\big|_e$类似在做调和平均。

将式$(4), (5)$带入式$(3)$，得到：

$$
\hat{u}_{e}=-\frac{1}{2}\left[\frac{1}{\left.A_{O}\right|_{E}} \sum_{n b} A_{n b}\bigg|_{E} \hat{u}_{n b}\bigg|_{E}+\frac{1}{\left.A_{O}\right|_{O}} \sum_{n b} A_{n b}\bigg|_{O} \hat{u}_{n b}\bigg|_{O}\right]\\
+\left[\frac{1}{\left.A_{O}\right|_{E}}+\frac{1}{\left.A_{O}\right|_{O}}\right] \frac{\left(p_{O}^{(k)}-p_{E}^{(k)}\right)}{2} \Delta y \tag{6}
$$

利用式$(1), (2)$的关系有：

$$
-\frac{1}{\left.A_{O}\right|_{O}} \sum_{n b} A_{n b}\bigg|_{O} \hat{u}_{n b}\bigg|_{O}=\hat{u}_{O}-\frac{\left(p_{W}^{(k)}-p_{E}^{(k)}\right)}{\left.2 A_{O}\right|_{O}} \Delta y \\
-\frac{1}{\left.A_{O}\right|_{E}} \sum_{n b} A_{n b}\bigg|_{E} \hat{u}_{n b}\bigg|_{E}=\hat{u}_{E}-\frac{\left(p_{O}^{(k)}-p_{E E}^{(k)}\right)}{\left.2 A_{O}\right|_{E}} \Delta y \tag{7}
$$

将式$(7)$带入式$(6)$得到：

$$
\hat{u}_{e}=\frac{1}{2}\left[\hat{u}_{O}-\frac{\left(p_{W}^{(k)}-p_{E}^{(k)}\right)}{\left.2 A_{O}\right|_{O}} \Delta y+\hat{u}_{E}-\frac{\left(p_{O}^{(k)}-p_{E E}^{(k)}\right)}{\left.2 A_{o}\right|_{E}} \Delta y\right]+\left[\frac{1}{\left.A_{O}\right|_{E}}+\frac{1}{\left.A_{O}\right|_{O}}\right] \frac{\left(p_{O}^{(k)}-p_{E}^{(k)}\right)}{2} \Delta y
$$

整理得到：

$$
\hat{u}_{e}=\frac{1}{2}\left(\hat{u}_{O}+\hat{u}_{E}\right)+\frac{1}{2} \frac{\left(p_{E}^{(k)}-p_{W}^{(k)}\right)}{\left.2 A_{O}\right|_{O}} \Delta y+\frac{1}{2} \frac{\left(p_{E E}^{(k)}-p_{O}^{(k)}\right)}{\left.2 A_{O}\right|_{E}} \Delta y-\left[\frac{1}{\left.A_{O}\right|_{E}}+\frac{1}{\left.A_{O}\right|_{O}}\right] \frac{\left(p_{E}^{(k)}-p_{O}^{(k)}\right)}{2} \Delta y
$$

这里得到的就是**PWIM差值格式**，用来差值速度的face value。可以看到，对于同位网格，速度的face value除了用cell value平均，还得额外加上压力的影响。

**注意**：这个差值格式只在$k>1$以后才开始使用，第一次迭代只用简单的平均。

为了进一步推导方便，将上式写成微分形式：

$$
\hat{u}_{e}=\frac{1}{2}\left(\hat{u}_{O}+\hat{u}_{E}\right)+\frac{1}{2} \Delta x \Delta y\left[\left.\frac{1}{\left.A_{O}\right|_{O}} \frac{\partial p^{(k)}}{\partial x}\right|_{O}+\left.\frac{1}{\left.A_{O}\right|_{E}} \frac{\partial p^{(k)}}{\partial x}\right|_{E}-\left.\left(\frac{1}{\left.A_{O}\right|_{E}}+\frac{1}{\left.A_{O}\right|_{O}}\right) \frac{\partial p^{(k)}}{\partial x}\right|_{e}\right]
$$

类似Y方向的速度：

$$
\hat{v}_{n}=\frac{1}{2}\left(\hat{v}_{O}+\hat{v}_{N}\right)+\frac{1}{2} \frac{\left(p_{N}^{(k)}-p_{S}^{(k)}\right)}{\left.2 A_{O}\right|_{O}} \Delta x+\frac{1}{2} \frac{\left(p_{N N}^{(k)}-p_{O}^{(k)}\right)}{\left.2 A_{O}\right|_{N}} \Delta x-\left[\frac{1}{\left.A_{O}\right|_{N}}+\frac{1}{\left.A_{O}\right|_{O}}\right] \frac{\left(p_{N}^{(k)}-p_{O}^{(k)}\right)}{2} \Delta x\\

\hat{v}_{n}=\frac{1}{2}\left(\hat{v}_{O}+\hat{v}_{N}\right)+\frac{1}{2} \Delta x \Delta y\left[\left.\frac{1}{\left.A_{O}\right|_{O}} \frac{\partial p^{(k)}}{\partial y}\right|_{O}+\left.\frac{1}{\left.A_{O}\right|_{N}} \frac{\partial p^{(k)}}{\partial y}\right|_{N}-\left.\left(\frac{1}{\left.A_{O}\right|_{N}}+\frac{1}{\left.A_{O}\right|_{O}}\right) \frac{\partial p^{(k)}}{\partial y}\right|_{n}\right]
$$

**注**：PWIM差值在编程的时候可以封装一个函数

## step 6：velocity correction equation

接下来推导velocity correction equation

**注意**：这里既需要修正cell value，也需要修正face value

- cell value修正
  
  这里认为两次outer iteration之间速度差值为$u'$：

$$
\hat{u}_{O}=-\frac{1}{\left.A_{O}\right|_{O}} \sum_{n b} A_{n b}\bigg|_{O} \hat{u}_{n b}\bigg|_{O}+\frac{\left(p_{W}^{(k)}-p_{E}^{(k)}\right)}{\left.2 A_{O}\right|_{O}} \Delta y \\

\hat{\hat{u}}_{O}=-\frac{1}{\left.A_{O}\right|_{O}} \sum_{n b} A_{n b}\bigg|_{O} \hat{\hat{u}}_{n b}\bigg|_{O}+\frac{\left(p_{W}^{(k+1)}-p_{E}^{(k+1)}\right)}{\left.2 A_{O}\right|_{O}} \Delta y \\

u_{O}^{\prime}=\hat{\hat{u}}_{O}-\hat{u}_{O}=-\frac{1}{\left.A_{O}\right|_{O}} \sum_{n b} A_{n b}\bigg|_{O} u_{n b}^{\prime}\bigg|_{O}+\frac{\left(p_{W}^{\prime}-p_{E}^{\prime}\right)}{\left.2 A_{O}\right|_{O}} \Delta y
$$

  将$-\frac{1}{\left.A_{O}\right|_{O}} \sum_{n b} A_{n b}\big|_{O} u_{n b}^{\prime}\big|_{O}$忽略。因此有：

$$
u_{O}^{\prime}=\frac{\left(p_{W}^{\prime}-p_{E}^{\prime}\right)}{\left.2 A_{O}\right|_{O}} \Delta y \quad \text { and } \quad v_{O}^{\prime}=\frac{\left(p_{S}^{\prime}-p_{N}^{\prime}\right)}{\left.2 A_{O}\right|_{O}} \Delta x
$$

- face value修正
  
  和上面步骤类似：

$$
\hat{u}_{e}=\frac{1}{2}\left[\hat{u}_{O}-\frac{\left(p_{W}^{(k)}-p_{E}^{(k)}\right)}{\left.2 A_{O}\right|_{O}} \Delta y+\hat{u}_{E}-\frac{\left(p_{O}^{(k)}-p_{E E}^{(k)}\right)}{\left.2 A_{o}\right|_{E}} \Delta y\right]
+\left[\frac{1}{\left.A_{O}\right|_{E}}+\frac{1}{\left.A_{O}\right|_{O}}\right] \frac{\left(p_{O}^{(k)}-p_{E}^{(k)}\right)}{2} \Delta y\\

\hat{\hat{u}}_{e}=\frac{1}{2}\left[\hat{\hat{u}}_{O}-\frac{\left(p_{W}^{(k+1)}-p_{E}^{(k+1)}\right)}{\left.2 A_{O}\right|_{O}} \Delta y+\hat{\hat{u}}_{E}-\frac{\left(p_{O}^{(k+1)}-p_{E E}^{(k+1)}\right)}{\left.2 A_{O}\right|_{E}} \Delta y\right]\\
+\left[\frac{1}{\left.A_{O}\right|_{E}}+\frac{1}{\left.A_{O}\right|_{O}}\right] \frac{\left(p_{O}^{(k+1)}-p_{E}^{(k+1)}\right)}{2} \Delta y 
$$

  相减得到：

$$
u_{e}^{\prime}=\hat{\hat{u}}_{e}-\hat{u}_{e}\\
=\frac{1}{2}\left[u_{O}^{\prime}-\frac{\left(p_{W}^{\prime}-p_{E}^{\prime}\right)}{\left.2 A_{O}\right|_{O}} \Delta y+u_{E}^{\prime}-\frac{\left(p_{O}^{\prime}-p_{E E}^{\prime}\right)}{\left.2 A_{O}\right|_{E}} \Delta y\right]+\left[\frac{1}{\left.A_{O}\right|_{E}}+\frac{1}{\left.A_{O}\right|_{O}}\right] \frac{\left(p_{O}^{\prime}-p_{E}^{\prime}\right)}{2} \Delta y
$$

  进一步化简得到：

$$
u_{e}^{\prime}=\left[\frac{1}{\left.A_{O}\right|_{E}}+\frac{1}{\left.A_{O}\right|_{O}}\right] \frac{\left(p_{O}^{\prime}-p_{E}^{\prime}\right)}{2} \Delta y
$$

  类似地：

$$
v_{n}^{\prime}=\left[\frac{1}{\left.A_{O}\right|_{N}}+\frac{1}{\left.A_{O}\right|_{O}}\right] \frac{\left(p_{O}^{\prime}-p_{N}^{\prime}\right)}{2} \Delta x
$$

## step 7：pressure correction equation

推导pressure correction equation

由连续性方程有：

$$
\begin{array}{l}
\left(\rho_{e} \hat{\hat{u}}_{e}-\rho_{w} \hat{\hat{u}}_{w}\right) \Delta y+\left(\rho_{n} \hat{\hat{v}}_{n}-\rho_{s} \hat{v}_{s}\right) \Delta x&=0 \\
\left(\rho_{e} u_{e}^{\prime}-\rho_{w} u_{w}^{\prime}\right) \Delta y+\left(\rho_{n} v_{n}^{\prime}-\rho_{s} v_{s}^{\prime}\right) \Delta x&= \\
-\left[\left(\rho_{e} \hat{u}_{e}-\rho_{w} \hat{u}_{w}\right) \Delta y+\left(\rho_{n} \hat{v}_{n}-\rho_{s} \hat{v}_{s}\right) \Delta x\right]&=-\dot{m}_\text{imbalance}
\end{array}
$$

将step 6推导的结果带入得到：

$$
\left(\rho_{e}\left[\frac{1}{\left.A_{O}\right|_{E}}+\frac{1}{\left.A_{o}\right|_{o}}\right] \frac{\left(p_{O}^{\prime}-p_{E}^{\prime}\right)}{2}-\rho_{w}\left[\frac{1}{\left.A_{O}\right|_{W}}+\frac{1}{\left.A_{O}\right|_{O}}\right] \frac{\left(p_{W}^{\prime}-p_{O}^{\prime}\right)}{2} \right)(\Delta y)^{2}+ \\
\left(\rho_{n}\left[\frac{1}{\left.A_{O}\right|_{N}}+\frac{1}{\left.A_{O}\right|_{O}}\right] \frac{\left(p_{O}^{\prime}-p_{N}^{\prime}\right)}{2}-\rho_{s}\left[\frac{1}{\left.A_{O}\right|_{S}}+\frac{1}{\left.A_{O}\right|_{O}}\right] \frac{\left(p_{S}^{\prime}-p_{O}^{\prime}\right)}{2}\right)(\Delta x)^{2}=-\dot{m}_\text{imbalance}
$$

写成Link coefficients形式：

$$
A_{O}^{p} p_{O}^{\prime}+A_{E}^{p} p_{E}^{\prime}+A_{W}^{p} p_{W}^{\prime}+A_{N}^{p} p_{N}^{\prime}+A_{S}^{p} p_{S}^{\prime}=A_{O}^{p} p_{O}^{\prime}+\sum_{n b} A_{n b}^{p} p_{n b}^{\prime}=S_{O}^{p}
$$

其中：

$$
A_{E}^{p}=-\frac{\rho_{e}(\Delta y)^{2}}{2}\left[\frac{1}{\left.A_{O}\right|_{E}}+\frac{1}{\left.A_{O}\right|_{O}}\right], A_{W}^{p}=-\frac{\rho_{w}(\Delta y)^{2}}{2}\left[\frac{1}{\left.A_{O}\right|_{W}}+\frac{1}{\left.A_{O}\right|_{O}}\right] \\
A_{N}^{p}=-\frac{\rho_{n}(\Delta x)^{2}}{2}\left[\frac{1}{\left.A_{O}\right|_{N}}+\frac{1}{\left.A_{O}\right|_{O}}\right], A_{S}^{p}=-\frac{\rho_{s}(\Delta x)^{2}}{2}\left[\frac{1}{\left.A_{O}\right|_{S}}+\frac{1}{\left.A_{O}\right|_{O}}\right] \\
A_O^p = -(A_E^p + A_W^p + A_N^p + A_S^p) \\
S_{O}^{p}=-\left[\left(\rho_{e} \hat{u}_{e}-\rho_{w} \hat{u}_{w}\right) \Delta y+\left(\rho_{n} \hat{v}_{n}-\rho_{s} \hat{v}_{s}\right) \Delta x\right]=-\dot{m}_\text{imbalance}
$$

## step 8：压力、速度修正

修正压力和速度：

- cell value

$$
p_{O}^{(k+1)}=p_{O}^{(k)}+\omega_{p} p_{O}^{\prime} \\

u_{O}^{(k+1)}=\hat{u}_{O}+\omega_{u v} u_{O}^{\prime}=\hat{u}_{O}+\omega_{u w} \frac{\left(p_{W}^{\prime}-p_{E}^{\prime}\right)}{\left.2 A_{O}\right|_{O}} \Delta y \\

v_{O}^{(k+1)}=\hat{v}_{O}+\omega_{u v} v_{O}^{\prime}=\hat{v}_{O}+\omega_{u w} \frac{\left(p_{S}^{\prime}-p_{N}^{\prime}\right)}{\left.2 A_{O}\right|_{O}} \Delta x
$$

- face value

$$
u_{e}^{(k+1)}=\hat{u}_{e}+\omega_{uv} u_{e}^{\prime}=\hat{u}_{e}+\omega_{uv}\left[\frac{1}{\left.A_{O}\right|_{E}}+\frac{1}{\left.A_{O}\right|_{O}}\right] \frac{\left(p_{O}^{\prime}-p_{E}^{\prime}\right)}{2} \Delta y \\

v_{n}^{(k+1)}=\hat{v}_{n}+\omega_{uv} v_{n}^{\prime}=\hat{v}_{n}+\omega_{uv}\left[\frac{1}{\left.A_{O}\right|_{N}}+\frac{1}{\left.A_{O}\right|_{O}}\right] \frac{\left(p_{O}^{\prime}-p_{N}^{\prime}\right)}{2} \Delta x
$$

  需要注意，对于边界条件给定了速度的face value的时候，就不需要对边界面进行差值了

  **注意**：编程的时候，这里的face value需要保存，以供下一次outer iteration计算Link coefficient时使用。

  课程中提到，有些人编程会直接保存$\mathbf{U}_\text{face}\cdot\mathbf{n}_\text{face}$这个标量，对于正交网格，有如下关系：

$$
\mathbf U_e \cdot \mathbf n_e = u_e, \quad
\mathbf U_w \cdot \mathbf n_w = -u_w, \quad
\mathbf U_n \cdot \mathbf n_n = v_n, \quad
\mathbf U_s \cdot \mathbf n_s = -v_s
$$

  因此对于正交网格，保存速度值即可。

## SIMPLE流程图

![](https://md-pic-1259272405.cos.ap-guangzhou.myqcloud.com/img/2020-08-21_161754.png)

# 边界条件

## Momentum Equations, Walls (No slip)

![](https://md-pic-1259272405.cos.ap-guangzhou.myqcloud.com/img/20200822193030.png)

假如壁面在左侧，考虑$X$方向动量方程，从通量形式开始推导：

$$
\left(J_{e}^{X}-J_{w}^{X}\right) \Delta y+\left(J_{n}^{X}-J_{s}^{X}\right) \Delta x=-\left(p_{e}-p_{w}\right) \Delta y \\

J_{w}^{X}=\rho_{w} u_{w} u_{w}-\left.\mu_{w} \frac{\partial u}{\partial x}\right|_{w} = 0 - \left.\mu_{w} \frac{\partial u}{\partial x}\right|_{w}
$$

课程中扩散项给出了二阶形式：

$$
\left.\frac{\partial u}{\partial x}\right|_{w} \approx \frac{9 u_{O}-u_{E}-8 u_{w}}{3 \Delta x}=\frac{9 u_{O}-u_{E}}{3 \Delta x}
$$

如果用一阶格式：

$$
\left.\frac{\partial u}{\partial x}\right|_{w} \approx \frac{u_O - u_w}{\Delta x / 2}
$$

压力的face value：

$$
p_{e}=\left(p_{O}+p_{E}\right) / 2 \\
p_{w} \approx p_{O}
$$

**注意**：通过量纲分析可以得出，壁面法向压降相对流动方向压降可以忽略不计，因此这里有上式的关系。

粘度系数的face value用一阶近似：

$$
\mu_w \approx \mu_O
$$

Link coefficient形式：

$$
\begin{aligned}{}
A_{E} &=-\frac{\left|(\rho u)_{e}\right|-(\rho u)_{e}}{2} \Delta y-\frac{\mu_{e}}{\Delta x} \Delta y-\frac{\mu_{O}}{3 \Delta x} \Delta y \\

A_{W} &=0 \\

A_{N} &=-\frac{\left|(\rho v)_{n}\right|-(\rho v)_{n}}{2} \Delta x-\frac{\mu_{n}}{\Delta y} \Delta x \\

A_{S} &=-\frac{\left|(\rho v)_{s}\right|+(\rho v)_{s}}{2} \Delta x-\frac{\mu_{s}}{\Delta y} \Delta x \\

A_{O} &=\frac{\left|(\rho u)_{e}\right|+(\rho u)_{e}}{2} \Delta y+\frac{\mu_{e}}{\Delta x} \Delta y+\frac{3 \mu_{O}}{\Delta x} \Delta y \\
&+\frac{\left|(\rho v)_{n}\right|+(\rho v)_{n}}{2} \Delta x+\frac{\mu_{n}}{\Delta y} \Delta x+\frac{\left|(\rho v)_{s}\right|-(\rho v)_{s}}{2} \Delta x+\frac{\mu_{s}}{\Delta y} \Delta x\\

A_{O} & u_{O}+A_{E} u_{E}+A_{N} u_{N}+A_{S} u_{S}=S^{X} \\
S^{X} &= \left(p_{O}-\frac{p_{O}+p_{E}}{2}\right) \Delta y

\end{aligned}
$$

## Momentum Equations, Inlet (Fixed velocity)

![](https://md-pic-1259272405.cos.ap-guangzhou.myqcloud.com/img/20200822201615.png)

假设速度入口在左侧，考虑$X$方向动量方程，从通量形式开始推导：

$$
\begin{aligned}
\left(J_{e}^{X}-J_{w}^{X}\right) \Delta y+\left(J_{n}^{X}-J_{s}^{X}\right) \Delta x=-\left(p_{e}-p_{w}\right) \Delta y \\
J_{w}^{X}=\rho_{w} u_{w} u_{w}-\left.\mu_{w} \frac{\partial u}{\partial x}\right|_{w}=\rho_{i n} u_{i n} u_{i n}-\left.\mu_{i n} \frac{\partial u}{\partial x}\right|_{i n}
\end{aligned}
$$

扩散项二阶近似：

$$
\left.\frac{\partial u}{\partial x}\right|_{i n} \approx \frac{9 u_{O}-u_{E}-8 u_{w}}{3 \Delta x}=\frac{9 u_{0}-u_{E}-8 u_{i n}}{3 \Delta x}
$$

一阶近似为：

$$
\left.\frac{\partial u}{\partial x}\right|_{i n} \approx \frac{u_O - u_{in}}{\Delta x / 2}
$$

压力的face value：

$$
p_{e} = \left(p_{O}+p_{E}\right) / 2 \qquad 2^\text{nd}\text{ order  accurate!}\\
p_{w} \approx p_{O} \qquad \qquad \qquad 1^\text{st}\text{ order  accurate!} \\
p_{w} = \frac{3}{2} p_{O}-\frac{1}{2} p_{E} \qquad 2^\text{nd}\text{ order  accurate!}
$$

课程中提到，这里壁面压力为了方便，通常大家只用一阶精度，可以通过增加壁面网格层数减小误差。

## Momentum Equations, Inlet (Fixed pressure)

![](https://md-pic-1259272405.cos.ap-guangzhou.myqcloud.com/img/20200822205053.png)

压力的face value已知：

$$
p_{w}=p_{i n}
$$

速度的face value：

$$
u_{w}=u_{O} \qquad \qquad 1^{\text {st }} \text{order accurate!} \\
u_{w}=\frac{3}{2} u_{O}-\frac{1}{2} u_{E} \quad 2^{\text {nd }} \text { order accurate! }
$$

**注意**：对于给定压力边界的情况，边界速度是不知道的，迭代过程中也会不断变化，最终收敛时趋于稳定。

## Momentum Equations, outlet (Fixed pressure)

CFD中，出口的速度既可以流入，也可以流出，通常**速度**具体值我们也**无法直接给出**，只能给出压力，而且通常只知道出口的**压力单一值**，而不知道面上的**压力分布**，因此，出口的位置选择就很重要了，要保证出口位置是**充分发展段**，此时截面压力才能假设为单一值，否则会出现**回流问题**，而且计算结果会有问题（即使收敛）。

![](https://md-pic-1259272405.cos.ap-guangzhou.myqcloud.com/img/20200822212229.png)

假设出口在右侧，$X$方向动量方程通量形式为：

$$
\left(J_{e}^{X}-J_{w}^{X}\right) \Delta y+\left(J_{n}^{X}-J_{s}^{X}\right) \Delta x=-\left(p_{e}-p_{w}\right) \Delta y
$$

出口通量：

$$
J_{e}^{X}=\rho_{e} u_{e} u_{e}-\left.\mu_{e} \frac{\partial u}{\partial x}\right|_{e}
$$

忽略出口粘性作用，并且将出口速度近似为网格中心速度，出口通量通常简化为：

$$
J_{e}^{X}=\rho_{O} u_{O} u_{O}
$$

这里我们实际上采用了一阶迎风格式，且认为速度是从出口流出，如果真实情况产生回流，这样的假设就不再成立，计算结果也不可靠。因此一定要将出口放在充分发展段。

压力的face value：

$$
\begin{aligned}
p_{w} &=\frac{p_{W}+p_{o}}{2} \\
p_{e} &=p_{out} \qquad \text{(prescribed BC)}
\end{aligned}
$$

Link coefficient形式：

$$
\begin{aligned}
A_{E} &=0 \\
A_{W} &=-\frac{\left|(\rho u)_{w}\right|+(\rho u)_{w}}{2} \Delta y-\frac{\mu_{w}}{\Delta x} \Delta y \\
A_{N} &=-\frac{\left|(\rho v)_{n}\right|-(\rho v)_{n}}{2} \Delta x-\frac{\mu_{n}}{\Delta y} \Delta x \\
A_{S} &=-\frac{\left|(\rho v)_{s}\right|+(\rho v)_{s}}{2} \Delta x-\frac{\mu_{s}}{\Delta y} \Delta x \\

A_{O} &=\rho_{O} u_{O}+\frac{\left|(\rho u)_{w}\right|-(\rho u)_{w}}{2} \Delta y+\frac{\mu_{w}}{\Delta x} \Delta y+\\
&+\frac{\left|(\rho v)_{n}\right|+(\rho v)_{n}}{2} \Delta x+\frac{\mu_{n}}{\Delta y} \Delta x+\frac{\left|(\rho v)_{s}\right|-(\rho v)_{s}}{2} \Delta x+\frac{\mu_{s}}{\Delta y} \Delta x \\


A_{O} & u_{O}+A_{W} u_{W}+A_{N} u_{N}+A_{S} u_{S}=S^{X} \\
S^{X} &=\left(\frac{p_{O}+p_{W}}{2}-p_{{out}}\right) \Delta y


\end{aligned}
$$

## Pressure Correction Equations, Walls (No slip)

![](https://md-pic-1259272405.cos.ap-guangzhou.myqcloud.com/img/20200822220740.png)

由于压力修正方程是以连续性方程为约束条件，因此从连续性方程出发：

$$
\left(\rho_{e} \hat{\hat{u}}_{e}-\rho_{w} \hat{\hat{u}}_{w}\right) \Delta y+\left(\rho_{n} \hat{\hat{v}}_{n}-\rho_{s} \hat{\hat{v}}_{s}\right) \Delta x=0
$$

对于壁面$\hat{\hat{u}}_w = 0$，因此壁面处网格的压力修正方程的Link coefficient形式为：

$$
\begin{aligned}
A_{O}^{p} &=\frac{\rho_{e}(\Delta y)^{2}}{2}\left[\frac{1}{\left.A_{O}\right|_{E}}+\frac{1}{\left.A_{O}\right|_{O}}\right]+\frac{\rho_{n}(\Delta x)^{2}}{2}\left[\frac{1}{\left.A_{O}\right|_{N}}+\frac{1}{\left.A_{O}\right|_{O}}\right]+\frac{\rho_{s}(\Delta x)^{2}}{2}\left[\frac{1}{\left.A_{O}\right|_{S}}+\frac{1}{\left.A_{O}\right|_{O}}\right] \\


A_{E}^{p} &=-\frac{\rho_{e}(\Delta y)^{2}}{2}\left[\frac{1}{\left.A_{O}\right|_{E}}+\frac{1}{\left.A_{O}\right|_{O}}\right]\\
A_{W}^{p} &=0 \\
A_{N}^{p} &=-\frac{\rho_{n}(\Delta x)^{2}}{2}\left[\frac{1}{\left.A_{O}\right|_{N}}+\frac{1}{\left.A_{O}\right|_{O}}\right]\\
A_{s}^{p} &=-\frac{\rho_{s}(\Delta x)^{2}}{2}\left[\frac{1}{\left.A_{O}\right|_{S}}+\frac{1}{\left.A_{O}\right|_{O}}\right] \\
S_{O}^{P} &=-\left[\left(\rho_{e} \hat{u}_{e}\right) \Delta y+\left(\rho_{n} \hat{v}_{n}-\rho_{s} \hat{v}_{s}\right) \Delta x\right]=-\dot{m}_{i m b a l a n c e}
\end{aligned}
$$

## Pressure Correction Equations, Inlet (Prescribed Velocity)

![](https://md-pic-1259272405.cos.ap-guangzhou.myqcloud.com/img/20200822222324.png)

同样从连续性方程出发：

$$
\left(\rho_{e} \hat{\hat{u}}_{e}-\rho_{w} \hat{\hat{u}}_{w}\right) \Delta y+\left(\rho_{n} \hat{\hat{v}}_{n}-\rho_{s} \hat{\hat{v}}_{s}\right) \Delta x=0
$$

对于速度入口处网格，有$\rho_w \hat{\hat{u}}_w = \rho_{in} u_{in}$，因此速度入口处网格的压力修正方程的Link coefficient形式为：

$$
\begin{aligned}
A_{O}^{p} &=\frac{\rho_{e}(\Delta y)^{2}}{2}\left[\frac{1}{\left.A_{O}\right|_{E}}+\frac{1}{\left.A_{O}\right|_{O}}\right]+\frac{\rho_{n}(\Delta x)^{2}}{2}\left[\frac{1}{\left.A_{O}\right|_{N}}+\frac{1}{\left.A_{O}\right|_{O}}\right]+\frac{\rho_{s}(\Delta x)^{2}}{2}\left[\frac{1}{\left.A_{O}\right|_{S}}+\frac{1}{\left.A_{O}\right|_{O}}\right] \\

A_{E}^{p} &=-\frac{\rho_{e}(\Delta y)^{2}}{2}\left[\frac{1}{\left.A_{o}\right|_{E}}+\frac{1}{\left.A_{o}\right|_{o}}\right] \\
A_{W}^{p} &=0 \\
A_{N}^{p} &=-\frac{\rho_{n}(\Delta x)^{2}}{2}\left[\frac{1}{\left.A_{O}\right|_{N}}+\frac{1}{\left.A_{O}\right|_{O}}\right]\\
A_{S}^{p} &=-\frac{\rho_{s}(\Delta x)^{2}}{2}\left[\frac{1}{\left.A_{O}\right|_{S}}+\frac{1}{\left.A_{O}\right|_{O}}\right] \\
S_{o}^{P} &=-\left[\left(\rho_{e} \hat{u}_{e}-\rho_{i n} u_{i n}\right) \Delta y+\left(\rho_{n} \hat{v}_{n}-\rho_{s} \hat{v}_{s}\right) \Delta x\right]=-\dot{m}_{i m b a l a n c e}
\end{aligned}
$$

**注意**：边界处的velocity correction永远为$0$

## Pressure Correction Equations, Outlet (Fixed Pressure)

![](https://md-pic-1259272405.cos.ap-guangzhou.myqcloud.com/img/20200822225702.png)

从连续性方程出发：

$$
\left(\rho_{e} \hat{\hat{u}}_{e}-\rho_{w} \hat{\hat{u}}_{w}\right) \Delta y+\left(\rho_{n} \hat{\hat{v}}_{n}-\rho_{s} \hat{\hat{v}}_{s}\right) \Delta x=0
$$

对于真正的出口，应该有$\rho_{e} \hat{\hat{u}}_{e}=\rho_{O} \hat{\hat{u}}_{O}$，因此：

$$
\left(\rho_{O} \hat{\hat{u}}_{O}-\rho_{w} \hat{\hat{u}}_{w}\right) \Delta y+\left(\rho_{n} \hat{\hat{v}}_{n}-\rho_{s} \hat{\hat{v}}_{s}\right) \Delta x=0 \\

\left(\rho_{O} u_{O}^{\prime}-\rho_{w} u_{w}^{\prime}\right) \Delta y+\left(\rho_{n} v_{n}^{\prime}-\rho_{s} v_{s}^{\prime}\right) \Delta x=-\left[\left(\rho_{O} \hat{u}_{O}-\rho_{w} \hat{u}_{w}\right) \Delta y+\left(\rho_{n} \hat{v}_{n}-\rho_{s} \hat{v}_{s}\right) \Delta x\right]
$$

其中：

$$
\begin{aligned}
u_{O}^{\prime} &=\frac{\Delta y}{\left.A_{O}\right|_{O}}\left(p_{w}^{\prime}-p_{e}^{\prime}\right)=\frac{\Delta y}{\left.A_{O}\right|_{O}}\left(\frac{p_{W}^{\prime}+p_{O}^{\prime}}{2}-p_{e}^{\prime}\right)=\frac{\Delta y}{\left.A_{O}\right|_{O}}\left(\frac{p_{W}^{\prime}+p_{O}^{\prime}}{2}-0\right) \\

u_{w}^{\prime} &=\left[\frac{1}{\left.A_{O}\right|_{W}}+\frac{1}{\left.A_{O}\right|_{O}}\right] \frac{\left(p_{W}^{\prime}-p_{O}^{\prime}\right)}{2} \Delta y \quad \text { etc. }
\end{aligned}
$$

注意到，$u_O'$需要特殊处理，即出口的压力保持不变，因此压力修正为$0$，其他方向保持不变。

因此压力修正方程，在压力出口处网格的Link coefficient形式为：

$$
\begin{aligned}
A_{W}^{p} &=-\frac{\rho_{w}(\Delta y)^{2}}{2}\left[\frac{1}{\left.A_{O}\right|_{W}}+\frac{1}{\left.A_{O}\right|_{O}}\right]+\frac{\rho_{O}(\Delta y)^{2}}{\left.2 A_{O}\right|_{O}}\\

A_{E}^{p} &=0 \\

A_{N}^{p} &=-\frac{\rho_{n}(\Delta x)^{2}}{2}\left[\frac{1}{\left.A_{O}\right|_{N}}+\frac{1}{\left.A_{O}\right|_{O}}\right] \\

A_{S}^{p} &=-\frac{\rho_{s}(\Delta x)^{2}}{2}\left[\frac{1}{\left.A_{O}\right|_{S}}+\frac{1}{\left.A_{O}\right|_{O}}\right] \\


A_{O}^{p} &=\frac{\rho_{w}(\Delta y)^{2}}{2}\left[\frac{1}{\left.A_{O}\right|_{W}}+\frac{1}{\left.A_{O}\right|_{O}}\right]+\frac{\rho_{O}(\Delta y)^{2}}{\left.2 A_{O}\right|_{O}} \\
&+\frac{\rho_{n}(\Delta x)^{2}}{2}\left[\frac{1}{\left.A_{O}\right|_{N}}+\frac{1}{\left.A_{O}\right|_{O}}\right]+\frac{\rho_{s}(\Delta x)^{2}}{2}\left[\frac{1}{\left.A_{O}\right|_{S}}+\frac{1}{\left.A_{O}\right|_{O}}\right]

\end{aligned}
$$

**注意**：压力出口处的Link coefficient**不再满足**$A_O = -(A_W + A_E + A_N + A_S)$，$\frac{\rho_{O}(\Delta y)^{2}}{\left.2 A_{O}\right|_{O}}$这一项在$A_O$和$A_W$中前面都是正号。

# PWIM格式计算边界速度

## Inlet / Wall

![](https://md-pic-1259272405.cos.ap-guangzhou.myqcloud.com/img/20200823145305.png)

左侧边界速度直接根据边界条件给出：

$$
\begin{array}{ll}
\text { Inlet: } & \hat{u}_{w}=u_{i n} \\
\text { Wall: } & \hat{u}_{w}=0
\end{array}
$$

右侧速度根据前面推导的结果：

$$
\hat{u}_{e}=\frac{1}{2}\left(\hat{u}_{O}+\hat{u}_{E}\right)+\frac{1}{2} \Delta x \Delta y\left[\left.\frac{1}{\left.A_{O}\right|_{O}} \frac{\partial p}{\partial x}\right|_{O}+\left.\frac{1}{\left.A_{O}\right|_{E}} \frac{\partial p}{\partial x}\right|_{E}-\left.\left(\frac{1}{\left.A_{O}\right|_{E}}+\frac{1}{\left.A_{O}\right|_{O}}\right) \frac{\partial p}{\partial x}\right|_{e}\right]
$$

其中$\left. \frac{\partial p}{\partial x} \right|_O$无法再通过左右两侧的网格中心压力计算出来，因为左侧为边界，没有网格，因此这里我们用face value计算：

$$
\left.\frac{\partial p}{\partial x}\right|_{O}=\frac{p_{e}-p_{w}}{\Delta x}=\frac{1}{\Delta x}\left[\frac{p_{E}+p_{O}}{2}-p_{w}\right]
$$

左侧压力如果采用一阶精度有：

$$
p_{w}=p_{O}
$$

**注意**：这里边界$p_w$使用的阶数需要和动量方程保持一致。

## Outlet

![](https://md-pic-1259272405.cos.ap-guangzhou.myqcloud.com/img/20200823150627.png)

右侧出口边界速度由一阶迎风给出：

$$
\hat{u}_{e}=\hat{u}_{O}
$$

左侧速度PWIM格式：

$$
\hat{u}_{w}=\frac{1}{2}\left(\hat{u}_{O}+\hat{u}_{W}\right)+\frac{1}{2} \Delta x \Delta y\left[\left.\frac{1}{\left.A_{O}\right|_{O}} \frac{\partial p}{\partial x}\right|_{O}+\left.\frac{1}{\left.A_{O}\right|_{W}} \frac{\partial p}{\partial x}\right|_{W}-\left.\left(\frac{1}{\left.A_{O}\right|_{W}}+\frac{1}{\left.A_{O}\right|_{O}}\right) \frac{\partial p}{\partial x}\right|_{w}\right]
$$

同样地，$\left. \frac{\partial p}{\partial x} \right|_O$也无法用两侧cell value求出，因此只能用face value求得：

$$
\left.\frac{\partial p}{\partial x}\right|_{O}=\frac{p_{e}-p_{w}}{\Delta x}=\frac{1}{\Delta x}\left[p_{{out}}-\frac{p_{W}+p_{O}}{2}\right]
$$

**注意**：不要计算两次face value，相邻网格只要有一个计算了face value就可以了。

# 算例

![](https://md-pic-1259272405.cos.ap-guangzhou.myqcloud.com/img/20200823152548.png)

![](https://md-pic-1259272405.cos.ap-guangzhou.myqcloud.com/img/20200823153443.png)
