@echo off
c:
cd\
cd Dev
cd MFC
del /f /q /a . /s
cd ..
rmdir mfc /s /q
git clone https://github.com/birdcagedout/MFC.git
