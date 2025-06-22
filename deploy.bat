set root="C:\Build\SlaveTatsNG"
set dest="F:\Games\Skyrim-1.6.1170"
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
copy %headersrc%\SlaveTatsNG_Interface.h %plugindest%\SKSE\Plugins\SlaveTatsNG
copy %scriptssrc%\*.pex %scriptsdest%\Scripts\
