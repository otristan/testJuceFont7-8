cmake_minimum_required(VERSION 3.12)

set(USE_JUCE7 ON CACHE BOOL "USE_JUCE7")

if(USE_JUCE7)
    project(TestFont7 VERSION 0.0.1)
    add_subdirectory(${PROJECT_SOURCE_DIR}/../JUCE7 ${CMAKE_CURRENT_BINARY_DIR}/JUCE7)
else()
    project(TestFont8 VERSION 0.0.1)
    add_subdirectory(${PROJECT_SOURCE_DIR}/../JUCE8 ${CMAKE_CURRENT_BINARY_DIR}/JUCE8)
endif()

juce_add_gui_app(${PROJECT_NAME}
    PRODUCT_NAME ${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
    Main.cpp
    MainComponent.cpp
    MainComponent.h)

if(USE_JUCE7)
    target_sources(${PROJECT_NAME} PRIVATE
    FreeTypeAmalgam.c
    FreeTypeAmalgam.h
    vf_FreeTypeFaces.cpp
    vf_FreeTypeFaces.h)
endif()

if(USE_JUCE7)
    target_compile_definitions(${PROJECT_NAME} PUBLIC USE_JUCE7=1)
else()
    target_compile_definitions(${PROJECT_NAME} PUBLIC USE_JUCE7=0)
endif()

target_compile_definitions(${PROJECT_NAME} PRIVATE
	JUCE_USE_DIRECTWRITE=1
    JUCE_COREGRAPHICS_DRAW_ASYNC=1
    JUCE_WIN_PER_MONITOR_DPI_AWARE=1
    JUCE_DISABLE_COREGRAPHICS_FONT_SMOOTHING=1
    DONT_SET_USING_JUCE_NAMESPACE=1
    JUCE_WEB_BROWSER=0  # If you remove this, add `NEEDS_WEB_BROWSER TRUE` to the `juce_add_gui_app` call
    JUCE_USE_CURL=0     # If you remove this, add `NEEDS_CURL TRUE` to the `juce_add_gui_app` call
    JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:${PROJECT_NAME},JUCE_PROJECT_NAME>"
    JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:${PROJECT_NAME},JUCE_VERSION>"
    )

target_link_libraries(${PROJECT_NAME} PRIVATE
    juce::juce_gui_extra)
