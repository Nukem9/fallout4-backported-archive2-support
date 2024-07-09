# Backported Archive2 Support System

A Fallout 4 Script Extender plugin that adds support for the new BA2 archive format introduced in NG update 1.10.980 to versions 1.10.163 and older. Fixes crashes, similar to Backported Extended ESL Support for Skyrim Special Edition.

## Building

- CMake and vcpkg are expected to be set up beforehand. Visual Studio 2022 is recommended.
- \<preset\> is `f4se`.
- \<build_preset\> is `f4se-release` or `f4se-debug`.

```
git clone --recurse-submodules https://github.com/Nukem9/fallout4-backported-archive2-support.git
cmake --preset <preset>
cmake --build --preset <build_preset>
```

## Installation

- For developers, edit `CMakeUserEnvVars.json` and set `GAME_ROOT_DIRECTORY` to Fallout 4's root directory. The build script will automatically copy library files to the game folder.

- For manual F4SE installs, place `BackportedBA2Support.dll` in the corresponding `Fallout 4\Data\F4SE\Plugins` folder. An example path is: `C:\steamapps\common\Fallout 4\Data\F4SE\Plugins\BackportedBA2Support.dll`

## License

- [GPLv3](COPYING) with [exceptions](EXCEPTIONS).
- Files within the `resources` folder are proprietary and not licensed. Dependencies are under their respective licenses.