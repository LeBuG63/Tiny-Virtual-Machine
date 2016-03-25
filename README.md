# Tiny-Virtual-Machine

Tiny Virtual Machine est un programme qui, en lisant un fichier source, va interpreter les commandes donnees par ce-dit fichier.
Chaque commande est constituée de quatre parties: une est l'opération, la deuxieme est l'emplacement dans le registre (0x00 - 0xC), la troisieme et quatrieme sont les nombres affectes par l'operation

Les opérations
 - 0x00: les additions
 - 0x01: les soustractions
 - 0x02: les multiplications
 - 0x03: les divisions
 - 0x04: l'opérateur logique ET
 - 0x05: l'opérateur logique OU
 - 0x06: l'opérateur logique OU EXCLUSIF

Méthodes d'affichage:
 - 0x10: affiche un entier
 - 0x11: affiche une lettre

Exemple
-------
Creez un fichier vide a l'endroit ou se trouve le fichier source et nommez le "code". Avec un editeur hexadecimal (comme HexEdit), entrez le code suivant:

00 00 0F 36 01 01 5A 2F 02 02 4B 8C 03 03 FF 0F 10 00 10 01 10 02 10 03
	
00 00 0F 36, qui est la premiere operation a effectuer, pourrait se traduire par: "je veux une addition que je place dans le registre numero 0x00 et cette addition est "0F + 36" "
	
Compilez le programme: gcc mv.c -o tinyvirtualmachine -Wall -Wextra

Executez ensuite ce programme: ./tinyvirtualmachine "code"
