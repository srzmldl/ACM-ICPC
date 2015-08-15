while true; do
./make
./hdu4742 >out1.txt
./check4742 >outstd.txt
if diff out1.txt outstd.txt; then
echo "AC"
else 
echo "WA"
exit 0
fi
done
