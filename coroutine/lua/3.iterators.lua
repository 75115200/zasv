#! /usr/bin/env lua

local testData = {1, 2, 3}
local testDataLen = #testData
-- permutation generation
-- @param a array
-- @param n int
function permgen(a, n)
    if n == 0 then
        execResult(a)
    else
        for i=1,n do
            -- swap
            -- put i-th element as the last one
            a[n], a[i]= a[i], a[n]

            -- generate all permuatations of the other elments
            permgen(a, n - 1)

            -- restore i-th element
            a[n], a[i]= a[i], a[n]
        end
    end
end

-- util
function printArr(array)
    for i,v in ipairs(array) do
        io.write(v, " ")
    end
    io.write("\n")
end



-- test

-- method 1
function conventionalRecursiveIterationTest()
    -- define strategy
    execResult = printArr

    permgen(testData, testDataLen)
end

-- method 2
function coroutineIterationTest_plainForLoop()
    function execResult(array)
        coroutine.yield(array)
    end

    local co = coroutine.create(function() permgen(testData, testDataLen) end)
    while true do
        local code, res = coroutine.resume(co)
        if not (res == nil) then
            printArr(res)
        else
            break
        end
    end
end

-- method 3
function coroutineIterationTest_withIterator()
    function execResult(arr)
        coroutine.yield(arr)
    end

    function perm(a)
        -- get array length
        -- table.getn was deprecated in lua5.1
        -- local n = table.getn(a)
        local n = #a
        local co = coroutine.create(function() permgen(a, n) end)
        return function() --iterator
            local code, res = coroutine.resume(co)
            return res
        end
    end

    for p in perm(testData) do
        printArr(p)
    end
end

-- method 4
function coroutineIterationTest_withCoroutineWrap()
    function execResult(arr)
        coroutine.yield(arr)
    end

    -- equals to method 3
    function perm(a)
        return coroutine.wrap(function() permgen(a, #a) end)
    end

    for p in perm(testData) do
        printArr(p)
    end
end

-- test
function runTest(functionName)
    io.write(functionName, "\n")
    local fun = _G[functionName]
    fun()
    io.write("\n\n")
end

runTest("conventionalRecursiveIterationTest")

runTest("coroutineIterationTest_plainForLoop")

runTest("coroutineIterationTest_withIterator")

runTest("coroutineIterationTest_withCoroutineWrap")
