rem set pluginsrc=C:\Build\SlaveTatsNG\build\Debug
set pluginsrc=C:\Build\SlaveTatsNG\build\Release
set configsrc=C:\Build\SlaveTatsNG\config
set headersrc=C:\Build\SlaveTatsNG\include
set dist=C:\Build\SlaveTatsNG\dist\SlaveTatsNG
mkdir %dist%
mkdir %dist%\SKSE
mkdir %dist%\SKSE\Plugins
mkdir %dist%\SKSE\Plugins\SlaveTatsNG
set plugindest=%dist%\SKSE\Plugins
copy %pluginsrc%\*.dll %plugindest%
copy %pluginsrc%\*.pdb %plugindest%
copy %configsrc%\*.ini %plugindest%\SlaveTatsNG
copy %headersrc%\SlaveTatsNG_Interface.h %plugindest%\SlaveTatsNG
set papyrussrc=C:\Build\SlaveTatsNG\papyrus
set scriptsdest=%dist%
mkdir %scriptsdest%\Scripts
mkdir %scriptsdest%\Scripts\Source
mkdir %scriptsdest%\Source\Scripts
copy %papyrussrc%\Scripts\*.pex %scriptsdest%\Scripts
copy %papyrussrc%\Source\Scripts\*.psc %scriptsdest%\Source\Scripts\
copy %papyrussrc%\Scripts\Source\*.psc %scriptsdest%\Scripts\Source\
