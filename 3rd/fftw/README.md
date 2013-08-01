## Using FFTW in Visual Studio 2010(2012)

Precompiled FFTW 3.3.1 Windows DLLs install using fftw-3.2.1-dll.zip, on my Windows XP machine.

Open cmd window and go to lib.exe folder C:\Program Files\Microsoft Visual Studio 10.0\VC\bin>

1.  Type lib /def:libfftw3-3.def
2.  Type lib /def:libfftw3f-3.def
3.  Type lib /def:libfftw3l-3.def

If you have a error on command, copy any mspdb80.dll or mspdb100.dll file to in bin directory.
You will get 6 files

libfftw3-3.exp, libfftw3-3.lib, libfftw3f-3.exp, libfftw3f-3.lib, libfftw3l-3.exp and libfftw3l-3.lib

and copy it to programming directory.

Delete all mspdb80.dll or mspdb100.dll file from bin directory.

Closed Project and open again and rebuild it again.
