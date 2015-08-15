while true; do
./makeB
./B
./Bcheck
if diff E1.out E2.out; then
echo "AC"
else
echo "WA"
exit 0
fi
done
