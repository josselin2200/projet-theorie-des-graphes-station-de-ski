cmake_minimum_required(VERSION 3.15)
project(projet-theorie-des-graphes-station-de-ski-g)

set(CMAKE_CXX_STANDARD 14)

add_executable(projet-theorie-des-graphes-station-de-ski-g
        CMakeLists.txt
        data_arcs.txt
        main.cpp
        PointGeographique.h
        PointGeographique.cpp
        Station.h
        Station.cpp
        Trajet.cpp
        Trajet.h
        Remontee.cpp
        Remontee.h
        Descente.cpp Descente.h Navette.cpp Navette.h allegro.cpp allegro.cpp allegro.h)

IF(WIN32)
    target_link_libraries(projet-theorie-des-graphes-station-de-ski-g -lmingw32 -lallegro-5.0.10-monolith-md-debug)
ELSE()
    INCLUDE_DIRECTORIES(/usr/local/Cellar/allegro/5.2.6.0/include)
    LINK_DIRECTORIES(/usr/local/Cellar/allegro/5.2.6.0/lib)
    file(GLOB LIBRARIES "/usr/local/Cellar/allegro/5.2.6.0/lib/*.dylib")
    message("LIBRARIES = ${LIBRARIES}")
    TARGET_LINK_LIBRARIES(projet-theorie-des-graphes-station-de-ski-g ${LIBRARIES})
ENDIF(WIN32)
