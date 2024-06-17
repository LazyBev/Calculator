package main

import (
	"fmt"
	"math"
	"strings"
)

func calc(op string, x float64, y float64) {
	switch op {
	case "+":
		fmt.Println("Result:", x + y);
	case "-":
		fmt.Println("Result:", x - y);
	case "*":
		fmt.Println("Result:", x * y);
	case "/":
		if y == 0 {
			fmt.Println("Error: Division by zero");
		} else {
			fmt.Println("Result:", x / y);
		}
	case "pow":
		fmt.Println("Result:", math.Pow(x, y));
	case "sqrt":
		fmt.Println("Result:", math.Sqrt(x));
	case "cos":
		fmt.Println("Result:", x * math.Cos(y));
	case "sin":
		fmt.Println("Result:", x * math.Sin(y));
	case "tan":
		fmt.Println("Result:", x * x * math.Tan(y));
	default:
		fmt.Println("Error: Invalid operator");
	}
}

func main() {
	var x, y float64;
	var op string;

	fmt.Print("Type an operator (+, -, *, /, pow, sqrt, sin, cos, tan): ");
	op = strings.TrimSpace(op);
	fmt.Scanf("%s", &op);
	fmt.Print("Type a number: ");
	fmt.Scan(&x);
	fmt.Print("Type another number: ");
	fmt.Scan(&y);

	calc(op, x, y);
}
