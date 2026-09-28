## Essai A (déjà exécuté)
PS C:\Users\EL GENIE\Desktop\chapitre 4> g++ -std=c++14 simu.cpp -o simu
>> .\simu | Select-String "image (38|39|40|41|42) "

image 38 focus=0 accum=29 yaw=1
image 39 focus=0 accum=30 yaw=1
image 40 focus=1 accum=0 yaw=4
image 41 focus=1 accum=0 yaw=4
image 42 focus=1 accum=0 yaw=4

## Observation 
1. Que fait accum pendant que la fenêtre n'a pas le focus ?
Il grossit à chaque image : 29 à l'image 38, 30 à l'image 39. La souris continue d'envoyer du mouvement, mais rien ne lit l'accumulateur ni ne le remet à zéro tant que la fenêtre n'a pas le focus.

2. Que fait yaw à l'image 40, alors que la main est immobile ?
Il passe de 1 à 4 d'un coup, alors que personne ne bouge la souris. La tête fait un saut brusque au retour dans la fenêtre. Ensuite (images 41 et 42) tout redevient stable.

3. Pourquoi ? D'où vient le 3 ?
Pendant les images 10 à 39, soit 30 images, l'accumulateur a reçu 1,0 par image sans jamais être vidé : il vaut donc 30. Au retour du focus, le code lit ce total et l'applique : 30 × 0,1 = 3, d'où le passage de 1 à 4. Ce sont les mouvements faits dehors qui sont appliqués d'un coup au retour.

## Essai B (déjà exécuté)

 PS C:\Users\EL GENIE\Desktop\chapitre 4> g++ -std=c++14 simu.cpp -o simu
>> .\simu | Select-String "image (38|39|40|41|42) "

image 38 focus=0 accum=0 yaw=1
image 39 focus=0 accum=0 yaw=1
image 40 focus=1 accum=0 yaw=1
image 41 focus=1 accum=0 yaw=1
image 42 focus=1 accum=0 yaw=1

## Observation 
essai B, avec remise à zéro hors focus

Images 38 et 39 (hors focus) : accum reste à 0 et yaw reste à 1.
Image 40 (retour du focus, main immobile) : yaw reste à 1. Aucun saut.
Images 41 et 42 : rien ne bouge non plus.

## Comparaison A contre B

	Essai A (sans remise à zéro hors focus) ,	Essai B (avec remise à zéro)
accum à l'image 39	,30,	0
yaw à l'image 40	passe de 1 à 4	reste à 1
Comportement au retour	saut de +3 alors que la main est immobile	rien, la tête reste où elle était

 l'essai B, la souris envoie toujours du mouvement hors focus, mais chaque image le jette (accumulateur = 0). Au retour, l'accumulateur est vide, donc il n'y a rien à appliquer.


 Essai A, sans remise à zéro hors focus. Aux images 38 et 39, la fenêtre n'a pas le focus et accum grossit (29, puis 30) pendant que yaw reste à 1. À l'image 40, le focus revient alors que la main est immobile, et yaw passe de 1 à 4. Les 30 images de mouvement faites dehors étaient restées dans l'accumulateur, et 30 × 0,1 = 3 est appliqué d'un coup.

Essai B, avec remise à zéro hors focus. accum reste à 0 pendant les images hors focus, et yaw reste à 1 à l'image 40 et après. Le mouvement fait dehors est jeté à chaque image, donc au retour il n'y a rien à appliquer.

Conclusion. Hors focus, la souris continue d'envoyer du mouvement brut à l'accumulateur. Sans remise à zéro, ce mouvement s'entasse et se déverse d'un coup au retour, ce qui fait sauter la tête alors que la main est immobile. La remise à zéro hors focus jette ce mouvement : la tête s'arrête quand la main s'arrête, comme l'exige le motif « accumuler et consommer ».

Précision sur la méthode. Je n'avais pas le code du moteur, donc ces observations viennent d'une petite simulation écrite en C++ (simu.cpp, 60 images, focus perdu de l'image 10 à 39). Elle reproduit le mécanisme mais n'est pas une observation du vrai moteur, où l'on cliquerait réellement ailleurs pendant dix secondes.
