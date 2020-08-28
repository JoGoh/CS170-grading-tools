#!/bin/bash
function clean_all
{
	for name in *
	do
		sub=${name}
		end_cond="test"
		if [ ${sub} = ${end_cond} ];
		then
		break
		fi
		echo ${sub}
		rm -f ${sub}/test
	done
}

function test_all
{
	
	for name in *
	do
		if [ -d ${name} ]
		then
			end_cond='test'
			if [ ${name} == ${end_cond} ]
			then
			break
			fi
			echo ${name}
			cp -r test/* ${name}
			cd ${name}
			./Grade.bat
			read -p "finished "$name". press any key to grade next student..."
			cd ..
		fi
	done
}

clean_all
test_all