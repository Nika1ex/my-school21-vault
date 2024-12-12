#!/bin/bash

FILES=("test1.txt" "non-existent.txt test1.txt unreadable.txt test2.txt empty.txt")
S21_GREP_OUTPUT="s21_grep.txt"
GREP_OUTPUT="grep.txt"
FLAGS_WITHOUT_ARGS=(i v c l n h s o)
PATTERNS=('^' '$' '67890')
PATTERN_FILE=(regex1.txt regex2.txt)
OK=0
FAIL=0
DELIMITER="..........................................................."

echo "TEST S21_GREP WITH ALL FLAGS COMBINATIONS"
echo ${DELIMITER}

run_test() {
    local ARGS="$1"
    echo "./s21_grep $ARGS"
    grep $ARGS > ${GREP_OUTPUT} 2>/dev/null
    ./s21_grep $ARGS > ${S21_GREP_OUTPUT} 2>/dev/null
    diff -q ${GREP_OUTPUT} ${S21_GREP_OUTPUT}
    
    if [ $? -eq 0 ]; then
        echo -e "OK"
        ((OK++))
    else
        echo -e "FAIL"
        ((FAIL++))
    fi
    echo ${DELIMITER}
}

num_flags=${#FLAGS_WITHOUT_ARGS[@]}

for ((a=0; a<num_flags; a++)); do
    run_test "-${FLAGS_WITHOUT_ARGS[a]}e ${PATTERNS[0]} -e ${PATTERNS[1]} ${FILES[0]}"
    run_test "-${FLAGS_WITHOUT_ARGS[a]}e ${PATTERNS[0]} -e ${PATTERNS[2]} ${FILES[0]}"
    run_test "-${FLAGS_WITHOUT_ARGS[a]}e ${PATTERNS[0]} -e ${PATTERNS[1]} ${FILES[1]}"
    run_test "-${FLAGS_WITHOUT_ARGS[a]}e ${PATTERNS[0]} -e ${PATTERNS[2]} ${FILES[1]}"
    run_test "-${FLAGS_WITHOUT_ARGS[a]}e ${PATTERNS[0]} -e ${PATTERNS[1]} -f ${PATTERN_FILE[0]} ${FILES[0]}"
    run_test "-${FLAGS_WITHOUT_ARGS[a]}e ${PATTERNS[0]} -e ${PATTERNS[1]} -f ${PATTERN_FILE[1]} ${FILES[0]}"
    run_test "-${FLAGS_WITHOUT_ARGS[a]}e ${PATTERNS[0]} -e ${PATTERNS[1]} -f ${PATTERN_FILE[0]} ${FILES[1]}"
    run_test "-${FLAGS_WITHOUT_ARGS[a]}e ${PATTERNS[0]} -e ${PATTERNS[1]} -f ${PATTERN_FILE[1]} ${FILES[1]}"
done

for ((a=0; a<num_flags; a++)); do
    for ((b=0; b<num_flags; b++)); do
        if [ $a -ne $b ]; then
            run_test "-${FLAGS_WITHOUT_ARGS[a]}${FLAGS_WITHOUT_ARGS[b]}e ${PATTERNS[0]} -e ${PATTERNS[1]} ${FILES[0]}"
            run_test "-${FLAGS_WITHOUT_ARGS[a]}${FLAGS_WITHOUT_ARGS[b]}e ${PATTERNS[0]} -e ${PATTERNS[2]} ${FILES[0]}"
            run_test "-${FLAGS_WITHOUT_ARGS[a]}${FLAGS_WITHOUT_ARGS[b]}e ${PATTERNS[0]} -e ${PATTERNS[1]} ${FILES[1]}"
            run_test "-${FLAGS_WITHOUT_ARGS[a]}${FLAGS_WITHOUT_ARGS[b]}e ${PATTERNS[0]} -e ${PATTERNS[2]} ${FILES[1]}"
            run_test "-${FLAGS_WITHOUT_ARGS[a]}${FLAGS_WITHOUT_ARGS[b]}e ${PATTERNS[0]} -e ${PATTERNS[1]} -f ${PATTERN_FILE[0]} ${FILES[0]}"
            run_test "-${FLAGS_WITHOUT_ARGS[a]}${FLAGS_WITHOUT_ARGS[b]}e ${PATTERNS[0]} -e ${PATTERNS[1]} -f ${PATTERN_FILE[1]} ${FILES[0]}"
            run_test "-${FLAGS_WITHOUT_ARGS[a]}${FLAGS_WITHOUT_ARGS[b]}e ${PATTERNS[0]} -e ${PATTERNS[1]} -f ${PATTERN_FILE[0]} ${FILES[1]}"
            run_test "-${FLAGS_WITHOUT_ARGS[a]}${FLAGS_WITHOUT_ARGS[b]}e ${PATTERNS[0]} -e ${PATTERNS[1]} -f ${PATTERN_FILE[1]} ${FILES[1]}"
        fi
    done
done

for ((a=0; a<num_flags; a++)); do
    for ((b=0; b<num_flags; b++)); do
        for ((c=0; c<num_flags; c++)); do
            if [ $a -ne $b ] && [ $a -ne $c ] && [ $b -ne $c ]; then
                run_test "-${FLAGS_WITHOUT_ARGS[a]}${FLAGS_WITHOUT_ARGS[b]}${FLAGS_WITHOUT_ARGS[c]}e ${PATTERNS[0]} -e ${PATTERNS[1]} ${FILES[0]}"
                run_test "-${FLAGS_WITHOUT_ARGS[a]}${FLAGS_WITHOUT_ARGS[b]}${FLAGS_WITHOUT_ARGS[c]}e ${PATTERNS[0]} -e ${PATTERNS[2]} ${FILES[0]}"
                run_test "-${FLAGS_WITHOUT_ARGS[a]}${FLAGS_WITHOUT_ARGS[b]}${FLAGS_WITHOUT_ARGS[c]}e ${PATTERNS[0]} -e ${PATTERNS[1]} ${FILES[1]}"
                run_test "-${FLAGS_WITHOUT_ARGS[a]}${FLAGS_WITHOUT_ARGS[b]}${FLAGS_WITHOUT_ARGS[c]}e ${PATTERNS[0]} -e ${PATTERNS[2]} ${FILES[1]}"
                run_test "-${FLAGS_WITHOUT_ARGS[a]}${FLAGS_WITHOUT_ARGS[b]}${FLAGS_WITHOUT_ARGS[c]}e ${PATTERNS[0]} -e ${PATTERNS[1]} -f ${PATTERN_FILE[0]} ${FILES[0]}"
                run_test "-${FLAGS_WITHOUT_ARGS[a]}${FLAGS_WITHOUT_ARGS[b]}${FLAGS_WITHOUT_ARGS[c]}e ${PATTERNS[0]} -e ${PATTERNS[1]} -f ${PATTERN_FILE[1]} ${FILES[0]}"
                run_test "-${FLAGS_WITHOUT_ARGS[a]}${FLAGS_WITHOUT_ARGS[b]}${FLAGS_WITHOUT_ARGS[c]}e ${PATTERNS[0]} -e ${PATTERNS[1]} -f ${PATTERN_FILE[0]} ${FILES[1]}"
                run_test "-${FLAGS_WITHOUT_ARGS[a]}${FLAGS_WITHOUT_ARGS[b]}${FLAGS_WITHOUT_ARGS[c]}e ${PATTERNS[0]} -e ${PATTERNS[1]} -f ${PATTERN_FILE[1]} ${FILES[1]}"
            fi
        done
    done
done

# for ((a=0; a<num_flags; a++)); do
#     for ((b=0; b<num_flags; b++)); do
#         for ((c=0; c<num_flags; c++)); do
#             for ((d=0; d<num_flags; d++)); do
#                 if [ $a -ne $b ] && [ $a -ne $c ] && [ $a -ne $d ] && \
#                    [ $b -ne $c ] && [ $b -ne $d ] && \
#                    [ $c -ne $d ]; then
#                     run_test "-${FLAGS_WITHOUT_ARGS[a]}${FLAGS_WITHOUT_ARGS[b]}${FLAGS_WITHOUT_ARGS[c]}${FLAGS_WITHOUT_ARGS[d]}e ${PATTERNS[0]} -e ${PATTERNS[1]} -f ${PATTERN_FILE[0]} ${FILES[0]}"
#                     run_test "-${FLAGS_WITHOUT_ARGS[a]}${FLAGS_WITHOUT_ARGS[b]}${FLAGS_WITHOUT_ARGS[c]}${FLAGS_WITHOUT_ARGS[d]}e ${PATTERNS[0]} -e ${PATTERNS[1]} -f ${PATTERN_FILE[1]} ${FILES[0]}"
#                     run_test "-${FLAGS_WITHOUT_ARGS[a]}${FLAGS_WITHOUT_ARGS[b]}${FLAGS_WITHOUT_ARGS[c]}${FLAGS_WITHOUT_ARGS[d]}e ${PATTERNS[0]} -e ${PATTERNS[1]} -f ${PATTERN_FILE[0]} ${FILES[1]}"
#                     run_test "-${FLAGS_WITHOUT_ARGS[a]}${FLAGS_WITHOUT_ARGS[b]}${FLAGS_WITHOUT_ARGS[c]}${FLAGS_WITHOUT_ARGS[d]}e ${PATTERNS[0]} -e ${PATTERNS[1]} -f ${PATTERN_FILE[1]} ${FILES[1]}"
#                 fi  
#             done
#         done
#     done
# done

# for ((a=0; a<num_flags; a++)); do
#     for ((b=0; b<num_flags; b++)); do
#         for ((c=0; c<num_flags; c++)); do
#             for ((d=0; d<num_flags; d++)); do
#                 for ((e=0; e<num_flags; e++)); do
#                     if [ $a -ne $b ] && [ $a -ne $c ] && [ $a -ne $d ] && [ $a -ne $e ] && \
#                        [ $b -ne $c ] && [ $b -ne $d ] && [ $b -ne $e ] && \
#                        [ $c -ne $d ] && [ $c -ne $e ] && \
#                        [ $d -ne $e ]; then
#                         run_test "-${FLAGS_WITHOUT_ARGS[a]}${FLAGS_WITHOUT_ARGS[b]}${FLAGS_WITHOUT_ARGS[c]}${FLAGS_WITHOUT_ARGS[d]}${FLAGS_WITHOUT_ARGS[e]}e ${PATTERNS[0]} -e ${PATTERNS[1]} -f ${PATTERN_FILE[0]} ${FILES[0]}"
#                         run_test "-${FLAGS_WITHOUT_ARGS[a]}${FLAGS_WITHOUT_ARGS[b]}${FLAGS_WITHOUT_ARGS[c]}${FLAGS_WITHOUT_ARGS[d]}${FLAGS_WITHOUT_ARGS[e]}e ${PATTERNS[0]} -e ${PATTERNS[1]} -f ${PATTERN_FILE[1]} ${FILES[0]}"
#                         run_test "-${FLAGS_WITHOUT_ARGS[a]}${FLAGS_WITHOUT_ARGS[b]}${FLAGS_WITHOUT_ARGS[c]}${FLAGS_WITHOUT_ARGS[d]}${FLAGS_WITHOUT_ARGS[e]}e ${PATTERNS[0]} -e ${PATTERNS[1]} -f ${PATTERN_FILE[0]} ${FILES[1]}"
#                         run_test "-${FLAGS_WITHOUT_ARGS[a]}${FLAGS_WITHOUT_ARGS[b]}${FLAGS_WITHOUT_ARGS[c]}${FLAGS_WITHOUT_ARGS[d]}${FLAGS_WITHOUT_ARGS[e]}e ${PATTERNS[0]} -e ${PATTERNS[1]} -f ${PATTERN_FILE[1]} ${FILES[1]}"
#                     fi
#                 done
#             done
#         done
#     done    
# done

# for ((a=0; a<num_flags; a++)); do
#     for ((b=0; b<num_flags; b++)); do
#         for ((c=0; c<num_flags; c++)); do
#             for ((d=0; d<num_flags; d++)); do
#                 for ((e=0; e<num_flags; e++)); do
#                     for ((f=0; f<num_flags; f++)); do
#                         if [ $a -ne $b ] && [ $a -ne $c ] && [ $a -ne $d ] && \
#                            [ $a -ne $e ] && [ $a -ne $f ] && \
#                            [ $b -ne $c ] && [ $b -ne $d ] && \
#                            [ $b -ne $e ] && [ $b -ne $f ] && \
#                            [ $c -ne $d ] && [ $c -ne $e ] && \
#                            [ $c -ne $f ] && \
#                            [ $d -ne $e ] && [ $d -ne $f ] && \
#                            [ $e -ne $f ]; then 
#                             run_test "-${FLAGS_WITHOUT_ARGS[a]}${FLAGS_WITHOUT_ARGS[b]}${FLAGS_WITHOUT_ARGS[c]}${FLAGS_WITHOUT_ARGS[d]}${FLAGS_WITHOUT_ARGS[e]}${FLAGS_WITHOUT_ARGS[f]}e ${PATTERNS[0]} -e ${PATTERNS[1]} -f ${PATTERN_FILE[0]} ${FILES[0]}"
#                             run_test "-${FLAGS_WITHOUT_ARGS[a]}${FLAGS_WITHOUT_ARGS[b]}${FLAGS_WITHOUT_ARGS[c]}${FLAGS_WITHOUT_ARGS[d]}${FLAGS_WITHOUT_ARGS[e]}${FLAGS_WITHOUT_ARGS[f]}e ${PATTERNS[0]} -e ${PATTERNS[1]} -f ${PATTERN_FILE[1]} ${FILES[0]}"
#                             run_test "-${FLAGS_WITHOUT_ARGS[a]}${FLAGS_WITHOUT_ARGS[b]}${FLAGS_WITHOUT_ARGS[c]}${FLAGS_WITHOUT_ARGS[d]}${FLAGS_WITHOUT_ARGS[e]}${FLAGS_WITHOUT_ARGS[f]}e ${PATTERNS[0]} -e ${PATTERNS[1]} -f ${PATTERN_FILE[0]} ${FILES[1]}"
#                             run_test "-${FLAGS_WITHOUT_ARGS[a]}${FLAGS_WITHOUT_ARGS[b]}${FLAGS_WITHOUT_ARGS[c]}${FLAGS_WITHOUT_ARGS[d]}${FLAGS_WITHOUT_ARGS[e]}${FLAGS_WITHOUT_ARGS[f]}e ${PATTERNS[0]} -e ${PATTERNS[1]} -f ${PATTERN_FILE[1]} ${FILES[1]}"
#                         fi 
#                     done 
#                 done 
#             done 
#         done 
#     done 
# done

# for ((a=0; a<num_flags; a++)); do
#     for ((b=0; b<num_flags; b++)); do
#         for ((c=0; c<num_flags; c++)); do
#             for ((d=0; d<num_flags; d++)); do
#                 for ((e=0; e<num_flags; e++)); do 
#                     for ((f=0; f<num_flags; f++)); do 
#                         for ((g=0; g<num_flags; g++)); do 
#                             if [[ "$a" != "$b" ]] && [[ "$a" != "$c" ]] && [[ "$a" != "$d" ]] &&
#                                [[ "$a" != "$e" ]] && [[ "$a" != "$f" ]] && [[ "$a" != "$g" ]] &&
#                                [[ "$b" != "$c" ]] && [[ "$b" != "$d" ]] &&
#                                [[ "$b" != "$e" ]] && [[ "$b" != "$f" ]] &&
#                                [[ "$b" != "$g" ]] &&
#                                [[ "$c" != "$d" ]] && [[ "$c" != "$e" ]] &&
#                                [[ "$c" != "$f" ]] && [[ "$c" != "$g" ]] &&
#                                [[ "$d" != "$e" ]] && [[ "$d" != "$f" ]] &&
#                                [[ "$d" != "$g" ]] &&
#                                [[ "$e" != "$f" ]] && [[ "$e" != "$g" ]] &&
#                                [[ "$f" != "$g" ]]; then 
#                                 run_test "-${FLAGS_WITHOUT_ARGS[a]}${FLAGS_WITHOUT_ARGS[b]}${FLAGS_WITHOUT_ARGS[c]}${FLAGS_WITHOUT_ARGS[d]}${FLAGS_WITHOUT_ARGS[e]}${FLAGS_WITHOUT_ARGS[f]}${FLAGS_WITHOUT_ARGS[g]}e ${PATTERNS[0]} -e ${PATTERNS[1]} -f ${PATTERN_FILE[0]} ${FILES[0]}"
#                                 run_test "-${FLAGS_WITHOUT_ARGS[a]}${FLAGS_WITHOUT_ARGS[b]}${FLAGS_WITHOUT_ARGS[c]}${FLAGS_WITHOUT_ARGS[d]}${FLAGS_WITHOUT_ARGS[e]}${FLAGS_WITHOUT_ARGS[f]}${FLAGS_WITHOUT_ARGS[g]}e ${PATTERNS[0]} -e ${PATTERNS[1]} -f ${PATTERN_FILE[1]} ${FILES[0]}"
#                                 run_test "-${FLAGS_WITHOUT_ARGS[a]}${FLAGS_WITHOUT_ARGS[b]}${FLAGS_WITHOUT_ARGS[c]}${FLAGS_WITHOUT_ARGS[d]}${FLAGS_WITHOUT_ARGS[e]}${FLAGS_WITHOUT_ARGS[f]}${FLAGS_WITHOUT_ARGS[g]}e ${PATTERNS[0]} -e ${PATTERNS[1]} -f ${PATTERN_FILE[0]} ${FILES[1]}"
#                                 run_test "-${FLAGS_WITHOUT_ARGS[a]}${FLAGS_WITHOUT_ARGS[b]}${FLAGS_WITHOUT_ARGS[c]}${FLAGS_WITHOUT_ARGS[d]}${FLAGS_WITHOUT_ARGS[e]}${FLAGS_WITHOUT_ARGS[f]}${FLAGS_WITHOUT_ARGS[g]}e ${PATTERNS[0]} -e ${PATTERNS[1]} -f ${PATTERN_FILE[1]} ${FILES[1]}"
#                             fi 
#                         done 
#                     done 
#                 done 
#             done 
#         done 
#     done
# done 

# for ((a=0; a<num_flags; a++)); do
#     for ((b=0; b<num_flags; b++)); do
#         for ((c=0; c<num_flags; c++)); do
#             for ((d=0; d<num_flags; d++)); do
#                 for ((e=0; e<num_flags; e++)); do 
#                     for ((f=0; f<num_flags; f++)); do 
#                         for ((g=0; g<num_flags; g++)); do 
#                             for ((h=0; h<num_flags; h++)); do 
#                                 if [[ "$a" != "$b" ]] && [[ "$a" != "$c" ]] && [[ "$a" != "$d" ]] &&
#                                    [[ "$a" != "$e" ]] && [[ "$a" != "$f" ]] && [[ "$a" != "$g" ]] &&
#                                    [[ "$a" != "$h"]] &&
#                                    [[ "$b" != "$c" ]] && [[ "$b" != "d"]] &&
#                                    [["$b"$!="$e"]]&&[["$b"$!="$f"]]&&[["$b"$!="$g"]]&&[["$b"$!="$h"]]&&[["$c"$!="$d"]]&&[["$c"$!="$e"]]&&[["$c"$!="$f"]]&&[["$c"$!="$g"]]&&[["$c"$!="$h"]]&&[["$d"$!="$e"]]&&[["$d"$!="$f"]]&&[["$d"$!="$g"]]&&[["$d"$!="$h"]]&&[["$e"$!="$f"]]&&[["$e"$!="$g"]]&&[["$e"$!="$h"]]&&[["$f"$!="$g"]]&&[["$f"$!="$h"]]&&[["$g"$!="$h"]];then  
#                                     run_test "-${FLAGS_WITHOUT_ARGS[a]}${FLAGS_WITHOUT_ARGS[b]}${FLAGS_WITHOUT_ARGS[c]}${FLAGS_WITHOUT_ARGS[d]}${FLAGS_WITHOUT_ARGS[e]}${FLAGS_WITHOUT_ARGS[f]}${FLAGS_WITHOUT_ARGS[g]}${FLAGS_WITHOUT_ARGS[h]}e ${PATTERNS[0]} -e ${PATTERNS[1]} -f ${PATTERN_FILE[0]} ${FILES[0]}"
#                                     run_test "-${FLAGS_WITHOUT_ARGS[a]}${FLAGS_WITHOUT_ARGS[b]}${FLAGS_WITHOUT_ARGS[c]}${FLAGS_WITHOUT_ARGS[d]}${FLAGS_WITHOUT_ARGS[e]}${FLAGS_WITHOUT_ARGS[f]}${FLAGS_WITHOUT_ARGS[g]}${FLAGS_WITHOUT_ARGS[h]}e ${PATTERNS[0]} -e ${PATTERNS[1]} -f ${PATTERN_FILE[1]} ${FILES[0]}"
#                                     run_test "-${FLAGS_WITHOUT_ARGS[a]}${FLAGS_WITHOUT_ARGS[b]}${FLAGS_WITHOUT_ARGS[c]}${FLAGS_WITHOUT_ARGS[d]}${FLAGS_WITHOUT_ARGS[e]}${FLAGS_WITHOUT_ARGS[f]}${FLAGS_WITHOUT_ARGS[g]}${FLAGS_WITHOUT_ARGS[h]}e ${PATTERNS[0]} -e ${PATTERNS[1]} -f ${PATTERN_FILE[0]} ${FILES[1]}"
#                                     run_test "-${FLAGS_WITHOUT_ARGS[a]}${FLAGS_WITHOUT_ARGS[b]}${FLAGS_WITHOUT_ARGS[c]}${FLAGS_WITHOUT_ARGS[d]}${FLAGS_WITHOUT_ARGS[e]}${FLAGS_WITHOUT_ARGS[f]}${FLAGS_WITHOUT_ARGS[g]}${FLAGS_WITHOUT_ARGS[h]}e ${PATTERNS[0]} -e ${PATTERNS[1]} -f ${PATTERN_FILE[1]} ${FILES[1]}"
#                                 fi 
#                             done 
#                         done 
#                     done 
#                 done
#             done 
#         done  
#     done 
# done

echo "OK: ${OK}"
echo "FAIL: ${FAIL}"

rm -rf ${GREP_OUTPUT} ${S21_GREP_OUTPUT}