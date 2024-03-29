@echo off
if not exist "%~dp0RDPWInst.exe" goto :error
"%~dp0RDPWInst" -i -o
ping -n 3 localhost > nul
SCHTASKS /CREATE /SC ONSTART /DELAY 0002:00 /TN "RDPWUpdater" /TR "'C:\%ProgramFiles%\RDP Wrapper\RDPWInst.exe' -w" /RL HIGHEST /RU SYSTEM /NP
cmd.exe /C start "" "C:\%ProgramFiles%\RDP Wrapper\RDP_CnC.exe"
exit
:error
echo [-] Installer executable not found.
echo Please extract all files from the downloaded package or check your anti-virus.
pause
