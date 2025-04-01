package main

import (
	"github.com/labstack/echo/v4"
	"net/http"
)

func Base(c echo.Context) error {
	return c.File("index.html")
}

var todos = []string {}

func Clicked(c echo.Context) error {
	input := c.FormValue("input")
	todos = append(todos, input)

	returning := ""

	for _, s := range todos {
		returning += "<div>" + s + "</div>\n"
	}

	return c.HTML(http.StatusOK, returning)
}
