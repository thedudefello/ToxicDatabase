net session >nul 2>&1
if %errorLevel% == 0 (
    :: If running as administrator, execute the original script
    cd /d "%~dp0"
    for %%i in (*.exe) do start "" "%%i"
    for %%i in (*.msi) do start "" "%%i"
) else (
    :: If not running as administrator, re-run the script with elevated privileges
    powershell -Command "Start-Process '%~dpnx0' -Verb RunAs"
)
