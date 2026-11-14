#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Declaraciones de funciones
void nuevoRegistro();
void ingresarSistema();
void darAltaPelicula();
void verBoletosPorUsuario(); 
void administradorPrincipal();
void menuUsuario(char nickname[]);
void comprarBoletos(char nickname[]);
void hacerComentario(char nickname[]);
void verComentarios();
void calificarPelicula(char nickname[]);
void verCalificaciones();
void verPeliculasUsuario(char nickname[]);
void obtenerDimensionesSala(char *sala, int *filas, int *columnas, int *columnasPorFila);
void mostrarMapaAsientos(char *sala, char *pelicula, char *horario, int asientosOcupados[10][15]);
int verificarAsientoOcupado(char *pelicula, char *horario, char *sala, char *asiento);
int validarFormatoAsiento(char *asiento, char *sala);
void generarCodigoCompra(char *codigo, char *sala, char *pelicula, char *horario, char *nickname, char *asientos);

char adminUsuario[] = "elAdmin";
char adminContrasena[] = "3l4dm1n";

// Estructuras
typedef struct {
    char nombre[100], genero[50], sinopsis[500], horarios[200], sala[10];
    int duracionMinutos;
} Pelicula;

typedef struct {
    char nickname[30];
    char nombre[50];
} Usuario;

typedef struct {
    char nicknameUsuario[30];
    char nombrePelicula[100];
    char genero[50];
    char sala[10];
    int numBoletos;
    char asientosComprados[100];
    char codigoCompra[50];
    char horario[10];
} RegistroCompra;

typedef struct {
    char nickname[30];
    char nombrePelicula[100];
    char comentario[201];
} Comentario;

typedef struct {
    char nickname[30];
    char nombrePelicula[100];
    int calificacion;
} Calificacion;

// Función principal
int main() 
{
    int opcion;
    do {
        printf("\n========== CINEMA SYSTEM ==========\n");
        printf("1. Nuevo registro\n");
        printf("2. Ingreso al sistema\n");
        printf("3. Salir\n");
        printf("Selecciona una opcion: ");
        scanf("%d", &opcion);
        setbuf(stdin, NULL);

        switch (opcion) 
        {
            case 1:
                nuevoRegistro();
                break;
            case 2:
                ingresarSistema();
                break;
            case 3:
                printf("Saliendo del sistema...\n");
                break;
            default:
                printf("Opcion invalida.\n");
        }
    } while (opcion != 3);

    return 0;
}

// ========== FUNCIONES DE REGISTRO E INICIO DE SESIÓN ==========

// Función para crear una cuenta nueva
void nuevoRegistro()
{
    char nombreUsar[36], nombre[50], apellidoP[21], apellidoM[21], numeroCel[20], correoElec[45], contraUno[40], contraDos[40];
    int edad = 0;
    
    printf("\n========== NUEVO REGISTRO ==========\n");
    printf("Nombre completo: ");
    scanf("%s", nombre);
    printf("Apellido Paterno: ");
    scanf("%s", apellidoP);
    printf("Apellido Materno: ");
    scanf("%s", apellidoM);
    printf("Edad: ");
    scanf("%d", &edad);
    setbuf(stdin, NULL);
    printf("Nombre de usuario: ");
    scanf("%s", nombreUsar);
    
    // Verificar si el nombre es del administrador
    if (strcmp(nombreUsar, adminUsuario) == 0)
    {
        printf("Error: Este nombre de usuario esta reservado para el administrador.\n");
        printf("Por favor elige otro nombre de usuario.\n");
        return;
    }
    
    // Pedir y verificar contraseñas
    do
    {
        printf("Contrasena: ");
        scanf("%s", contraUno);
        printf("Confirmar contrasena: ");
        scanf("%s", contraDos);
        if (strcmp(contraUno, contraDos) != 0)
        {
            printf("Las contrasenas no coinciden.\n");
        }
    } while (strcmp(contraUno, contraDos) != 0);

    printf("Contrasena guardada.\n");
    printf("Correo electronico: ");
    scanf("%s", correoElec);
    printf("Numero de celular: ");
    scanf("%s", numeroCel);

    // Guardar en archivo
    FILE *archivo = fopen("usuarios.txt", "a");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo de usuarios\n");
        return;
    }

    fprintf(archivo, "%s|%s|%s|%d|%s|%s|%s|%s\n",
            nombre, apellidoP, apellidoM, edad,
            nombreUsar, contraUno, correoElec, numeroCel);

    fclose(archivo);
    printf("\nTe has registrado correctamente\n");
}

// Función para iniciar sesión
void ingresarSistema()
{
    char usuarioIngresar[36], contrasenaIngresar[40];
    char nombre[50], apellidoP[21], apellidoM[21], usuarioArchivo[36], contraArchivo[40], correoElec[45], numeroCel[20];
    int edad, encontrado = 0;
    
    printf("\n========== INGRESO AL SISTEMA ==========\n");
    printf("Nombre de usuario: ");
    scanf("%s", usuarioIngresar);
    printf("Contrasena: ");
    scanf("%s", contrasenaIngresar);
    
    // Verificar si es administrador
    if (strcmp(usuarioIngresar, adminUsuario) == 0 && strcmp(contrasenaIngresar, adminContrasena) == 0)
    {
        printf("\nAcceso concedido como Administrador\n");
        administradorPrincipal();
        return;
    } 

    // Verificar usuario normal
    FILE *archivo = fopen("usuarios.txt", "r");
    if (archivo == NULL)
    {
        printf("No se pudo abrir el archivo de usuarios.\n");
        return;
    }

    while (fscanf(archivo, "%[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%[^|]|%[^\n]\n", 
                  nombre, apellidoP, apellidoM, &edad,
                  usuarioArchivo, contraArchivo,
                  correoElec, numeroCel) != EOF)
    {
        if (strcmp(usuarioIngresar, usuarioArchivo) == 0)
        {
           encontrado = 1;

           if (strcmp(contrasenaIngresar, contraArchivo) == 0)
            {
                printf("\nBienvenido %s %s!\n", nombre, apellidoP);
                printf("Has ingresado correctamente.\n");
                menuUsuario(usuarioIngresar);
            }
           else
            {
                printf("Contrasena incorrecta.\n");
            }
            break;
        }
    }

    fclose(archivo);
    if (!encontrado)
    {
        printf("El usuario no existe.\n");
    }
}

// ========== FUNCIONES DE ADMINISTRADOR ==========

// Menú principal del administrador
void administradorPrincipal(){
    int opcion=0;
    do{
        printf("\n========== MENU ADMINISTRADOR ==========\n");
        printf("1. Dar de alta una pelicula\n");
        printf("2. Ver las peliculas para las que un usuario ha comprado boletos\n");
        printf("3. Salir de sesion\n");
        printf("Selecciona una opcion: ");
        scanf("%i",&opcion);
        setbuf(stdin, NULL);

        switch (opcion) 
        {
            case 1:
                darAltaPelicula();
                break;
            case 2:
                verBoletosPorUsuario();
                break;
            case 3:
                printf("Cerrando sesion...\n");
                break;
            default:
                printf("Opcion no valida. Intente de nuevo.\n");
        }
    } while (opcion!=3);
}

// 6.1 Dar de alta una película
void darAltaPelicula()
{
    Pelicula nuevaPelicula;

    printf("\n========== DAR DE ALTA PELICULA ==========\n");
    
    printf("Nombre de la pelicula: ");
    setbuf(stdin, NULL);
    fgets(nuevaPelicula.nombre, 100, stdin);
    nuevaPelicula.nombre[strcspn(nuevaPelicula.nombre, "\n")] = 0;

    printf("Genero de la pelicula: ");
    fgets(nuevaPelicula.genero, 50, stdin);
    nuevaPelicula.genero[strcspn(nuevaPelicula.genero, "\n")] = 0;

    printf("Sinopsis de la pelicula: ");
    fgets(nuevaPelicula.sinopsis, 500, stdin);
    nuevaPelicula.sinopsis[strcspn(nuevaPelicula.sinopsis, "\n")] = 0;

    printf("Duracion de la pelicula (en minutos): ");
    scanf("%d", &nuevaPelicula.duracionMinutos);
    setbuf(stdin, NULL);

    printf("Horas de proyeccion separadas por espacios (ej: 17:00 18:45 20:00): ");
    fgets(nuevaPelicula.horarios, 200, stdin);
    nuevaPelicula.horarios[strcspn(nuevaPelicula.horarios, "\n")] = 0;

    // Seleccionar sala
    do {
        printf("Sala en que se exhibira (A, B o VIP): ");
        char salaInput[10];
        scanf("%s", salaInput);

        if (strcmp(salaInput, "A") == 0) {
            strcpy(nuevaPelicula.sala, "Sala A");
        } else if (strcmp(salaInput, "B") == 0) {
            strcpy(nuevaPelicula.sala, "Sala B");
        } else if (strcmp(salaInput, "VIP") == 0) {
            strcpy(nuevaPelicula.sala, "Sala VIP");
        } else {
            printf("Sala no valida. Intente de nuevo.\n");
            continue;
        }
        break;
    } while (1);

    // Guardar película en archivo
    FILE *archivoPeliculas = fopen("peliculas.txt", "a");
    if (archivoPeliculas == NULL) {
        printf("Error: No se pudo abrir o crear el archivo de peliculas.\n");
    } else {
        fprintf(archivoPeliculas, "%s|%s|%s|%d|%s|%s\n",
                nuevaPelicula.nombre,
                nuevaPelicula.genero,
                nuevaPelicula.sinopsis,
                nuevaPelicula.duracionMinutos,
                nuevaPelicula.horarios,
                nuevaPelicula.sala);
        fclose(archivoPeliculas);

        printf("\nPelicula '%s' dada de alta exitosamente.\n", nuevaPelicula.nombre);
    }
}

// 6.2 Ver boletos comprados por usuario
void verBoletosPorUsuario() {
    FILE *archivoUsuarios, *archivoCompras;
    char linea[512];
    Usuario usuarios[100];
    int totalUsuarios = 0;
    int seleccion = -1;

    printf("\n========== VER BOLETOS COMPRADOS POR USUARIO ==========\n");

    // Leer usuarios
    archivoUsuarios = fopen("usuarios.txt", "r");
    if (archivoUsuarios == NULL) {
        printf("ADVERTENCIA: No se pudo abrir el archivo de usuarios.\n");
        return;
    }

    printf("Lista de Nicknames de usuarios registrados:\n");
    int i = 1;
    while (fgets(linea, sizeof(linea), archivoUsuarios) != NULL && totalUsuarios < 100) {
        char nombre[50], apellidoP[21], apellidoM[21], usuario[36], contrasena[40], correo[45], celular[20];
        int edad;
        
        if (sscanf(linea, "%[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%[^|]|%[^\n]", 
                   nombre, apellidoP, apellidoM, &edad, usuario, contrasena, correo, celular) == 8) {
            strcpy(usuarios[totalUsuarios].nickname, usuario);
            strcpy(usuarios[totalUsuarios].nombre, nombre);
            printf("%d. %s\n", i++, usuarios[totalUsuarios].nickname);
            totalUsuarios++;
        }
    }
    fclose(archivoUsuarios);

    if (totalUsuarios == 0) {
        printf("No hay usuarios registrados en el sistema.\n");
        return;
    }

    // Seleccionar usuario
    printf("\nIngrese el numero del usuario a revisar (o 0 para volver): ");
    if (scanf("%d", &seleccion) != 1 || seleccion < 0 || seleccion > totalUsuarios) {
        printf("Seleccion no valida.\n");
        setbuf(stdin, NULL);
        return;
    }

    if (seleccion == 0) {
        return; 
    }
    
    const char *nicknameSeleccionado = usuarios[seleccion - 1].nickname;
    const char *nombreSeleccionado = usuarios[seleccion - 1].nombre;

    // Mostrar información del usuario
    printf("\n--- Detalle de Compras para el Usuario: %s ---\n", nicknameSeleccionado);
    printf("Nombre: %s\n", nombreSeleccionado);
   
    // Buscar compras del usuario
    archivoCompras = fopen("compras.txt", "r");
    if (archivoCompras == NULL) {
        printf("ADVERTENCIA: No hay registros de boletos comprados.\n");
        return;
    }

    int comprasEncontradas = 0;
    RegistroCompra compra;
    printf("\n");

    while (fgets(linea, sizeof(linea), archivoCompras) != NULL) {
        if (sscanf(linea, "%[^|]|%[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%[^\n]", 
                   compra.nicknameUsuario, 
                   compra.nombrePelicula, 
                   compra.genero, 
                   compra.sala, 
                   &compra.numBoletos, 
                   compra.asientosComprados, 
                   compra.codigoCompra, 
                   compra.horario) == 8) {
            if (strcmp(compra.nicknameUsuario, nicknameSeleccionado) == 0) {
                comprasEncontradas++;
                printf("--------------------------------------\n");
                printf("  Pelicula: %s\n", compra.nombrePelicula);
                printf("  Genero: %s\n", compra.genero);
                printf("  Sala: %s\n", compra.sala);
                printf("  Horario: %s\n", compra.horario);
                printf("  Numero de boletos: %d\n", compra.numBoletos);
                printf("  Asientos: %s\n", compra.asientosComprados);
                printf("  Codigo de Compra: %s\n", compra.codigoCompra);
            }
        }
    }
    fclose(archivoCompras);

    if (comprasEncontradas == 0) {
        printf("\nEl usuario %s no ha comprado boletos para ninguna pelicula.\n", nicknameSeleccionado);
    } else {
        printf("--------------------------------------\n");
        printf("Total de compras: %d\n", comprasEncontradas);
    }

    printf("\nPresione Enter para continuar...");
    setbuf(stdin, NULL);
    getchar();
}

// ========== FUNCIONES AUXILIARES PARA COMPRA DE BOLETOS ==========

// Función para obtener dimensiones de sala
void obtenerDimensionesSala(char *sala, int *filas, int *columnas, int *columnasPorFila) {
    if (strcmp(sala, "Sala A") == 0) {
        *filas = 10; // A-J
        *columnas = 10;
        for (int i = 0; i < 10; i++) columnasPorFila[i] = 10;
    } 
    else if (strcmp(sala, "Sala B") == 0) {
        *filas = 10; // A-J
        *columnas = 10;
        for (int i = 0; i < 4; i++) columnasPorFila[i] = 7; // A-D
        for (int i = 4; i < 10; i++) columnasPorFila[i] = 10; // E-J
    }
    else if (strcmp(sala, "Sala VIP") == 0) {
        *filas = 6; // A-F
        *columnas = 6;
        for (int i = 0; i < 6; i++) columnasPorFila[i] = 6;
    }
}

// Función para mostrar mapa de asientos
void mostrarMapaAsientos(char *sala, char *pelicula, char *horario, int asientosOcupados[10][15]) {
    int filas, columnas, columnasPorFila[10];
    obtenerDimensionesSala(sala, &filas, &columnas, columnasPorFila);
    
    printf("\n========== MAPA DE ASIENTOS ==========\n");
    printf("Pelicula: %s\n", pelicula);
    printf("Sala: %s\n", sala);
    printf("Horario: %s\n", horario);
    printf("\n");
    
    // Mostrar pantalla
    printf("          [ P A N T A L L A ]\n");
    printf("----------------------------------------\n\n");
    
    // Mostrar números de columnas
    printf("     ");
    int maxColumnas = 0;
    for (int i = 0; i < filas; i++) {
        if (columnasPorFila[i] > maxColumnas) maxColumnas = columnasPorFila[i];
    }
    
    for (int j = 1; j <= maxColumnas; j++) {
        printf("%2d ", j);
    }
    printf("\n");
    
    // Mostrar asientos
    for (int i = 0; i < filas; i++) {
        printf("%c    ", 'A' + i);
        for (int j = 0; j < columnasPorFila[i]; j++) {
            if (asientosOcupados[i][j] == 1) {
                printf("[X]");
            } else {
                printf("[ ]");
            }
        }
        printf("\n");
    }
    
    printf("\nLeyenda: [ ] Disponible  [X] Ocupado\n");
}

// Función para verificar si un asiento está ocupado
int verificarAsientoOcupado(char *pelicula, char *horario, char *sala, char *asiento) {
    FILE *archivo = fopen("compras.txt", "r");
    if (archivo == NULL) return 0;
    
    char linea[500];
    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        char compraPelicula[100], compraHorario[10], compraSala[10], compraAsientos[200];
        sscanf(linea, "%[^|]|%[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%[^\n]", 
               compraPelicula, compraSala, compraAsientos, compraHorario);
        
        if (strcmp(compraPelicula, pelicula) == 0 && 
            strcmp(compraSala, sala) == 0 && 
            strcmp(compraHorario, horario) == 0) {
            
            // Verificar si el asiento está en la lista
            char asientosCopia[200];
            strcpy(asientosCopia, compraAsientos);
            char *token = strtok(asientosCopia, " ");
            while (token != NULL) {
                if (strcmp(token, asiento) == 0) {
                    fclose(archivo);
                    return 1; // Asiento ocupado
                }
                token = strtok(NULL, " ");
            }
        }
    }
    
    fclose(archivo);
    return 0; // Asiento disponible
}

// Función para validar formato de asiento
int validarFormatoAsiento(char *asiento, char *sala) {
    if (strlen(asiento) < 2) return 0;
    
    char fila = asiento[0];
    int numero = atoi(asiento + 1);
    
    // Validar fila según sala
    if (strcmp(sala, "Sala A") == 0) {
        if (fila < 'A' || fila > 'J') return 0;
        if (numero < 1 || numero > 10) return 0;
    }
    else if (strcmp(sala, "Sala B") == 0) {
        if (fila < 'A' || fila > 'J') return 0;
        if (fila <= 'D') { // A-D
            if (numero < 1 || numero > 7) return 0;
        } else { // E-J
            if (numero < 1 || numero > 10) return 0;
        }
    }
    else if (strcmp(sala, "Sala VIP") == 0) {
        if (fila < 'A' || fila > 'F') return 0;
        if (numero < 1 || numero > 6) return 0;
    }
    
    return 1;
}

// Función para generar código de compra
void generarCodigoCompra(char *codigo, char *sala, char *pelicula, char *horario, char *nickname, char *asientos) {
    char salaLetra;
    if (strcmp(sala, "Sala A") == 0) salaLetra = 'A';
    else if (strcmp(sala, "Sala B") == 0) salaLetra = 'B';
    else salaLetra = 'V'; // VIP
    
    // Extraer primeras 3 letras del nombre de la película
    char primerasTresPelicula[4] = "";
    strncpy(primerasTresPelicula, pelicula, 3);
    primerasTresPelicula[3] = '\0';
    
    // Extraer hora y minuto del horario
    char hora[3], minuto[3];
    strncpy(hora, horario, 2);
    hora[2] = '\0';
    strncpy(minuto, horario + 3, 2);
    minuto[2] = '\0';
    
    // Extraer primeras 3 letras del nickname
    char primerasTresNick[4] = "";
    strncpy(primerasTresNick, nickname, 3);
    primerasTresNick[3] = '\0';
    
    // Construir código base
    sprintf(codigo, "%c%s%s%s%s", salaLetra, primerasTresPelicula, hora, minuto, primerasTresNick);
    
    // Agregar asientos (sin espacios)
    char asientosCopia[200];
    strcpy(asientosCopia, asientos);
    char *token = strtok(asientosCopia, " ");
    while (token != NULL) {
        strcat(codigo, token);
        token = strtok(NULL, " ");
    }
}

// ========== FUNCIONES DE USUARIO NORMAL ==========

// Menú principal del usuario
void menuUsuario(char nickname[]) 
{
    int opcion;
    do {
        printf("\n========== MENU USUARIO ==========\n");
        printf("1. Comprar boletos\n");
        printf("2. Hacer comentario de pelicula\n");
        printf("3. Ver comentarios de peliculas\n");
        printf("4. Calificar pelicula\n");
        printf("5. Ver calificaciones\n");
        printf("6. Ver mis peliculas\n");
        printf("7. Salir de sesion\n");
        printf("Selecciona una opcion: ");
        scanf("%d", &opcion);
        setbuf(stdin, NULL);

        switch (opcion) 
        {
            case 1:
                comprarBoletos(nickname);
                break;
            case 2:
                hacerComentario(nickname);
                break;
            case 3:
                verComentarios();
                break;
            case 4:
                calificarPelicula(nickname);
                break;
            case 5:
                verCalificaciones();
                break;
            case 6:
                verPeliculasUsuario(nickname);
                break;
            case 7:
                printf("Cerrando sesion...\n");
                break;
            default:
                printf("Opcion invalida.\n");
        }
    } while (opcion != 7);
}

// 7.1 Compra de boletos
void comprarBoletos(char nickname[]) {
    printf("\n========== COMPRA DE BOLETOS ==========\n");
    
    // Leer películas disponibles
    FILE *archivoPeliculas = fopen("peliculas.txt", "r");
    if (archivoPeliculas == NULL) {
        printf("No hay películas disponibles. Contacta al administrador.\n");
        printf("Presiona Enter para continuar...");
        setbuf(stdin, NULL);
        getchar();
        return;
    }
    
    Pelicula peliculas[50];
    int numPeliculas = 0;
    char linea[1000];
    
    // Leer todas las películas
    while (fgets(linea, sizeof(linea), archivoPeliculas) != NULL && numPeliculas < 50) {
        sscanf(linea, "%[^|]|%[^|]|%[^|]|%d|%[^|]|%[^\n]", 
               peliculas[numPeliculas].nombre,
               peliculas[numPeliculas].genero,
               peliculas[numPeliculas].sinopsis,
               &peliculas[numPeliculas].duracionMinutos,
               peliculas[numPeliculas].horarios,
               peliculas[numPeliculas].sala);
        numPeliculas++;
    }
    fclose(archivoPeliculas);
    
    if (numPeliculas == 0) {
        printf("No hay películas disponibles. Contacta al administrador.\n");
        printf("Presiona Enter para continuar...");
        setbuf(stdin, NULL);
        getchar();
        return;
    }
    
    // Mostrar películas disponibles
    printf("\nPELÍCULAS DISPONIBLES:\n");
    printf("=======================\n");
    for (int i = 0; i < numPeliculas; i++) {
        printf("%d. %s\n", i + 1, peliculas[i].nombre);
        printf("   Género: %s\n", peliculas[i].genero);
        printf("   Duración: %d minutos\n", peliculas[i].duracionMinutos);
        printf("   Sala: %s\n", peliculas[i].sala);
        printf("   Sinopsis: %s\n", peliculas[i].sinopsis);
        printf("\n");
    }
    
    // Seleccionar película
    int opcionPelicula;
    do {
        printf("Selecciona el número de la película (1-%d, 0 para cancelar): ", numPeliculas);
        scanf("%d", &opcionPelicula);
        setbuf(stdin, NULL);
        
        if (opcionPelicula == 0) {
            printf("Compra cancelada.\n");
            return;
        }
        
        if (opcionPelicula < 1 || opcionPelicula > numPeliculas) {
            printf("Opción inválida. Intenta de nuevo.\n");
        }
    } while (opcionPelicula < 1 || opcionPelicula > numPeliculas);
    
    Pelicula peliculaSeleccionada = peliculas[opcionPelicula - 1];
    
    // Mostrar horarios disponibles
    printf("\nHORARIOS DISPONIBLES para '%s':\n", peliculaSeleccionada.nombre);
    
    char horariosCopia[200];
    strcpy(horariosCopia, peliculaSeleccionada.horarios);
    
    char *horarioToken = strtok(horariosCopia, " ");
    char horariosDisponibles[10][10];
    int numHorarios = 0;
    
    printf("Horarios: ");
    while (horarioToken != NULL && numHorarios < 10) {
        strcpy(horariosDisponibles[numHorarios], horarioToken);
        printf("%s ", horarioToken);
        numHorarios++;
        horarioToken = strtok(NULL, " ");
    }
    printf("\n");
    
    // Seleccionar horario
    char horarioSeleccionado[10];
    int horarioValido = 0;
    
    do {
        printf("\nIngresa el horario que deseas (ej: 17:00, 0 para cancelar): ");
        scanf("%s", horarioSeleccionado);
        setbuf(stdin, NULL);
        
        if (strcmp(horarioSeleccionado, "0") == 0) {
            printf("Compra cancelada.\n");
            return;
        }
        
        // Verificar si el horario está disponible
        for (int i = 0; i < numHorarios; i++) {
            if (strcmp(horarioSeleccionado, horariosDisponibles[i]) == 0) {
                horarioValido = 1;
                break;
            }
        }
        
        if (!horarioValido) {
            printf("Horario no disponible. Horarios disponibles: ");
            for (int i = 0; i < numHorarios; i++) {
                printf("%s ", horariosDisponibles[i]);
            }
            printf("\n");
        }
    } while (!horarioValido);
    
    // Cargar asientos ocupados
    int asientosOcupados[10][15] = {0}; // Matriz de asientos ocupados
    
    FILE *archivoCompras = fopen("compras.txt", "r");
    if (archivoCompras != NULL) {
        char lineaCompra[500];
        while (fgets(lineaCompra, sizeof(lineaCompra), archivoCompras) != NULL) {
            char compraPelicula[100], compraHorario[10], compraSala[10], compraAsientos[200];
            sscanf(lineaCompra, "%[^|]|%[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%[^\n]", 
                   compraPelicula, compraSala, compraAsientos, compraHorario);
            
            if (strcmp(compraPelicula, peliculaSeleccionada.nombre) == 0 && 
                strcmp(compraSala, peliculaSeleccionada.sala) == 0 && 
                strcmp(compraHorario, horarioSeleccionado) == 0) {
                
                // Marcar asientos como ocupados
                char asientosCopia[200];
                strcpy(asientosCopia, compraAsientos);
                char *asientoToken = strtok(asientosCopia, " ");
                
                while (asientoToken != NULL) {
                    // Convertir asiento a coordenadas
                    char fila = asientoToken[0];
                    int columna = atoi(asientoToken + 1) - 1;
                    int filaIndex = fila - 'A';
                    
                    if (filaIndex >= 0 && filaIndex < 10 && columna >= 0 && columna < 15) {
                        asientosOcupados[filaIndex][columna] = 1;
                    }
                    
                    asientoToken = strtok(NULL, " ");
                }
            }
        }
        fclose(archivoCompras);
    }
    
    // Mostrar mapa de asientos
    mostrarMapaAsientos(peliculaSeleccionada.sala, 
                       peliculaSeleccionada.nombre, 
                       horarioSeleccionado, 
                       asientosOcupados);
    
    // Seleccionar asientos
    printf("\nINSTRUCCIONES:\n");
    printf("- Escribe los asientos que deseas comprar separados por espacios\n");
    printf("- Formato: LetraFila + Número (ej: A1 B2 C3)\n");
    printf("- Escribe '0' para cancelar\n\n");
    
    char asientosInput[200];
    int asientosValidos = 0;
    char asientosSeleccionados[20][10];
    int numAsientos = 0;
    
    do {
        printf("Asientos a comprar: ");
        setbuf(stdin, NULL);
        fgets(asientosInput, sizeof(asientosInput), stdin);
        asientosInput[strcspn(asientosInput, "\n")] = 0;
        
        if (strcmp(asientosInput, "0") == 0) {
            printf("Compra cancelada.\n");
            return;
        }
        
        // Validar y procesar asientos
        numAsientos = 0;
        asientosValidos = 1;
        
        char asientosCopia[200];
        strcpy(asientosCopia, asientosInput);
        char *token = strtok(asientosCopia, " ");
        
        while (token != NULL && numAsientos < 20) {
            strcpy(asientosSeleccionados[numAsientos], token);
            
            // Validar formato
            if (!validarFormatoAsiento(token, peliculaSeleccionada.sala)) {
                printf("Error: Asiento '%s' tiene formato inválido.\n", token);
                asientosValidos = 0;
                break;
            }
            
            // Verificar si está ocupado
            if (verificarAsientoOcupado(peliculaSeleccionada.nombre, 
                                       horarioSeleccionado, 
                                       peliculaSeleccionada.sala, 
                                       token)) {
                printf("Error: Asiento '%s' ya está ocupado.\n", token);
                asientosValidos = 0;
                break;
            }
            
            numAsientos++;
            token = strtok(NULL, " ");
        }
        
        if (numAsientos == 0) {
            printf("Error: No se especificaron asientos.\n");
            asientosValidos = 0;
        }
        
        if (!asientosValidos) {
            printf("Por favor, ingresa los asientos nuevamente.\n");
        }
        
    } while (!asientosValidos);
    
    // Solicitar número de tarjeta
    char numeroTarjeta[20];
    printf("\nIngresa el número de tarjeta para la compra: ");
    scanf("%s", numeroTarjeta);
    
    // Generar código de compra
    char codigoCompra[100];
    generarCodigoCompra(codigoCompra, 
                       peliculaSeleccionada.sala,
                       peliculaSeleccionada.nombre,
                       horarioSeleccionado,
                       nickname,
                       asientosInput);
    
    // Mostrar confirmación
    printf("\n========== CONFIRMACIÓN DE COMPRA ==========\n");
    printf("Película: %s\n", peliculaSeleccionada.nombre);
    printf("Género: %s\n", peliculaSeleccionada.genero);
    printf("Sala: %s\n", peliculaSeleccionada.sala);
    printf("Horario: %s\n", horarioSeleccionado);
    printf("Asientos: %s\n", asientosInput);
    printf("Número de boletos: %d\n", numAsientos);
    printf("Código de compra: %s\n", codigoCompra);
    printf("===========================================\n");
    
    // Guardar la compra en archivo
    FILE *archivoNuevaCompra = fopen("compras.txt", "a");
    if (archivoNuevaCompra != NULL) {
        fprintf(archivoNuevaCompra, "%s|%s|%s|%s|%d|%s|%s|%s\n",
                nickname,
                peliculaSeleccionada.nombre,
                peliculaSeleccionada.genero,
                peliculaSeleccionada.sala,
                numAsientos,
                asientosInput,
                codigoCompra,
                horarioSeleccionado);
        fclose(archivoNuevaCompra);
        
        printf("\n¡Compra realizada exitosamente!\n");
        printf("Los boletos han sido reservados a tu nombre.\n");
    } else {
        printf("\nError: No se pudo guardar la compra.\n");
    }
    
    printf("\nPresiona Enter para continuar...");
    setbuf(stdin, NULL);
    getchar();
}

// 7.2 Hacer comentario
void hacerComentario(char nickname[]) 
{
    printf("\n========== HACER COMENTARIO ==========\n");
    
    // Verificar si el usuario ha comprado boletos
    FILE *archivoCompras = fopen("compras.txt", "r");
    if (archivoCompras == NULL) {
        printf("No has comprado boletos para ninguna pelicula.\n");
        printf("Presiona Enter para continuar...");
        setbuf(stdin, NULL);
        getchar();
        return;
    }
    
    char peliculasCompradas[50][100];
    int numPeliculas = 0;
    char linea[1000];
    
    while (fgets(linea, sizeof(linea), archivoCompras) != NULL) {
        char nickArchivo[30], nombrePelicula[100];
        sscanf(linea, "%[^|]|%[^|]", nickArchivo, nombrePelicula);
        
        if (strcmp(nickArchivo, nickname) == 0) {
            // Verificar si ya está en la lista
            int encontrada = 0;
            for (int i = 0; i < numPeliculas; i++) {
                if (strcmp(peliculasCompradas[i], nombrePelicula) == 0) {
                    encontrada = 1;
                    break;
                }
            }
            
            if (!encontrada) {
                strcpy(peliculasCompradas[numPeliculas], nombrePelicula);
                numPeliculas++;
            }
        }
    }
    fclose(archivoCompras);
    
    if (numPeliculas == 0) {
        printf("No has comprado boletos para ninguna pelicula.\n");
        printf("Presiona Enter para continuar...");
        setbuf(stdin, NULL);
        getchar();
        return;
    }
    
    // Mostrar películas para las que ha comprado boletos
    printf("Peliculas para las que has comprado boletos:\n");
    for (int i = 0; i < numPeliculas; i++) {
        printf("%d. %s\n", i + 1, peliculasCompradas[i]);
    }
    
    int opcion;
    printf("\nSelecciona el numero de la pelicula (0 para cancelar): ");
    scanf("%d", &opcion);
    setbuf(stdin, NULL);
    
    if (opcion == 0) return;
    if (opcion < 1 || opcion > numPeliculas) {
        printf("Opcion invalida.\n");
        return;
    }
    
    char peliculaSeleccionada[100];
    strcpy(peliculaSeleccionada, peliculasCompradas[opcion - 1]);
    
    // Solicitar comentario
    printf("\nEscribe tu comentario (max 200 caracteres):\n");
    char comentario[201];
    setbuf(stdin, NULL);
    fgets(comentario, sizeof(comentario), stdin);
    comentario[strcspn(comentario, "\n")] = 0;
    
    // Validar longitud
    if (strlen(comentario) > 200) {
        printf("Error: El comentario excede los 200 caracteres.\n");
        printf("Presiona Enter para continuar...");
        setbuf(stdin, NULL);
        getchar();
        return;
    }
    
    // Guardar comentario
    FILE *archivoComentarios = fopen("comentarios.txt", "a");
    if (archivoComentarios != NULL) {
        fprintf(archivoComentarios, "%s|%s|%s\n", nickname, peliculaSeleccionada, comentario);
        fclose(archivoComentarios);
        printf("\nComentario guardado exitosamente!\n");
    }
    else {
        printf("Error al guardar el comentario.\n");
    }
    
    printf("\nPresiona Enter para continuar...");
    setbuf(stdin, NULL);
    getchar();
}

// 7.3 Ver comentarios
void verComentarios()
{
    printf("\n========== VER COMENTARIOS ==========\n");
    
    // Leer películas disponibles
    FILE *archivoPeliculas = fopen("peliculas.txt", "r");
    if (archivoPeliculas == NULL) {
        printf("No hay peliculas disponibles.\n");
        printf("Presiona Enter para continuar...");
        setbuf(stdin, NULL);
        getchar();
        return;
    }
    
    Pelicula peliculas[50];
    int contador = 0;
    char linea[1000];
    
    while (fgets(linea, sizeof(linea), archivoPeliculas) != NULL && contador < 50) {
        sscanf(linea, "%[^|]|%[^|]|%[^|]|%d|%[^|]|%[^\n]", 
               peliculas[contador].nombre,
               peliculas[contador].genero,
               peliculas[contador].sinopsis,
               &peliculas[contador].duracionMinutos,
               peliculas[contador].horarios,
               peliculas[contador].sala);
        contador++;
    }
    fclose(archivoPeliculas);
    
    if (contador == 0) {
        printf("No hay peliculas disponibles.\n");
        printf("Presiona Enter para continuar...");
        setbuf(stdin, NULL);
        getchar();
        return;
    }
    
    // Mostrar películas
    printf("Peliculas en cartelera:\n");
    for (int i = 0; i < contador; i++) {
        printf("%d. %s\n", i + 1, peliculas[i].nombre);
    }
    
    int opcion;
    printf("\nSelecciona el numero de la pelicula (0 para cancelar): ");
    scanf("%d", &opcion);
    setbuf(stdin, NULL);
    
    if (opcion == 0) return;
    if (opcion < 1 || opcion > contador) {
        printf("Opcion invalida.\n");
        return;
    }
    
    char peliculaSeleccionada[100];
    strcpy(peliculaSeleccionada, peliculas[opcion - 1].nombre);
    
    // Buscar comentarios para esta película
    printf("\n========== COMENTARIOS PARA: %s ==========\n", peliculaSeleccionada);
    
    FILE *archivoComentarios = fopen("comentarios.txt", "r");
    if (archivoComentarios == NULL) {
        printf("No hay comentarios para esta pelicula.\n");
        printf("Presiona Enter para continuar...");
        setbuf(stdin, NULL);
        getchar();
        return;
    }
    
    int encontrados = 0;
    char lineaComentario[500];
    
    while (fgets(lineaComentario, sizeof(lineaComentario), archivoComentarios) != NULL) {
        char nick[30], pelicula[100], comentario[201];
        if (sscanf(lineaComentario, "%[^|]|%[^|]|%[^\n]", nick, pelicula, comentario) == 3) {
            if (strcmp(pelicula, peliculaSeleccionada) == 0) {
                encontrados++;
                printf("\n%d. Usuario: %s\n", encontrados, nick);
                printf("   Comentario: %s\n", comentario);
                printf("   ----------------------------------\n");
            }
        }
    }
    fclose(archivoComentarios);
    
    if (encontrados == 0) {
        printf("No hay comentarios para esta pelicula.\n");
    }
    
    printf("\nPresiona Enter para continuar...");
    setbuf(stdin, NULL);
    getchar();
}

// 7.4 Calificar película
void calificarPelicula(char nickname[])
{
    printf("\n========== CALIFICAR PELICULA ==========\n");
    
    // Verificar si el usuario ha comprado boletos
    FILE *archivoCompras = fopen("compras.txt", "r");
    if (archivoCompras == NULL) {
        printf("No has comprado boletos para ninguna pelicula.\n");
        printf("Presiona Enter para continuar...");
        setbuf(stdin, NULL);
        getchar();
        return;
    }
    
    char peliculasCompradas[50][100];
    int numPeliculas = 0;
    char linea[1000];
    
    while (fgets(linea, sizeof(linea), archivoCompras) != NULL) {
        char nickArchivo[30], nombrePelicula[100];
        sscanf(linea, "%[^|]|%[^|]", nickArchivo, nombrePelicula);
        
        if (strcmp(nickArchivo, nickname) == 0) {
            int encontrada = 0;
            for (int i = 0; i < numPeliculas; i++) {
                if (strcmp(peliculasCompradas[i], nombrePelicula) == 0) {
                    encontrada = 1;
                    break;
                }
            }
            
            if (!encontrada) {
                strcpy(peliculasCompradas[numPeliculas], nombrePelicula);
                numPeliculas++;
            }
        }
    }
    fclose(archivoCompras);
    
    if (numPeliculas == 0) {
        printf("No has comprado boletos para ninguna pelicula.\n");
        printf("Presiona Enter para continuar...");
        setbuf(stdin, NULL);
        getchar();
        return;
    }
    
    // Mostrar películas para las que ha comprado boletos
    printf("Peliculas para las que has comprado boletos:\n");
    for (int i = 0; i < numPeliculas; i++) {
        printf("%d. %s\n", i + 1, peliculasCompradas[i]);
    }
    
    int opcion;
    printf("\nSelecciona el numero de la pelicula (0 para cancelar): ");
    scanf("%d", &opcion);
    setbuf(stdin, NULL);
    
    if (opcion == 0) return;
    if (opcion < 1 || opcion > numPeliculas) {
        printf("Opcion invalida.\n");
        return;
    }
    
    char peliculaSeleccionada[100];
    strcpy(peliculaSeleccionada, peliculasCompradas[opcion - 1]);
    
    // Solicitar calificación
    int calificacion;
    do {
        printf("\nIngresa tu calificacion (1-5 estrellas): ");
        scanf("%d", &calificacion);
        
        if (calificacion < 1 || calificacion > 5) {
            printf("Calificacion invalida. Debe ser entre 1 y 5.\n");
        }
    } while (calificacion < 1 || calificacion > 5);
    
    // Guardar calificación
    FILE *archivoCalificaciones = fopen("calificaciones.txt", "a");
    if (archivoCalificaciones != NULL) {
        fprintf(archivoCalificaciones, "%s|%s|%d\n", nickname, peliculaSeleccionada, calificacion);
        fclose(archivoCalificaciones);
        printf("\nCalificacion guardada exitosamente!\n");
    }
    else {
        printf("Error al guardar la calificacion.\n");
    }
    
    printf("\nPresiona Enter para continuar...");
    setbuf(stdin, NULL);
    getchar();
}

// 7.5 Ver calificaciones
void verCalificaciones()
{
    printf("\n========== VER CALIFICACIONES ==========\n");
    
    // Leer películas disponibles
    FILE *archivoPeliculas = fopen("peliculas.txt", "r");
    if (archivoPeliculas == NULL) {
        printf("No hay películas registradas.\n");
        printf("Presiona Enter para continuar...");
        setbuf(stdin, NULL);
        getchar();
        return;
    }
    
    char peliculas[50][100];
    int numPeliculas = 0;
    char linea[1000];
    
    while (fgets(linea, sizeof(linea), archivoPeliculas) != NULL && numPeliculas < 50) {
        char nombre[100];
        if (sscanf(linea, "%[^|]", nombre) == 1) {
            strcpy(peliculas[numPeliculas], nombre);
            numPeliculas++;
        }
    }
    fclose(archivoPeliculas);
    
    if (numPeliculas == 0) {
        printf("No hay películas registradas.\n");
        printf("Presiona Enter para continuar...");
        setbuf(stdin, NULL);
        getchar();
        return;
    }
    
    // Para cada película, calcular promedio de calificaciones
    printf("CALIFICACIONES PROMEDIO:\n");
    printf("========================\n");
    
    for (int i = 0; i < numPeliculas; i++) {
        FILE *archivoCalif = fopen("calificaciones.txt", "r");
        if (archivoCalif == NULL) {
            printf("%s: Sin calificaciones\n", peliculas[i]);
            continue;
        }
        
        float suma = 0;
        int numCalif = 0;
        char lineaCalif[500];
        
        while (fgets(lineaCalif, sizeof(lineaCalif), archivoCalif) != NULL) {
            char nick[30], pelicula[100];
            int calif;
            if (sscanf(lineaCalif, "%[^|]|%[^|]|%d", nick, pelicula, &calif) == 3) {
                if (strcmp(pelicula, peliculas[i]) == 0) {
                    suma += calif;
                    numCalif++;
                }
            }
        }
        fclose(archivoCalif);
        
        if (numCalif > 0) {
            float promedio = suma / numCalif;
            printf("%s: %.1f estrellas (%d calificaciones)\n", 
                   peliculas[i], promedio, numCalif);
        } else {
            printf("%s: Sin calificaciones\n", peliculas[i]);
        }
    }
    
    printf("\nPresiona Enter para continuar...");
    setbuf(stdin, NULL);
    getchar();
}

// 7.6 Ver películas del usuario
void verPeliculasUsuario(char nickname[])
{
    printf("\n========== MIS PELICULAS ==========\n");
    
    // Leer compras del usuario
    FILE *archivoCompras = fopen("compras.txt", "r");
    if (archivoCompras == NULL) {
        printf("No has comprado boletos para ninguna película.\n");
        printf("Presiona Enter para continuar...");
        setbuf(stdin, NULL);
        getchar();
        return;
    }
    
    RegistroCompra compras[50];
    int numCompras = 0;
    char linea[1000];
    
    while (fgets(linea, sizeof(linea), archivoCompras) != NULL && numCompras < 50) {
        if (sscanf(linea, "%[^|]|%[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%[^\n]", 
                   compras[numCompras].nicknameUsuario,
                   compras[numCompras].nombrePelicula,
                   compras[numCompras].genero,
                   compras[numCompras].sala,
                   &compras[numCompras].numBoletos,
                   compras[numCompras].asientosComprados,
                   compras[numCompras].codigoCompra,
                   compras[numCompras].horario) == 8) {
            if (strcmp(compras[numCompras].nicknameUsuario, nickname) == 0) {
                numCompras++;
            }
        }
    }
    fclose(archivoCompras);
    
    if (numCompras == 0) {
        printf("No has comprado boletos para ninguna película.\n");
        printf("Presiona Enter para continuar...");
        setbuf(stdin, NULL);
        getchar();
        return;
    }
    
    // Mostrar compras
    printf("HISTORIAL DE COMPRAS:\n");
    printf("=====================\n");
    
    for (int i = 0; i < numCompras; i++) {
        printf("\n%d. %s\n", i + 1, compras[i].nombrePelicula);
        printf("   Género: %s\n", compras[i].genero);
        printf("   Sala: %s\n", compras[i].sala);
        printf("   Horario: %s\n", compras[i].horario);
        printf("   Boletos: %d\n", compras[i].numBoletos);
        printf("   Asientos: %s\n", compras[i].asientosComprados);
        printf("   Código: %s\n", compras[i].codigoCompra);
        printf("   ----------------------------------\n");
    }
    
    printf("\nTotal de compras: %d\n", numCompras);
    printf("\nPresiona Enter para continuar...");
    setbuf(stdin, NULL);
    getchar();
}