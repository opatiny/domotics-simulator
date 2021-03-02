#!/bin/bash

OUTPUT="./tests.c"
TEST_FILES=`find . -mindepth 2 -name "*test.h"`

cat <<EOF > $OUTPUT
#include <stdio.h>
#include <stdlib.h>

EOF

for FILE in $TEST_FILES; do
  echo "#include \"$FILE\"" >> $OUTPUT
done

echo "int main(void) {" >> $OUTPUT


for FILE in $TEST_FILES; do
  TESTS=`grep void $FILE | sed -E "s/.* (.*)\(.*/\1/"`;
  for TEST in $TESTS; do
  cat << EOF >> $OUTPUT
printf("%-40s %10s\n", "$TEST",
        $TEST() ? "\033[0;31mFAILING\033[0m"
                         : "\033[0;32mPASSING\033[0m");
EOF
  done
done

cat <<EOF >> $OUTPUT
  return EXIT_SUCCESS;
}
EOF

C_FILES=`find . -mindepth 2 -name "*.c"`

if gcc -g $C_FILES ./tests.c -lm -o ./tests.out ; then
  ./tests.out
else
    echo "Compilation failed! Tests could not be run."
fi
