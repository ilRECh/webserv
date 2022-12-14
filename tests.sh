send_to_server() {
    echo $1 | nc -w $2 localhost $3
}

make_test_build() {
    make fclean
    make debug CMDFLAGS+=-DTESTING CMDSRC+=$1
}

config_test() {
    CONFIG_TEST_DIR=config/test/
    make_test_build test/config_test.cpp
    for CONFIG in $(ls $CONFIG_TEST_DIR | sort -n)
    do
        echo
        echo "===>TESTING CONFIG: $CONFIG_TEST_DIR$CONFIG<==="
        echo
        ./webserv $CONFIG_TEST_DIR$CONFIG
        echo
        echo "========>DONE TESTING<========="
        echo
    done
}

server_test() {
    EXEC=./webserv
    PORT="8888"

    make_test_build test/server_test.cpp
    $EXEC $PORT & EXEC_PID=$!
    send_to_server "Hello there!" 1 $PORT
    kill -9 $EXEC_PID
}

# server_test
config_test
