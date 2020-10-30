(***********************************)
(** List Processing functionality **)
(***********************************)

let rec reverse = fun l -> match l with
| [] -> []
| a::more -> reverse more @ [a]

let reverse_tests = ("Reverse", reverse, [
  (Some("simple list"), [1;2;3;4;5], [5;4;3;2;1]);
  (Some("empty"), [], []);
  (Some("1 item"), [77], [77]);
  (Some("repeats"), [3;3;4;4;56;56], [56;56;4;4;3;3]);
])

let rec selection_sort = fun l ->
  let rec extract_smallest = fun (x,l) -> (match l with
    | [] -> (x,[])
    | y::more ->
      let (m,l2) = extract_smallest (y,more) in
      if m < x then (m,(x::l2))
      else (x,(m::l2))
  ) in
  match l with
  | [] -> []
  | a::more -> (
    let tup = extract_smallest (a, more) in
    match tup with
    | (a,[]) -> [a]
    | (a, l) -> [a] @ (selection_sort l)
  )

let sort_tests = ("Selection Sort", selection_sort, [
  (Some("simple list sort"), [3;2;4;1;5], [1;2;3;4;5]);
  (Some("empty"), [], []);
  (Some("1 item"), [2], [2]);
  (Some("duplicates"), [1;2;1;3;5;4;3], [1;1;2;3;3;4;5]);
])

let rec map = fun (f,l) -> match l with
| [] -> []
| a::more -> (f a)::(map (f, more))


let rec fold_left = fun (f,init,l) -> match l with
| [] -> init
| a::more -> fold_left (f, f (init, a), more)

let rec fold_right = fun (f,l,init) -> match l with 
| [] -> init
| l -> ( let rev_l = reverse l in
  match rev_l with
  | a::more -> fold_right (f, reverse more, f (a, init))
)

let rec filter = fun (f,l) -> match l with 
| [] -> []
| a::more -> (
  let res = f a in
  match res with
  | true -> a::filter (f, more)
  | false -> filter (f, more)
)

let filter_tests = ("Filter", filter, [
  (Some("simple list"), ((fun x -> (x > 3)),[1;4;2;5;3;6]), [4;5;6]);
  (Some("empty list"), ((fun x -> (x > 3)),[]), []);
  (Some("no negatives"), ((fun x -> (x > 0)),[-1;4;-2;5;3;6]), [4;5;3;6]);
  (Some("all filtered"), ((fun x -> (x > 5)),[1;4;2;3]), []);
  (Some("none filtered"), ((fun x -> (x < 3)),[1;2]), [1;2]);
  (Some("duplicates"), ((fun x -> (x != 4)),[1;1;4;4;6;4;8;6]), [1;1;6;8;6]);
])