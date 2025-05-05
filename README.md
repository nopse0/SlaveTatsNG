# SlaveTatsNG

SlaveTats as C++/SKSE plugin  

## Requirements
* [CMake](https://cmake.org/)
	* Add this to your `PATH`
* [Vcpkg](https://github.com/microsoft/vcpkg)
	* Add the environment variable `VCPKG_ROOT` to the path containing vcpkg
* [Visual Studio Community 2022](https://visualstudio.microsoft.com/)
	* Desktop development with C++
* [CommonLibSSE-NG](https://github.com/CharmedBaryon/CommonLibSSE-NG)

## Links:
[VMTHook](https://github.com/gfreivasc/VMTHook)


## User Requirements
* [Address Library for SKSE](https://www.nexusmods.com/skyrimspecialedition/mods/32444)
	* Needed for SSE/AE
* [VR Address Library for SKSEVR](https://www.nexusmods.com/skyrimspecialedition/mods/58101)
	* Needed for VR


## Building
See [commonlibsse-sample-plugin](https://gitlab.com/colorglass/commonlibsse-sample-plugin).
In short, open "Local Directory" SlaveTatsNG in Visual Studio, then VS automatically runs the CMake and VCPkg configuration. 
And, of course, you have to checkout the project first from Git:
```
git clone https://github.com/nopse0/SlaveTatsNG.git
```

## License
[Apache-2.0](LICENSE)
