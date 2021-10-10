test "PINA: 1,0,1,01 -> PORTC: 0x09"
setPINA 0x01
continue 2
setPINA 0x00
continue 2
setPINA 0x01
continue 2
setPINA 0x00
continue 2
setPINA 0x01
continue 2
expectPORTC 0x09
checkResult