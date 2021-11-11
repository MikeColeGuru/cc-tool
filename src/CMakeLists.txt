message("Here is src")

add_subdirectory(application)
add_subdirectory(common)
add_subdirectory(data)
add_subdirectory(debugger)
add_subdirectory(programmer)
add_subdirectory(usb)

target_include_directories(cc-tool 
    PRIVATE
        application 
        common 
        data
        debugger
        programmer
        usb
        .
)

target_sources(cc-tool 
    PRIVATE 
        main.cpp 
        main.h
)