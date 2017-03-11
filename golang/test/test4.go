package main

import (
    "fmt"
    "bufio"
    "os"
    "strings"
)

type Point struct {
    x,y int
}

func (p *Point) moveX(dx int) {
    p.x += dx
}

func (p *Point) moveY(dy int) {
    p.y += dy
}

func (p *Point) move(dp Point) {
    p.x += dp.x
    p.y += dp.y
}

func main() {
    fmt.Println("Hello, World! - test4")

    pt := Point{x: 1, y: 1}
    fmt.Printf("pt = [%v]\n", pt)

    reader := bufio.NewReader(os.Stdin)
    for {
        fmt.Print("Enter text: ")
        text, _ := reader.ReadString('\n')
        var str string = strings.ToUpper(strings.TrimSpace(text))
        if str == "QUIT" {
            fmt.Println("Exiting...")
            break
        }
        tokens := strings.Split(str, " ")
        numTokens := len(tokens)
        fmt.Printf("tokens --> len() == [%d] %q\n", len(tokens), tokens)

        switch (numTokens) {
        case 0:
            // no args, nothing to do
            continue
        case 1:
            // Commands with no arguments
            if tokens[0] == "MOVE" {
                fmt.Println("MOVE command not implemented")
            } else if str == "MOVEX" {
                if pt.x >= 5 {
                    pt.x = 0
                } else {
                    pt.moveX(1)
                }
            } else if str == "MOVEY" {
                if pt.y >= 5 {
                    pt.y = 0
                } else {
                    pt.moveY(1)
                }
            }
        case 3:
            // Commands with 2 arguments
            if tokens[0] == "PLACE" {
                fmt.Println("PLACE command not implemented")
            }
        default:
            fmt.Println("Unknown command [%s] %q", tokens[0], tokens[1:])
        }
        fmt.Printf("pt = [%v]\n", pt)
    }
}
