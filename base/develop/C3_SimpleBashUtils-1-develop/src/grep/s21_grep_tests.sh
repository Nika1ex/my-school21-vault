#!/bin/bash

FILES="non-existent.txt test1.txt unreadable.txt test2.txt empty.txt"
S21_GREP_OUTPUT="s21_grep.txt"
GREP_OUTPUT="grep.txt"
FLAGS_WITHOUT_ARGS=(i v c l n h s o)
PATTERNS=('^' '67890')
PATTERN_FILE=(regex1.txt regex2.txt regex3.txt)
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

echo -e "${PURPLE}Input stream for reading: FILE *stream${RESET}"
echo ${DELIMITER}

echo "./s21_grep PATTERN FILE"
ARGS="${PATTERNS[0]} test1.txt"
grep $ARGS > ${GREP_OUTPUT} 2>/dev/null
./s21_grep $ARGS > ${S21_GREP_OUTPUT} 2>/dev/null
diff -q ${GREP_OUTPUT} ${S21_GREP_OUTPUT}
if [ $? -eq 0 ]; then
    echo -e "${GREEN}OK${RESET}"
    ((OK++))
    echo ${DELIMITER}
    else
    echo -e "${RED}FAIL${RESET}"
    ((FAIL++))
    echo ${DELIMITER}
fi

echo "./s21_grep PATTERN FILE..."
ARGS="${PATTERNS[0]} ${FILES}"
grep $ARGS > ${GREP_OUTPUT} 2>/dev/null
./s21_grep $ARGS > ${S21_GREP_OUTPUT} 2>/dev/null
diff -q ${GREP_OUTPUT} ${S21_GREP_OUTPUT}
if [ $? -eq 0 ]; then
    echo -e "${GREEN}OK${RESET}"
    ((OK++))
    echo ${DELIMITER}
    else
    echo -e "${RED}FAIL${RESET}"
    ((FAIL++))
    echo ${DELIMITER}
fi

for ((i=0; i<${#FLAGS_WITHOUT_ARGS[@]}; i++)); do
    ARGS="-${FLAGS_WITHOUT_ARGS[i]} ${PATTERNS[0]} ${FILES}"
    echo "./s21_grep -${FLAGS_WITHOUT_ARGS[i]} PATTERN FILE..."
    grep $ARGS > ${GREP_OUTPUT} 2>/dev/null
    ./s21_grep $ARGS > ${S21_GREP_OUTPUT} 2>/dev/null
    diff -q ${GREP_OUTPUT} ${S21_GREP_OUTPUT}
    if [ $? -eq 0 ]; then
        echo -e "${GREEN}OK${RESET}"
        ((OK++))
        echo ${DELIMITER}
    else
        echo -e "${RED}FAIL${RESET}"
        ((FAIL++))
        echo ${DELIMITER}
    fi
    for ((j=0; j<${#FLAGS_WITHOUT_ARGS[@]}; j++)); do
        ARGS="-${FLAGS_WITHOUT_ARGS[i]} -${FLAGS_WITHOUT_ARGS[j]} ${PATTERNS[0]} ${FILES}"
        echo "./s21_grep -${FLAGS_WITHOUT_ARGS[i]} -${FLAGS_WITHOUT_ARGS[j]} PATTERN FILE..."
        grep $ARGS > ${GREP_OUTPUT} 2>/dev/null
        ./s21_grep $ARGS > ${S21_GREP_OUTPUT} 2>/dev/null
        diff -q ${GREP_OUTPUT} ${S21_GREP_OUTPUT}
        if [ $? -eq 0 ]; then
            echo -e "${GREEN}OK${RESET}"
            ((OK++))
            echo ${DELIMITER}
        else
            echo -e "${RED}FAIL${RESET}"
            ((FAIL++))
            echo ${DELIMITER}
        fi
        ARGS="-${FLAGS_WITHOUT_ARGS[i]}${FLAGS_WITHOUT_ARGS[j]} ${PATTERNS[0]} ${FILES}"
        echo "./s21_grep -${FLAGS_WITHOUT_ARGS[i]}${FLAGS_WITHOUT_ARGS[j]} PATTERN FILE..."
        grep $ARGS > ${GREP_OUTPUT} 2>/dev/null
        ./s21_grep $ARGS > ${S21_GREP_OUTPUT} 2>/dev/null
        diff -q ${GREP_OUTPUT} ${S21_GREP_OUTPUT}
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
done

ARGS="-e ${PATTERNS[0]} ${FILES}"
echo "./s21_grep -e PATTERN FILE..."
grep $ARGS > ${GREP_OUTPUT} 2>/dev/null
./s21_grep $ARGS > ${S21_GREP_OUTPUT} 2>/dev/null
diff -q ${GREP_OUTPUT} ${S21_GREP_OUTPUT}
if [ $? -eq 0 ]; then
    echo -e "${GREEN}OK${RESET}"
    ((OK++))
    echo ${DELIMITER}
else
    echo -e "${RED}FAIL${RESET}"
    ((FAIL++))
    echo ${DELIMITER}
fi

ARGS="-e ${PATTERNS[0]} -e ${PATTERNS[1]} ${FILES}"
echo "./s21_grep -e PATTERN -e PATTERN FILE..."
grep $ARGS > ${GREP_OUTPUT} 2>/dev/null
./s21_grep $ARGS > ${S21_GREP_OUTPUT} 2>/dev/null
diff -q ${GREP_OUTPUT} ${S21_GREP_OUTPUT}
if [ $? -eq 0 ]; then
    echo -e "${GREEN}OK${RESET}"
    ((OK++))
    echo ${DELIMITER}
else
    echo -e "${RED}FAIL${RESET}"
    ((FAIL++))
    echo ${DELIMITER}
fi

ARGS="-ee ${PATTERNS[0]} ${FILES}"
echo "./s21_grep -ee PATTERN FILE..."
grep $ARGS > ${GREP_OUTPUT} 2>/dev/null
./s21_grep $ARGS > ${S21_GREP_OUTPUT} 2>/dev/null
diff -q ${GREP_OUTPUT} ${S21_GREP_OUTPUT}
if [ $? -eq 0 ]; then
    echo -e "${GREEN}OK${RESET}"
    ((OK++))
    echo ${DELIMITER}
else
    echo -e "${RED}FAIL${RESET}"
    ((FAIL++))
    echo ${DELIMITER}
fi

for ((i=0; i<${#FLAGS_WITHOUT_ARGS[@]}; i++)); do
    ARGS="-e ${PATTERNS[0]} -${FLAGS_WITHOUT_ARGS[i]} ${FILES}"
    echo "./s21_grep -e PATTERN -${FLAGS_WITHOUT_ARGS[i]} FILE..."
    grep $ARGS > ${GREP_OUTPUT} 2>/dev/null
    ./s21_grep $ARGS > ${S21_GREP_OUTPUT} 2>/dev/null
    diff -q ${GREP_OUTPUT} ${S21_GREP_OUTPUT}
    if [ $? -eq 0 ]; then
        echo -e "${GREEN}OK${RESET}"
        ((OK++))
        echo ${DELIMITER}
    else
        echo -e "${RED}FAIL${RESET}"
        ((FAIL++))
        echo ${DELIMITER}
    fi
    ARGS="-e${FLAGS_WITHOUT_ARGS[i]} ${FILES}"
    echo "./s21_grep -e${FLAGS_WITHOUT_ARGS[i]} FILE..."
    grep $ARGS > ${GREP_OUTPUT} 2>/dev/null
    ./s21_grep $ARGS > ${S21_GREP_OUTPUT} 2>/dev/null
    diff -q ${GREP_OUTPUT} ${S21_GREP_OUTPUT}
    if [ $? -eq 0 ]; then
        echo -e "${GREEN}OK${RESET}"
        ((OK++))
        echo ${DELIMITER}
    else
        echo -e "${RED}FAIL${RESET}"
        ((FAIL++))
        echo ${DELIMITER}
    fi
    ARGS="-${FLAGS_WITHOUT_ARGS[i]} -e ${PATTERNS[0]} ${FILES}"
    echo "./s21_grep -${FLAGS_WITHOUT_ARGS[i]} -e PATTERN FILE..."
    grep $ARGS > ${GREP_OUTPUT} 2>/dev/null
    ./s21_grep $ARGS > ${S21_GREP_OUTPUT} 2>/dev/null
    diff -q ${GREP_OUTPUT} ${S21_GREP_OUTPUT}
    if [ $? -eq 0 ]; then
        echo -e "${GREEN}OK${RESET}"
        ((OK++))
        echo ${DELIMITER}
    else
        echo -e "${RED}FAIL${RESET}"
        ((FAIL++))
        echo ${DELIMITER}
    fi
    ARGS="-${FLAGS_WITHOUT_ARGS[i]}e ${PATTERNS[0]} ${FILES}"
    echo "./s21_grep -${FLAGS_WITHOUT_ARGS[i]}e PATTERN FILE..."
    grep $ARGS > ${GREP_OUTPUT} 2>/dev/null
    ./s21_grep $ARGS > ${S21_GREP_OUTPUT} 2>/dev/null
    diff -q ${GREP_OUTPUT} ${S21_GREP_OUTPUT}
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

ARGS="-f ${PATTERN_FILE[0]} ${FILES}"
echo "./s21_grep -f PATTERN_FILE FILE..."
grep $ARGS > ${GREP_OUTPUT} 2>/dev/null
./s21_grep $ARGS > ${S21_GREP_OUTPUT} 2>/dev/null
diff -q ${GREP_OUTPUT} ${S21_GREP_OUTPUT}
if [ $? -eq 0 ]; then
    echo -e "${GREEN}OK${RESET}"
    ((OK++))
    echo ${DELIMITER}
else
    echo -e "${RED}FAIL${RESET}"
    ((FAIL++))
    echo ${DELIMITER}
fi

ARGS="-f ${PATTERN_FILE[0]} -f ${PATTERN_FILE[1]} ${FILES}"
echo "./s21_grep -f PATTERN_FILE -f PATTERN_FILE FILE..."
grep $ARGS > ${GREP_OUTPUT} 2>/dev/null
./s21_grep $ARGS > ${S21_GREP_OUTPUT} 2>/dev/null
diff -q ${GREP_OUTPUT} ${S21_GREP_OUTPUT}
if [ $? -eq 0 ]; then
    echo -e "${GREEN}OK${RESET}"
    ((OK++))
    echo ${DELIMITER}
else
    echo -e "${RED}FAIL${RESET}"
    ((FAIL++))
    echo ${DELIMITER}
fi

ARGS="-ff ${PATTERN_FILE[0]} ${FILES}"
echo "./s21_grep -ff PATTERN_FILE FILE..."
grep $ARGS > ${GREP_OUTPUT} 2>/dev/null
./s21_grep $ARGS > ${S21_GREP_OUTPUT} 2>/dev/null
diff -q ${GREP_OUTPUT} ${S21_GREP_OUTPUT}
if [ $? -eq 0 ]; then
    echo -e "${GREEN}OK${RESET}"
    ((OK++))
    echo ${DELIMITER}
else
    echo -e "${RED}FAIL${RESET}"
    ((FAIL++))
    echo ${DELIMITER}
fi

ARGS="-f ${PATTERN_FILE[0]} -e ${PATTERNS[0]} ${FILES}"
echo "./s21_grep -f PATTERN_FILE -e PATTERN FILE..."
grep $ARGS > ${GREP_OUTPUT} 2>/dev/null
./s21_grep $ARGS > ${S21_GREP_OUTPUT} 2>/dev/null
diff -q ${GREP_OUTPUT} ${S21_GREP_OUTPUT}
if [ $? -eq 0 ]; then
    echo -e "${GREEN}OK${RESET}"
    ((OK++))
    echo ${DELIMITER}
else
    echo -e "${RED}FAIL${RESET}"
    ((FAIL++))
    echo ${DELIMITER}
fi

ARGS="-fe ${PATTERNS[0]} ${FILES}"
echo "./s21_grep -fe PATTERN FILE..."
grep $ARGS > ${GREP_OUTPUT} 2>/dev/null
./s21_grep $ARGS > ${S21_GREP_OUTPUT} 2>/dev/null
diff -q ${GREP_OUTPUT} ${S21_GREP_OUTPUT}
if [ $? -eq 0 ]; then
    echo -e "${GREEN}OK${RESET}"
    ((OK++))
    echo ${DELIMITER}
else
    echo -e "${RED}FAIL${RESET}"
    ((FAIL++))
    echo ${DELIMITER}
fi

ARGS="-e ${PATTERNS[0]} -f ${PATTERN_FILE[0]} ${FILES}"
echo "./s21_grep -e PATTERN -f PATTERN_FILE FILE..."
grep $ARGS > ${GREP_OUTPUT} 2>/dev/null
./s21_grep $ARGS > ${S21_GREP_OUTPUT} 2>/dev/null
diff -q ${GREP_OUTPUT} ${S21_GREP_OUTPUT}
if [ $? -eq 0 ]; then
    echo -e "${GREEN}OK${RESET}"
    ((OK++))
    echo ${DELIMITER}
else
    echo -e "${RED}FAIL${RESET}"
    ((FAIL++))
    echo ${DELIMITER}
fi

ARGS="-ef ${PATTERN_FILE[0]} ${FILES}"
echo "./s21_grep -ef PATTERN_FILE FILE..."
grep $ARGS > ${GREP_OUTPUT} 2>/dev/null
./s21_grep $ARGS > ${S21_GREP_OUTPUT} 2>/dev/null
diff -q ${GREP_OUTPUT} ${S21_GREP_OUTPUT}
if [ $? -eq 0 ]; then
    echo -e "${GREEN}OK${RESET}"
    ((OK++))
    echo ${DELIMITER}
else
    echo -e "${RED}FAIL${RESET}"
    ((FAIL++))
    echo ${DELIMITER}
fi

for ((i=0; i<${#FLAGS_WITHOUT_ARGS[@]}; i++)); do
    ARGS="-f ${PATTERN_FILE[0]} -${FLAGS_WITHOUT_ARGS[i]} ${FILES}"
    echo "./s21_grep -f PATTERN_FILE -${FLAGS_WITHOUT_ARGS[i]} FILE..."
    grep $ARGS > ${GREP_OUTPUT} 2>/dev/null
    ./s21_grep $ARGS > ${S21_GREP_OUTPUT} 2>/dev/null
    diff -q ${GREP_OUTPUT} ${S21_GREP_OUTPUT}
    if [ $? -eq 0 ]; then
        echo -e "${GREEN}OK${RESET}"
        ((OK++))
        echo ${DELIMITER}
    else
        echo -e "${RED}FAIL${RESET}"
        ((FAIL++))
        echo ${DELIMITER}
    fi
    ARGS="-f${FLAGS_WITHOUT_ARGS[i]} ${FILES}"
    echo "./s21_grep -f${FLAGS_WITHOUT_ARGS[i]} FILE..."
    grep $ARGS > ${GREP_OUTPUT} 2>/dev/null
    ./s21_grep $ARGS > ${S21_GREP_OUTPUT} 2>/dev/null
    diff -q ${GREP_OUTPUT} ${S21_GREP_OUTPUT}
    if [ $? -eq 0 ]; then
        echo -e "${GREEN}OK${RESET}"
        ((OK++))
        echo ${DELIMITER}
    else
        echo -e "${RED}FAIL${RESET}"
        ((FAIL++))
        echo ${DELIMITER}
    fi
    ARGS="-${FLAGS_WITHOUT_ARGS[i]} -f ${PATTERN_FILE[0]} ${FILES}"
    echo "./s21_grep -${FLAGS_WITHOUT_ARGS[i]} -f PATTERN_FILE FILE..."
    grep $ARGS > ${GREP_OUTPUT} 2>/dev/null
    ./s21_grep $ARGS > ${S21_GREP_OUTPUT} 2>/dev/null
    diff -q ${GREP_OUTPUT} ${S21_GREP_OUTPUT}
    if [ $? -eq 0 ]; then
        echo -e "${GREEN}OK${RESET}"
        ((OK++))
        echo ${DELIMITER}
    else
        echo -e "${RED}FAIL${RESET}"
        ((FAIL++))
        echo ${DELIMITER}
    fi
    ARGS="-${FLAGS_WITHOUT_ARGS[i]}f ${PATTERN_FILE[0]} ${FILES}"
    echo "./s21_grep -${FLAGS_WITHOUT_ARGS[i]}f PATTERN_FILE FILE..."
    grep $ARGS > ${GREP_OUTPUT} 2>/dev/null
    ./s21_grep $ARGS > ${S21_GREP_OUTPUT} 2>/dev/null
    diff -q ${GREP_OUTPUT} ${S21_GREP_OUTPUT}
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

echo -e "${PURPLE}Error handling${RESET}"
echo ${DELIMITER}

echo "./s21_grep PATTERN non-existent.txt"
ARGS="${PATTERNS[0]} non-existent.txt"
grep $ARGS > ${GREP_OUTPUT} 2>&1
./s21_grep $ARGS > ${S21_GREP_OUTPUT} 2>&1
cmp --ignore-initial=0:6 ${GREP_OUTPUT} ${S21_GREP_OUTPUT}
if [ $? -eq 0 ]; then
    echo -e "${GREEN}OK${RESET}"
    ((OK++))
    echo ${DELIMITER}
else
    echo -e "${RED}FAIL${RESET}"
    ((FAIL++))
    echo ${DELIMITER}
fi

echo "./s21_grep -s PATTERN non-existent.txt"
ARGS="-s ${PATTERNS[0]} non-existent.txt"
grep $ARGS > ${GREP_OUTPUT} 2>&1
./s21_grep $ARGS > ${S21_GREP_OUTPUT} 2>&1
cmp --ignore-initial=0:6 ${GREP_OUTPUT} ${S21_GREP_OUTPUT}
if [ $? -eq 0 ]; then
    echo -e "${GREEN}OK${RESET}"
    ((OK++))
    echo ${DELIMITER}
else
    echo -e "${RED}FAIL${RESET}"
    ((FAIL++))
    echo ${DELIMITER}
fi

echo "./s21_grep PATTERN unreadable.txt"
ARGS="${PATTERNS[0]} unreadable.txt"
grep $ARGS > ${GREP_OUTPUT} 2>&1
./s21_grep $ARGS > ${S21_GREP_OUTPUT} 2>&1
cmp --ignore-initial=0:6 ${GREP_OUTPUT} ${S21_GREP_OUTPUT}
if [ $? -eq 0 ]; then
    echo -e "${GREEN}OK${RESET}"
    ((OK++))
    echo ${DELIMITER}
else
    echo -e "${RED}FAIL${RESET}"
    ((FAIL++))
    echo ${DELIMITER}
fi

echo "./s21_grep -s PATTERN unreadable.txt"
ARGS="-s ${PATTERNS[0]} unreadable.txt"
grep $ARGS > ${GREP_OUTPUT} 2>&1
./s21_grep $ARGS > ${S21_GREP_OUTPUT} 2>&1
cmp --ignore-initial=0:6 ${GREP_OUTPUT} ${S21_GREP_OUTPUT}
if [ $? -eq 0 ]; then
    echo -e "${GREEN}OK${RESET}"
    ((OK++))
    echo ${DELIMITER}
else
    echo -e "${RED}FAIL${RESET}"
    ((FAIL++))
    echo ${DELIMITER}
fi

echo "./s21_grep PATTERN empty.txt"
ARGS="${PATTERNS[0]} empty.txt"
grep $ARGS > ${GREP_OUTPUT} 2>&1
./s21_grep $ARGS > ${S21_GREP_OUTPUT} 2>&1
cmp --ignore-initial=0:6 ${GREP_OUTPUT} ${S21_GREP_OUTPUT}
if [ $? -eq 0 ]; then
    echo -e "${GREEN}OK${RESET}"
    ((OK++))
    echo ${DELIMITER}
else
    echo -e "${RED}FAIL${RESET}"
    ((FAIL++))
    echo ${DELIMITER}
fi

echo "./s21_grep -s PATTERN empty.txt"
ARGS="-s ${PATTERNS[0]} empty.txt"
grep $ARGS > ${GREP_OUTPUT} 2>&1
./s21_grep $ARGS > ${S21_GREP_OUTPUT} 2>&1
cmp --ignore-initial=0:6 ${GREP_OUTPUT} ${S21_GREP_OUTPUT}
if [ $? -eq 0 ]; then
    echo -e "${GREEN}OK${RESET}"
    ((OK++))
    echo ${DELIMITER}
else
    echo -e "${RED}FAIL${RESET}"
    ((FAIL++))
    echo ${DELIMITER}
fi

ARGS="-f non-existent.reg non-existent.txt"
echo "./s21_grep -f non-existent.reg non-existent.txt"
grep $ARGS > ${GREP_OUTPUT} 2>&1
./s21_grep $ARGS > ${S21_GREP_OUTPUT} 2>&1
cmp --ignore-initial=0:6 ${GREP_OUTPUT} ${S21_GREP_OUTPUT}
if [ $? -eq 0 ]; then
    echo -e "${GREEN}OK${RESET}"
    ((OK++))
    echo ${DELIMITER}
else
    echo -e "${RED}FAIL${RESET}"
    ((FAIL++))
    echo ${DELIMITER}
fi

ARGS="-sf non-existent.reg non-existent.txt"
echo "./s21_grep -sf non-existent.reg non-existent.txt"
grep $ARGS > ${GREP_OUTPUT} 2>&1
./s21_grep $ARGS > ${S21_GREP_OUTPUT} 2>&1
cmp --ignore-initial=0:6 ${GREP_OUTPUT} ${S21_GREP_OUTPUT}
if [ $? -eq 0 ]; then
    echo -e "${GREEN}OK${RESET}"
    ((OK++))
    echo ${DELIMITER}
else
    echo -e "${RED}FAIL${RESET}"
    ((FAIL++))
    echo ${DELIMITER}
fi

ARGS="-f unreadable.txt unreadable.txt"
echo "./s21_grep -f unreadable.txt unreadable.txt"
grep $ARGS > ${GREP_OUTPUT} 2>&1
./s21_grep $ARGS > ${S21_GREP_OUTPUT} 2>&1
cmp --ignore-initial=0:6 ${GREP_OUTPUT} ${S21_GREP_OUTPUT}
if [ $? -eq 0 ]; then
    echo -e "${GREEN}OK${RESET}"
    ((OK++))
    echo ${DELIMITER}
else
    echo -e "${RED}FAIL${RESET}"
    ((FAIL++))
    echo ${DELIMITER}
fi

ARGS="-sf unreadable.txt unreadable.txt"
echo "./s21_grep -sf unreadable.txt unreadable.txt"
grep $ARGS > ${GREP_OUTPUT} 2>&1
./s21_grep $ARGS > ${S21_GREP_OUTPUT} 2>&1
cmp --ignore-initial=0:6 ${GREP_OUTPUT} ${S21_GREP_OUTPUT}
if [ $? -eq 0 ]; then
    echo -e "${GREEN}OK${RESET}"
    ((OK++))
    echo ${DELIMITER}
else
    echo -e "${RED}FAIL${RESET}"
    ((FAIL++))
    echo ${DELIMITER}
fi

ARGS="-f empty.txt empty.txt"
echo "./s21_grep -f empty.txt empty.txt"
grep $ARGS > ${GREP_OUTPUT} 2>&1
./s21_grep $ARGS > ${S21_GREP_OUTPUT} 2>&1
cmp --ignore-initial=0:6 ${GREP_OUTPUT} ${S21_GREP_OUTPUT}
if [ $? -eq 0 ]; then
    echo -e "${GREEN}OK${RESET}"
    ((OK++))
    echo ${DELIMITER}
else
    echo -e "${RED}FAIL${RESET}"
    ((FAIL++))
    echo ${DELIMITER}
fi

ARGS="-sf empty.txt empty.txt"
echo "./s21_grep -sf empty.txt empty.txt"
grep $ARGS > ${GREP_OUTPUT} 2>&1
./s21_grep $ARGS > ${S21_GREP_OUTPUT} 2>&1
cmp --ignore-initial=0:6 ${GREP_OUTPUT} ${S21_GREP_OUTPUT}
if [ $? -eq 0 ]; then
    echo -e "${GREEN}OK${RESET}"
    ((OK++))
    echo ${DELIMITER}
else
    echo -e "${RED}FAIL${RESET}"
    ((FAIL++))
    echo ${DELIMITER}
fi

ARGS="-f ${PATTERN_FILE[2]} ${FILES}"
echo "./s21_grep -f FILE_WITH_UNMATCHED_REGEXES FILE..."
grep $ARGS  2>&1 | wc -l > ${GREP_OUTPUT}
./s21_grep $ARGS 2>&1 | wc -l > ${S21_GREP_OUTPUT}
diff -q ${GREP_OUTPUT} ${S21_GREP_OUTPUT}
if [ $? -eq 0 ]; then
    echo -e "${GREEN}OK${RESET}"
    ((OK++))
    echo ${DELIMITER}
else
    echo -e "${RED}FAIL${RESET}"
    ((FAIL++))
    echo ${DELIMITER}
fi

ARGS="-sf ${PATTERN_FILE[2]} ${FILES}"
echo "./s21_grep -sf FILE_WITH_UNMATCHED_REGEXES FILE..."
grep $ARGS  2>&1 | wc -l > ${GREP_OUTPUT}
./s21_grep $ARGS 2>&1 | wc -l > ${S21_GREP_OUTPUT}
diff -q ${GREP_OUTPUT} ${S21_GREP_OUTPUT}
if [ $? -eq 0 ]; then
    echo -e "${GREEN}OK${RESET}"
    ((OK++))
    echo ${DELIMITER}
else
    echo -e "${RED}FAIL${RESET}"
    ((FAIL++))
    echo ${DELIMITER}
fi

ARGS="-e \ -f ${PATTERN_FILE[2]} ${FILES}"
echo "./s21_grep -e \ -f FILE_WITH_UNMATCHED_REGEXES FILE..."
grep $ARGS  2>&1 | wc -l > ${GREP_OUTPUT}
./s21_grep $ARGS 2>&1 | wc -l > ${S21_GREP_OUTPUT}
diff -q ${GREP_OUTPUT} ${S21_GREP_OUTPUT}
if [ $? -eq 0 ]; then
    echo -e "${GREEN}OK${RESET}"
    ((OK++))
    echo ${DELIMITER}
else
    echo -e "${RED}FAIL${RESET}"
    ((FAIL++))
    echo ${DELIMITER}
fi

ARGS="-se \ -f ${PATTERN_FILE[2]} ${FILES}"
echo "./s21_grep -e \ -f FILE_WITH_UNMATCHED_REGEXES FILE..."
grep $ARGS  2>&1 | wc -l > ${GREP_OUTPUT}
./s21_grep $ARGS 2>&1 | wc -l > ${S21_GREP_OUTPUT}
diff -q ${GREP_OUTPUT} ${S21_GREP_OUTPUT}
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

rm -rf ${GREP_OUTPUT} ${S21_GREP_OUTPUT}