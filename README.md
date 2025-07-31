<!--
 * @Author: Yin Weijie
 * @Date: 2020-11-06 22:48:48
 * @LastEditTime: 2020-11-06 22:51:15
-->

# 简介

基于[Eigen](http://eigen.tuxfamily.org/index.php?title=Main_Page) 3.3.7开发的简易CFD Sovler，可用于熟悉CFD基本理论和实现过程。

标量输运部分编写参考[Fluid 101](https://www.fluidmechanics101.com/)
[course 1](https://www.udemy.com/course/computational-fluid-dynamics-fundamentals-course/)
[course 2](https://www.udemy.com/course/computational-fluid-dynamics-fundamentals-course-2/)

SIMPLE算法部分编写参考[Sandip CFD Lectures](https://www.youtube.com/channel/UCtNV6Ew24I_T2XIJJdYT2kQ)

笔记整理见:

[Co-Located SIMPLE · 语雀](https://www.yuque.com/yinweijie/gr78mf/edyam2148k7cvng8?singleDoc#)

[TheoryNotes · 语雀](https://www.yuque.com/yinweijie/gr78mf/hqe7xfpr5lyiurpd?singleDoc#)

---

# 编译

下载Eigen库

```bash
cd CFD-Eigen-Solver
wget https://gitlab.com/libeigen/eigen/-/archive/3.3.7/eigen-3.3.7.tar.gz
```

下载nlohmann/json库

```bash
git clone --branch v3.12.0 https://github.com/nlohmann/json.git
```

编译Eigen：

```bash
tar xvf eigen-3.3.7.tar.gz
cd eigen-3.3.7/
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=release \
      -DCMAKE_INSTALL_PREFIX=../../lib_eigen337 \
      ..
make -j
make check
make install
```

编译nlohmann/json库

```bash
cd json/
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=release \
      -DCMAKE_INSTALL_PREFIX=../../lib_json \
      ..
make -j6
make install
```

编译CFD_Eigen：

```bash
cmake -S . -B build
cmake --build build
```
