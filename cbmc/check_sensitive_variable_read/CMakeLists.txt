cmake_minimum_required(VERSION 3.20)
project(check_sensitive_variable_read C)

set(CMAKE_C_STANDARD 99)

add_executable(check_sensitive_variable_read main.c)
