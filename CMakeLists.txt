cmake_minimum_required(VERSION 3.0)
project(CPU_Raytracer)

file(GLOB RT_FILES
    src/*.cpp 
    src/*.hpp 

    src/geometric_objects/*.hpp 
    src/geometric_objects/*.cpp
    src/geometric_objects/part_objects/*.hpp 
    src/geometric_objects/part_objects/*.cpp
    src/geometric_objects/compound/*.hpp 
    src/geometric_objects/compound/*.cpp
    src/geometric_objects/containers/*.hpp 
    src/geometric_objects/containers/*.cpp

    src/tracers/*.hpp 
    src/tracers/*.cpp

    src/samplers/*.hpp 
    src/samplers/*.cpp

    src/cameras/*.hpp 
    src/cameras/*.cpp

    src/lights/*.hpp 
    src/lights/*.cpp

    src/brdf/*.hpp 
    src/brdf/*.cpp

    src/materials/*.hpp 
    src/materials/*.cpp

    src/acceleration_data_structures/*.hpp 
    src/acceleration_data_structures/*.cpp
)

if(TARGET glm)
    message("ALREADY CREATED")
else()
    add_subdirectory(dependencies/glm)
endif()



add_library(cpu_raytracer STATIC ${RT_FILES})
target_link_libraries(cpu_raytracer glm)