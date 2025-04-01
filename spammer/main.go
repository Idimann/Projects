package main

import (
	"fmt"
	"time"
	"unicode"
	// "runtime"
	"os"
	"bufio"
	"strconv"
	"github.com/micmonay/keybd_event"
)

var keys map[rune]int = map[rune]int {
	'a': keybd_event.VK_A,
	'b': keybd_event.VK_B,
	'c': keybd_event.VK_C,
	'd': keybd_event.VK_D,
	'e': keybd_event.VK_E,
	'f': keybd_event.VK_F,
	'g': keybd_event.VK_G,
	'h': keybd_event.VK_H,
	'i': keybd_event.VK_I,
	'j': keybd_event.VK_J,
	'k': keybd_event.VK_K,
	'l': keybd_event.VK_L,
	'm': keybd_event.VK_M,
	'n': keybd_event.VK_N,
	'o': keybd_event.VK_O,
	'p': keybd_event.VK_P,
	'q': keybd_event.VK_Q,
	'r': keybd_event.VK_R,
	's': keybd_event.VK_S,
	't': keybd_event.VK_T,
	'u': keybd_event.VK_U,
	'v': keybd_event.VK_V,
	'w': keybd_event.VK_W,
	'x': keybd_event.VK_X,
	'y': keybd_event.VK_Y,
	'z': keybd_event.VK_Z,
	'1': keybd_event.VK_1,
	'2': keybd_event.VK_2,
	'3': keybd_event.VK_3,
	'4': keybd_event.VK_4,
	'5': keybd_event.VK_5,
	'6': keybd_event.VK_6,
	'7': keybd_event.VK_7,
	'8': keybd_event.VK_8,
	'9': keybd_event.VK_9,
	'0': keybd_event.VK_0,
	'\'': keybd_event.VK_SP7,
	';': keybd_event.VK_SP6,
	',': keybd_event.VK_SP9,
	' ': keybd_event.VK_SPACE,
}

type Key struct {
	code int
	upper bool
}

func getKeys(input string) []Key {
	returning := []Key {}

	for _, c := range input {
		key, check := keys[unicode.ToLower(c)]
		if !check {
			continue
		}

		returning = append(returning, Key {
			code: key,
			upper: unicode.IsUpper(c),
		})
	}

	return returning
}

func main() {
	fmt.Println("Spammer by Idimann");

	if len(os.Args) < 4 {
		panic("Usage: ./spammer <spam num> <delay in s> <type delay in ms>!\n")
	}

	buffer := bufio.NewReader(os.Stdin)
	input, _, err := buffer.ReadLine()
	if err != nil {
		panic(err)
	}

	kb, err := keybd_event.NewKeyBonding()
	if err != nil {
		panic(err)
	}

	// For linux, nessecary to wait at least 2 seconds, for windows it's just nice
	time.Sleep(10 * time.Second)

	keys := getKeys(fmt.Sprintf("%s", input))

	num, err := strconv.Atoi(os.Args[1])
	if err != nil {
		panic(err)
	}

	num2, err := strconv.Atoi(os.Args[2])
	if err != nil {
		panic(err)
	}

	num3, err := strconv.Atoi(os.Args[3])
	if err != nil {
		panic(err)
	}

	for range num {
		for _, k := range keys {
			kb.AddKey(k.code)
			kb.HasSHIFT(k.upper)

			err = kb.Launching()
			if err != nil {
				panic(err)
			}
			kb.Clear()

			time.Sleep(time.Duration(num3) * time.Millisecond)
		}

		kb.AddKey(keybd_event.VK_ENTER)
		kb.HasSHIFT(false)
		err = kb.Launching()
		if err != nil {
			panic(err)
		}
		kb.Clear()

		time.Sleep(time.Duration(num2) * time.Second)
	}
}
