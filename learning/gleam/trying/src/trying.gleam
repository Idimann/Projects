import gleam/bool
import gleam/io
import gleam/list

fn all_match(input: List(a), func: fn(a) -> Bool) -> Bool {
  case input {
    [] -> True
    [head, ..tail] ->
      case func(head) {
        True -> all_match(tail, func)
        False -> False
      }
  }
}

fn map(input: List(a), func: fn(a) -> b) -> List(b) {
  case input {
    [] -> []
    [head, ..tail] -> list.prepend(map(tail, func), func(head))
  }
}

pub fn main() {
  let list = [1, 2, 3]
  let match = all_match(list, fn(x) { x % 2 == 0 })
  let _ = map(list, fn(x) { x * 2 })

  io.println("List matched with func: " <> bool.to_string(match))
}
