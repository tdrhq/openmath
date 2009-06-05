# Microsoft Developer Studio Project File - Name="openmath" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=openmath - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "openmath.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "openmath.mak" CFG="openmath - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "openmath - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "openmath - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "openmath - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D "_NO_INTERNATIONAL_" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "openmath - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "_NO_INTERNATIONAL_" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "openmath - Win32 Release"
# Name "openmath - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\tornadomath\src\_expr.cpp
# End Source File
# Begin Source File

SOURCE=.\tornadomath\src\_oper.cpp
# End Source File
# Begin Source File

SOURCE=.\tornadomath\src\_oper_expr.cpp
# End Source File
# Begin Source File

SOURCE=.\tornadomath\src\cmdparser.cpp
# End Source File
# Begin Source File

SOURCE=.\tornadomath\src\expression_working.cpp
# End Source File
# Begin Source File

SOURCE=.\tornadomath\src\main.cpp
# End Source File
# Begin Source File

SOURCE=.\tornadomath\src\my_string.cpp
# End Source File
# Begin Source File

SOURCE=.\tornadomath\src\session.cpp
# End Source File
# Begin Source File

SOURCE=.\tornadomath\src\session_user.cpp
# End Source File
# Begin Source File

SOURCE=.\tornadomath\src\tornadomath.cpp
# End Source File
# Begin Source File

SOURCE=.\tornadomath\src\value.cpp
# End Source File
# Begin Source File

SOURCE=.\tornadomath\src\value_double.cpp
# End Source File
# Begin Source File

SOURCE=.\tornadomath\src\value_normal.cpp
# End Source File
# Begin Source File

SOURCE=.\tornadomath\src\valuestack.cpp
# End Source File
# Begin Source File

SOURCE=.\tornadomath\src\world.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\tornadomath\src\_expr.h
# End Source File
# Begin Source File

SOURCE=.\tornadomath\src\_oper.h
# End Source File
# Begin Source File

SOURCE=.\tornadomath\src\_oper_expr.h
# End Source File
# Begin Source File

SOURCE=.\tornadomath\src\cmdparser.h
# End Source File
# Begin Source File

SOURCE=.\tornadomath\src\config.h
# End Source File
# Begin Source File

SOURCE=.\tornadomath\src\dbgapi.h
# End Source File
# Begin Source File

SOURCE=.\tornadomath\src\expression.h
# End Source File
# Begin Source File

SOURCE=.\tornadomath\src\gt_lib.h
# End Source File
# Begin Source File

SOURCE=.\tornadomath\src\my_string.h
# End Source File
# Begin Source File

SOURCE=.\tornadomath\src\session.h
# End Source File
# Begin Source File

SOURCE=.\tornadomath\src\session_user.h
# End Source File
# Begin Source File

SOURCE=.\tornadomath\src\stackar.h
# End Source File
# Begin Source File

SOURCE=.\tornadomath\src\tpdefs.h
# End Source File
# Begin Source File

SOURCE=.\tornadomath\src\value.h
# End Source File
# Begin Source File

SOURCE=.\tornadomath\src\value_double.h
# End Source File
# Begin Source File

SOURCE=.\tornadomath\src\value_normal.h
# End Source File
# Begin Source File

SOURCE=.\tornadomath\src\value_vector_interface.h
# End Source File
# Begin Source File

SOURCE=.\tornadomath\src\valuestack.h
# End Source File
# Begin Source File

SOURCE=.\tornadomath\src\world.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
