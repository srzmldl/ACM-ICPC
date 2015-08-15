while true; do
    ./makeI
    ./I
    ./checkI
    if diff iq.out iqstd.out; then
        echo "AC"
    else
        echo "WA"
        exit 0
    fi
done
