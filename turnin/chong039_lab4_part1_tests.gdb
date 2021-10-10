test "PINA: 0,1,0 -> PINB: 0x02"
setPINA 0x00
continue 2
setPINA 0x01
continue 2
setPINA 0x00
continue 2
expectPORTB 0x02
checkResult