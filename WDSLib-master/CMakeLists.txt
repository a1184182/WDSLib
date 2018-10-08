cmake_minimum_required(VERSION 2.8)

set (WDSLib_VERSION_MAJOR 1)
set (WDSLib_VERSION_MINOR 0)
set (CMAKE_CXX_STANDARD 11)

project(WDSLib)

ADD_SUBDIRECTORY(lib/SuiteSparse)
ADD_SUBDIRECTORY(lib/EPANET)


ADD_LIBRARY(WDSLib STATIC
             Simulation/Simulation.cc Simulation/ELVA.cc Simulation/Flag.cc Simulation/Parameter.cc Network/Net.cc Network/Edge/PIPES/pipe.cc Network/Vertex/NODE/node.cc Network/Geometry/topology.cc math/Matrix.cc IO/Input.cc hydraulic/result.cc hydraulic/solver.cc hydraulic/GGA/GGAsolver.cc hydraulic/RCTM/RCTMsolver.cc)

TARGET_LINK_LIBRARIES(WDSLib
                       EPANET)
TARGET_LINK_LIBRARIES(WDSLib cxsparse)

add_executable(Netsolver NetSolver.cc)

TARGET_LINK_LIBRARIES(Netsolver
                       WDSLib)

add_executable(1+1EA 1+1EA.cc)

TARGET_LINK_LIBRARIES(1+1EA
                       WDSLib)

enable_testing ()
add_custom_target(test COMMAND ${CMAKE_CTEST_COMMAND}
     --force-new-ctest-process
     --verbose
      --output-on-failure
)
add_subdirectory (Test)

