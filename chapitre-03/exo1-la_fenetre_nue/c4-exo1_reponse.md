## Le fichier .jenga :

#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# fenetre - Jenga Workspace (relie au kit Nkentseu, Debug-Windows uniquement)

from Jenga import *
from Jenga.GlobalToolchains import RegisterJengaGlobalToolchains

with workspace("fenetre"):
    RegisterJengaGlobalToolchains()

    configurations(['Debug'])
    targetoses([TargetOS.WINDOWS])
    targetarchs([TargetArch.X86_64])

    useconfig("C:/Users/EL GENIE/Desktop/Nkentseu/Nkentseu/Build/Kit/NkentseuKit/NkentseuKit.jenga")

    with project("fenetre"):
        windowedapp()
        language("C++")
        cppdialect("C++20")
        location("fenetre")
        files(["src/**.cpp"])
        usetoolchain("clang-mingw")
        usenkentseukit()

 ## Le fichier main.cpp:

 #include "NKWindow/NkWindow.h"
#include "NKWindow/Core/NkMain.h"

using namespace nkentseu;

NKENTSEU_DEFINE_APP_DATA(([]() {
    NkAppData d{};
    d.appName = "Ma salle";
    return d;
})());

int nkmain(const NkEntryState& state)
{
    (void)state;

    NkWindowConfig config;
    config.title  = "Ma salle";
    config.width  = 1280;
    config.height = 720;

    NkWindow fenetre(config);
    if (!fenetre.IsValid()) {
        return 1;
    }

    while (fenetre.IsOpen()) {
        NkEvents().PollEvents();
    }
    return 0;
}


## La capture :
https://github.com/ElGenie-beep/ani-4087/blob/a6a253001b0deb19ab96f16cd30a1e6cf37c5932/fene.png

##  temps 

 ##  avec cette commande j'ai eu la duree exacte de mon travail: 
PS C:\Users\EL GENIE\Desktop\fenetre> $d=(Get-Item "C:\Users\EL GENIE\Desktop\fenetre").CreationTime; $f=(Get-Item "C:\Users\EL GENIE\Desktop\fenetre\fenetre\Build\Bin\Debug-Windows\fenetre\fenetre.exe").LastWriteTime; "Début : 
$d"; "Fin : $f"; "Durée : " + ($f-$d)
Début : 09/28/2026 23:37:37
Fin : 09/29/2026 00:52:27
Durée : 01:14:50.7393743

 ## temps mesuré est de 1 h 14 min 50 s, soit environ 1 h 15.

Début : 28/09/2026 à 23:37 (création du dossier fenetre).
Fin : 29/09/2026 à 00:52 (dernière construction réussie du .exe).

