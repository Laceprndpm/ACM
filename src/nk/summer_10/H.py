for a in range(0, 10):
    for b in range(0, 10):
        if (b == a):
            continue
        for c in {"-"}:
            d = str(a) + c + str(b)
            e = str(b) + c + str(a)
            print(d, "=", eval(d))
            print(e, "=", eval(e))
            assert eval(d) != eval(e), f"Error: {d} != {e}"
for a in range(0, 10):
    for b in range(0, 10):
        if b == a:
            continue
        for c in {"+", "*"}:
            d = str(a) + c + str(b)
            e = str(b) + c + str(a)
            print(d, "=", eval(d))
            print(e, "=", eval(e))
            assert eval(d) == eval(e), f"Error: {d} != {e}"
