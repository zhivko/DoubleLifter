python c:/msys32/home/klemen/esp/esp-idf-v3.1.1/components/esptool_py/esptool/esptool.py --chip esp32 --port COM24 --baud 921600 --before "default_reset" --after "hard_reset" erase_flash