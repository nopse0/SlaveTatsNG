set configsrc=C:\Build\SlaveTatsNG\config
set pluginsrc=C:\Build\SlaveTatsNG\build\Release
rem set pluginsrc=C:\Build\SlaveTatsNG\build\Debug
set dist=C:\Build\SlaveTatsNG\dist\SlaveTatsNG
mkdir %dist%
mkdir %dist%\SKSE
mkdir %dist%\SKSE\Plugins
set plugindest=%dist%\SKSE\Plugins
copy %pluginsrc%\SlaveTatsNG.dll %plugindest%\_SlaveTatsNG.dll
rem copy %pluginsrc%\*.pdb %plugindest%
copy %configsrc%\*.ini %plugindest%
set papyrussrc=C:\Build\SlaveTatsNG\papyrus
set scriptsdest=%dist%
rem mkdir %scriptsdest%\Scripts
rem mkdir %scriptsdest%\Scripts\Source
rem mkdir %scriptsdest%\Source\Scripts
rem copy %papyrussrc%\Scripts\*.pex %scriptsdest%\Scripts
rem copy %papyrussrc%\Source\Scripts\*.psc %scriptsdest%\Source\Scripts\
rem copy %papyrussrc%\Scripts\Source\*.psc %scriptsdest%\Scripts\Source\
