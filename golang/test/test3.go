package main

import (
    "fmt"
    "bufio"
    "os"
    "strings"
)

func main() {
    fmt.Println("Hello, World!")

    reader := bufio.NewReader(os.Stdin)
    for {
        fmt.Print("Enter text: ")
        text, _ := reader.ReadString('\n')
        var str string = strings.ToUpper(strings.TrimSpace(text))
        if str == "QUIT" {
            fmt.Println("Exiting...")
            break;
        }
        fmt.Printf("Read: [%q]\n",str)
    }
}
