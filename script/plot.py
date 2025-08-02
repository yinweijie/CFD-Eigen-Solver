#!/bin/python3

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import griddata
import matplotlib
import matplotlib.font_manager as fm

# 使用非交互式后端
matplotlib.use('Agg')

# 解决中文字体问题
plt.rcParams['font.sans-serif'] = ['SimHei', 'DejaVu Sans', 'Arial Unicode MS', 'Liberation Sans']
plt.rcParams['axes.unicode_minus'] = False  # 解决负号显示问题

# 如果上面的方法不行，使用英文标题
USE_ENGLISH = True  # 设置为True使用英文，False使用中文

# 读取CSV文件，跳过空格
df = pd.read_csv('../u.csv', skipinitialspace=True)

# 提取坐标和速度数据，忽略z列
x = np.array(df['x'])
y = np.array(df['y'])
u = np.array(df['u'])

# 创建网格用于插值
x_unique = np.unique(x)
y_unique = np.unique(y)
X, Y = np.meshgrid(x_unique, y_unique)

# 将散点数据插值到规则网格
U = griddata((x, y), u, (X, Y), method='linear')

# 创建等高线图
plt.figure(figsize=(12, 10))

# 等高线图
cs = plt.contourf(X, Y, U, levels=40, cmap='viridis')
plt.title('U-Velocity Contour Plot', pad=20)
plt.xlabel('x (m)')
plt.ylabel('y (m)')
plt.axis('equal')
cbar = plt.colorbar(cs, label='u (m/s)', shrink=0.8)
cbar.ax.tick_params(labelsize=10)


# 添加边界条件标注
plt.text(0.5, 1.08, 'U_top = 0.01 m/s', transform=plt.gca().transAxes, 
         ha='center', fontsize=10, bbox=dict(boxstyle="round,pad=0.3", facecolor="yellow", alpha=0.7))
# plt.text(-0.12, 0.5, 'U_left = 0', transform=plt.gca().transAxes, 
#          ha='center', rotation=90, fontsize=10, bbox=dict(boxstyle="round,pad=0.3", facecolor="lightblue", alpha=0.7))

plt.tight_layout()
plt.savefig('u_velocity_contour.png', dpi=300, bbox_inches='tight')

# 打印数据统计信息
print("=== Data Statistics ===")
print(f"Total data points: {len(x)}")
print(f"X coordinate range: [{x.min():.3f}, {x.max():.3f}]")
print(f"Y coordinate range: [{y.min():.3f}, {y.max():.3f}]")
print(f"U velocity range: [{u.min():.6f}, {u.max():.6f}]")
print(f"Unique X coordinates: {len(x_unique)}")
print(f"Unique Y coordinates: {len(y_unique)}")
print(f"Max velocity location: x={x[np.argmax(u)]:.3f}, y={y[np.argmax(u)]:.3f}")

plt.show()