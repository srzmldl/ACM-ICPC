while true; do
./make >in.txt
./G <in.txt >outck.txt
./longBinarySequence <in.txt >out.txt
if diff outck.txt out.txt
    then echo "AC"
    else echo "WA"
    exit 0
fi
done
