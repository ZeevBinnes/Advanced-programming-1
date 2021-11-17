cmake_minimum_required(VERSION 3.20)
project(Advanced_programming_1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Advanced_programming_1
        anomaly_detection_util.cpp
        anomaly_detection_util.h
        MainTrain.cpp
        AnomalyDetector.h
        SimpleAnomalyDetector.cpp
        SimpleAnomalyDetector.h
        timeseries.cpp
        timeseries.h)
