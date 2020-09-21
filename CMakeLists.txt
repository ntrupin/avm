cmake_minimum_required(VERSION 3.17)
project(giant C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DGENERATE -DDEBUG")
add_executable(giant vm/vm.c vm/loader/loader.c vm/loader/constpool/constpool.c vm/loader/constpool/constpool.h vm/loader/constpool/utf8.c vm/loader/constpool/utf8.h vm/loader/constpool/const.c vm/loader/constpool/const.h vm/loader/constpool/string.c vm/loader/constpool/string.h vm/loader/class.c vm/loader/class.h vm/loader/constpool/method.c vm/loader/constpool/method.h vm/loader/constpool/nametype.c vm/loader/constpool/nametype.h vm/loader/methods/methods.c vm/loader/methods/methods.h vm/loader/methods/method.c vm/loader/methods/method.h vm/loader/methods/attributes.c vm/loader/methods/attributes.h vm/loader/methods/attribute.c vm/loader/methods/attribute.h vm/loader/project.c vm/loader/project.h main.c vm/interpreter/frame.c vm/interpreter/frame.h vm/interpreter/stack.c vm/interpreter/stack.h vm/interpreter/value.c vm/interpreter/value.h vm/interpreter/vars.c vm/interpreter/vars.h vm/interpreter/interpreter.c vm/interpreter/interpreter.h)