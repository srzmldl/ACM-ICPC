while true; do
./data
./la4128 >out1.txt
./check4128 >out2.txt
if diff out1.txt out2.txt; then
echo "AC"
else 
echo "WA"
exit 0
fi
done
