@echo off
make
pushd .\Keil_Project
uv4 -d .\TM4C123.uvprojx
popd
