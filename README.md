# PLC Test 2

### Regular Expression: 
* Addition: +
* Subtraction: - 
* Multiplication: * 
* Division: /
* Module: %
* Less than: <
* Greater than: >
* Less than Equal To: #
* Greater than Equal To: $
* Equal To: ~
* Not Equal To: !
* Assignment: =
* (There must also be a way to break precedence, this is usually done with the use of parenthesis): ([a-zA-Z0-9_/+-*% ]*)

### Variable Names:
[a-z_A-Z] [a-z_A-Z] [a-z_ A-Z] [a-z_ A-Z] [a-z_ A-Z] [a-z_ A-Z] [a-z_ A-Z]?[a-z_ A-Z]?
### Integer Literals:
1 byte: [0-9]+_b
2 byte: s_[0-9]+_s
4 byte: i_[0-9]+_i
8 byte: [0-9]+_l


## Production Rules
* <program> --> begin <stmt_list> end
* <stmt_list> --> { <stmt> ‘\n’ }
* <stmt> --> <declare> | <cake_stmt> | <pie_loop> | <assign_stmt> 
* <declare> --> `data` `id` 
* <assign_stmt> --> `id` `=` <expr>
* <pie_loop> --> `pie` `(`<bool_expr> `)` <stmt>
* <cake_stmt> --> `cake` `(` <bool_expr> `)` <stmt> [`cookies` <stmt>] 
* <expr> --> <term> { (`+`|`*`) <term> }
* <term> --> <factor> { (`-` | `/` | `%`) <factor> }
* <factor> --> `id` | `int_lit` |  `(` <expr> `)`

* <bool_expr> --> <brel> { (`!` | `~`) <brel> } 
* <brel> --> <bexpr> { (`#` | `$` | `<` | `>`)  <bexpr> }
* <bexpr> --> <bterm> { (`+`|`*`) <bterm> }
* <bterm> --> <bfactor> { (`-` | `/` | `%`) <bfactor> }
* <bfactor> --> `id` | `int_lit` |  `(` <bexpr> `)` | `bool_lit`



