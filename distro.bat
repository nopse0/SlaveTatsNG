set configsrc=C:\Build\SlaveTatsNG\config
set pluginsrc=C:\Build\SlaveTatsNG\build\Release
rem set pluginsrc=C:\Build\SlaveTatsNG\build\Debug
set dist=C:\Build\SlaveTatsNG\dist\SlaveTatsNG
mkdir %dist%
mkdir %dist%\SKSE
mkdir %dist%\SKSE\Plugins
set plugindest=%dist%\SKSE\Plugins
copy %pluginsrc%\SlaveTatsNG.dll %plugindest%\SlaveTatsNG.dll
copy %pluginsrc%\SlaveTatsNG.pdb %plugindest%\SlaveTatsNG.pdb
copy %configsrc%\*.ini %plugindest%
set papyrussrc=C:\Build\SlaveTatsNG\papyrus
set scriptsdest=%dist%
mkdir %scriptsdest%\Scripts
mkdir %scriptsdest%\Scripts\Source
mkdir %scriptsdest%\Source\Scripts
copy %papyrussrc%\Scripts\*.pex %scriptsdest%\Scripts
copy %papyrussrc%\Source\Scripts\*.psc %scriptsdest%\Source\Scripts\
copy %papyrussrc%\Scripts\Source\*.psc %scriptsdest%\Scripts\Source\
