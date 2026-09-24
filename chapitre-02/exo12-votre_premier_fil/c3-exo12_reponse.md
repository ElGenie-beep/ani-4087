# Voici mon fichier de projet `Ma salle.jenga`, préparé pour tout le livre. Il se construit déjà (`jenga build` réussit en Debug avec la chaîne `mingw`). Chaque ligne commentée dit ce qu'il faudra y ajouter au sprint correspondant ; je les décocherai une à une.


```python
from Jenga import *

with workspace("Ma salle"):
    configurations(['Debug', 'Release'])
    targetoses([TargetOS.WINDOWS])
    # Sprint 16 : ajouter Android dans targetoses([...]) pour le déploiement
    targetarchs([TargetArch.X86_64])

    # Project: Ma salle
    with project("Ma salle"):
        windowedapp()
        language("C++")
        cppdialect("C++17")
        location("Ma salle")
        files(["src/**.cpp", "include/**.hpp"])

        # Sprint 3  : NKWindow et NKEvent : les ajouter en tête de links([...]) ; bibliothèques système Windows dans filter("system:Windows")
        # Sprint 4  : NKRHI et NKRenderer : les ajouter dans links([...]) avant NKWindow, le lieur lisant la liste du plus haut au plus bas
        # Sprint 5  : Images, modèles, textes, sons : ajouter les modules correspondants dans links([...]) (noms à relever dans le chapitre) ; les ressources sont dans le paquet, pas ouvertes avec fopen
        # Sprint 6  : La tête, l'orientation et les deux yeux : ajouter NKMath et NKXR dans links([...])
        # Sprint 7  : La cadence et la prédiction : a priori rien à ajouter ; mesurer uniquement en Release, jamais en Debug
        # Sprint 8  : Les chaînes d'échange : à préciser à la lecture du chapitre
        # Sprint 9  : Les actions : ajouter le module d'entrées/actions dans links([...]) (nom à relever dans le chapitre)
        # Sprint 10 : La composition et les couches : ajouter le module de composition dans links([...]) (nom à relever dans le chapitre)
        # Sprint 11 : Lire le vrai backend, et la même application sur deux backends : choisir le backend avec un filter("options:...") ou un define, déclaré aussi côté programme pour éviter l'en-tête « coquille vide »
        # Sprint 12 : Rendre deux fois : à préciser à la lecture du chapitre
        # Sprint 13 : La porte s'ouvre : à préciser à la lecture du chapitre
        # Sprint 14 : Des panneaux qu'on lit, et le son qui place les choses : ajouter les modules de texte/interface et d'audio spatial dans links([...])
        # Sprint 15 : Quelqu'un d'autre entre : à préciser à la lecture du chapitre
        # Sprint 16 : Bâtir et livrer : filter("system:Android") pour Android, puis jenga build, package, sign, deploy ; clé de signature gardée hors du dépôt
        # Sprint 17 : Approfondissement : à préciser à la lecture du chapitre
```
