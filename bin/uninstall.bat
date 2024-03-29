@echo off
if not exist "%~dp0RDPWInst.exe" goto :error
"%~dp0RDPWInst" -u
SCHTASKS /DELETE /TN "RDPWUpdater" /F
rmdir /Q /S "C:\Program Files\RDP Wrapper"
echo.
goto :anykey
:error
echo [-] Installer executable not found.
echo Please extract all files from the downloaded package or check your anti-virus.
:anykey
pause
