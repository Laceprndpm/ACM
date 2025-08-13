function shuffle(t)
    math.randomseed(os.time()) -- 设随机种子（只需调用一次）
    for i = #t, 2, -1 do
        local j = math.random(i)  -- 1 到 i 之间
        t[i], t[j] = t[j], t[i]
    end
end

io.write("1\n")
n = arg[1]
io.write(n, "\n")
arr = {}
for i = 1, n do
    arr[i] = i
end
shuffle(arr)
for i = 1, n do
    io.write(arr[i], " ")
end
io.stderr:write(n, "\n")
for i = 1, n do
    io.stderr:write(arr[i], " ")
end
io.stderr:write("\n")
