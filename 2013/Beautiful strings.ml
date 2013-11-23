let input = open_in "input.txt" ;;
let output = open_out "output.txt" ;;

let m = int_of_string (input_line input) ;;

let is_alpha c = (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z') ;;

let get_index c = 
    if c >= 'a' && c <= 'z' then (int_of_char c) - (int_of_char 'a')
    else (int_of_char c) - (int_of_char 'A') ;;

let maximum_beauty s =
    let freq = Array.make 26 0 and beauty = Array.make 26 0
    in let rec compute_freq i =
        if i = String.length s then ()
        else if is_alpha s.[i] then let ind = get_index s.[i] in
            freq.(ind) <- freq.(ind) + 1 ;
            compute_freq (i + 1)
        else
            compute_freq (i + 1)
    in compute_freq 0 ;
    let rec assign_beauty value = 
        if value = 0 then ()
        else 
            let rec loop i c f =
                if i = Array.length beauty then c
                else if beauty.(i) = 0 && freq.(i) > f then 
                    loop (i + 1) i freq.(i)
                else loop (i + 1) c f
            in beauty.(loop 0 0 (-1)) <- value ;
            assign_beauty (value - 1)
    in assign_beauty 26 ;    
    let rec compute_total i total =
        if i = Array.length beauty then total
        else compute_total (i + 1) (total + freq.(i) * beauty.(i))
    in compute_total 0 0
in let rec loop i =
    if i > m then (close_in input ; close_out output)
    else let s = input_line input in 
        Printf.fprintf output "Case #%d: %d\n" i (maximum_beauty s) ;
        loop (i + 1)
in loop 1 ;;