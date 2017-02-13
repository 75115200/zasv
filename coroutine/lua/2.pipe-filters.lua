#! /usr/bin/env lua

-- consumes data form "from"
function consumer(from)
    while true do
        local x = receive(from) -- receive from producer
        io.write(x, "\n")       -- consume new value
    end
end

function producer()
    return coroutine.create(function()
        while true do
            local x = io.read() -- produce new value
            send(x)             -- send to consumer
        end
    end)
end

function filter(from)
    return coroutine.create(function(x)
        local line = 1
        while true do
            local x = receive(from)
            x = string.format("%5d %s", line, x)
            send(x) -- send it to consumer
            line = line +1
        end
    end)
end

-- utils --

receive = function(from)
    local success, value =  coroutine.resume(from)
    return value
end

send = function(x)
    coroutine.yield(x);
end


-- run --

consumer(filter(producer()))


