# TruckTechHub

Bonjour, bienvenue dans notre projet TruckManiaStadium

Notre projet se constitue ainsi : le fichier shell qui est la racine du projet (projet.sh), un fichier texte contenant un message d'aide (Aide.txt) et un dossier contenant le makefile et deux sous-dossiers contenant respectivement les options s et t. Il y a un également un fichier demo mais celui-ci sert uniquement à montrer les résultats que le programme génère à partir du fichier de données passé en argument.

Ce projet peut réaliser jusqu'à 5 traitements différents : l'option -d1, l'option -d2, l'option -l, l'option -s, l'option -t et l'option h

Pour utiliser ce programme, il vous faudra exécuter une des deux commandes suivantes : 

- bash projet.sh 'Fichier' 'Une ou plusieurs options' // Exemple : bash projet.sh data.csv -d1 -s -l 

- ./projet.sh 'Fichier' 'Une ou plusieurs options' // Exemple : ./projet.sh data.csv -d2 -t

ATTENTION : Pour exécuter la deuxième commande, il vous faudra donner les droits d'exécution au script shell projet.sh avec la commande chmod // Exemple : chmod 777 projet.sh

De plus, si l'on veut obtenir de l'aide, il faut donc entrer l'option -h dans les options mais il est à noter qu'il n'est pas nécéssaire d'entrer le nom du fichier à traiter (En effet, on cherche à obtenir de l'aide et non à traiter les données du fichier).

Pour obtenir de plus amples informations sur les différentes options disponible, nous vous invitons à lancer l'exécution du script shell et d'entrer l'option -h qui pourra vous renseigner sur ces dernières.

IMPORTANT : Pour le bon fonctionnement du programme, vous aurez besoin de télécharger les packages suivants :
- imagemagick (sudo apt install imagemagick)
- gnuplot (sudo apt install gnuplot)

Nous vous souhaitons une bonne journée :)
