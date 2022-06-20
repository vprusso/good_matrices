if [ -z "$1" ]
then
	echo "Use ./driver.sh n to enumerate good matrices of odd orders n divisible by 3"
	echo "or ./driver.sh n m to enumerate good matrices of odd orders between n and m divisible by 3"
	exit
else
	if [ -z "$2" ]
	then
		u=$1
	else
		u=$2
	fi
	if [ $((u%2)) -eq 0 ]
	then
		echo "Order must be odd"
		exit
	fi
	make all
	for n in `seq $1 6 $u`
	do

		start_time="$(date -u +%s)"
		./generate_matching_instances_comp $n
		end_time="$(date -u +%s)"
		elapsed="$(($end_time-$start_time))"
		echo "Total of $elapsed seconds elapsed for generate_matching_instances_comp\n"

		start_time="$(date -u +%s)"
		./generate_pairedmatchings $n
		end_time="$(date -u +%s)"
		elapsed="$(($end_time-$start_time))"
		echo "Total of $elapsed seconds elapsed for generate_pairedmatchings\n"

		start_time="$(date -u +%s)"
		./sortpairs.sh $n
		end_time="$(date -u +%s)"
		elapsed="$(($end_time-$start_time))"
		echo "Total of $elapsed seconds elapsed for sortpairs\n"

		start_time="$(date -u +%s)"
		./join_pairedmatchings $n
		end_time="$(date -u +%s)"
		elapsed="$(($end_time-$start_time))"
		echo "Total of $elapsed seconds elapsed for join_pairedmatchings\n"

		start_time="$(date -u +%s)"
		./remove_equivalent_matchedpairs $n
		end_time="$(date -u +%s)"
		elapsed="$(($end_time-$start_time))"
		echo "Total of $elapsed seconds elapsed for remove_equivalent_matchedpairs\n"
	done
fi
