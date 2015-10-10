while true; do
    ./make
    ./hduInTouch
    ./lerence
    if diff out.txt outstd.txt; then
        echo AC
    else
        echo WA
        exit
    fi
done
