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

        

## La capture :
