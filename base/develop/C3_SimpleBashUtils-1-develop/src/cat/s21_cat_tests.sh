#!/bin/bash
 
FILES="non-existent.txt test1.txt unreadable.txt test2.txt empty.txt"
FILE="test1.txt"
S21_CAT_OUTPUT="s21_cat.txt"
CAT_OUTPUT="cat.txt"
SHORT_FLAGS=(-b -e -v -E -n -s -t -T)
LONG_FLAGS=(--number-nonblank --number --squeeze-blank)
OK=0
FAIL=0
DELIMITER="..........................................................."
RED="\033[1;31m"
GREEN="\033[1;32m"
PURPLE="\033[1;35m"
RESET="\033[0m"

echo ${DELIMITER}

echo "Style test"
cp ../../materials/linters/.clang-format ../.clang-format
clang-format --Werror -n *.c *.h ../common/*.c ../common/*.h
if [ $? -eq 0 ]; then
    echo -e "${GREEN}OK${RESET}"
    ((OK++))
    echo ${DELIMITER}
else
    echo -e "${RED}FAIL${RESET}"
    ((FAIL++))
    echo ${DELIMITER}
fi

echo -e "${PURPLE}Input stream for reading: stdin${RESET}"
echo ${DELIMITER}

echo "./s21_cat - < FILE"
cat - < ${FILE} > ${CAT_OUTPUT} 2>/dev/null
./s21_cat - < ${FILE} > ${S21_CAT_OUTPUT} 2>/dev/null
diff -q ${CAT_OUTPUT} ${S21_CAT_OUTPUT}
if [ $? -eq 0 ]; then
    echo -e "${GREEN}OK${RESET}"
    ((OK++))
    echo ${DELIMITER}
else
    echo -e "${RED}FAIL${RESET}"
    ((FAIL++))
    echo ${DELIMITER}
fi

for ((i=0; i<${#SHORT_FLAGS[@]}; i++)); do
    ARG="${SHORT_FLAGS[i]}"
    echo "./s21_cat ${SHORT_FLAGS[i]} - < FILE"
    cat $ARG - < ${FILE} > ${CAT_OUTPUT} 2>/dev/null
    ./s21_cat $ARG - < ${FILE} > ${S21_CAT_OUTPUT} 2>/dev/null
    diff -q ${CAT_OUTPUT} ${S21_CAT_OUTPUT}
    set +x
    if [ $? -eq 0 ]; then
        echo -e "${GREEN}OK${RESET}"
        ((OK++))
        echo ${DELIMITER}
    else
        echo -e "${RED}FAIL${RESET}"
        ((FAIL++))
        echo ${DELIMITER}
    fi
done

for ((i=0; i<${#LONG_FLAGS[@]}; i++)); do
    ARG="${LONG_FLAGS[i]}"
    echo "./s21_cat ${LONG_FLAGS[i]} - < FILE"
    cat $ARG - < ${FILE} > ${CAT_OUTPUT} 2>/dev/null
    ./s21_cat $ARG - < ${FILE} > ${S21_CAT_OUTPUT} 2>/dev/null
    diff -q ${CAT_OUTPUT} ${S21_CAT_OUTPUT}
    if [ $? -eq 0 ]; then
        echo -e "${GREEN}OK${RESET}"
        ((OK++))
        echo ${DELIMITER}
    else
        echo -e "${RED}FAIL${RESET}"
        ((FAIL++))
        echo ${DELIMITER}
    fi
done

echo "./s21_cat --non-existent_flag - < FILE"
cat --non-existent_flag - < ${FILE} > ${CAT_OUTPUT} 2>&1
./s21_cat --non-existent_flag - < ${FILE} > ${S21_CAT_OUTPUT} 2>&1
cmp --ignore-initial=0:6 ${CAT_OUTPUT} ${S21_CAT_OUTPUT}
if [ $? -eq 0 ]; then
    echo -e "${GREEN}OK${RESET}"
    ((OK++))
    echo ${DELIMITER}
else
    echo -e "${RED}FAIL${RESET}"
    ((FAIL++))
    echo ${DELIMITER}
fi

echo -e "${PURPLE}Input stream for reading: FILE *stream${RESET}"
echo ${DELIMITER}

echo "./s21_cat FILE..."
cat ${FILES} > ${CAT_OUTPUT} 2>/dev/null
./s21_cat ${FILES} > ${S21_CAT_OUTPUT} 2>/dev/null
diff -q ${CAT_OUTPUT} ${S21_CAT_OUTPUT}
if [ $? -eq 0 ]; then
    echo -e "${GREEN}OK${RESET}"
    ((OK++))
    echo ${DELIMITER}
else
    echo -e "${RED}FAIL${RESET}"
    ((FAIL++))
    echo ${DELIMITER}
fi

for ((i=0; i<${#SHORT_FLAGS[@]}; i++)); do
    ARGS="${SHORT_FLAGS[i]} ${FILES}"
    echo "./s21_cat ${SHORT_FLAGS[i]} FILE..."
    cat $ARGS > ${CAT_OUTPUT} 2>/dev/null
    ./s21_cat $ARGS > ${S21_CAT_OUTPUT} 2>/dev/null
    diff -q ${CAT_OUTPUT} ${S21_CAT_OUTPUT}
    if [ $? -eq 0 ]; then
        echo -e "${GREEN}OK${RESET}"
        ((OK++))
        echo ${DELIMITER}
    else
        echo -e "${RED}FAIL${RESET}"
        ((FAIL++))
        echo ${DELIMITER}
    fi
done

for ((i=0; i<${#LONG_FLAGS[@]}; i++)); do
    ARGS="${LONG_FLAGS[i]} ${FILES}"
    echo "./s21_cat ${LONG_FLAGS[i]} FILE..."
    cat $ARGS > ${CAT_OUTPUT} 2>/dev/null
    ./s21_cat $ARGS > ${S21_CAT_OUTPUT} 2>/dev/null
    diff -q ${CAT_OUTPUT} ${S21_CAT_OUTPUT}
    if [ $? -eq 0 ]; then
        echo -e "${GREEN}OK${RESET}"
        ((OK++))
        echo ${DELIMITER}
    else
        echo -e "${RED}FAIL${RESET}"
        ((FAIL++))
        echo ${DELIMITER}
    fi
done

echo "./s21_cat --non-existent_flag FILE..."
cat --non-existent_flag ${FILES} > ${CAT_OUTPUT} 2>&1
./s21_cat --non-existent_flag ${FILES} > ${S21_CAT_OUTPUT} 2>&1
cmp --ignore-initial=0:6 ${CAT_OUTPUT} ${S21_CAT_OUTPUT}
if [ $? -eq 0 ]; then
    echo -e "${GREEN}OK${RESET}"
    ((OK++))
    echo ${DELIMITER}
else
    echo -e "${RED}FAIL${RESET}"
    ((FAIL++))
    echo ${DELIMITER}
fi

echo "./s21_cat non-existent.txt"
cat non-existent.txt > ${CAT_OUTPUT} 2>&1
./s21_cat non-existent.txt > ${S21_CAT_OUTPUT} 2>&1
cmp --ignore-initial=0:6 ${CAT_OUTPUT} ${S21_CAT_OUTPUT}
if [ $? -eq 0 ]; then
    echo -e "${GREEN}OK${RESET}"
    ((OK++))
    echo ${DELIMITER}
else
    echo -e "${RED}FAIL${RESET}"
    ((FAIL++))
    echo ${DELIMITER}
fi

echo "./s21_cat unreadable.txt"
cat unreadable.txt > ${CAT_OUTPUT} 2>&1
./s21_cat unreadable.txt > ${S21_CAT_OUTPUT} 2>&1
cmp --ignore-initial=0:6 ${CAT_OUTPUT} ${S21_CAT_OUTPUT}
if [ $? -eq 0 ]; then
    echo -e "${GREEN}OK${RESET}"
    ((OK++))
    echo ${DELIMITER}
else
    echo -e "${RED}FAIL${RESET}"
    ((FAIL++))
    echo ${DELIMITER}
fi

echo "./s21_cat empty.txt"
cat empty.txt > ${CAT_OUTPUT} 2>&1
./s21_cat empty.txt > ${S21_CAT_OUTPUT} 2>&1
cmp --ignore-initial=0:6 ${CAT_OUTPUT} ${S21_CAT_OUTPUT}
if [ $? -eq 0 ]; then
    echo -e "${GREEN}OK${RESET}"
    ((OK++))
    echo ${DELIMITER}
else
    echo -e "${RED}FAIL${RESET}"
    ((FAIL++))
    echo ${DELIMITER}
fi

echo -e "${GREEN}OK${RESET}: $OK"
echo -e "${RED}FAIL${RESET}: $FAIL"

rm -rf ${CAT_OUTPUT} ${S21_CAT_OUTPUT}