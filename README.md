make dir : creates project directories 
make clean : removes compilation files

make : dir, clean, compiles and executes ./rsfind
make ARGS="some args" : clean, compiles and executes ./rsfind "some args"


make test : compiles tests and executes ./test/bin/test_rsfind


COMPORTEMENT :

./rsfind : affiche tous les fichiers du répertoire courant (récursif)

./rsfind --name CHAINE : affiche toutes les occurences de CHAINE (récursif) avec le chemin

./rsfind --print [-p] : 