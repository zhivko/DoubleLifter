set echo on
rem set project_folder=c:\msys32\home\klemen\esp\DoubleLifter

set "project_folder=%cd%"

echo %project_folder%

rem cd ./data_template
rem convert.bat
rem cd %project_folder%

del spiffs.bin
mkspiffs.exe -p 256 -b 4096 -s 1433600 -d 5 -c ./data ./spiffs.bin

rem COM13
rem COM28

rem python c:\msys32\home\klemen\esp\esp-idf-v3.1.1\components\esptool_py\esptool\esptool.py --chip esp32 --port COM28 --baud 921600 --before "default_reset" --after "hard_reset" write_flash --compress -z --flash_mode "dio" --flash_freq "40m" --flash_size detect 0x1000 "%project_folder%\build\bootloader\bootloader.bin" 0x10000 "%project_folder%\build\DoubleLifter.bin" 0x8000 "%project_folder%\build\partitions.bin" 0x291000 "%project_folder%\spiffs.bin"
rem python c:\msys32\home\klemen\esp\esp-idf-v3.1.1\components\esptool_py\esptool\esptool.py --chip esp32 --port COM13 --baud 921600 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size detect 0x10000 "%project_folder%\build\DoubleLifter.bin"


python c:\msys32\home\klemen\esp\esp-idf-v3.1.1\components\esptool_py\esptool\esptool.py --chip esp32 --port COM28 --baud 921600 --before "default_reset" --after "hard_reset" write_flash --compress -z --flash_mode "dio" --flash_freq "40m" --flash_size detect 0x1000 "%project_folder%\build\bootloader\bootloader.bin" 0x10000 "%project_folder%\build\DoubleLifter.bin" 0x8000 "%project_folder%\build\partitions.bin" 0x291000 "%project_folder%\spiffs.bin"