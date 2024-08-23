set pluginsrc=C:\Build\SlaveTatsNG\buildae\Debug
set scriptssrc=C:\Build\SlaveTatsNG\papyrus\Scripts
set plugindest="D:\Games\Skyrim-1.6.1170\overwrite"
set scriptsdest="D:\Games\Skyrim-1.6.1170\overwrite"
copy %pluginsrc%\*.dll %plugindest%\SKSE\Plugins\
copy %pluginsrc%\*.pdb %plugindest%\SKSE\Plugins\
copy %scriptssrc%\*.pex %scriptsdest%\Scripts\
