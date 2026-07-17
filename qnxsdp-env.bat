@echo off
REM This script sets environment variables required to use this version of QNX Software Development Platform
REM from the command line. To use this script execute it in windows command shell (cmd).

set QNX_BASE=%~dp0

@echo on

set QNX_BASE=%QNX_BASE:\=/%
if "%QNX_BASE:~-1%"=="/" set QNX_BASE=%QNX_BASE:~,-1%
set QNX_TARGET=%QNX_BASE%/target/qnx
set QNX_HOST=%QNX_BASE%/host/win64/x86_64

set QNX_CONFIGURATION_EXCLUSIVE=%USERPROFILE%/.qnx
set QNX_CONFIGURATION=%QNX_CONFIGURATION_EXCLUSIVE%


set MAKEFLAGS=-I%QNX_TARGET%/usr/include
set PATH=%QNX_HOST%/usr/bin;%QNX_BASE%/host/common/bin;%PATH%

@REM This is set to make sdp installation read-only (otherwise python will create extra files when you run debuger)
@REM If you using python for something else and need it, comment out this line
set PYTHONDONTWRITEBYTECODE=1

set TMPDIR=%TMP%

@set LICENSE_SCRIPT=%QNX_BASE%\license-env.bat
if exist %LICENSE_SCRIPT% %LICENSE_SCRIPT%

@REM Do not edit past this line
