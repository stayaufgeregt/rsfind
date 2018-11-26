#!/bin/bash
DOSSIER="..";
CHAINE="int";
mkdir -p auto_tests;
echo basic
diff <(../rsfind $DOSSIER) <(find $DOSSIER) > basic;
echo basic
diff <(../rsfind $DOSSIER --name "$CHAINE") <(find $DOSSIER -name "$CHAINE") > auto_tests/name;
echo basic
diff <(../rsfind $DOSSIER --print) <(find $DOSSIER -print)	>	auto_tests/print;
echo basic
diff <(../rsfind $DOSSIER -t CHAINE) <(grep -r -l $DOSSIER -e CHAINE)	>	auto_tests/chaine;
echo basic
diff <(../rsfind $DOSSIER -i) <(find $DOSSIER -type f -exec file {} \; | grep image | cut -d : -f 1)	>	auto_tests/image;
echo basic
diff <(../rsfind $DOSSIER -l) <(find $DOSSIER -exec ls -l -d {} \;)	>	auto_tests/ll;
echo basic
diff <(../rsfind $DOSSIER --exec "COMMANDE") <(find $DOSSIER -exec COMMANDE \;)	> auto_tests/exec;
echo basic
diff <(../rsfind $DOSSIER --ename REGEXP) <(find $DOSSIER -name REGEXP)	> auto_tests/rename;
echo basic
diff <(../rsfind $DOSSIER -T "regexp") <(grep -r -l $DOSSIER -e "int") > auto_tests/re;