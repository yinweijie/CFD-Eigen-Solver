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