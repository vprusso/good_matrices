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
	for n in `seq $1 2 $u`
	do
		./generate_matching_instances_comp $n
		./generate_pairedmatchings $n
		./sortpairs.sh $n
		./join_pairedmatchings $n
		./remove_equivalent_matchedpairs $n
	done
fi
