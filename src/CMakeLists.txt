#find_library(MGL mgl PATHS /usr/local/lib)

ADD_EXECUTABLE( landmark main.cpp)
TARGET_LINK_LIBRARIES( landmark ${OpenCV_LIBS} )
#target_link_libraries( eyeLike ${MGL})