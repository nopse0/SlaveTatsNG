set dist=C:\Build\SlaveTatsNG\dist\SlaveTatsNG
mkdir %dist%
mkdir %dist%\SKSE
mkdir %dist%\SKSE\Plugins
set plugindest=%dist%\SKSE\Plugins
set pluginsrc=C:\Build\SlaveTatsNG\buildae\Debug
copy %pluginsrc%\*.dll %plugindest%
copy %pluginsrc%\*.pdb %plugindest%
set papyrussrc=C:\Build\SlaveTatsNG\papyrus
set scriptsdest=%dist%
mkdir %scriptsdest%\Scripts
mkdir %scriptsdest%\Scripts\Source
mkdir %scriptsdest%\Source\Scripts
copy %papyrussrc%\Scripts\*.pex %scriptsdest%\Scripts
copy %papyrussrc%\Source\Scripts\*.psc %scriptsdest%\Source\Scripts\
copy %papyrussrc%\Scripts\Source\*.psc %scriptsdest%\Scripts\Source\
