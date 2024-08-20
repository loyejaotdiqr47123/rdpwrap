========================================================================  
    DYNAMIC LINK LIBRARY. Overview of the RDPWrap Project  
========================================================================

This RDPWrap DLL library was automatically created using the application wizard.

This file provides a summary of the contents of all files included in the RDPWrap application.


RDPWrap.vcxproj  
    This is the main VC++ project file created using the application wizard. It contains information about the version of Visual C++ used to create the file, as well as details about the platforms, configurations, and features of the project selected via the wizard.

RDPWrap.vcxproj.filters  
    This is a filter file for VC++ projects created using the application wizard. It contains information about the mappings between files in your project and filters. These mappings are used in the IDE environment to group files with the same extensions under one node (for example, CPP files are mapped to the "Source Files" filter).

RDPWrap.cpp  
    This is the main source file of the DLL library.

    When creating this DLL library, there is no symbol export performed. Therefore, no LIB file is created when it is built. If this project needs to define a dependency on another project, you will need to add code to export symbols from the DLL library to ensure the creation of an export library, or set the "Skip Import Library" option to "Yes" in the "Linker" section of the project's "Property Pages".

/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp  
    These files are used to build a precompiled header file (PCH) named RDPWrap.pch and a precompiled types file named StdAfx.obj.

/////////////////////////////////////////////////////////////////////////////
Other notes.

Code fragments that need to be completed or modified are marked with “TODO:” comments in the application wizard.

/////////////////////////////////////////////////////////////////////////////