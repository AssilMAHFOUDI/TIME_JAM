# TIME_JAM adaptation du projet Space Collector
Équipe du projet
Nom de l'équipe : TIME_JAMMembres :  

MAHFOUDI Assil  
GADEBILLE Baptiste  
BOURAS Amar  
ELOTMANI Nassima  
HADJI Mourad

Sommaire

Introduction générale
Objectifs pédagogiques
Objectifs fonctionnels
Démarche étape par étape
Explication de la stratégie
Principales difficultés et solutions
Éléments développés du jeu
Prérequis pour l'exécution
Notions apprises
Perspectives d'amélioration
Conclusion

Introduction générale
Dans le cadre du module Systèmes d’exploitation embarqués, le projet Space Collector est un jeu de stratégie spatiale multijoueur basé sur la programmation embarquée et la coordination multi-agent. Chaque équipe contrôle une flotte de neuf vaisseaux (collecteurs, attaquants, explorateurs) avec pour objectif de capturer toutes les planètes assignées avant ses adversaires, tout en protégeant ses unités et en contrant les stratégies ennemies.
Objectifs pédagogiques
Le projet vise à développer les compétences suivantes :

Maîtriser la programmation multitâche avec CMSIS RTOS v2 pour gérer les threads des vaisseaux.
Implémenter une communication robuste par liaison série entre les composants du système.
Concevoir des algorithmes autonomes pour le déplacement, l’attaque et l’exploration des vaisseaux.
Interpréter les données complexes du radar pour une prise de décision stratégique.
Adopter les bonnes pratiques embarquées : tests unitaires, automatisation via GitHub Actions et documentation claire.

Objectifs fonctionnels
Le projet cherche à :

Développer une stratégie autonome pour collecter les planètes, attaquer, explorer et réparer les vaisseaux.
Coordonner le pilotage des vaisseaux en respectant les contraintes de vitesse, d’angle, de délais d’attaque et de portée radar.
Assurer une communication efficace entre entités pour garantir la cohérence et le respect des règles du jeu.

Démarche étape par étape

Mise en place de l’environnement de travail collaboratif :
Création d’un dépôt Git avec une branche principale main et une branche de développement development.


Prise en main de la carte électronique STM32F4 Discovery :
Configuration et familiarisation avec la carte pour le développement embarqué.


Installation des outils nécessaires :
Utilisation du compilateur GCC pour les tests unitaires sur PC.
Adoption de la bibliothèque MinUnit pour les tests unitaires.
Création d’un projet portable avec PlatformIO pour l’environnement embarqué.
Installation d’outils de vérification de code (pre-commit, Cppcheck, gcovr) via uv pour assurer la qualité et la fonctionnalité.


Implémentation des premiers tests unitaires :
Développement de tests pour les fonctions de base comme move et fire en utilisant MinUnit.


Mise en place d’une pipeline CI :
Configuration d’un pre-commit lançant les tests unitaires, l’analyse statique avec Cppcheck et la couverture de code avec gcovr.
Rejet des commits si les tests échouent ou si la couverture est insuffisante.
Création d’une pipeline GitHub Actions pour exécuter ces vérifications à chaque push.


Évolution des tests unitaires :
Ajout progressif de tests unitaires plus complexes au fur et à mesure du développement.


Communication par liaison série :
Établissement d’une connexion série entre la carte STM32F4 et le serveur pour envoyer et recevoir des trames.
Parsing des données reçues pour assurer une interprétation correcte des informations.


Développement de stratégies de jeu :
Implémentation de stratégies autonomes de plus en plus sophistiquées, exploitant les données du radar pour optimiser les déplacements, attaques et explorations.


Amélioration de la qualité du code :
Refactorisation pour améliorer la lisibilité, la modularité et la maintenabilité, en respectant les standards (ex. : conventions de style adaptées au C).



Explication de la stratégie
La stratégie du jeu repose sur les étapes suivantes :

Lecture des données radar : Récupération des informations brutes du radar.
Parsing des données : Organisation des informations dans deux structures :
Tableau ships[] pour les vaisseaux alliés.
Tableau planets[] pour les planètes.


Classement des planètes : Tri des planètes par distance croissante par rapport à la base la plus proche.
Déploiement des collecteurs : Envoi des collecteurs vers les planètes ciblées.
Protection par les attaquants : Assignation des attaquants pour escorter les collecteurs.
Gestion des réparations : Retour des vaisseaux endommagés à la base pour réparation.
Retour des collecteurs : Rapatriement des planètes collectées à la base.
Condition de victoire : La partie est gagnée lorsque toutes les planètes assignées sont récupérées.

Principales difficultés et solutions

Compilation multiplateforme :
Problème : Les commandes de compilation diffèrent entre Linux et Windows, ce qui empêche le bon fonctionnement du pre-commit sur les deux systèmes.
Solution : Utilisation d’une commande basée sur sh exécutable via Git Bash, compatible avec les deux OS :  sh -c 'gcc -I. -Iinclude -lm ./test/test_player.c ./src/player_action.c -o /tmp/test_player_now -lm && /tmp/test_player_now'




Installation des outils de vérification :
Problème : Difficulté à installer et rendre fonctionnels les outils comme pre-commit et gcovr immédiatement après leur configuration.
Solution : Utilisation de uv pour installer les packages nécessaires et simplifier leur configuration et leur usage.


Parsing des données radar :
Problème : La fonction de parsing, fonctionnelle sur PC avec tous les tests unitaires réussis, plantait sur la carte STM32F4 en raison de :
Mémoire stack insuffisante.
Utilisation de fonctions de la bibliothèque standard (ex. : strtok) inadaptées à l’embarqué.
Conflits avec stdio.h due à des redéfinitions de fonctions dans le projet.


Solution :
Augmentation de la taille de la stack.
Développement de fonctions de substitution pour éviter les bibliothèques standard.
Adaptation des fonctions de parsing aux besoins spécifiques, en évitant les bibliothèques complexes.





Éléments développés du jeu
Le projet inclut les éléments suivants, implémentés en C pour la carte STM32F4 Discovery :

Fonctions de base : move (déplacement des vaisseaux), fire (tir des attaquants), radar (lecture des données brutes), attack (gestion des attaques).
Parsing des données : parse_radar_data pour organiser les informations radar dans des structures adaptées.
Navigation : go_planet (envoi d’un vaisseau vers une planète, à décommenter pour utilisation en raison de problèmes avec pre-commit) et go_base (retour à la base pour réparation ou dépôt, à décommenter pour utilisation en raison de problèmes avec pre-commit).
Stratégie : reorder_planets (tri des planètes par distance à la base, de la plus proche à la plus éloignée).
Orientation : calculate_angle (calcul de l’angle pour orienter un vaisseau vers un point, une planète, un autre vaisseau ou la base).

Structures de données :

Planet : Représente une planète avec son type, ID, coordonnées (abscissa, ordinate), vaisseau associé et statut de capture.
Ship : Décrit un vaisseau avec son type, équipe, ID, coordonnées et état (endommagé ou non).
Base : Contient les coordonnées de la base de l’équipe.
Radar : Agrège les tableaux planets[] et ships[], le nombre d’éléments, la base et l’ID du radar pour centraliser les données du jeu.

Prérequis pour l'exécution
Pour exécuter le projet Space Collector, les outils suivants doivent être installés :

GCC : Compilateur C pour les tests unitaires sur PC.
MinUnit : Bibliothèque pour les tests unitaires des fonctions de base (move, fire, etc.).
PlatformIO : Environnement de développement pour créer un projet portable sur la carte STM32F4 Discovery.
uv : Gestionnaire de packages pour installer les outils de vérification (pre-commit, Cppcheck, gcovr).
Pre-commit : Outil pour exécuter des vérifications automatiques avant chaque commit (tests unitaires, analyse statique, couverture de code).
Cppcheck : Outil d’analyse statique pour détecter les erreurs dans le code C.
gcovr : Outil pour mesurer la couverture de code par les tests unitaires.
Git Bash : Nécessaire pour exécuter les commandes de compilation multiplateforme (ex. : commande sh pour GCC).

Notions apprises
Le projet a permis d’acquérir les compétences suivantes :

Programmation embarquée, notamment en multitâche avec CMSIS RTOS v2, communication série et tests unitaires.
Pratique du développement piloté par les tests (TDD) pour assurer la fiabilité des fonctions critiques.
Mise en place d’un système CI robuste avec double validation (pre-commit et GitHub Actions) intégrant Cppcheck et gcovr pour la qualité et la couverture du code.
Compréhension des contraintes de l’embarqué, notamment pour l’utilisation des bibliothèques standard et la gestion de la mémoire (ex. : stack limitée).
Techniques de parsing de données en C, en évitant les bibliothèques inadaptées.
Organisation des données via des structures (ships[], planets[]) pour une gestion efficace.
Utilisation de uv comme gestionnaire de packages pour simplifier l’installation des outils.

Perspectives d'amélioration
Pour optimiser le projet Space Collector, les améliorations suivantes sont envisagées :

Exploitation avancée des données radar : Utiliser les données radar pour cibler les vaisseaux ennemis de manière proactive et éviter efficacement les attaquants adverses.
Stratégies d’embuscade : Développer des tactiques pour tendre des embuscades aux vaisseaux ennemis, en exploitant les positions stratégiques et les données radar.
Amélioration de la qualité du code : Poursuivre la refactorisation pour renforcer la lisibilité, la modularité et la maintenabilité, tout en augmentant la couverture des tests unitaires.
Utilisation approfondie des mécanismes d’OS embarqué : Exploiter davantage les sémaphores et les principes de CMSIS RTOS v2 pour améliorer la synchronisation et la gestion des threads des vaisseaux.

Conclusion
Le projet Space Collector, réalisé par l’équipe TIME_JAM, a permis de développer des compétences clés en programmation embarquée, TDD et gestion CI, tout en surmontant des défis liés à la compilation, à l’installation d’outils et au parsing en environnement contraint. Les éléments développés, tels que les fonctions de navigation (go_planet, go_base) et de stratégie (reorder_planets, calculate_angle), forment une base solide pour le jeu, malgré la nécessité de décommenter certaines fonctions en raison de problèmes avec pre-commit. L’installation des outils comme uv, PlatformIO et MinUnit a facilité le développement. Les perspectives d’amélioration, notamment l’utilisation avancée des données radar et des sémaphores, permettraient d’optimiser la stratégie et la robustesse du système.
