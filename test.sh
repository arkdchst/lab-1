#!/usr/bin/env bash

for i in tests/*.test; do
	i=${i#tests/}
	i=${i%.test}

	echo "test $i"

	cat tests/$i.test | ./out | pcregrep -M "answer:\n([\d .i+-]*\n)*" | pcregrep "^[\d .i+-]" > ans

	status="${PIPESTATUS[1]}"
	if [[ "$status" != "0" ]]; then
		echo "test $i NOT passed - exit status "$status
	else

		echo "answer:"; cat ans
		echo; echo "right answer:"; cat tests/$i.ans


		if [[ "$(cat ans)" == "$(cat tests/$i.ans)" ]]; then
			echo "test $i passed"
		else
			echo "test $i NOT passed"
		fi
	fi

	echo -en "\n\n"
done