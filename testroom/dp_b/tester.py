import os

path = "./target.cpp"
generater1 = "./gene.py"
generater2 = "./handmaker.py"
outputname = "target.O2"
os.system(f"g++ -O2 {path} -o {outputname}")
datapath = "./data/"
os.makedirs(os.path.dirname(datapath), exist_ok=True)
os.system(f"python {generater1}")
os.system(f"python {generater2}")

# 对于所有./data/*.in
for filename in os.listdir("./data"):
    if filename.endswith(".in"):
        testname = filename[:-3]
        os.system(f"time ./{outputname} < ./data/{testname}.in > ./data/{testname}.out")
        print(f"used time for {testname}")
