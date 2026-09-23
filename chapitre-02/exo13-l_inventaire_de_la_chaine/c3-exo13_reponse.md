Available Toolchains
------------------------------------------------------------
Name       Family   Target OS   Arch     Env  
==============================================
host-gcc   gcc      Windows     x86_64   mingw
mingw      gcc      Windows     x86_64   mingw

## Ce qui est présent :
# Une famille de compilateur : gcc, via MinGW .
# Une seule cible : Windows / x86_64.
# Deux entrées nommées différemment (host-gcc et mingw)

## Ce qui manque :
-Aucun compilateur autre que gcc/mingw : pas de clang, pas de MSVC
-Aucune cible non-Windows
-Aucune architecture autre que x86_64

## Ce qu'il faudrait installer
- clang/LLVM pour une deuxième famille de compilateur
