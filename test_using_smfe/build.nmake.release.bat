@echo off
mkdir build.nmake.release
pushd build.nmake.release
cmake.exe -G "NMake Makefiles" -DCMAKE_BUILD_TYPE=Release -DSMFE_DIR="F:/proj/sm-feature-extraction" -DBOOST_DIR="F:/lib/boost/boost_1_53_0" -DBoost_USE_STATIC_LIBS=ON .. && nmake
popd

