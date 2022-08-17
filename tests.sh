EXEC=./webserv
LOCALHOST="127.0.0.1"
PORT="8888"

send_to_server() {
    echo $1 | nc -w 1 $LOCALHOST $PORT 
}

$EXEC $PORT & EXEC_PID=$!

send_to_server "Hello there!"

kill -9 $EXEC_PID
