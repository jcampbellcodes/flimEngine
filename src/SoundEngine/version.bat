@echo off
set vernum=-1

if EXIST C:\Windows\System32\XAudio2_8.dll (
	set /p texte=< vcsversion.h
	set vernum=8
	GOTO :checked
)
if EXIST C:\Windows\SysWOW64\XAudio2_8.dll (
	set /p texte=< vcsversion.h
	set vernum=8
	GOTO :checked
)
if EXIST C:\Windows\SysWOW64\XAudio2_7.dll (
	set /p texte=< vcsversion.h
	set vernum=7
	GOTO :checked
)
if EXIST C:\Windows\System32\XAudio2_7.dll (
	set /p texte=< vcsversion.h
	set vernum=7
	GOTO :checked
)
if EXIST C:\Windows\System32\XAudio2_9.dll (
	set /p texte=< vcsversion.h
	set vernum=9
	GOTO :checked
)



if EXIST C:\Windows\SysWOW64\XAudio2_9.dll (
	set /p texte=< vcsversion.h
	set vernum=9
	GOTO :checked
)

else(
	set /p texte=< vcsversion.h
	set vernum=-1
}
:checked
if NOT "%texte%" == "#define __XAUDIO2VER %vernum% " ( 
	echo #define __XAUDIO2VER %vernum% > vcsversion.h
)
