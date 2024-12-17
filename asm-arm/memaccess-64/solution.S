// Это комментарий, как в Си/С++
.text      // начало секции .text с кодом программы
.global sum  // указание о том, что метка f будет доступна извне
           // (аналог extern в языке Си)
              
sum:     
    // A - x0 B - x1 C - x2 x = x3
    mov       x3, 0
    mov       x4, 0
    LoopBegin:
        cmp    x1, x3   
        ble    LoopEnd    
        
        ldr    x5, [x2, x4]
        add    x0, x0, x5

        add    x3, x3, 1 
        add    x4, x4, 4 
        b      LoopBegin  
    LoopEnd:
        // цикл закончился
    ret
