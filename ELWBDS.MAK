###############################################################################
#####               This makefile generates ELWBDS.DLL                   #####
###############################################################################
!include $(WGDEV)\src\gcrules.mak

VIRDIR = .\GCVIRDAT
DLLLIB =                           \
     $(DLLLIB)                     \
     wgserver.lib     \
     galgsbl.lib

OBJFILES =          \
     elwbds.obj    
     
VIRFILES =          \ 
     GCVIRDAT\elwbds.vir 

start:              \
     $(GCBUILD)     \
     elwbds.dll

elwbds.dll:        \
     elwbds.h      \
     $(OBJFILES)    \
     $(DLLLIB)      \
     $(DEFILE)      \
     $(VIRFILES)
     $(LINK) $(LIBCMD) @&&|
$(PRODLL) $(OBJFILES)
$(RUNDIR)\$&
$(RUNDIR)\$&
$(DLLLIB) $(LINKDLL)
$(DEFILE)
|
