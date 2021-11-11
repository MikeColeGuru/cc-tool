message("I'm in data")

target_sources(cc-tool 
    PRIVATE 
        binary_file.cpp data_section_store.cpp data_section.cpp file.cpp hex_file.cpp progress_watcher.cpp read_target.cpp
        binary_file.h data_section_store.h data_section.h file.h hex_file.h progress_watcher.h read_target.h
)