set root="C:\Build\SlaveTatsNG"
REM set dest="F:\Games\Skyrim-1.6.1170"
set dest="D:\Games\Skyrim-1.5.97"
set pluginsrc=%root%\build\release-msvc
set configsrc=%root%\config
set headersrc=%root%\include
set scriptssrc=%root%\papyrus\Scripts
set plugindest=%dest%\overwrite
set scriptsdest=%dest%\overwrite
copy %pluginsrc%\*.dll %plugindest%\SKSE\Plugins\
copy %pluginsrc%\*.pdb %plugindest%\SKSE\Plugins\
mkdir %plugindest%\SKSE\Plugins\SlaveTatsNG
copy %configsrc%\*.ini %plugindest%\SKSE\Plugins\SlaveTatsNG
copy %configsrc%\*.json %plugindest%\SKSE\Plugins\SlaveTatsNG
copy %headersrc%\SlaveTatsNG_Interface.h %plugindest%\SKSE\Plugins\SlaveTatsNG
copy %scriptssrc%\*.pex %scriptsdest%\Scripts\
