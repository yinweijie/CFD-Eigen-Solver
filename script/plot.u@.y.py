#!/bin/python3

import pandas as pd
import matplotlib
matplotlib.use('Agg')  # 设置非交互式后端
import matplotlib.pyplot as plt
import numpy as np

# 读取CSV文件
csv_file = '../u.csv'
df = pd.read_csv(csv_file)
df_ref = pd.read_csv('../ref.data/u.@.y.Re1000.csv')

# 去除列名中的空格
df.columns = df.columns.str.strip()
df_ref.columns = df_ref.columns.str.strip()

# 筛选x=0.5的数据点
x_target = 0.5
tolerance = 1e-10  # 浮点数比较容差
data_at_x05 = df[abs(df['x'] - x_target) < tolerance].copy()

# 按y坐标排序
data_at_x05 = data_at_x05.sort_values('y')
df_ref = df_ref.sort_values('y')

# 创建图形
plt.figure(figsize=(10, 8))
plt.plot(data_at_x05['y'], data_at_x05['u'], 'b-o', linewidth=2, markersize=4, label='u velocity')
plt.plot(df_ref['y'], df_ref['u'], 'ro', markersize=4, label='Reference u velocity')

# 设置图形属性
plt.ylabel('u velocity', fontsize=12)
plt.xlabel('y axis', fontsize=12)
plt.title(f'x = {x_target}, velocity distribution', fontsize=14)
plt.grid(True, alpha=0.3)
plt.legend()

# 设置坐标轴范围
plt.ylim(min(data_at_x05['u']) * 0.9 - 0.5, max(data_at_x05['u']) * 1.1)
plt.xlim(0, 1)

# 显示图形
plt.tight_layout()

# 保存图片到文件
output_file = 'u_velocity_at_x05.png'
plt.savefig(output_file, dpi=300, bbox_inches='tight')
print(f"图片已保存到: {output_file}")

# 如果有显示环境，也尝试显示
try:
    plt.show()
except:
    print("无法显示图形，但图片已保存")

# 打印一些统计信息
print(f"在x = {x_target} 处找到 {len(data_at_x05)} 个数据点")
print(f"速度范围: {min(data_at_x05['u']):.6f} 到 {max(data_at_x05['u']):.6f}")
print(f"y坐标范围: {min(data_at_x05['y']):.2f} 到 {max(data_at_x05['y']):.2f}")
