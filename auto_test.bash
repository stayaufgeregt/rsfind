#!/bin/bash
DOSSIER="./test";
OUTPUT="./test_output/"
CHAINE="int";
mkdir -p "$OUTPUT";

diff <(./rsfind $DOSSIER) <(find $DOSSIER) > "$OUTPUT"/basic;
echo basic
diff <(./rsfind $DOSSIER --name "$CHAINE") <(find $DOSSIER -name "$CHAINE") > "$OUTPUT"/name;
echo basic
diff <(./rsfind $DOSSIER --print) <(find $DOSSIER -print)	>	"$OUTPUT"/print;
echo basic
diff <(./rsfind $DOSSIER -t CHAINE) <(grep -r -l $DOSSIER -e CHAINE)	>	"$OUTPUT"/chaine;
echo basic
diff <(./rsfind $DOSSIER -i) <(find $DOSSIER -type f -exec file {} \; | grep image | cut -d : -f 1)	>	"$OUTPUT"/image;
echo basic
diff <(./rsfind $DOSSIER -l) <(find $DOSSIER -exec ls -l -d {} \;)	>	"$OUTPUT"/ll;
echo basic
diff <(./rsfind $DOSSIER --exec "COMMANDE") <(find $DOSSIER -exec "COMMANDE" \;)	> "$OUTPUT"/exec;
echo basic
diff <(./rsfind $DOSSIER --ename REGEXP) <(find $DOSSIER -name REGEXP)	> "$OUTPUT"/rename;
echo basic
diff <(./rsfind $DOSSIER -T "regexp") <(grep -r -l $DOSSIER -e "int") > "$OUTPUT"/re;