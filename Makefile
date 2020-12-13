#
# Variablen helfen in Makefiles copy&paste zu verringern und die "Rezepte"
# uebersichtlicher zu gestalten.
#

CC = gcc
CFLAGS = -std=c99 -pedantic -Wall -Wextra

# Rezept wird mit `make blatt03_1.exe` aufgerufen, Windows-Nutzer muessen vor
# `./blatt03_1.exe` ggf. das `./` entfernen.

blatt06_1.exe:
	$(CC) $(CFLAGS) -o blatt06_1.exe blatt06_1.c
	blatt06_1.exe