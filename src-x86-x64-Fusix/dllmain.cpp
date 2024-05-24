// Include the header file "stdafx.h", which is a Visual Studio compiler-specific macro that includes some header files at the beginning, so that they can be included during compilation.
#include "stdafx.h"

// Define a function that returns a boolean value
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    // This function returns true, indicating that the module can be safely initialized
    return true;
}

// Note: This function is a Visual Studio compiler-specific function that is called in a DLL module to implement initialization logic. In this function, we return true, indicating that the module can be safely initialized.