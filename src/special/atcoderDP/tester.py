import os
roundtime = 25
path = "/home/patchouli/Code/ACM/src/special/atcoderDP/dp_b_teach_1.cpp"
generater = "/home/patchouli/Code/ACM/src/special/atcoderDP/dp_b_teach_1.py"
outputname = "dp_b_teach_1.O2"
os.system(f"g++ -O2 {path} -o {outputname}")
for i in range(roundtime):
    os.system(f"python3 {generater} > in{i}.txt")
    os.system(f"time ./{outputname} < in{i}.txt > out{i}.txt")
    print("used time for round", i)
