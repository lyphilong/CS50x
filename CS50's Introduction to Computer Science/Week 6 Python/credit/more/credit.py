from cs50 import get_int
import numpy as np
import math

number_raw = get_int("Number: ")

number = list(map(int, str(number_raw)))
odd = []
even = []

AMEX =[34,37]
MASTER = [51,52,53,53]
VISA = [4]

second = math.ceil(number_raw / pow(10,(len(str(number_raw)) -2)))-1
first = math.ceil(number_raw / pow(10,(len(str(number_raw)) -1)))-1

for i in range(len(number)):
    if(i%2 == 0):
        odd.append(number[i])
    else:
        even.append(number[i])

for i in range(len(odd)):
    odd[i] = odd[i]*2

for i in range(len(odd)):
    odd[i] = list(map(int, str(odd[i])))


odd_result = np.sum(odd)
even_result = np.sum(even)

legit = odd_result + even_result

a = 0

if(len(str(number_raw)) == 15  and second in AMEX and (legit%10 == 0) ):
    a = 1
elif (len(str(number_raw)) == 16  and second in MASTER and (legit%10 == 0)):
    a = 2
elif ((len(str(number_raw)) == 16 or len(str(number_raw)) == 13)  and first in VISA and (legit%10 == 0)):
    print("vv")
else:
    a = 0
