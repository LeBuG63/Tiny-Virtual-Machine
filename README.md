# Tiny-Virtual-Machine
Exemple
-------
Il faut tout d'abord créér un fichier vide et que vous ouvrirez avec un éditeur hexadécimal comme Hex Edit.
Ensuite, entrez ce code: 00 00 0F 36 01 01 5A 2F 02 02 4B 8C 03 03 FF 0F 10 00 10 01 10 02 10 03

00 00 0F 36 doit se lire: je veux une addtion que je place dans le registre numero 0 et cette adition est 0F + 36.

La premiere partie est l'opération que vous voulez effectuer: 
 - 0x00 concerne les additions
 - 0x01 les soustractions
 - 0x02 les multiplications
 - 0x03 les divisions
 - 0x04 l'opérateur logique ET
 - 0x05 l'opérateur logique OU
 - 0x06 l'opérateur logique OU ESCLUSIF

La seconde est le registre, qui va de 0x00 à 0xC
Et la 3éme et 4éme partie representent les nombres à ajouter, soustraire...

Pour afficher le contenu d'un registre, c'est le même principe:
 - 0x10 pour afficher un entier
 - 0x11 pour affichre une lettre

10 00 doit donc se lire: afficher par un entier le contenu du registre 0
