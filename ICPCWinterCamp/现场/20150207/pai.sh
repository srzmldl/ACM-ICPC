while true; do
    ./make >tmp.in
    ./A <tmp.in>out1
    ./B2 <tmp.in> out2
    if diff out1 out2
	then echo "AC"
	else echo "WA" 
	exit 0
fi
done
