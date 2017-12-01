@echo off

set (PROJECT_DIR)=%~1
set (TARGET_OUTPUT_DIR)=%~2
set (CONFIGURATION)=%~3

IF "%(CONFIGURATION)%"=="DEBUG" (
copy "%(PROJECT_DIR)%libs\TDM-GCC-32\libstdc++-6.dll" "%(PROJECT_DIR)%%(TARGET_OUTPUT_DIR)%"
copy "%(PROJECT_DIR)%libs\SFML-2.4.2-tdm\bin\sfml-graphics-d-2.dll" "%(PROJECT_DIR)%%(TARGET_OUTPUT_DIR)%"
copy "%(PROJECT_DIR)%libs\SFML-2.4.2-tdm\bin\sfml-window-d-2.dll" "%(PROJECT_DIR)%%(TARGET_OUTPUT_DIR)%"
copy "%(PROJECT_DIR)%libs\SFML-2.4.2-tdm\bin\sfml-system-d-2.dll" "%(PROJECT_DIR)%%(TARGET_OUTPUT_DIR)%"
)

Xcopy /E /I /Y "%(PROJECT_DIR)%assets" "%(TARGET_OUTPUT_DIR)%assets"
