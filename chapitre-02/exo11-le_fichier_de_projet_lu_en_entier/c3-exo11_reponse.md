#  fichier de configuration du projet XR (NKWindow)

### 1. Structure et livrables 

* Une bibliothèque statique principale (`NKWindow`) : Elle sert de couche d'abstraction logicielle pour le système de fenêtrage.
  
   *Trois applications de démonstration interactives (`Sandbox`, `SandboxCamera` et `SandboxCameraFull`): C livrables finaux se matérialisent sous la forme d'exécutables graphiques autonomes (`WINDOWED_APP`) .

### 2. Cartographie  du projet
L'architecture logicielle  de liaisons internes et de dépendances  :
* Architecture interne : applications de démonstration dépendent directement du module fonctionnel `NKWindow` via les directives `.
* Couches matérielles Windows : (`opengl32`, `gdi32`, `user32`, `dwmapi`, `shell32`, `xinput`).
* Couches matérielles Linux : Dépendances  sur le protocole de communication du serveur d'affichage graphique `X11` .
* Couches matérielles mobiles (Android): Utilisation des API bas niveau du kit de développement natif (`android`, `log`).

### 3. Variations et adaptations du système d'exploitation

* Windows : Initialisation exclusive via l'interface native Win32 .
* Linux: s'appuyant sur XLib pour les environnements de bureau.
* macOS & iOS : Intégration  avec l'écosystème Apple (gestion via Cocoa/UIKit, et interfaces de rendu Metal ou QuartzCore).
* Web : Compilation portable optimisée pour s'exécuter dans un navigateur via la technologie WebAssembly assistée par l'émulateur Emscripten.

### 4.  trois pièges documentés en commentaires

####  Le mode d'exécution Linux virtuel 

* Mécanisme documenté : intégration continue (CI) ou l'utilisation de WSL sans serveur d'affichage physique, une branche conditionnelle `system:Linux && options:headless`.
  
* Conséquence de son omission : Sans ce filtre d'affichage virtuel, le binaire tenterait de forcer l'ouverture d'un contexte de rendu X11 physique inexistant.

####  Le flag d'asynchronisme web (`ASYNCIFY`)

* Mécanisme documenté: La compilation à destination des navigateurs web l'injection de l'option spécifique `emscriptenextraflags(["-s", "ASYNCIFY"])`.
* Conséquence de son omission : Les applications de bureau traditionnelles s'appuient sur une boucle de rendu synchrone et infinie. Sans l'activation d'ASYNCIFY.

####  La gestion des cibles embryonnaires (Le fallback HarmonyOS)

* Mécanisme documenté : Pour la plateforme HarmonyOS dont l'implémentation graphique n'est pas encore finalisée.
* Conséquence de son omission : cette solution de repli temporaire (fallback) venait à être retirée du fichier projet, le compilateur se retrouverait face à un catalogue de fonctions déclarées mais totalement vides.
