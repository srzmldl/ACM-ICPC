while true; do
./makeThreeCircle
./topSort >outTop.txt
./bestMethod >best.txt
if diff outTop.txt best.txt; then
echo "AC"
else echo "WA"
fi
done
