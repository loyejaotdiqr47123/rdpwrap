@echo off
if not exist "%~dp0RDPWInst.exe" goto :error
"%~dp0RDPWInst" -w
ping -n 3 localhost > nul
cmd.exe /C start "" "C:\Program Files\RDP Wrapper\RDP_CnC.exe"
:error
echo [-] Installer executable not found.
echo Please extract all files from the downloaded package or check your anti-virus.
pause
