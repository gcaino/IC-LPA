@echo off

set (PROJECT_DIR)=%~1
set (TARGET_OUTPUT_DIR)=%~2

copy "%(PROJECT_DIR)%libs\SFML-2.4.2-vc14-32\SFML-2.4.2\bin\sfml-graphics-d-2.dll" "%(TARGET_OUTPUT_DIR)%"
copy "%(PROJECT_DIR)%libs\SFML-2.4.2-vc14-32\SFML-2.4.2\bin\sfml-window-d-2.dll" "%(TARGET_OUTPUT_DIR)%"
copy "%(PROJECT_DIR)%libs\SFML-2.4.2-vc14-32\SFML-2.4.2\bin\sfml-system-d-2.dll" "%(TARGET_OUTPUT_DIR)%"

