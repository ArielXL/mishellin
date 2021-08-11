MISHELLIN
============
**Integrantes:**
- Leonel Alejandro García López
- Ariel Plasencia Díaz

**Las funcionalidades implementadas son las siguientes:**

1. Al ejecutar el programa este debe imprimir un prompt (ejemplo "$ ")
2. Ejecutar comandos e imprimir su salida
3. Poder ejecutar el comando `cd` (y que cambie de directorio)
4. Redirigir entrada y salida estándar de comandos hacia/desde ficheros con `>`, `<`, `>>`
5. Redirigir la salida estándar de un comando hacia la entrada de otro con un pipe `|`
6. Una vez terminado el comando previo, se debe mostrar el prompt nuevamente.
7. Solamente habrá un espacio entre cada uno de los *tokens* de la entrada
  - comandos
  - parámetros
  - operadores de redirección (`>`, `|`, etc.)

8. Implementar más de una tubería (1pt adicional)
9. Permitir cualquier cantidad de espacios entre los comandos y parámetros (0.5pt adicional)
10. Implementar un historial de comandos (un comando `history`) que permita imprimir enumeradamente los últimos 50 comandos ejecutados en la consola (0.5pt adicional). Un comando no va a parar al historial si:
  - Se repite el último comando.
  - El comando empieza con espacio.
11. Implementar Re-utilización de comandos.
  - El comando history muestra la secuencia de comandos, con un número a su izquierda. Con este número es posible llamar de nuevo el comando utilizando el caracter admiración "!" (comando `![número]`). El último comando se repite con doble admiración "!!" (0.5pt adicional)
  - Ejecutar el último comando (`command`) que se ha ejecutado escribiendo `![command]` (0.5pt adicional)
  * NOTA: Por ejemplo history retorna:
    1  history
    2  ls
    3  cd /dev
    4  ls
    5  rm *.bak
    6  cd /etc
    7  history

*Esperemos les guste*