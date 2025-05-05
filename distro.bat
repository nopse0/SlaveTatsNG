set root="C:\Build\ColorGlass\SlaveTatsNG"
set pluginsrc=%root%\build\release-msvc
set configsrc=%root%\config
set headersrc=%root%\include
set dist=%root%\dist\SlaveTatsNG
mkdir %dist%
mkdir %dist%\SKSE
mkdir %dist%\SKSE\Plugins
mkdir %dist%\SKSE\Plugins\SlaveTatsNG
set plugindest=%dist%\SKSE\Plugins
copy %pluginsrc%\*.dll %plugindest%
copy %pluginsrc%\*.pdb %plugindest%
copy %configsrc%\*.ini %plugindest%\SlaveTatsNG
copy %headersrc%\SlaveTatsNG_Interface.h %plugindest%\SlaveTatsNG
set papyrussrc=%root%\papyrus
set scriptsdest=%dist%
mkdir %scriptsdest%\Scripts
mkdir %scriptsdest%\Scripts\Source
mkdir %scriptsdest%\Source\Scripts
copy %papyrussrc%\Scripts\*.pex %scriptsdest%\Scripts
copy %papyrussrc%\Source\Scripts\*.psc %scriptsdest%\Source\Scripts\
copy %papyrussrc%\Scripts\Source\*.psc %scriptsdest%\Scripts\Source\
