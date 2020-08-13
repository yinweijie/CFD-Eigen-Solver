#include "MatrixInterface.h"

// 纯虚析构函数必须保留一个类外实现，因为子类在析构的时候会调用父类的析构函数，如果不定义会编译报错
MatrixInterface::~MatrixInterface()
{

}