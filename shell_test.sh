
function kbd {
    xvkbd -text "$1\r"
    sleep 1
}

echo "Sleeping for 5 seconds. Go and focus the window now!!!"
sleep 5
# xvkbd -text "\A1"
# sleep 5


kbd "echo --------------------------Testing History and again-------------------"

kbd "echo testing history"
kbd "ls -l"
kbd "history"
kbd "again 2"




#1. Al ejecutar el programa este debe imprimir un prompt (ejemplo "$ ")
#2. Ejecutar comandos e imprimir su salida
#7. Solamente habrá un espacio entre cada uno de los *tokens* de la entrada
kbd "echo ---------------------------Testing commands---------------------------"
kbd "echo Hola2"
kbd "pwd"
kbd "ls"
kbd "ls -l -h -a"


#3. Poder ejecutar el comando `cd` (y que cambie de directorio)
kbd "echo ---------------------------Testing cd---------------------------"

kbd "mkdir -p test_dir"
kbd "pwd"
kbd "cd ./test_dir"
kbd "pwd"
kbd "cd .."
kbd "pwd"
kbd "rm -rf ./test_dir"
kbd "ls"


#4. Redirigir entrada y salida estandar de comandos hacia/desde ficheros con `>`, `<`, `>>`
kbd "echo ---------------------------Testing redirectors---------------------------"

kbd "> a.txt"
kbd "> a1.txt"
kbd "> a2.txt"
kbd "> a3.txt"
kbd "> abbbb.txt"
kbd "> abbbccc.txt"
kbd "> aasdasd.txt"
kbd "> arttrtrr.txt"
kbd "> asdasdasda.txt"

kbd "ls -l | grep a | grep s > a.txt"
kbd "cat a.txt"
kbd "rm -rf a.txt"
kbd "rm -rf a1.txt"
kbd "rm -rf a2.txt"
kbd "rm -rf a3.txt"
kbd "rm -rf abbbb.txt"
kbd "rm -rf abbbccc.txt"
kbd "rm -rf aasdasd.txt"
kbd "rm -rf arttrtrr.txt"
kbd "rm -rf asdasdasda.txt"

kbd "echo testing > testing.txt"
kbd "cat testing.txt"
kbd "echo testing_appended >> testing.txt"
kbd "cat testing.txt"
kbd "echo output > testing.txt"
kbd "cat < testing.txt"
kbd "rm -rf testing.txt"
kbd "ls"

#5. Redirigir la salida estandar de un comando hacia la entrada de otro con `|`
kbd "echo ---------------------------Testing pipes---------------------------"

kbd "ls -l | grep x"
kbd "echo testing | cat"

#y hasta aqui tienen 3 puntos en el proyecto
kbd "echo ---------------------------Has 3 points so far---------------------------"

#7. Implementar mas de una tubería (1pt adicional)
kbd "echo ---------------------------Testing multiple pipes---------------------------"

kbd "echo testing | cat | cat | cat"
kbd "echo hola | tee /dev/stdout | tee /dev/stdout | cat"

#9. Permitir cualquier cantidad de espacios o no entre los comandos y parametros
kbd "echo ---------------------------Testing multiple spaces---------------------------"




kbd ">    a.txt"
kbd ">         a1.txt"
kbd ">  a2.txt"
kbd ">    a3.txt"
kbd ">  abbbb.txt"
kbd "> abbbccc.txt"
kbd "> aasdasd.txt"
kbd "> arttrtrr.txt"
kbd "> asdasdasda.txt"

kbd "ls   -l     |    grep  a  |  grep s           > a.txt"
kbd "cat   a.txt"
kbd "rm -rf  a.txt"
kbd "rm -rf   a1.txt"
kbd "rm -rf  a2.txt"
kbd "rm  -rf a3.txt"
kbd "rm   -rf abbbb.txt"
kbd "rm    -rf abbbccc.txt"
kbd "rm -rf     aasdasd.txt"
kbd "rm -rf  arttrtrr.txt"
kbd "rm -rf  asdasdasda.txt"



kbd "echo    testing"
kbd "echo  Hola2"
kbd "ls  -l   -h -a"
kbd "echo hola |tee /dev/stdout |tee /dev/stdout|cat"
kbd "echo nospaces>some_file.txt"
kbd "cat some_file.txt"
kbd "rm some_file.txt"
kbd "ls"

#8. Implementar el operador `&` y tener procesos en el background (1pt adicional)
kbd "echo ---------------------------Testing ampersand---------------------------"

kbd "sleep 020 &"
kbd "ps aux | grep 07"
kbd "jobs"

kbd "echo ---------------------------Done---------------------------"

