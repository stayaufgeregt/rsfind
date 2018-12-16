#!/bin/bash
DOSSIER='.';
OUTPUT="./test_output"
CHAINE="int";
mkdir -p "$OUTPUT";

diff <(./rsfind $DOSSIER) <(find $DOSSIER) > "$OUTPUT"/basic;
echo basic $(wc -c "$OUTPUT"/basic | cut -d " " -f 1) bytes
diff <(./rsfind $DOSSIER --name "$CHAINE") <(find $DOSSIER -name "$CHAINE") > "$OUTPUT"/name;
echo name $(wc -c "$OUTPUT"/name | cut -d " " -f 1) bytes
diff <(./rsfind $DOSSIER --print) <(find $DOSSIER -print)	>	"$OUTPUT"/print;
echo print $(wc -c "$OUTPUT"/print | cut -d " " -f 1) bytes
diff <(./rsfind $DOSSIER -t CHAINE) <(grep -r -l $DOSSIER -e CHAINE)	>	"$OUTPUT"/chaine;
echo chaine $(wc -c "$OUTPUT"/chaine | cut -d " " -f 1) bytes
diff <(./rsfind $DOSSIER -i) <(find $DOSSIER -type f -exec file {} \; | grep image | cut -d : -f 1)	>	"$OUTPUT"/img;
echo img $(wc -c "$OUTPUT"/img | cut -d " " -f 1) bytes
diff <(./rsfind $DOSSIER -l) <(find $DOSSIER -exec ls -l -d {} \;)	>	"$OUTPUT"/ll;
echo ll $(wc -c "$OUTPUT"/ll | cut -d " " -f 1) bytes
diff <(./rsfind $DOSSIER --exec "cat {} | grep int | grep -v pipe | wc -c") <(find $DOSSIER -exec sh -c "cat {} | grep int | grep -v pipe | wc -c" \;)	> "$OUTPUT"/exec;
echo exec $(wc -c "$OUTPUT"/exec | cut -d " " -f 1) bytes
diff <(./rsfind $DOSSIER --ename REGEXP) <(find $DOSSIER -name REGEXP)	> "$OUTPUT"/rename;
echo rename $(wc -c "$OUTPUT"/rename | cut -d " " -f 1) bytes
diff <(./rsfind $DOSSIER -T "regexp") <(grep -r -l $DOSSIER -e "int") > "$OUTPUT"/re;
echo re $(wc -c "$OUTPUT"/re | cut -d " " -f 1) bytes
diff <(./rsfind $DOSSIER -p 4) <(./rsfind $DOSSIER) > "$OUTPUT"/threads;
echo threads $(wc -c "$OUTPUT/threads" | cut -d " " -f 1) bytes
diff <(./rsfind $DOSSIER --print --exec "cat {} | wc -c " ) <(find $DOSSIER -print -exec sh -c "cat {} | wc -c " \;) > $OUTPUT/pexec
echo pexec $(wc -c "$OUTPUT/pexec" | cut -d " " -f 1) bytes
