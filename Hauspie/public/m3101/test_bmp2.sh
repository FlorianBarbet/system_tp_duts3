#!/bin/bash
CMD="valgrind -q $1"
DISPLAY_CMD="display"
FOLDER=$(cd $(dirname $0) && pwd)
OUTPUT_FOLDER="testbmp_abcde${RANDOM}"
mkdir -p $OUTPUT_FOLDER

function usage()
{
    echo "usage: $0 chemin_vers_executable_a_tester" 1>&2
    exit 1
}

function do_test()
{
    SRC=$1
    set -x
    # copie
    $CMD "$FOLDER/${SRC}" "$OUTPUT_FOLDER/copie-${SRC}"
    
    # rouge
    $CMD -r "$FOLDER/${SRC}" "$OUTPUT_FOLDER/red-${SRC}"

    # negatif
    $CMD -n "$FOLDER/${SRC}" "$OUTPUT_FOLDER/neg-${SRC}"

    # noir et blanc
    $CMD -b "$FOLDER/${SRC}" "$OUTPUT_FOLDER/nb-${SRC}"

    # sup
    $CMD -s "$FOLDER/${SRC}" "$OUTPUT_FOLDER/sup-${SRC}"

    # inf
    $CMD -i "$FOLDER/${SRC}" "$OUTPUT_FOLDER/inf-${SRC}"

    # multiples 1
    $CMD -n -b -s "$FOLDER/${SRC}" "$OUTPUT_FOLDER/nbs-${SRC}"

    # multiples 2
    $CMD -s -r -n "$FOLDER/${SRC}" "$OUTPUT_FOLDER/srn-${SRC}"

    # multiples 3
    $CMD -i -s -r "$FOLDER/${SRC}" "$OUTPUT_FOLDER/isr-${SRC}"
set +x

    for file in copie red neg nb sup inf nbs srn isr
    do
	if [ -f "$OUTPUT_FOLDER/${file}-${SRC}" ]
	then
		$DISPLAY_CMD "$OUTPUT_FOLDER/${file}-${SRC}"
	else
		echo Fichier manquant "$OUTPUT_FOLDER/${file}-${SRC}"
	fi
    done
}

function do_test_errors()
{
    set -x
    # fichier inexistant
    $CMD iouaehrouiaheoiuh $OUTPUT_FOLDER/non.bmp

    # fichier non autorisé
    chmod 0 "$FOLDER/test24-000.bmp" >& /dev/null
    $CMD "$FOLDER/test24-000.bmp" "$OUTPUT_FOLDER/chmod.bmp"
    chmod 644 "$FOLDER/test24-000.bmp" >& /dev/null

    # Fichier avec mauvaise profondeur de couleur
    $CMD "$FOLDER/test16.bmp" "$OUTPUT_FOLDER/test16.bmp"
    set +x


    for file in non chmod test16
    do
	test -e "$OUTPUT_FOLDER/${file}.bmp" && echo "Le fichier $file.bmp ne devrait pas exister"
    done
}

test -z "$1" && usage

cat <<EOF

Lisez attentivement le message qui va suivre lors de la première
exécution de ce script!

Appuyez sur [Entrée] pour continuer...
EOF

read

cat <<EOF

Ce script va tester votre programme avec quatre images différentes.
Chaque image a des caractéristiques différentes, en particulier, le
nombre d'octets de bourrage (padding) est différent sur chaque image.

Chaque exécution de votre programme sera faite dans l'utilitaire
valgrind et la ligne de commande utilisée sera affichée avant
l'exécution. Il ne doit y avoir aucune erreur reportée par valgrind.

Votre programme sera utilisé plusieur fois pour chaque image. Après toutes
les exécutions sur une image, le résultat sera affiché pour vérification.

Pour chaque image les filtres appliqué seront:
1. copie simple
2. rouge
3. negatif
4. noir et blanc
5. moitié supérieure
6. moitié inférieure
7. négatif suivi de noir et blanc suivi de moitié supérieure
8. moitié supérieure suivi de rouge suivi de negatif
9. moitié inférieure suivi de moitié supérieure suivi de rouge

Une fois tous les tests passés pour chaque image, votre programme sera
exécuté avec de mauvaises images source pour vérifier votre traitement
d'erreur:

1. Un fichier inexistant
2. Un fichier pour lequel vous n'avez pas les droits de lecture
3. Un fichier BMP avec une profondeur de 16 bits

Dans tous ces cas, vous devez afficher un message d'erreur et NE PAS
créer le fichier destination.

Appuyer sur [Entrée] pour continuer...

EOF

read

do_test test24-pad1.bmp
do_test test24-pad2.bmp
do_test test24-pad3.bmp
do_test test24-pad0.bmp

do_test_errors
