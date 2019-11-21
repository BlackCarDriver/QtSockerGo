package main

import (
	"bufio"
	"fmt"
	"net"
	"os"
)

func main() {
	conn, err := net.Dial("tcp", ":4747")
	if err != nil {
		fmt.Printf("Error at net.Dial(): %v", err)
		os.Exit(1)
	}
	fmt.Println("The Client is running...")
	go func() {
		for {
			data, err := bufio.NewReader(conn).ReadString('\n')
			if err != nil {
				fmt.Printf("Error at bufio.NewReader: %v", err)
				os.Exit(1)
			} else {
				fmt.Printf("Response from server : %v\n", data)
			}
		}
	}()
	for {
		var input string
		fmt.Println("Send input:")
		fmt.Scanf("%s\n", &input)
		fmt.Fprintf(conn, input)
	}
}
