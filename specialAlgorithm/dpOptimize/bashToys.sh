while true; do
    ./makeToys >toys.in
    ./checkToy <toys.in >std.out
    ./hnoi2008toys >toys.out
    if diff std.out toys.out; then
        echo "AC"
        else
        echo "WA"
        exit 0
        fi
    done
