package main

import (
	"github.com/labstack/echo/v4"
	// "github.com/labstack/echo/v4/middleware"
)

const port string = ":8080"

func main() {
	e := echo.New()

	// Middleware
	// e.Use(middleware.Logger())
	// e.Use(middleware.Recover())

	// Routes
	e.GET("/", Base)
	e.PUT("/clicked", Clicked)

	// Start server
	err := e.Start(port)
	if err != nil {
		panic(err)
	}
}
