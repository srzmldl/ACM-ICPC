while true; do
    ./makeB >in.txt
    ./B <in.txt >out1.txt
    ./checkB <in.txt > out2.txt
    if diff out1.txt out2.txt; 
	then echo "AC"
	else echo "WA" 
	exit 0
fi
done
