CREATION OF AN OPENGL PROJECT (WHICH USES FREEGLUT) USING IDE :
****************************************************************
(Documentation By : Pradnya Vijay Gokhale)


I have performed the following steps on Microsoft Visual Studio 2010 and on
Windows 7 (32-bit) Operating System. However, all of these steps are applicable
with some minor changes right until Microsoft Visual Studio 2015. 

INTRODUCTION :
***************
The following is a document explaining the creation of an OpenGL Project, which
uses the open source windowing library - 'freeglut'.


PROCEDURE :
************

Step 1 : DOWNLOADING FREEGLUT !!!
-----------------------------------
Firsty, download the latest 'freeglut' (I am using 'freeglut-3.0.0', so the rest of the document shall be relative to 'freeglut-3.0.0') for whichever Operating
System you shall be working in. Suggested website for downloading freeglut :- http://freeglut.sourceforge.net/. Here, Windows users must go to the link 'Martin Payne's Windows binaries (MSVC and MinGW)' and download 
'freeglut-3.0.0-MSVC.zip'.

Step 2 : ABOUT THE DOWNLOADED FREEGLUT PACKAGE !!!
----------------------------------------------------
The downloaded ZIP file will have a name like 'freeglut-3.0.0-MSVC.zip'. Upon
decompressing it, a directory with the same name as the ZIP file will be
created. This directory will have 3 sub-directories and 2 text files as follows-

-> 'bin' directory - containing the 32-bit and 64-bit DLLs. The 64-bit DLL shall
    be in the 'x64' directory within the 'bin' directory.

-> 'include' directory -> containing a sub-directory named 'GL' which contains
    four header files - freeglut.h, freeglut_ext.h, freeglut_std.h and glut.h

-> 'lib' directory -> containing the 32-bit and 64-bit import libraries (.lib
    files). The 64-bit import library shall be in the 'x64' directory within the
   'lib' directory.

-> Readme.txt -> A text file containing instructions to make your project
   freeglut compatible.

-> Copying.txt -> A text file containing copyright information.

Step 3 : RENAME AND RELOCATE FREEGLUT DIRECTORY !!!
-----------------------------------------------------
Rename the unzipped directory as 'freeglut', for easy referencing.
Move or copy this directory to an easily accessible and important location, for
instance, move it directly to the C: drive (i.e: Root Drive). Now, we shall
access freeglut from the C: drive itself (i.e: C:\freeglut\).

Step 4 : RELOCATE FREEGLUT DLLs (DYNAMIC LINK LIBRARIES) !!!
------------------------------------------------------------
Visual Studio creates a 32-bit project by default. Hence, without making any
changes to it, copy the 32-bit DLL (C:\freeglut\bin\freeglut.dll) from the 'bin'
directory, i.e: the DLL which is NOT in 'x64' sub-directory of 'bin' directory,
to (assuming your project is 32-bit):

1) C:\Windows\System32\         (If your Operating System is 32-bit)
2) C:\windows\SysWOW64\         (If your Operating System is 64-bit)

Step 5 : CREATE A PROJECT !!!
------------------------------
1) Open Visual Studio IDE (Integrated Development Environment). DO NOT CLOSE THE
   IDE TILL YOU HAVE SUCCESSFULLY COMPLETED THE EXECUTION OF YOUR PROGRAM.

2) Go to 'File' menu -> 'New' -> 'Project...'

3) The 'New Project' dialog box appears. Select 'Visual C++' from the 'Installed
   Templates' under 'Recent Templates' in the left pane. Then, Select 'Win32
   Project' from the right pane. Mostly, this step is done by default.

4) a) Give a suitable name to the project by typing it in the 'Name' text box.
   b) Give the path (location) where the project is to be stored in the
      'Location' text box.
   c) Uncheck the 'Create directory for solution' checkbox.

5) Click the 'OK' button.

6) The 'Win32 Application Wizard - <project name>' dialog box appears.
   a) Select 'Application Settings' from the left pane.

   b) In the right pane, under 'Application type : ' select the 'Windows
      application' radio button and under 'Additional options : ' check the
      'Empty Project' checkbox.

   c) Click the 'Finish' button.
   
7) The project is now created.

8) Usually, the 'Solution Explorer' is open at the left side of the client area.
   If it is not present, open it by going to 'View' menu -> 'Solution Explorer'.
   
Step 6 : ADD NEW SOURCE CODE FILE(S) TO THE CREATED PROJECT !!!
----------------------------------------------------------------
1) In the Visual Studio IDE, go to the 'Project' menu -> 'Add New Item...' OR
   right-click on the project hive (NOT the solution hive) in the 'Solution
   Explorer' -> (from the floating menu) -> 'Add' -> 'New Item...'.
   The 'Add New Item - <project name>' dialog box appears.

2) In the left pane of this dialog box, under 'Installed Templates', select
   'Visual C++' (usually done by default). From the right pane, select the
    file type desired.

3) a) In the 'Name : ' text box below, type in the desired name for the file
      along with the correct extension.

   b) Check that the path specified by default in the 'Location : ' text box
      below, is the path of the appropriate project for which this file is to be
      written.

   c) Click the 'Add' button.
    
   d) The file, as specified, is added to the project and can be seen clearly in
      the client area as well as under 'Source Files' under the project hive in
      the 'Solution Explorer'.

Step 7 : MAKE THE PROJECT FREEGLUT COMPATIBLE !!!
--------------------------------------------------
Assumption : The unzipped directory of the downloaded freeglut zip exists by the
name of 'freeglut' directly on C: drive (i.e: C:\freeglut\), in accordance with
'Step 3' above. It is not mandatory to store the freeglut directory directly on
C: drive. We have done so just for easy and quick access to it.

1) In the Visual Studio IDE, in the 'Solution Explorer', right-click on the
   project hive and from the floating menu, select 'Properties' or go to
   'Project' menu -> 'Properties'. The '<project name> Property Pages' dialog
   box appears.

2) a) In the left pane, click on the arrow against 'C/C++' and from the options
      that appear thereafter, select 'General'. In the right pane, against
      'Additional Include Directories', type in the path of the 'include'
      directory of 'freeglut'. That is, in our case, we shall type 
      'C:\freeglut\include' (without the quotes). Then, press 'Enter' key from  
      keyboard. The entered path appears bold, hence confirming it. Click the
      'Apply' button. Do not close the dialog box. Do not click the 'OK' button
      just yet as it shall close the dialog box.

   b) Now, in the left pane of the dialog box, click on the arrow against
      'Linker' and from the options that appear thereafter, select 'General'.
      In the right pane, against 'Additional Library Directories', type in the
      path of the 'lib' directory of 'freeglut'. That is, in our case, we shall
      type 'C:\freeglut\lib' (without the quotes). Then, press 'Enter' key from
      keyboard. The entered path appears bold, hence confirming it. Click the
      'Apply' button. Do not close the dialog box. Do not click the 'OK' button
      just yet as it shall close the dialog box.

   c) Now, in the left pane of the dialog box, under 'Linker', select
      'Advanced'. In the right pane, against 'Entry Point', type in
      'mainCRTStartup' (without the quotes). Then, press 'Enter' key from  
      keyboard. The entry appears bold, hence confirming it. Click the 'Apply'
      button. Now, click the 'OK' button.

Step 8 : START CODING !!!
--------------------------
You can now start coding in the source code files. Upon finishing the writing of
your code, save it and go to 'Build' menu -> 'Rebuild <project name>'. The
entire source code of your project gets compiled and linked. Any errors or
warnings occurring, will be displayed in the 'Output Window' below. Once, your
code is free of errors and warnings, 'Build succeeded' will appear in the
'Output Window'.

Step 9 : EXECUTE YOUR CODE !!!
-------------------------------
Open 'Windows Explorer' and browse to your project directory. Inside it, you
will find the 'Debug' directory. Open it. You will see your executable file in
it which will have the name of your project followed by he extension '.exe'.
That is, your executable file will look like '<project name>.exe'.
Double-click on the .exe file to execute your code.
Once satisfied with the execution of the program, you may close the window,
hence terminating the application.


CONCLUSION :
*************
From now onwards, whenever you create an OpenGL Project which is compatible with
FREEGLUT, you must follow Steps 5 to 9 as mentioned above, for a successful
application. Steps 1 to 4 need to be done only once.
