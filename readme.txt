!!!! Project Complete !!!



*****  --------------------------  *****

All the code files are in the 'live-gesture-recognition' folder.
Please read this file 'readme.txt' and the User Manual 'manual.pdf' before beginning.

*****  --------------------------  *****

Download the .tar.gz or .zip file and uncompress it. It contains the code, the project report and the user manual.

Implementing the code is very simple. However sometimes executable files do not run
correctly, in which case the code has to be compiled before running. The packages required for compiling the code are gcc, opencv-doc, libcv2.1, linhighgui2.1, libcvaux2.1, libcv-dev, libcvaux-dev, linhighgui-dev, libx11-dev, and libxtst-dev. These packages can be collectively
installed from the Synaptic Package Manager or using individual system commands:

$ sudo apt-get install [package-name]

After installing all the packages compile the file - install.cpp using the command:

$g++ install.cpp -o install

Running the file install inturn compiles all the other required files, provided the required libraries are installed correctly and up-to-date.

$ ./install


**** If install runs correctly you dont need to do this ***
Altenetively, you can compile all the files individually using the command:
$ g++ `pkg-config opencv --cflags` [filename].cpp -o [filename] `pkg-config opencv --libs` -lX11 -lXtst
The files to be compiled are : initialize.cpp, main.cpp, gesture.cpp, addgesture.cpp, checkgesture.cpp and delgesture.cpp.
****  ---------------------------- ***

Before beginning run the file initialize:
$ ./initialize

The main code is run using the file gesture :
$ ./gesture

