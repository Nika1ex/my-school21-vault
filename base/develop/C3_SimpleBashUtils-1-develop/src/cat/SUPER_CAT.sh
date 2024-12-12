#!/bin/bash
 
FILES="non-existent.txt test1.txt unreadable.txt test2.txt empty.txt"
S21_CAT_OUTPUT="s21_cat.txt"
CAT_OUTPUT="cat.txt"
SHORT_FLAGS=(b v E n s T)
OK=0
FAIL=0
DELIMITER="..........................................................."

echo "TEST S21_CAT WITH ALL FLAGS COMBINATIONS"
echo ${DELIMITER}

run_test() {
    local ARGS="$1"
    echo "./s21_cat $ARGS"
    cat $ARGS > ${CAT_OUTPUT} 2>/dev/null
    ./s21_cat $ARGS > ${S21_CAT_OUTPUT} 2>/dev/null
    diff -q ${CAT_OUTPUT} ${S21_CAT_OUTPUT}
    
    if [ $? -eq 0 ]; then
        echo -e "OK"
        ((OK++))
    else
        echo -e "FAIL"
        ((FAIL++))
    fi
    echo ${DELIMITER}
}

num_flags=${#SHORT_FLAGS[@]}

for ((a=0; a<num_flags; a++)); do
    run_test "-${SHORT_FLAGS[a]} ${FILES}"
done

for ((a=0; a<num_flags; a++)); do
    for ((b=0; b<num_flags; b++)); do
        if [ $a -ne $b ]; then
            run_test "-${SHORT_FLAGS[a]}${SHORT_FLAGS[b]} ${FILES}"
        fi
    done
done

for ((a=0; a<num_flags; a++)); do
    for ((b=0; b<num_flags; b++)); do
        for ((c=0; c<num_flags; c++)); do
            if [ $a -ne $b ] && [ $a -ne $c ] && [ $b -ne $c ]; then
                run_test "-${SHORT_FLAGS[a]}${SHORT_FLAGS[b]}${SHORT_FLAGS[c]} ${FILES}"
            fi
        done
    done
done

for ((a=0; a<num_flags; a++)); do
    for ((b=0; b<num_flags; b++)); do
        for ((c=0; c<num_flags; c++)); do
            for ((d=0; d<num_flags; d++)); do
                if [ $a -ne $b ] && [ $a -ne $c ] && [ $a -ne $d ] && \
                   [ $b -ne $c ] && [ $b -ne $d ] && \
                   [ $c -ne $d ]; then
                    run_test "-${SHORT_FLAGS[a]}${SHORT_FLAGS[b]}${SHORT_FLAGS[c]}${SHORT_FLAGS[d]} ${FILES}"
                fi
            done
        done
    done
done

for ((a=0; a<num_flags; a++)); do
    for ((b=0; b<num_flags; b++)); do
        for ((c=0; c<num_flags; c++)); do
            for ((d=0; d<num_flags; d++)); do
                for ((e=0; e<num_flags; e++)); do
                    if [ $a -ne $b ] && [ $a -ne $c ] && [ $a -ne $d ] && [ $a -ne $e ] && \
                       [ $b -ne $c ] && [ $b -ne $d ] && [ $b -ne $e ] && \
                       [ $c -ne $d ] && [ $c -ne $e ] && \
                       [ $d -ne $e ]; then
                        run_test "-${SHORT_FLAGS[a]}${SHORT_FLAGS[b]}${SHORT_FLAGS[c]}${SHORT_FLAGS[d]}${SHORT_FLAGS[e]} ${FILES}"
                    fi
                done
            done
        done
    done    
done

for ((a=0; a<num_flags; a++)); do
    for ((b=0; b<num_flags; b++)); do
        for ((c=0; c<num_flags; c++)); do
            for ((d=0; d<num_flags; d++)); do
                for ((e=0; e<num_flags; e++)); do
                    for ((f=0; f<num_flags; f++)); do
                        if [ $a -ne $b ] && [ $a -ne $c ] && [ $a -ne $d ] && \
                           [ $a -ne $e ] && [ $a -ne $f ] && \
                           [ $b -ne $c ] && [ $b -ne $d ] && \
                           [ $b -ne $e ] && [ $b -ne $f ] && \
                           [ $c -ne $d ] && [ $c -ne $e ] && \
                           [ $c -ne $f ] && \
                           [ $d -ne $e ] && [ $d -ne $f ] && \
                           [ $e -ne $f ]; then
                            run_test "-${SHORT_FLAGS[a]}${SHORT_FLAGS[b]}${SHORT_FLAGS[c]}${SHORT_FLAGS[d]}${SHORT_FLAGS[e]}${SHORT_FLAGS[f]} ${FILES}"
                        fi 
                    done 
                done 
            done 
        done 
    done 
done

echo "OK: $OK"
echo "FAIL: $FAIL"

rm -rf ${CAT_OUTPUT} ${S21_CAT_OUTPUT}