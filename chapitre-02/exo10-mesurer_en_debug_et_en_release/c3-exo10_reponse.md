## resultat Debug:


PS C:\Users\EL GENIE\Desktop\calcul\calcul> jenga build --config Debug

╔══════════════════════════════════════════════════════════════════╗
║                                                                  ║
║                ██╗███████╗███╗   ██╗ ██████╗  █████╗             ║
║                ██║██╔════╝████╗  ██║██╔════╝ ██╔══██╗            ║
║                ██║█████╗  ██╔██╗ ██║██║  ███╗███████║            ║
║           ██   ██║██╔══╝  ██║╚██╗██║██║   ██║██╔══██║            ║
║           ╚█████╔╝███████╗██║ ╚████║╚██████╔╝██║  ██║            ║
║            ╚════╝ ╚══════╝╚═╝  ╚═══╝ ╚═════╝ ╚═╝  ╚═╝            ║
║                                                                  ║
║             Multi-platform C/C++ Build System v2.8.0             ║
║                                                                  ║
╚══════════════════════════════════════════════════════════════════╝

Loading workspace...

Configuration: Debug
Target:        Windows x86_64
Toolchain:     mingw

Build Order (1 projects):
  1. calcul [CONSOLE_APP]


╔══════════════════════════════════════════════════════════════════════════════════════════════╗
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)
✓   [1/1] Compiled: main.cpp
ℹ Linking...
✓ Built: Build\Bin\Debug-Windows\calcul\calcul.exe

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 3.32s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                BUILD COMPLETED                                 
════════════════════════════════════════════════════════════════════════════════
Projects Built:  1/1
Time:           3.32s
Status:         ✓ SUCCESS
════════════════════════════════════════════════════════════════════════════════

PS C:\Users\EL GENIE\Desktop\calcul\calcul> Build\Bin\Debug-Windows\calcul\calcul.exe
Debut du calcul lourd...
Resultat du calcul : 0.447924
Temps d'execution : 74153.6 ms
PS C:\Users\EL GENIE\Desktop\calcul\calcul> 

 ## resultat release

PS C:\Users\EL GENIE\Desktop\calcul\calcul> jenga build --config Release

╔══════════════════════════════════════════════════════════════════╗
║                                                                  ║
║                ██╗███████╗███╗   ██╗ ██████╗  █████╗             ║
║                ██║██╔════╝████╗  ██║██╔════╝ ██╔══██╗            ║
║                ██║█████╗  ██╔██╗ ██║██║  ███╗███████║            ║
║           ██   ██║██╔══╝  ██║╚██╗██║██║   ██║██╔══██║            ║
║           ╚█████╔╝███████╗██║ ╚████║╚██████╔╝██║  ██║            ║
║            ╚════╝ ╚══════╝╚═╝  ╚═══╝ ╚═════╝ ╚═╝  ╚═╝            ║
║                                                                  ║
║             Multi-platform C/C++ Build System v2.8.0             ║
║                                                                  ║
╚══════════════════════════════════════════════════════════════════╝

Loading workspace...

Configuration: Release
Target:        Windows x86_64
Toolchain:     mingw

Build Order (1 projects):
  1. calcul [CONSOLE_APP]


╔══════════════════════════════════════════════════════════════════════════════════════════════╗
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)
✓   [1/1] Compiled: main.cpp
ℹ Linking...
✓ Built: Build\Bin\Release-Windows\calcul\calcul.exe

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 3.55s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                BUILD COMPLETED                                 
════════════════════════════════════════════════════════════════════════════════
Projects Built:  1/1
Time:           3.55s
Status:         ✓ SUCCESS
════════════════════════════════════════════════════════════════════════════════

PS C:\Users\EL GENIE\Desktop\calcul\calcul>  Build\Bin\Release-Windows\calcul\calcul.exe
Debut du calcul lourd...
Resultat du calcul : 0.447924
Temps d'execution : 74232.7 ms

## interpretation 

 ## Mes mesures
Configuration	Résultat	Temps
Debug	0.447924	74 153,6 ms
Release	0.447924	74 232,7 ms
Le résultat est identique dans les deux cas : le calcul est correct et cohérent.
Le temps est identique : l'écart est de 79 ms sur 74 s, soit environ 0,1 %, et Release est même un peu plus lent. C'est du bruit de mesure, pas une vraie différence.

sachant une image dure environ 11 ms. Mon calcul dure environ 74 s, soit près de 6 700 images. Il est donc impossible de l'exécuter d'un seul bloc sur le thread de rendu, en Debug comme en Release.

 ## DEcision

une mauvaise décision
En principe, c'est la mesure Debug. Ce n'est pas la version livrée, car elle n'est pas optimisée
On ne décide donc jamais sur une mesure Debug.
