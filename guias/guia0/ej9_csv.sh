declare -a array_c1=()  
declare -a array_c2=()  
declare -a array_c3=()
declare -a array_c4=() 
for num in $(cut -d "," -f1 tabla.csv); do array_c1+=($num); done
for num in $(cut -d "," -f2 tabla.csv); do array_c2+=($num); done
for num in $(cut -d "," -f3 tabla.csv); do array_c3+=($num); done
for i in ${!array_c2[@]}; do
ef2=${array_c2[$i]}
ef3=${array_c3[$i]}
diff=$(($ef2-$ef3))
array_c4+=($diff)
done
echo "" > tabla.csv
for i in ${!array_c1[@]}; do
ef1=${array_c1[$i]}
ef2=${array_c2[$i]}
ef3=${array_c3[$i]}
ef4=${array_c4[$i]}
echo "$ef1,$ef2,$ef3,$ef4" >> tabla.csv
done