::./RayTracer/x64/Debug/RayTracer.exe > a.ppm
set devenv="%DevenvPath%\devenv.exe"
echo on 
%devenv% ./RayTracer/RayTracer.sln /build release /Project RayTracer
cd ./RayTracer/x64/Release
RayTracer.exe > ../../../a.ppm
pause
