## -ETAPE 1:  -Les capteurs mesurent le mouvement    -ORDRE DE GRANDEUR: 1à2ms  -Valeurs: VRAI  -SOURCE: datasheet bosch Sensortec BMI085/BMI270-IMU pour casque VR : latence motion-to-photon<3ms
## -ETAPE 2: -Le système transmet la mesure  -ORDRE DE GRANDEUR: 1à3ms   -Valeurs: VRAI  -SOURCE: Sunny et ai, AI Enabbled 6G FOR Semantic Metaverse - décomposition du budget de latence VR: traitement de l'entrée  1à3ms 
## -ETAPE 3: - VOTRE application décide et dessine   -ORDRE DE GRANDEUR: 5à11ms   -Valeurs: VRAI  -SOURCE: Sunny et ai, AI Enabbled 6G FOR Semantic Metaverse   - décomposition, catégorie rendu : 2à10ms 
## -ETAPE 4: -Composition assemble    -ORDRE DE GRANDEUR: 1à2ms  -Valeurs: VRAI  -SOURCE: Documentation Meta Horizon OS Developers -décrit  le rôle du compositor : aucune valeur chiffrée 
## -ETAPE 5:L'ecran affiche la ligne  -ORDRE DE GRANDEUR: 2à5ms   -Valeurs: VRAI   -SOURCE: VR ET AR wiki  -dalles OLED de casques VR : temps de montée = 0.3ms, temps de descente = 0.5ms
