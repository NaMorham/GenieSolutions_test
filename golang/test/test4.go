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
        } else {
            fmt.Printf("Read invalid: [%q]\n",str)
            continue
        }
        fmt.Printf("pt = [%v]\n", pt)
    }
}
