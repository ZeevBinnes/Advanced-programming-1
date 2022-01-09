cmake_minimum_required(VERSION 3.20)
project(Advanced_programming_1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

include_directories()

add_executable(decector
        anomaly_detection_util.cpp
        anomaly_detection_util.h
        MainTrain.cpp
        AnomalyDetector.h
        SimpleAnomalyDetector.cpp
        SimpleAnomalyDetector.h
        timeseries.cpp
        timeseries.h
        minCircle.cpp
        minCircle.h
        CLI.cpp
        CLI.h
        HybridAnomalyDetector.cpp
        HybridAnomalyDetector.h
        commands.h
        Server.cpp
        Server.h)

