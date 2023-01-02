#!/bin/sh
find ./srcs/bonus -type f -name *.c
read -p "Do you want to continue? [Y/n] " yn
case "$yn" in [yY]*) ;; *) echo "abort." ; exit ;; esac

# # find ./srcs/lib -type f -name *.c | sed -n ${a}P -
# # find ./srcs/lib -type f -name *.c | sed -n ${a}P - | grep c
# # find ./srcs/lib -type f -name *.c | awk 'NR==${a}' -
# # find ./srcs/lib -type f -name *.c | head -n ${a} - | tail -n 1

# cnt=1
# while true
# do
# 	echo "job $cnt"
# 	find ./srcs/bonus -type f -name *.c | sed -n ${cnt}P - | grep -q c
# 	if [ $? -ne 0 ]
# 	then
# 		break
# 	fi
# 	find ./srcs/bonus -type f -name *.c | sed -n ${cnt}P -
# 	find ./srcs/bonus -type f -name *.c | sed -n ${cnt}P - | xargs sed -e "s/\.h\"$/_bonus\.h\"/g" > tmp
# 	find ./srcs/bonus -type f -name *.c | sed -n ${cnt}P - | xargs mv tmp
# 	cnt=`expr $cnt + 1`
# done

# find ./includes -type f -name *.h | grep .h$ | sed -e s/\.h$// | awk '{print $1 ".h " $1 "_bonus.h"}' | xargs -n 2 cp

cnt=1
while true
do
	echo "job $cnt"
	find ./includes -type f -name *bonus.h | sed -n ${cnt}P - | grep -q c
	if [ $? -ne 0 ]
	then
		break
	fi
	find ./includes -type f -name *bonus.h | sed -n ${cnt}P -
	find ./includes -type f -name *bonus.h | sed -n ${cnt}P - | xargs sed -e "s/_H$/_BONUS_H/g" > tmp
	find ./includes -type f -name *bonus.h | sed -n ${cnt}P - | xargs mv tmp
	cnt=`expr $cnt + 1`
done

# find ./includes -type f -name *.h | xargs -L 1 sed -e "s/_H$/_BONUS_H/g"

# cnt=1
# while true
# do
# 	echo "job $cnt"
# 	find ./srcs/bonus -type f -name *.c | sed -n ${cnt}P - | grep -q c
# 	if [ $? -ne 0 ]
# 	then
# 		break
# 	fi
# 	find ./srcs/bonus -type f -name *.c | sed -n ${cnt}P -
# 	find ./srcs/bonus -type f -name *.c | sed -n ${cnt}P - | sed -e s/\.c$// | awk '{print $1 ".c " $1 "_bonus.c"}' | xargs mv
# 	cnt=`expr $cnt + 1`
# done
#一行ずつやったら，ファイルネーム変わった時点で順番が変わっちゃう

# ls -R srcs/bonus/ | grep .c$ | sed -e s/\.c$// | awk '{print $1 ".c " $1 "_bonus.c"}' | xargs -n 2 mv
# find ./srcs/bonus -type f -name *.c | grep .c$ | sed -e s/\.c$// | awk '{print $1 ".c " $1 "_bonus.c"}' | xargs -n 2 mv
