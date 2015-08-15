while true; do
./gen>tmp.in #出数据
./std<tmp.in>std.out #正确（暴力）程序
./Btree<tmp.in>my.out #被测程序
if diff std.out my.out; then #比较两个输出文件
echo "AC" #结果相同显示AC
else
echo "WA" #结果不同显示WA，并退出
exit 0
fi #if的结束标志,与c语言相反，0为真
done #while的结束标志

#by lerence ray 2014-09-15
#在终端下，进入当前目录，输入"sh ./cheker.sh",（其中checker.sh为当前shell脚本名） '#'表示单行注释
#diff在两文件相同时返回空串
