message("I'm in common")

set(SOURCES common.cpp log.cpp timer.cpp)
set(HEADER_FILES common.h log.h timer.h)

target_sources(cc-tool 
    PRIVATE 
    common.cpp log.cpp timer.cpp
    common.h log.h timer.h
)

