echo off

del /S /Q /F build
rd /s /Q build
mkdir build

pushd build 
cmake ..
popd