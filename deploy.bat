set pluginsrc=C:\Build\SlaveTatsNG\build\Release
rem set pluginsrc=C:\Build\SlaveTatsNG\build\Debug
set scriptssrc=C:\Build\SlaveTatsNG\papyrus\Scripts
set plugindest="D:\Games\Skyrim-1.6.1170\overwrite"
rem plugindest="D:\Games\Skyrim-1.5.97\overwrite"
set scriptsdest="D:\Games\Skyrim-1.6.1170\overwrite"
rem set scriptsdest="D:\Games\Skyrim-1.5.97\overwrite"
copy %pluginsrc%\*.dll %plugindest%\SKSE\Plugins\
copy %pluginsrc%\*.pdb %plugindest%\SKSE\Plugins\
copy %scriptssrc%\*.pex %scriptsdest%\Scripts\
