while true; do
    ./make
    ./zoj1015
    ./std1015
    if diff out.txt std.out; then
        echo "AC"
    else
        echo "WA"
        exit
    fi
done
