set pluginsrc=C:\Build\SlaveTatsNG\build\Release
set scriptssrc=C:\Build\SlaveTatsNG\papyrus\Scripts
rem set plugindest="D:\Games\Skyrim-1.6.1170\overwrite"
set plugindest="D:\Games\Skyrim-1.5.97\overwrite"
rem set scriptsdest="D:\Games\Skyrim-1.6.1170\overwrite"
set scriptsdest="D:\Games\Skyrim-1.5.97\overwrite"
set configsrc=C:\Build\SlaveTatsNG\config
copy %pluginsrc%\SlaveTatsNG.dll %plugindest%\SKSE\Plugins\_SlaveTatsNG.dll
copy %pluginsrc%\SlaveTatsNG.pdb %plugindest%\SKSE\Plugins\_SlaveTatsNG.pdb
copy %scriptssrc%\*.pex %scriptsdest%\Scripts\
copy %configsrc%\*.ini %plugindest%\SKSE\Plugins\