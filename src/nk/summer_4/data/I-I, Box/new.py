import sys
import os
for i in range(1, 42, 1):
    os.system("./I.test < {}.in > x{}.out".format(i, i))
    os.system("./checker.O2 {}.in {}.out x{}.out".format(i, i, i))
