#! /usr/bin/env lua

--require "luasocket"

local socket = require "socket"

function download(host, file)
    local c = assert(socket.connect(host, 80))
    local count = 0 -- counts number of bytes read
    c:send("GET" .. file .. " HTTP/1.0\r\n\r\n")
    while true do
        local content, status = receive(c)
        count = count + string.len(content)
        if status == "closed" then break end
    end
    c:close()
    print(file, count)
end

function receive(connection)
    connection:time(0) -- do not block
    local s, status = conn:receive(2^10)
    if status == "timeout" then
        print("yield")
        coroutine.yield(connection)
    else
        print("received")
    end
    return s, status
end


threads = {}
function get(host, file)
    -- create coroutine
    local co = coroutine.create(function()
        download(host, file)
    end)

    -- insert it in the list
    table.insert(threads, co)
end

function dispatcher()
    while true do
        local n = #threads
        print("threads = " .. tostring(n))
        if n == 0 then break end -- no more threads to run

        -- schedule
        for i=1,n do
            local status, res = coroutine.resume(threads[i])
            if not res then -- thread finished its task?
                table.remove(threads, i)
                break
            end
        end
    end
end

-- test

local host = "www.w3c.org"
local file = "/TR/REC-html32.html"
get(host, file)
--get(host, "/TR/html401/html40.txt")
--get(host,"/TR/2002/REC-xhtml1-20020801/xhtml1.pdf")
--get(host,"/TR/REC-html32.html")
--get(host, "/TR/2000/REC-DOM-Level-2-Core-20001113/DOM2-Core.txt")

dispatcher() -- main loop

