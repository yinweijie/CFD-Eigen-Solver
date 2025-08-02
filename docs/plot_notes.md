# Python科学绘图技巧详解

本笔记基于CFD数据可视化脚本，详细介绍Python绘图中的关键技巧和数据处理方法。

## 1. 库导入和后端设置

### 1.1 matplotlib后端设置
```python
import matplotlib
matplotlib.use('Agg')  # 使用非交互式后端
```

**技巧解释：**
- `Agg`后端：Anti-Grain Geometry，用于生成光栅图像（PNG、JPG等）
- 非交互式后端：不显示图形窗口，适合服务器环境或批量处理
- 其他常用后端：`TkAgg`（交互式）、`Qt5Agg`（交互式）

### 1.2 中文字体配置
```python
plt.rcParams['font.sans-serif'] = ['SimHei', 'DejaVu Sans', 'Arial Unicode MS', 'Liberation Sans']
plt.rcParams['axes.unicode_minus'] = False
```

**技巧解释：**
- `rcParams`：matplotlib的全局配置字典
- 字体优先级列表：系统会按顺序尝试字体
- `unicode_minus`：解决中文环境下负号显示问题

## 2. 数据读取和预处理

### 2.1 CSV数据读取
```python
df = pd.read_csv('../u.csv', skipinitialspace=True)
```

**参数说明：**
- `skipinitialspace=True`：自动去除分隔符后的空格
- 适用于格式不规范的CSV文件

### 2.2 数据提取和类型转换
```python
x = np.array(df['x'])
y = np.array(df['y']) 
u = np.array(df['u'])
```

**数据结构说明：**
- `pandas.Series` → `numpy.array`转换
- numpy数组优势：更快的数值计算、内存效率更高

**示例：**
```python
# DataFrame结构示例
#     x     y      u
# 0  0.1   0.1   0.001
# 1  0.2   0.1   0.002
# 2  0.1   0.2   0.003

# 转换后的numpy数组
x = [0.1, 0.2, 0.1]  # 一维数组
y = [0.1, 0.1, 0.2]  # 一维数组
u = [0.001, 0.002, 0.003]  # 一维数组
```

## 3. 网格生成和数据插值

### 3.1 唯一值提取和网格生成
```python
x_unique = np.unique(x)
y_unique = np.unique(y)
X, Y = np.meshgrid(x_unique, y_unique)
```

**数据结构详解：**

**np.unique()示例：**
```python
x = [0.1, 0.2, 0.1, 0.3, 0.2]
x_unique = np.unique(x)  # [0.1, 0.2, 0.3]
```

**np.meshgrid()详解：**
```python
x_unique = [0, 1, 2]
y_unique = [0, 1]

X, Y = np.meshgrid(x_unique, y_unique)

# X矩阵（每行相同）:
# [[0, 1, 2],
#  [0, 1, 2]]

# Y矩阵（每列相同）:
# [[0, 0, 0],
#  [1, 1, 1]]
```

**用途：**
- 创建规则网格，用于等高线图和3D绘图
- X、Y矩阵的每个对应位置(i,j)代表一个网格点坐标

### 3.2 散点数据插值
```python
U = griddata((x, y), u, (X, Y), method='linear')
```

**griddata函数详解：**
- `(x, y)`：已知散点的坐标
- `u`：已知散点的数值
- `(X, Y)`：目标网格点坐标
- `method='linear'`：线性插值方法

**插值方法对比：**
```python
# 线性插值：速度快，平滑度一般
U_linear = griddata((x, y), u, (X, Y), method='linear')

# 立方插值：更平滑，计算量大
U_cubic = griddata((x, y), u, (X, Y), method='cubic')

# 最近邻插值：保持原始数据特征
U_nearest = griddata((x, y), u, (X, Y), method='nearest')
```

## 4. 等高线图绘制技巧

### 4.1 contourf函数详解
```python
cs = plt.contourf(X, Y, U, levels=40, cmap='viridis')
```

**参数说明：**
- `X, Y`：网格坐标矩阵
- `U`：对应的数值矩阵
- `levels=40`：等高线数量（或自定义等高线值列表）
- `cmap='viridis'`：颜色映射

**levels参数的不同用法：**
```python
# 方法1：指定等高线数量
cs = plt.contourf(X, Y, U, levels=20)

# 方法2：指定具体等高线值
cs = plt.contourf(X, Y, U, levels=[0, 0.005, 0.01, 0.015, 0.02])

# 方法3：使用numpy生成等间距值
cs = plt.contourf(X, Y, U, levels=np.linspace(U.min(), U.max(), 30))
```

### 4.2 颜色映射(colormap)选择
```python
# 科学可视化推荐色彩
cmap='viridis'    # 感知均匀，色盲友好
cmap='plasma'     # 高对比度
cmap='coolwarm'   # 双极数据（正负值）
cmap='RdYlBu_r'   # 传统彩虹色（反向）
```

## 5. 图形美化技巧

### 5.1 坐标轴设置
```python
plt.axis('equal')  # 等比例坐标轴
plt.xlabel('x (m)')  # 带单位的标签
plt.ylabel('y (m)')
```

**axis参数详解：**
```python
plt.axis('equal')    # x、y轴比例相等
plt.axis('scaled')   # 类似equal，但允许缩放
plt.axis('tight')    # 紧贴数据范围
plt.axis('off')      # 关闭坐标轴
```

### 5.2 颜色条(colorbar)定制
```python
cbar = plt.colorbar(cs, label='u (m/s)', shrink=0.8)
cbar.ax.tick_params(labelsize=10)
```

**颜色条参数：**
- `shrink=0.8`：缩放至原高度的80%
- `label`：颜色条标签
- `orientation='horizontal'`：水平放置
- `pad=0.1`：与主图的间距

### 5.3 文本标注技巧
```python
plt.text(0.5, 1.08, 'U_top = 0.01 m/s', 
         transform=plt.gca().transAxes,
         ha='center', fontsize=10,
         bbox=dict(boxstyle="round,pad=0.3", facecolor="yellow", alpha=0.7))
```

**坐标系统详解：**
- `transform=plt.gca().transAxes`：使用轴坐标系（0-1范围）
- `transform=None`：使用数据坐标系（默认）

**文本对齐参数：**
```python
ha='center'    # 水平对齐：'left', 'center', 'right'
va='center'    # 垂直对齐：'bottom', 'center', 'top'
rotation=90    # 旋转角度
```

**文本框样式：**
```python
bbox=dict(
    boxstyle="round,pad=0.3",    # 圆角矩形，内边距0.3
    facecolor="yellow",          # 背景色
    alpha=0.7,                   # 透明度
    edgecolor="black",           # 边框色
    linewidth=1                  # 边框宽度
)
```

## 6. 图形输出和保存

### 6.1 高质量图像保存
```python
plt.savefig('u_velocity_contour.png', dpi=300, bbox_inches='tight')
```

**保存参数详解：**
- `dpi=300`：分辨率，300 DPI适合印刷
- `bbox_inches='tight'`：自动裁剪空白边缘
- `facecolor='white'`：设置背景色
- `transparent=True`：透明背景

**不同格式对比：**
```python
plt.savefig('figure.png', dpi=300)    # 光栅图，适合网页
plt.savefig('figure.pdf')             # 矢量图，适合印刷
plt.savefig('figure.svg')             # 矢量图，适合网页
plt.savefig('figure.eps')             # 矢量图，适合学术期刊
```

## 7. 数据分析和统计

### 7.1 数组统计函数
```python
print(f"U velocity range: [{u.min():.6f}, {u.max():.6f}]")
print(f"Max velocity location: x={x[np.argmax(u)]:.3f}, y={y[np.argmax(u)]:.3f}")
```

**常用统计函数：**
```python
u.min()          # 最小值
u.max()          # 最大值
u.mean()         # 平均值
u.std()          # 标准差
np.argmin(u)     # 最小值索引
np.argmax(u)     # 最大值索引
np.percentile(u, 95)  # 95百分位数
```

### 7.2 字符串格式化技巧
```python
# f-string格式化（Python 3.6+）
print(f"Value: {value:.3f}")      # 保留3位小数
print(f"Count: {count:,}")        # 千位分隔符
print(f"Percent: {ratio:.2%}")    # 百分比格式

# 科学计数法
print(f"Scientific: {value:.2e}")  # 2.34e-05
```

## 8. 高级技巧和最佳实践

### 8.1 内存优化
```python
# 对于大数据集，使用视图而不是副本
x_view = df['x'].values  # 直接获取numpy数组
y_view = df['y'].values  # 避免额外的转换开销
```

### 8.2 错误处理
```python
try:
    U = griddata((x, y), u, (X, Y), method='linear')
    # 检查插值结果
    if np.all(np.isnan(U)):
        print("Warning: All interpolated values are NaN")
        U = griddata((x, y), u, (X, Y), method='nearest')
except Exception as e:
    print(f"Interpolation failed: {e}")
```

### 8.3 性能优化建议
```python
# 1. 预分配数组大小
n_points = len(x)
result = np.empty(n_points)

# 2. 使用向量化操作
u_normalized = (u - u.min()) / (u.max() - u.min())  # 而不是循环

# 3. 适当的数据类型
x = x.astype(np.float32)  # 如果精度允许，使用float32节省内存
```

## 9. 总结

本脚本展示了科学计算可视化的典型流程：
1. **数据预处理**：清洗、转换数据格式
2. **网格化**：将散乱数据插值到规则网格
3. **可视化**：使用等高线图展示空间分布
4. **美化**：添加标签、颜色条、注释
5. **输出**：保存高质量图像

这些技巧广泛应用于CFD、气象学、地质学等领域的数据可视化工作。