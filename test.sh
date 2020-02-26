#!/usr/bin/env bash

for i in tests/*.test; do
	i=${i#tests/}
	i=${i%.test}

	echo "TEST $i"

	cat tests/$i.test | ./out | pcregrep -M "answer:\n([\d ]*\n)*" | pcregrep "^\d" > ans

	status="${PIPESTATUS[1]}"
	if [[ "$status" != "0" ]]; then
		echo "test NOT passed - exit status "$status
	else

		echo "answer:"; cat ans
		echo; echo "right answer:"; cat tests/$i.ans


		if [[ "$(cat ans)" == "$(cat tests/$i.ans)" ]]; then
			echo "test passed"
		else
			echo "test NOT passed"
		fi
	fi

	echo "END OF TEST $i"
	echo -en "\n\n"
done