message("I'm in usb")

target_sources(cc-tool 
    PRIVATE 
    usb_device.cpp
    usb_device.h
)