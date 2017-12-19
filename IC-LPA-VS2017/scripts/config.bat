@echo off

set (PROJECT_DIR)=%~1
set (TARGET_OUTPUT_DIR)=%~2
set (CONFIGURATION)=%~3

IF "%(CONFIGURATION)%"=="DEBUG" (
Xcopy "%(PROJECT_DIR)%libs\SFML-2.4.2-vc14-32\SFML-2.4.2\bin\sfml-graphics-d-2.dll" "%(TARGET_OUTPUT_DIR)%" /E /D 
Xcopy "%(PROJECT_DIR)%libs\SFML-2.4.2-vc14-32\SFML-2.4.2\bin\sfml-window-d-2.dll" "%(TARGET_OUTPUT_DIR)%" /E /D 
Xcopy "%(PROJECT_DIR)%libs\SFML-2.4.2-vc14-32\SFML-2.4.2\bin\sfml-system-d-2.dll" "%(TARGET_OUTPUT_DIR)%" /E /D 
Xcopy "%(PROJECT_DIR)%libs\SFML-2.4.2-vc14-32\SFML-2.4.2\bin\sfml-audio-d-2.dll" "%(TARGET_OUTPUT_DIR)%" /E /D 

Xcopy "%(PROJECT_DIR)%libs\VLD\bin\Win32\dbghelp.dll" "%(TARGET_OUTPUT_DIR)%" /E /D 
Xcopy "%(PROJECT_DIR)%libs\VLD\bin\Win32\Microsoft.DTfW.DHL.manifest" "%(TARGET_OUTPUT_DIR)%" /E /D 
Xcopy "%(PROJECT_DIR)%libs\VLD\bin\Win32\vld_x86.dll" "%(TARGET_OUTPUT_DIR)%" /E /D 
)

Xcopy /E /I /Y /D "%(PROJECT_DIR)%assets" "%(TARGET_OUTPUT_DIR)%assets"
Xcopy "%(PROJECT_DIR)%libs\SFML-2.4.2-vc14-32\SFML-2.4.2\bin\openal32.dll" "%(TARGET_OUTPUT_DIR)%" /E /D