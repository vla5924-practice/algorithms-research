cmake_minimum_required(VERSION 3.16)

macro(add_single_file_module module_name)
    add_executable(${module_name} "${module_name}.cpp")
endmacro()
