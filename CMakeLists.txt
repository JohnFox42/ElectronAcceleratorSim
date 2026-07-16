# (1)
cmake_minimum_required(VERSION 3.16...3.27)
project(ElectronAcceleratorSim)

#(2)
find_package(Geant4 REQUIRED ui_all vis_all)

#(3)
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

#(4)
add_executable(ElectronAcceleratorSim ElectronAcceleratorSim.cc ${sources} ${headers})
target_include_directories(ElectronAcceleratorSim PRIVATE include)
target_link_libraries(ElectronAcceleratorSim PRIVATE ${Geant4_LIBRARIES})

#(5)
set(BASICDETECTOR_SCRIPTS
    ElectronAcceleratorSim.cc
    )

#(6)
file(GLOB macros ${PROJECT_SOURCE_DIR}/*.mac)

foreach (_file ${macros})
    get_filename_component(_name ${_file} NAME)

    configure_file(
        ${_file}
        ${CMAKE_CURRENT_BINARY_DIR}/${_name} 
        COPYONLY
    )
endforeach()

#Setting vscode things
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
