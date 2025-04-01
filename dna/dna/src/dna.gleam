import gleam/bit_array
import gleam/int
import gleam/list
import gleam/option

pub type Nucl {
  Adenin
  Cytosin
  Guanin
  Thymin
}

fn encode(n: Nucl) -> BitArray {
  case n {
    Adenin -> <<0:1, 0:1>>
    Cytosin -> <<0:1, 1:1>>
    Guanin -> <<1:1, 0:1>>
    Thymin -> <<1:1, 1:1>>
  }
}

fn decode(b: BitArray) -> option.Option(Nucl) {
  case b {
    <<0:1, 0:1>> -> option.Some(Adenin)
    <<0:1, 1:1>> -> option.Some(Cytosin)
    <<1:1, 0:1>> -> option.Some(Guanin)
    <<1:1, 1:1>> -> option.Some(Thymin)
    _ -> option.None
  }
}

type Rna =
  List(Nucl)

fn encode_rna(r: Rna) -> BitArray {
  case r {
    [] -> <<>>
    [head, ..tail] -> <<encode(head):bits, encode_rna(tail):bits>>
  }
}

fn decode_rna(b: BitArray) -> Rna {
  case b {
    <<nuc:2, rest:bits>> ->
      case decode(<<nuc:2>>) {
        option.Some(x) -> list.prepend(decode_rna(rest), x)
        option.None -> decode_rna(rest)
      }
    _ -> []
  }
}

fn prepend_random(r: Rna) -> Rna {
  case int.random(4) {
    0 -> list.prepend(r, Adenin)
    1 -> list.prepend(r, Cytosin)
    2 -> list.prepend(r, Guanin)
    3 -> list.prepend(r, Thymin)
    _ -> r
  }
}

fn gen_rna(l: Int) -> Rna {
  case l {
    0 -> []
    x -> prepend_random(gen_rna(x - 1))
  }
}

type Dna =
  List(#(Nucl, Nucl))

fn to_dna(r: Rna) -> Dna {
  case r {
    [] -> []
    [head, ..tail] -> {
      let next = to_dna(tail)
      list.prepend(
        next,
        #(head, case head {
          Adenin -> Thymin
          Cytosin -> Guanin
          Guanin -> Cytosin
          Thymin -> Adenin
        }),
      )
    }
  }
}

fn unwrap_dna(d: Dna) -> #(Rna, Rna) {
  case d {
    [] -> #([], [])
    [head, ..tail] -> {
      let unwrap = unwrap_dna(tail)
      #(list.prepend(unwrap.0, head.0), list.prepend(unwrap.1, head.1))
    }
  }
}

fn encode_dna(d: Dna) -> BitArray {
  case d {
    [] -> <<>>
    [head, ..tail] -> <<
      encode(head.0):bits,
      encode(head.1):bits,
      encode_dna(tail):bits,
    >>
  }
}

fn decode_dna(b: BitArray) -> Dna {
  case b {
    <<nuc:2, nuc2:2, rest:bits>> ->
      case decode(<<nuc:2>>), decode(<<nuc2:2>>) {
        option.Some(x), option.Some(y) ->
          list.prepend(decode_dna(rest), #(x, y))
        _, _ -> decode_dna(rest)
      }
    _ -> []
  }
}

pub fn main() {
  echo gen_rna(150_000) |> to_dna() |> encode_dna() |> bit_array.byte_size()
}
