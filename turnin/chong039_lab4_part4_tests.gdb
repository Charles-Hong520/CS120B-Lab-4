test "PINA: Lock, #,0,Y,0 -> PORTB: 0x00"
setPINA 0x04
continue 2
setPINA 0x00
continue 2
setPINA 0x02
continue 2
setPINA 0x00
continue 2
setPINA 0x04
continue 2
setPINA 0x00
continue 2
setPINA 0x02
continue 2
setPINA 0x00
continue 2
expectPORTB 0x00
checkResult