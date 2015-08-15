while true; do
    ./make3507
    ./hdu3507 >out.txt
    ./hdu3507Std >outStd.txt
    if diff out.txt outStd.txt; then
        echo "AC"
    else  echo "WA"
        exit 0
    fi

 done
