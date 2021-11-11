message("I'm in application")
# set(SOURCES cc_base.cpp cc_debugger.cpp cc_flasher.cpp)
# set(HEADER_FILES cc_base.h cc_debugger.h cc_flasher.h)

target_sources(cc-tool 
    PRIVATE 
        cc_base.cpp 
        cc_debugger.cpp 
        cc_flasher.cpp 
        cc_base.h 
        cc_debugger.h 
        cc_flasher.h 
)

