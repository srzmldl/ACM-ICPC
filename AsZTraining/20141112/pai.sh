while true; do
./makedate
./walk >outme.txt
./check <walk.in >outstd.txt
if diff outme.txt outstd.txt; then
echo "AC"
else
echo "WA"
exit 0
fi
done
