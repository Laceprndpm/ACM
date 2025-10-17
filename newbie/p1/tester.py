import os

programs = ["std", "std"]

generater1 = "./gene.py"
# os.system(f"g++ -O2 {program1} -o {program1}.O2 -std=c++23")
# os.system(f"g++ -O2 {program2} -o {program2}.O2 -std=c++23")
for program in programs:
    os.system(f"g++ -O2 ./{program}.cpp -o {program}.O2 -std=c++23")
datapath = "./data/"
os.makedirs(os.path.dirname(datapath), exist_ok=True)
os.system(f"python {generater1}")

# 对于所有./data/*.in
for program in programs:
    for filename in os.listdir("./data"):
        if filename.endswith(".in"):
            testname = filename[:-3]
            os.system(
                f"time ./{program}.O2 < ./data/{testname}.in > ./data/{testname}_{program}.out"
            )
            print(f"{program} used time for {testname}")


program1 = programs[0]
program2 = programs[1]
for filename in os.listdir("./data"):
    if filename.endswith(".in"):
        testname = filename[:-3]
        with open(f"./data/{testname}_{program1}.out", "r") as f1, open(
            f"./data/{testname}_{program2}.out", "r"
        ) as f2:
            out1 = f1.read()
            out2 = f2.read()
            if out1 != out2:
                print(f"Wrong Answer on {testname}")
                with open(
                    f"./data/{testname}_WA_{program1}_{program2}.out", "w"
                ) as fwa:
                    fwa.write(out1)
                    fwa.write("-----\n")
                    fwa.write(out2)
            else:
                print(f"Accepted on {testname}")
