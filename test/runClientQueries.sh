#!/usr/bin/expect -f

cd client

spawn "./ConcuClient"



for {set i 1} {$i < 5} {incr i 1} {
 expect "3) Salir"
 send "2\r"

 expect "Ingrese nombre a buscar"

 send "pepito\r"

 expect "3) Salir"
 send "1\r"

 expect "Ingrese nombre"
 send "pepito\r"
 expect "Ingrese direccion"
 send "direccion\r"
 expect "Ingrese telefono"
 send "telefono\r"
}
 

expect "3) Salir"
send "3\r"