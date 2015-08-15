while true; do
    ./makeD
    ./D  >out1.txt
    ./checkD  > out2.txt
    if diff out1.txt out2.txt; 
	then echo "AC"
	else echo "WA" 
	exit 0
fi
done
