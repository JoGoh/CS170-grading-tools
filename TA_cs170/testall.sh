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
		rm -f ${sub}.out
		if [ -d ${sub}/${sub}_compile ];
		then
		rm -r ${sub}/${sub}_compile
		fi
		rm -f ${sub}/gnu_out.exe
		rm -f ${sub}/ms_out.exe
		rm -f ${sub}/test_gnu.*
		rm -f ${sub}/test_ms.*
		rm -f ${sub}/in.*
		rm -f ${sub}/out.*
		rm -f ${sub}/input.txt
		rm -f ${sub}/output.txt
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
			mkdir ${name}_compile
			make -f makefile.gnu
			make -f makefile.ms
			g++ -std=c++11 -Wall -Wextra -Werror -ansi -pedantic -o gnu_out.exe list.cpp main.cpp &> ${name}_compile/gnu_compile.out
			cl /EHsc /W4 /WX /Fems_out.exe list.cpp main.cpp &> ${name}_compile/ms_compile.out
			if [ -f gnu_out.exe ]
			then
			./gnu_out.exe < input.txt > test_gnu.0
			./gnu_out.exe < in.1 > test_gnu.1
			./gnu_out.exe < in.2 > test_gnu.2
			./gnu_out.exe < in.3 > test_gnu.3
			./gnu_out.exe < in.4 > test_gnu.4
			./gnu_out.exe < in.5 > test_gnu.5
			diff --strip-trailing-cr --ignore-blank-lines test_gnu.0 output.txt | wc.exe | ./append.exe 0 >> ../${name}.out
			diff --strip-trailing-cr --ignore-blank-lines test_gnu.1 out.1 | wc.exe | ./append.exe 1 >> ../${name}.out
			diff --strip-trailing-cr --ignore-blank-lines test_gnu.2 out.2 | wc.exe | ./append.exe 2 >> ../${name}.out
			diff --strip-trailing-cr --ignore-blank-lines test_gnu.3 out.3 | wc.exe | ./append.exe 3 >> ../${name}.out
			diff --strip-trailing-cr --ignore-blank-lines test_gnu.4 out.4 | wc.exe | ./append.exe 4 >> ../${name}.out
			diff --strip-trailing-cr --ignore-blank-lines test_gnu.5 out.5 | wc.exe | ./append.exe 5 >> ../${name}.out
			else
			echo ${name} cannot be compiled in GNU!
			fi
			if [ -f ms_out.exe ]
			then
			./ms_out.exe < input.txt > test_ms.0
			./ms_out.exe < in.1 > test_ms.1
			./ms_out.exe < in.2 > test_ms.2
			./ms_out.exe < in.3 > test_ms.3
			./ms_out.exe < in.4 > test_ms.4
			./ms_out.exe < in.5 > test_ms.5
			diff --strip-trailing-cr --ignore-blank-lines test_ms.0 output.txt | wc.exe | ./append.exe 6 >> ../${name}.out
			diff --strip-trailing-cr --ignore-blank-lines test_ms.1 out.1 | wc.exe | ./append.exe 7 >> ../${name}.out
			diff --strip-trailing-cr --ignore-blank-lines test_ms.2 out.2 | wc.exe | ./append.exe 8 >> ../${name}.out
			diff --strip-trailing-cr --ignore-blank-lines test_ms.3 out.3 | wc.exe | ./append.exe 9 >> ../${name}.out
			diff --strip-trailing-cr --ignore-blank-lines test_ms.4 out.4 | wc.exe | ./append.exe 10 >> ../${name}.out
			diff --strip-trailing-cr --ignore-blank-lines test_ms.5 out.5 | wc.exe | ./append.exe 11 >> ../${name}.out
			else
			echo ${name} cannot be compiled in MS!
			fi
			cat ../${name}.out
			read -p "finished "$name". press any key to grade next student..."
			cd ..
		fi
	done
}

clean_all
test_all