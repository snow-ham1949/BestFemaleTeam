for i in $(seq 1 10000);
do
  python3 gen.py
  ./ac < test.in > out_ac
  ./wa < test.in > out_wa
  diff out_ac out_wa || break
done
