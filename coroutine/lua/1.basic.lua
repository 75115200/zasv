#! /usr/bin/env lua

function consumer()
    while true do
        local x = receive() -- receive from producer

        -- consumer the new data
        io.write(string.format("consume value [%s]", x), "\n")
    end
end

producer = coroutine.create(function()
    while true do
        local x = io.read() -- produce one new data
        send(x)             -- send it to consumer
    end
end)

-- utils

function receive()
    local success, value  = coroutine.resume(producer)
    return value
end

function send(x)
    coroutine.yield(x)
end

-- main

consumer()

