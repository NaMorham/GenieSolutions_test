package main

import (
    "fmt"
    "bufio"
    "os"
)

func main() {
    fmt.Println("Hello, World!")

    reader := bufio.NewReader(os.Stdin)
    fmt.Print("Enter text: ")
    text, _ := reader.ReadString('\n')
    fmt.Printf("Read: [%q]\n",text)
}
