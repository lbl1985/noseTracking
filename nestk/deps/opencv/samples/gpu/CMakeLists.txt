if (BUILD_EXAMPLES)
    project(gpu_samples)

    include_directories(
        "${OpenCV_SOURCE_DIR}/modules/core/include"
        "${OpenCV_SOURCE_DIR}/modules/flann/include"
        "${OpenCV_SOURCE_DIR}/modules/imgproc/include"
        "${OpenCV_SOURCE_DIR}/modules/video/include"
        "${OpenCV_SOURCE_DIR}/modules/highgui/include"
        "${OpenCV_SOURCE_DIR}/modules/ml/include"
        "${OpenCV_SOURCE_DIR}/modules/calib3d/include"
        "${OpenCV_SOURCE_DIR}/modules/features2d/include"
        "${OpenCV_SOURCE_DIR}/modules/objdetect/include"
        "${OpenCV_SOURCE_DIR}/modules/legacy/include"
        "${OpenCV_SOURCE_DIR}/modules/contrib/include"
        "${OpenCV_SOURCE_DIR}/modules/gpu/include"
    )   

    if(CMAKE_COMPILER_IS_GNUCXX)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-unused-function")
    endif()
    
    # ---------------------------------------------
    #      Define executable targets
    # ---------------------------------------------
    MACRO(MY_DEFINE_EXAMPLE name srcs)
        set(the_target "example_gpu_${name}")
    	add_executable(${the_target} ${srcs})
		set_target_properties(${the_target} PROPERTIES
		    OUTPUT_NAME "${name}_gpu"
		    PROJECT_LABEL "(EXAMPLE_GPU) ${name}")
    	add_dependencies(${the_target} opencv_core opencv_flann opencv_imgproc opencv_highgui
    	    opencv_ml opencv_video opencv_objdetect opencv_features2d
    	    opencv_calib3d opencv_legacy opencv_contrib opencv_gpu)
    	target_link_libraries(${the_target} ${OPENCV_LINKER_LIBS} opencv_core
    	    opencv_flann opencv_imgproc opencv_highgui opencv_ml opencv_video opencv_objdetect
    	    opencv_features2d opencv_calib3d opencv_legacy opencv_contrib opencv_gpu)

        if(WIN32)
            install(TARGETS ${the_target}
                RUNTIME DESTINATION "samples/gpu" COMPONENT main)
        endif()
    ENDMACRO(MY_DEFINE_EXAMPLE)
    
    file(GLOB gpu_samples RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
    
    foreach(sample_filename ${gpu_samples})
        get_filename_component(sample ${sample_filename} NAME_WE)
        MY_DEFINE_EXAMPLE(${sample}  ${sample_filename})
    endforeach()
endif(BUILD_EXAMPLES)

if (NOT WIN32)
    file(GLOB GPU_FILES *.c *.cpp *.jpg *.png *.data makefile.* build_all.sh *.dsp *.cmd )
    install(FILES ${GPU_FILES}
            DESTINATION share/opencv/samples/gpu
            PERMISSIONS OWNER_READ GROUP_READ WORLD_READ)
endif ()

