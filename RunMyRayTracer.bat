::./RayTracer/x64/Debug/RayTracer.exe > a.ppm
set devenv="D:\VSProgramFiles\VS2019\Common7\IDE\devenv.exe"
echo on 
%devenv% ./RayTracer/RayTracer.sln /build debug
cd ./RayTracer/x64/Debug
RayTracer.exe > ../../../a.ppm
pause
