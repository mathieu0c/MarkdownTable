# s7a_STM32_VSCode

> __**ATTENTION**__ : Si vous utilisez les machines de l'ENIB et que vous n'utilisez pas votre machine personnelle, je ne peux pas garantir le fonctionnement de ce qui est fourni ici.

Ce repo contient les outils nécessaires à l'utilisation des cartes STM32 F411RE/F103RB avec ***VSCode*** (Ou Codium) notamment pour les matières **Bus Can** et **Projet Robot**.

Le but étant de remplacer l'IDE infâme qu'est Eclipse.

<br/>

<!--MARKDOWN_INDEX_BEGIN-->
<!--MARKDOWN_INDEX_END-->

# Solution rapide (Compter 5-10min)

<br/>

## 1 - Installer le SDK_eled

> Ne l'installez que si ce n'a pas encore été fait

### Méthode 1
<br/>

Utilisez ces commandes dans un terminal
```
wget -q --show-progress -c --directory-prefix $PWD https://www.enib.fr/~kerhoas/INSTALL_/install_ide.sh.zip
unzip install_ide.sh.zip
rm -f install_ide.sh.zip
chmod +x install_ide.sh
bash install_ide.sh
```

### Méthode 2
<br/>

Suivre la procédure décrite sur le site de Vincent KERHOAS si ce n'a pas encore été fait :
https://www.enib.fr/~kerhoas/install.html

> Procédure "1.IDE Eclipse / Tdb ( ECLIPSE + TDB + GCC-ARM-NONE-EABI + OPENOCD )"

<br/>
<br/>

## 2 - Installer les extensions VSCode

### 1 -> Extension essentielle
<br/>

Pour cela :
1. Ouvrez VSCode
2. Basculez sur l'onglet "Extensions" :
    - Ctrl+Shift+X
    - Ou cliquez sur l'icone suivant :
        ![](Docs/Images/extensionMarket.png)
3. Recherchez l'extension "Cortex-Debug"
    ![](Docs/Images/extCortexDebug.png)
4. Installez l'extension créée par **marus25** en cliquant sur le bouton "Install"
    ![](Docs/Images/extCortexDebugInstall.png)


<br/>

### 2 -> Extensions conseillées

<br/>

Je vous conseille vivement d'installer les extensions suivantes qui augmenteront significativement votre confort de travail.

Cela ne prend que 2min que vous gagnerez en programmant après.

1. C/C++ par **Microsoft**

    L'extension la plus complète et efficace que j'aie pu essayer pour la programmation en C/C++ sur VSCode :
    ![](Docs/Images/extCpp.png)
    https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools

2. Bracket Pair Colorizer 2 par **Coenraads**

    Très très efficace pour se repérer au milieu des différentes accolades et parenthèses :
    ![](Docs/Images/extBP2.png)
    https://marketplace.visualstudio.com/items?itemName=CoenraadS.bracket-pair-colorizer-2



<br/>
<br/>

## 3 - Initialiser le dossier du projet
<br/>

Utilisez un terminal pour vous placer à la racine du projet STM32 (à l'aide de `cd`).

> ***Note*** : Cette opération sera à répéter pour chaque projet puisque lié directement au dossier de celui-ci.

Exemple de chemin :
`/home/mathieu/Documents/TRAVAIL/crs_robot/WORKSPACE_ROBOT/stm32f411_base`

Une fois à la racine, exécutez les commandes suivantes :
```
wget -q --show-progress -c --directory-prefix="$PWD" https://git.enib.fr/m8charle/s7a_stm32_vscode/-/raw/master/EnibSTMInit.sh
chmod +x EnibSTMInit.sh
bash EnibSTMInit.sh
```

Suivez les instructions s'affichant à l'écran.

(Décrites ci-après si besoin est.)

1. Confirmation du dossier de la racine du projet : `Init folder <VotreChemin> ? : [y/n] : `

    Répondre en appuyant sur `y` (yes) ou `n` (no)

2. Sélection du type de carte utilisée :
    - F411 en projet Bus CAN
    - F403 en projet Robot
    
    <br/>

    `Card type : [411/103] (enter 'q' to quit):`
    
    Répondre en rentrant l'une des valeur entre les crochets ou `q` pour quitter

3. En cas de succès, un message de ce type devrait être affiché : `Successfully init <VotreChemin>`

    Dans le cas contraire, vous pouvez demander assistance ici : https://git.enib.fr/m8charle/s7a_stm32_vscode/-/issues

    En créant une nouvelle demande avec le bouton **`New Issue`** :
    ![](Docs/Images/gitIssue.png)

    > ***Note*** : Afin de pouvoir ouvrir une demande, vous devrez vous connecter avec cotre compte enib sur le gitLab

<br/>
<br/>

## 4 - Ouvrir le dossier du projet avec VSCode
<br/>

Si vous avez toujours votre terminal placé à la racine du projet STM32, il vous suffit de lancer la commande suivante.
```
code .
```

Dans le cas contraire, rouvrez un terminal, replacez vous à la racine du projet et exécutez la commande ci-dessus.

> ***Note*** : Il est important d'ouvrir le dossier entier et non un unique fichier sans quoi cela ne marchera pas.


<br/>

# Utilisation

<br/>

## 1 - Compilation
<br/>

Pour compiler le projet il faut exécuter l'action
```
Run build task (Ctrl+Maj+B)
```
Visible dans le menu **`Terminal`**

VSCode vous laisse alors le choix entre deux actions :
![](Docs/Images/buildTask.png)

Sélectionnez l'action souhaitée à l'aide des flèches ↑↓ puis validez avec entrée.

> ***Note*** : Si VSCode vous refez de nouveau plusieurs proposition comme cela :
![](Docs/Images/buildTask2.png)
Je vous conseille de choisir la première option ou la **deuxième** pour ne pas avoir à répéter cette action à l'avenir.<br>
Validez à nouveau avec entrée.

<br/>

Le résultat de la compilation s'affiche dans une fenêtre `terminal` :
![](Docs/Images/buildTask3.png)

<br/>
<br/>

## 2 - Lancement du programme
<br/>

Pour exécuter le programme sur la carte en mode débug, il faut exécuter l'action :
```
Start Debugging (F5)
```
Visible dans le menu `Run`
<br/>

Une fois ce mode lancé, une nouvelle vue (perspective) s'ouvre :
![](Docs/Images/runTask.png)

<br/>

Il s'agit de la perspective Debug.

A gauche, la section `watch` permet d'afficher une valeur lorsque le débogueur est **arrêté**.

Les différentes actions du débogueur sont disponibles dans la petite barre d'action dans la partie haute de l'écran.

<br/>
<br/>

## 3 - En cas de problème

<br/>

Vous pouvez demander assistance ici : https://git.enib.fr/m8charle/s7a_stm32_vscode/-/issues

En créant une nouvelle demande avec lebouton **`New Issue`** :
![](Docs/Images/gitIssue.png)

> ***Note*** : Afin de pouvoir ouvrir unedemande, vous devrez vous connecter aveccotre compte enib sur le gitLab


<br/>
<br/>
<br/>
<br/>

### En rédaction 
# Procédure manuelle détaillée

## Pré-requis

Il est nécessaire malgré tout d'installer les outils nécessaires à l'utilisation de la chaîne de développement ARM.