# 42sh
*Ce projet consiste à créer de toutes pièces un shell complet.*

#### Repository original: [skuppers/42sh](https://github.com/skuppers/42sh)

## Team:
* [skuppers](https://github.com/skuppers)
* [nrechati](https://github.com/Nrechati)
* [cempassi](https://github.com/cempassi)
* [ffoissey](https://github.com/ffoissey)

## Fonctionnalité:

#### Basique
* Affichage d’un prompt
* Exécution de commandes avec leurs paramètres et gestion du PATH
* Gestion des erreurs, sans utiliser errno, et de la valeur de retour des commandes
* Gestion correcte des espaces et des tabulations

#### Redirection et séparateurs
* Opérateurs de redirection et d’aggrégation : >, >>, <, <<, >&, <&
* Pipes '|'
* Déparateurs ';'
* Opérateurs logiques '&&' et '||'

#### Variables internes
* Gestion des variables internes au shell
* Création de variable interne selon la syntaxe : name=value
* Exportation des variables internes vers l’environnement (via le built-in export)
* Création de variable d’environnement pour une commande unique (exemple HOME=/tmp cd)
* Gestion des parametres speciaux: $?, $$, $!, $-, $0

#### Édition de ligne
* Édition complète de la ligne de commande
* Gestion des sub-prompts

#### Job control
* Gestion du job control, avec les built-ins jobs, fg, bg et l’opérateur &

#### Signaux
* Gestion des signaux

#### Inhibitheurs
* Gestion des inhibiteurs " (double quote), ' (simple quote) et \ (backslash)

#### Expansions
* Expansion simple des paramètres selon la syntaxe ${} et la syntaxe $
* Expansion du tilde
* ${parameter:-word}
* ${parameter:=word}
* ${parameter:?word}
* ${parameter:+word}
* ${#parameter}
* ${parameter%}
* ${parameter%%}
* ${parameter#}
* ${parameter##}

#### Expansion Arithmétique: $(())
* Incrémentation, Décrémentation ++ --
* Addition, Soustraction + -
* Multiplication, Division, Modulo * / %
* Comparaison <= >= < >
* Égalité, Différence == !=
* ET/OU logique && ||

#### Historique
* Gestion complète de l’historique :
* Expansion !!
* Expansion !word
* Expansion !number
* Expansion !-number
* Recherche incrémentale avec CTRL+R
* Recherche dans l'historique via les flèches directionnelles haut et bas 
* Sauvegarde dans un fichier pour être utilisé sur plusieurs sessions
* Buil-in fc

#### Autocomplétion contextuelle
* Complétion des commandes et des built-ins
* Complétion des fichiers
* Complétion des variables internes

#### Table de hashage
* Gestion d'une table de hashage pour les binaires et pour les built-ins
* Buil-in hash

#### Batch mode
* Execution de commande avec l'option -c
* Execution de commande par pipe

#### Built-ins POSIX (sauf set et unset)
* cd
* echo
* exit
* type
* set
* unset
* export
* jobs
* fg
* bg
* fc
* hash
* pwd
* test
