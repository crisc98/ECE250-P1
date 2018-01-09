cmake_minimum_required(VERSION 3.9)
project(ECE250_P1)

set(CMAKE_CXX_STANDARD 11)

add_executable(ECE250_P1
        Double_node_tester.h
        Double_sentinel_list.h
        Double_sentinel_list_driver.cpp
        Double_sentinel_list_tester.h
        ece250.h
        Exception.h
        simpleTester.cpp
        test.cpp
        Tester.h)
