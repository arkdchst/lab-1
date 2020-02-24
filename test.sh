#!/usr/bin/env bash

for i in tests/*.test; do
	i=${i#tests/}
	i=${i%.test}

	echo "TEST $i"

	cat tests/$i.test | ./out | pcregrep -M "answer:\n([\d ]*\n)*" | pcregrep "^\d" > ans

	echo "answer:"; cat ans
	echo; echo "right answer:"; cat tests/$i.ans


	if [[ "$(cat ans)" == "$(cat tests/$i.ans)" ]]; then
		echo "TEST PASSED"
	else
		echo "TEST NOT PASSED"
	fi

	echo "END OF TEST $i"
	echo -en "\n\n"
done