#!/usr/bin/env bash

set -u

OUTPUT_FILE="test_results.txt"
EXECUTABLE="./projet"
TEST_DIR="tests"

: > "$OUTPUT_FILE"

echo "===== Compilation avec make =====" | tee -a "$OUTPUT_FILE"
if ! make >> "$OUTPUT_FILE" 2>&1; then
    echo "La compilation a échoué. Regarde $OUTPUT_FILE pour les détails." | tee -a "$OUTPUT_FILE"
    exit 1
fi

echo >> "$OUTPUT_FILE"
echo "===== Début des tests =====" | tee -a "$OUTPUT_FILE"

for i in $(seq -w 0 17); do
    TEST_FILE="$TEST_DIR/t${i}.txt"
    echo >> "$OUTPUT_FILE"
    echo "----- Test $TEST_FILE -----" | tee -a "$OUTPUT_FILE"

    if [ ! -f "$TEST_FILE" ]; then
        echo "Fichier introuvable : $TEST_FILE" | tee -a "$OUTPUT_FILE"
        continue
    fi

    "$EXECUTABLE" "$TEST_FILE" >> "$OUTPUT_FILE" 2>&1
    STATUS=$?
    echo >> "$OUTPUT_FILE"
    echo "Code de retour : $STATUS" | tee -a "$OUTPUT_FILE"
done

echo >> "$OUTPUT_FILE"
echo "===== Fin des tests =====" | tee -a "$OUTPUT_FILE"
echo "Résultats enregistrés dans $OUTPUT_FILE"