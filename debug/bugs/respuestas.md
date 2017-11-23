#1 Correr el programa con un debugger, sin agregar flags de debug. ¿Tienen toda la información que requerían?

Al correrlo sin ninguna flag obtengo 

barbara@bsidoruk ~/Desktop/HOdebug-profile/debug/bugs $ make segfault
gcc   -c add_array_segfault.c -o add_array_segfault_c.o
add_array_segfault.c: In function ‘add_array’:
add_array_segfault.c:7:12: warning: implicit declaration of function ‘abs’ [-Wimplicit-function-declaration]
     sum += abs(a[i]);
            ^
gcc  add_array_segfault_c.o -o add_array_segfault.e


No me dice absolutamente nada 

----------------------------------------------------------------------------------------------------------------
corriendo el .e

barbara@bsidoruk ~/Desktop/HOdebug-profile/debug/bugs $ gcc ./add_array_segfault.e
./add_array_segfault.e: In function `_fini':
(.fini+0x0): multiple definition of `_fini'
/usr/lib/gcc/x86_64-linux-gnu/5/../../../x86_64-linux-gnu/crti.o:(.fini+0x0): first defined here
./add_array_segfault.e: In function `data_start':
(.data+0x0): multiple definition of `__data_start'
/usr/lib/gcc/x86_64-linux-gnu/5/../../../x86_64-linux-gnu/crt1.o:(.data+0x0): first defined here
./add_array_segfault.e: In function `data_start':
(.data+0x8): multiple definition of `__dso_handle'
/usr/lib/gcc/x86_64-linux-gnu/5/crtbegin.o:(.data+0x0): first defined here
./add_array_segfault.e:(.rodata+0x0): multiple definition of `_IO_stdin_used'
/usr/lib/gcc/x86_64-linux-gnu/5/../../../x86_64-linux-gnu/crt1.o:(.rodata.cst4+0x0): first defined here
./add_array_segfault.e: In function `_start':
(.text+0x0): multiple definition of `_start'
/usr/lib/gcc/x86_64-linux-gnu/5/../../../x86_64-linux-gnu/crt1.o:(.text+0x0): first defined here
./add_array_segfault.e: In function `_init':
(.init+0x0): multiple definition of `_init'
/usr/lib/gcc/x86_64-linux-gnu/5/../../../x86_64-linux-gnu/crti.o:(.init+0x0): first defined here
/usr/lib/gcc/x86_64-linux-gnu/5/crtend.o:(.tm_clone_table+0x0): multiple definition of `__TMC_END__'
./add_array_segfault.e:(.data+0x10): first defined here
/usr/bin/ld: error in ./add_array_segfault.e(.eh_frame); no .eh_frame_hdr table will be created.
collect2: error: ld returned 1 exit status
---------------------------------------------------------------------------------------------------

y al correr el gdb

Starting program: /home/barbara/Desktop/HOdebug-profile/debug/bugs/add_array_segfault.e 

Program received signal SIGSEGV, Segmentation fault.
0x00000000004005eb in main ()

----------------------------------------------------------------------------------------------------
Si en el makefile pongo el flag -debug

barbara@bsidoruk ~/Desktop/HOdebug-profile/debug/bugs $ make segfault
gcc  -debug -c add_array_segfault.c -o add_array_segfault_c.o
cc1: warning: unrecognized gcc debugging option: e
cc1: warning: unrecognized gcc debugging option: b
cc1: warning: unrecognized gcc debugging option: u
cc1: warning: unrecognized gcc debugging option: g
add_array_segfault.c: In function ‘add_array’:
add_array_segfault.c:7:12: warning: implicit declaration of function ‘abs’ [-Wimplicit-function-declaration]
     sum += abs(a[i]);
            ^
gcc  add_array_segfault_c.o -o add_array_segfault.e


-------------------------------------------------------------------------------------------------
Si en el makefile pongo el flag -g

barbara@bsidoruk ~/Desktop/HOdebug-profile/debug/bugs $ make segfault
gcc  -g -c add_array_segfault.c -o add_array_segfault_c.o
add_array_segfault.c: In function ‘add_array’:
add_array_segfault.c:7:12: warning: implicit declaration of function ‘abs’ [-Wimplicit-function-declaration]
     sum += abs(a[i]);
            ^
gcc  add_array_segfault_c.o -o add_array_segfault.e


-------------------------------------------------------------------------------------------------
Con g3

(gdb) run
Starting program: /home/barbara/Desktop/HOdebug-profile/debug/bugs/add_array_segfault.e 

Program received signal SIGSEGV, Segmentation fault.
0x00000000004005eb in main (argc=1, argv=0x7fffffffe578)
    at add_array_segfault.c:19
19	    b[i] = i;
(gdb) Quit

OSEA QUE CUANDO HAGO EL RUN Y YA LE PONGO FLAG, YA ME DEVUELVE ALGO MAS DE INFO


------------------------------------------------------------------------------------------------------

gcc -O sirve para establecer el nivel de optimizacion

option 	optimization level 	execution time 	code size 	memory usage 	compile time
-O0 	optimization for compilation time (default) 	+ 	+ 	- 	-
-O1 or -O 	optimization for code size and execution time 	- 	- 	+ 	+
-O2 	optimization more for code size and execution time 	-- 	  	+ 	++
-O3 	optimization more for code size and execution time 	--- 	  	+ 	+++
-Os 	optimization for code size 	  	-- 	  	++
-Ofast 	O3 with fast none accurate math calculations 	--- 	  	+ 	+++

#DUDAAAA
EN clase usamos el -O0, que por lo que entendi era para que no se optimice el codigo, pero posiblemente haya entendido mal por lo que leo ahora .... 

--------------------------------------------------------------------------------------------------

Con -Wall

barbara@bsidoruk ~/Desktop/HOdebug-profile/debug/bugs $ make segfault
gcc  -Wall -c add_array_segfault.c -o add_array_segfault_c.o
add_array_segfault.c: In function ‘add_array’:
add_array_segfault.c:7:12: warning: implicit declaration of function ‘abs’ [-Wimplicit-function-declaration]
     sum += abs(a[i]);
            ^
add_array_segfault.c: In function ‘main’:
add_array_segfault.c:18:6: warning: ‘a’ may be used uninitialized in this function [-Wmaybe-uninitialized]
     a[i] = i;
      ^
add_array_segfault.c:19:6: warning: ‘b’ may be used uninitialized in this function [-Wmaybe-uninitialized]
     b[i] = i;
      ^
gcc  add_array_segfault_c.o -o add_array_segfault.e

CON WALL ME MUESTRA UN MONTON DE WARNINGS:
    EL primero lo tengo hasta con el de nobugs, no esta declarada la funcion abs, pero no es problema
    EL segundo y tercero me dice que a y b no esta inicializadas,en linea 18 y 19

Pasa que en el main le digo tengo a los punteros a y b y listo, pero ninguna info de a donde apuntan

Para eso le agrego el MALLOC
  a=(int*)malloc(n*sizeof(int));    
  b=(int*)malloc(n*sizeof(int));

--------------------------------------------------------------------------------------------------

CASO NOBUGS

add=6


CASO STATIC

Se diferencia con nobugs, por tener en add_array i<=n+1 en lugar de i<n


The addition is 6806

AL igual que no bugs me tira el warning de abs, de que no esta declarada pero no hay errores


CASO SEGFAULT

Luego de añadirle el malloc devuelve The addition is 6


CASO DYNAMIC

DEvuelve The addition is 6

Pero le cambie el n+1 por n+10 y ahora devuelve cualquier cosa, debia ser que no habia nada dsp en la memoria







