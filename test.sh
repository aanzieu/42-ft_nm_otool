#!/bin/sh

bin="./bin/ft_nm"
foo="./test"

# make fclean && make
printf  "#------------- TEST 1 --------------------#\n"
printf  "#------------- Classic A.out -------------#\n\n"

${bin} ${foo}/a.out

printf "\n#------------- TEST 2 --------------------#\n"
printf "#------------- Archives Test -------------#\n\n"
${bin} ${foo}/ar_corr1.a
${bin} ${foo}/ar_corr2.a
${bin} ${foo}/ar_corr3.a
${bin} ${foo}/ar_corr4.a
${bin} ${foo}/ar_corr5.a
${bin} ${foo}/ar_corr6.a

printf "\n#------------- TEST 3 ------------------#\n"
printf  "#------------- Fat Archive -------------#\n\n"

${bin} ${foo}/archive_fat.a

printf "\n#------------- TEST 4 --------------------#\n"
printf  "#------------- Archive 2 niv -------------#\n\n"

${bin} ${foo}/archiveception_niv1.a
${bin} ${foo}/archiveception_niv2.a

printf "\n#------------- TEST 5 -----------------------#\n"
printf  "#------------- Big and Fat Arch -------------#\n\n"

${bin} ${foo}/big_ar.c
${bin} ${foo}/big_fat

printf "\n#------------- TEST 6 -----------#\n"
printf  "#------------- Corr -------------#\n\n"

${bin} ${foo}/corr1
${bin} ${foo}/corr2

printf "\n#------------- TEST 7 --------------#\n"
printf  "#------------- scvfsdb -------------#\n\n"

${bin} ${foo}/cvfsdb_sbin

printf "\n#------------- TEST 8 ---------------#\n"
printf  "#------------- Ds Store -------------#\n\n"

${bin} ${foo}/ds_store

printf "\n#------------- TEST 9 ------------#\n"
printf  "#------------- Troll -------------#\n\n"

${bin} ${foo}/electric_troll.o

printf "\n#------------- TEST 10 -----------#\n"
printf  "#------------- Empty -------------#\n\n"

${bin} ${foo}/empty_file

printf "\n#------------- TEST 11 --------------#\n"
printf  "#------------- Fat Arch -------------#\n\n"

${bin} ${foo}/fat_binary_ar.a

printf "\n#------------- TEST 12 --------------#\n"
printf  "#------------- Fat corr -------------#\n\n"

${bin} ${foo}/fat_corr1
${bin} ${foo}/fat_corr2
${bin} ${foo}/fat_corr3
${bin} ${foo}/fat_corr4
${bin} ${foo}/fat_corr5
${bin} ${foo}/fat_corr6
${bin} ${foo}/fat_corr7

printf "\n#------------- TEST 13 --------------#\n"
printf  "#------------- Fat File -------------#\n\n"

${bin} ${foo}/fat_file.a

printf "\n#------------- TEST 14 ---------------#\n"
printf  "#------------- Fat Macho -------------#\n\n"

${bin} ${foo}/fat_macho.a

printf "\n#------------- TEST 15 ------------------#\n"
printf  "#------------- Fucking Bomb -------------#\n\n"

${bin} ${foo}/fucking_bomb

printf "\n#------------- TEST 16 ---------------#\n"
printf  "#------------- Hard Test -------------#\n\n"

${bin} ${foo}/hard_test_1

printf "\n#------------- TEST 17 -----------------#\n"
printf  "#------------- HelloWorld -------------#\n\n"

${bin} ${foo}/helloworldx32
${bin} ${foo}/helloworldx64
${bin} ${foo}/helloworldx64_samevalue_samename1
${bin} ${foo}/helloworldx64_samevalue1

printf "\n#------------- TEST 18 ---------------#\n"
printf  "#------------- Macho Fat -------------#\n\n"

${bin} ${foo}/macho_fat.a
${bin} ${foo}/macho_lft_macho.a
${bin} ${foo}/macho_lft.a
${bin} ${foo}/macho.a

printf "\n#------------- TEST 19 --------------#\n"
printf  "#------------- PPC only -------------#\n\n"

${bin} ${foo}/ppc_only

printf "\n#------------- TEST 20 --------------#\n"
printf  "#------------- Segfault -------------#\n\n"

${bin} ${foo}/segfault_nm

printf "\n#------------- TEST 21 ----------------#\n"
printf  "#------------- Other Test -------------#\n\n"

${bin} ${foo}/test.a
${bin} ${foo}/test.c
${bin} ${foo}/test1.c
${bin} ${foo}/test1.o