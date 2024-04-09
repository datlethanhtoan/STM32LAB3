# !/bin/bash
# Init variables
add="+"
sub="-"
mul="*"
div="/"
modulo="%"
Errorcheck=0
indexDelete=0

# Save value for ANS
if [ -f "ans.txt" ] # IF exist file
then
# Read ANS from file
ANS=$(cat ans.txt)
else
# Set default for ANS
touch ans.txt # Create file to save ANS value
ANS=0
fi 

#Function HIST
HIST(){
    for i in "${HIST_Array[@]}"
    do 
        echo "$i"
    done 
}

#Start while
while true; do
# Read expression
read -p">> " expression
if [ "$expression" = "EXIT" ]
then
exit 0

elif [ "$expression" = "HIST" ]
then
HIST

else # Split expression
num1=$(echo "$expression" | cut -d ' ' -f 1)
num2=$(echo "$expression" | cut -d ' ' -f 3)
operator=$(echo "$expression" | cut -d ' ' -f 2)

if [ "$num1" = "ANS" ]
then
num1=$ANS
fi

if [ "$num2" = "ANS" ]
then
num2=$ANS
fi


# Add
if [ "$operator" = $add ]
then
ANS=$(echo "scale=2; $num1 + $num2" |bc)

# Sub
elif [ "$operator" = $sub ]
then
ANS=$(echo "scale=2; $num1 - $num2" |bc)

# Mul
elif [ "$operator" = "$mul" ]
then
ANS=$(echo "scale=2; $num1 * $num2" | bc)

# Div
elif [ "$operator" = $div ]
then
if [ $num2 -eq 0 ]
then
Errorcheck=1
echo "MATH ERROR"
else
ANS=$(echo "scale=2; $num1 / $num2" |bc)
fi

# Idiv
elif [ "$operator" = $modulo ]
then
if [ $num2 -eq 0 ]
then
Errorcheck=1
echo "MATH ERROR"
else
ANS=$(echo "scale=2; $num1 % $num2" |bc)
fi

# Syntax error
else
Errorcheck=1
echo "SYNTAX ERROR"
fi


# Print ANS & save ANS value
if [ $Errorcheck -eq 0 ]
then
echo $ANS
# Write value to file
echo $ANS > ans.txt
# Save expression to HIST
HIST_Array+=("$expression = $ANS")
if [ ${#HIST_Array[@]} -gt 5 ]
then
unset HIST_Array[$indexDelete]
((indexDelete++))
fi # IF-Hist

else
Errorcheck=0
fi # IF Errorcheck
fi
read temp
clear
# End while
done