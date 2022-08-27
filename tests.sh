#!/bin/bash

send_to_server() {
    echo $1 | nc -w $2 localhost $3
}

make_test_build() {
    make fclean
    make debug CMDFLAGS+=-DTESTING CMDSRC+=$1
}

config_test() {
    if [ -z "$1" ]
    then
        CONFIG_TEST_DIR_BAD=config/test/bad
        CONFIG_TEST_DIR_GOOD=config/test/good
        make_test_build test/config_test.cpp

        echo "++++++++++++++++++++++++++++++"
        echo "=======>Testing good<========="
        echo "++++++++++++++++++++++++++++++"
        for CONFIG in $(ls $CONFIG_TEST_DIR_GODD | sort -n)
        do
            echo
            echo "===>TESTING CONFIG: $CONFIG_TEST_DIR_GOOD$CONFIG<==="
            echo
            ./webserv $CONFIG_TEST_DIR_GOOD$CONFIG
            echo
            echo "========>DONE TESTING<========="
            echo
        done

        echo "++++++++++++++++++++++++++++++"
        echo "=======>Testing bad<========="
        echo "++++++++++++++++++++++++++++++"
        for CONFIG in $(ls $CONFIG_TEST_DIR_BAD | sort -n)
        do
            echo
            echo "===>TESTING CONFIG: $CONFIG_TEST_DIR_BAD$CONFIG<==="
            echo
            ./webserv $CONFIG_TEST_DIR_BAD$CONFIG
            echo
            echo "========>DONE TESTING<========="
            echo
        done
    else
        for QWERTY in "$@"
        do
            if [  ]
        done
    fi
}

server_test() {
    EXEC=./webserv
    PORT="8888"

    make_test_build test/server_test.cpp
    $EXEC $PORT & EXEC_PID=$!
    send_to_server "Hello there!" 1 $PORT
    kill -9 $EXEC_PID
}

dispatcher_test() {
    EXEC=./webserv
    CONF=./config/test/multiple_ports.conf
    PORT_1=7777
    PORT_2=8888
    PORT_3=9999

    make fclean ; make debug
    $EXEC $CONF & EXEC_PID=$!
    send_to_server "Hello first!" 1 $PORT_1 &
    send_to_server "Hello second!" 1 $PORT_2 &
    send_to_server "Hello third!" 1 $PORT_3 &
    sleep 3
    kill -9 $EXEC_PID
}

# config_test
# server_test
# dispatcher_test

if  [ "$1" == "config_test" ]
then
    config_test
fi

config_test  asdf shit qwerty
