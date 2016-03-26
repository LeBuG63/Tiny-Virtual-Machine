# Tiny-Virtual-Machine

Tiny Virtual Machine est un programme qui, en lisant un fichier source, va interpreter les commandes donnees par ce-dit fichier.
Chaque commande est constituée de quatre parties: une est l'opération, la deuxieme est l'emplacement dans le registre (0x00 - 0x10), la troisieme et quatrieme sont les nombres affectes par l'operation

Les opérations
 - 0x01: les additions
 - 0x02: les soustractions
 - 0x03: les multiplications
 - 0x04: les divisions
 - 0x05: l'opérateur logique ET
 - 0x06: l'opérateur logique OU
 - 0x07: l'opérateur logique OU EXCLUSIF
 - 0x08: le modulo (%)
 - 0x09: decallage de bits vers la gauche
 - 0x0A: decallage de bits vers la droite
 - 0x0B: l'operateur NON

Méthodes d'affichage:
 - 0x20: affiche un entier
 - 0x21: affiche une lettre

Saisir l'entree du clavier:
 - 0x22

Exemple
-------
Creez un fichier vide a l'endroit ou se trouve le fichier source et nommez le "code". Avec un editeur hexadecimal (comme HexEdit), entrez le code suivant: 01 00 0F 0F 02 01 0F 05 03 02 0F 0F 04 03 10 02 05 04 0F 0F 06 05 0F 0F 07 06 0F 0F 08 07 06 04 09 08 09 03 0A 09 06 05 0B 0A 09 02 20 00 20 01 20 0A 22 0B 20 0B
	
01 00 0F 0F, qui est la premiere operation a effectuer, pourrait se traduire par: "je veux une addition que je place dans le registre numero 0x00 et cette addition est "0F + 0F" "
	
Compilez le programme: gcc mv.c -o tinyvirtualmachine -Wall -Wextra

Executez ensuite ce programme: ./tinyvirtualmachine "code"
