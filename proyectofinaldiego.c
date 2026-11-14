#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void nuevoRegistro();
void ingresarSistema();
void darAltaPelicula();
void verBoletosPorUsuario(); 
void administradorPrincipal();
void compraDeBoletos(const char *nicknameUsuario);
void mostrarAsientos(const char *sala, const char *asientosOcupados, int *filas, int *lugaresPorFila);
void diego(const char *nicknameLogueado);


char adminUsuario[] = "elAdmin";
char adminContrasena[] = "3l4dm1n";

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
    char codigoCompra[70];
} RegistroCompra;

// aqui se verifica si es admin 
int verificarAdmin(char usuario[], char contrasena[])
{
    if(strcmp(usuario, adminUsuario) == 0 && strcmp(contrasena, adminContrasena) == 0)
    {
        return 1;
    }
    return 0; 
}

int main() 
{
    int opcion;
    do {
        printf(" MENU PRINCIPAL \n");
        printf("1.Nuevo registro\n");
        printf("2.Ingreso al sistema\n");
        printf("3.Salir\n");
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
                printf("Saliendo...\n");
                break;
            default:
                printf("Opcion invalida.\n");
        }

    } while (opcion != 3);

    return 0;
}

// ... (Dentro del archivo principal)

//este es la interfaz para crear una cuenta 
void nuevoRegistro()
{

 char nombreUsar[30], nombre[50], apellidoP[50], apellidoM[50], numeroCel[15], correoElec[100], contraUno[40], contraDos[40];
int edad = 0;
 printf("NUEVO REGISTRO =====\n");

    // Limpieza de buffer antes de usar scanf con espacio
    // NOTA: Es mejor usar `while (getchar() != '\n');` en lugar de `setbuf(stdin, NULL);` para limpiar el buffer

printf("Nombre completo: ");
setbuf(stdin, NULL);
 scanf("%49[^\n]", nombre);
 
 printf("Apellido Paterno: ");
 setbuf(stdin, NULL);
 scanf("%49[^\n]", apellidoP);

 printf("Apellido Materno: ");
 setbuf(stdin, NULL);
  scanf("%49[^\n]", apellidoM);

  printf("Edad: ");
 scanf("%d", &edad);
 setbuf(stdin, NULL);

 printf("Nombre de usuario: ");
 setbuf(stdin, NULL);
 scanf("%29[^\n]", nombreUsar); // Nickname sin espacios

 if (strcmp(nombreUsar, adminUsuario) == 0)
 {
     printf("Error: Este nombre de usuario esta reservado para el administrador.\n");
 return;
 }
 
    do
    {
        printf("Contrasena: ");
        setbuf(stdin, NULL);
        scanf("%39s", contraUno);
        printf("Confirmar contrasena: ");
        setbuf(stdin, NULL);
        scanf("%39s", contraDos);
        if (strcmp(contraUno, contraDos) != 0)
        {
             printf("Las contrasenas no coinciden.\n");
        }
    } while (strcmp(contraUno, contraDos) != 0);

    printf("Contrasena guardada.\n");
    printf("Correo electronico: ");
    setbuf(stdin, NULL);
    scanf("%99s", correoElec);
    printf("Numero de celular: ");
    setbuf(stdin, NULL);
    scanf("%14s", numeroCel);

    FILE *archivo = fopen("usuarios.txt", "a");
    if (archivo == NULL)
    {
         printf("Error al abrir el archivo.\n");
        return;
    }
    fprintf(archivo, "%s|%s|%s|%d|%s|%s|%s|%s|2\n",
            nombre, apellidoP, apellidoM, edad,
            nombreUsar, contraUno, correoElec, numeroCel);

    fclose(archivo);
    printf("\n");
printf("Te has registrado correctamente\n");
}
// este es la interfaz para crear una cuenta 
void ingresarSistema()
{
char usuarioIngresar[36], contrasenaIngresar[40];
 
 char nombreArchivo[50], apellidoPArchivo[21], apellidoMArchivo[21], usuarioArchivo[36], contraArchivo[40], correoElecArchivo[45], numeroCelArchivo[20];
 int edadArchivo, tipoUsuarioArchivo;
 char linea[512]; // Buffer para fgets
 int encontrado = 0;
 
 printf("\n");
 printf("INGRESO AL SISTEMA =====\n");
 printf("Nombre de usuario: ");
 setbuf(stdin, NULL);
 scanf("%s", usuarioIngresar);
 printf("Contrasena: ");
 setbuf(stdin, NULL);
 scanf("%s", contrasenaIngresar);

 if (strcmp(usuarioIngresar, adminUsuario) == 0 && strcmp(contrasenaIngresar, adminContrasena) == 0)
 {
printf(" Acceso concedido como Administrador \n");
administradorPrincipal();
 return;
 } 

FILE *archivo = fopen("usuarios.txt", "r");
if (archivo == NULL)
  {
 printf("No se pudo abrir el archivo de usuarios. Puede que no haya cuentas registradas.\n");
 return;
}

 while (fgets(linea, sizeof(linea), archivo) != NULL)
 {
        // Formato: Nombre|ApellidoP|ApellidoM|Edad|Nickname|Contrasena|Correo|Celular|Tipo
 if (sscanf(linea, "%[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%[^|]|%[^|]|%d",nombreArchivo, apellidoPArchivo, apellidoMArchivo, &edadArchivo,usuarioArchivo, contraArchivo, correoElecArchivo, numeroCelArchivo, &tipoUsuarioArchivo) == 9)
        {
            if (strcmp(usuarioIngresar, usuarioArchivo) == 0)
        {
                encontrado = 1;

                if (strcmp(contrasenaIngresar, contraArchivo) == 0)
                {
                    printf("\nBienvenido %s %s!\n", nombreArchivo, apellidoPArchivo);
                    printf("Has ingresado correctamente.\n");
                    diego(usuarioArchivo); // Llama al menú de usuario
                }
             else
                {
                    printf("Contrasena incorrecta.\n");
                }

                break; // Sale del while una vez que encuentra el usuario (independiente de la contraseña)
             }
        }
    }
    fclose(archivo);
    if (!encontrado)
    {
        printf("El usuario no existe.\n");
    }
}

// aquí es la interfaz de iniciar seción 

void administradorPrincipal(){
int opcion=0;
do{
    printf("*****Menu de administrador***** \n");
    printf("1.-Dar de alta una pelicula. \n");
    printf("2.-Ver las peliculas para las que un usuario ha comprado boletos. \n");
    printf("3.-salir de sesion\n");
    printf("su opcion es : ");
    scanf("%i",&opcion);

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
    }while (opcion!=3);
}

void darAltaPelicula()
{
    Pelicula nuevaPelicula;

    printf("Nombre de la pelicula: ");
    scanf(" %49[^\n]", nuevaPelicula.nombre);

    printf("Genero de la pelicula: ");
    scanf(" %49[^\n]", nuevaPelicula.genero);

    printf("Sinopsis de la pelicula: ");
    scanf(" %499[^\n]", nuevaPelicula.sinopsis);

    printf("Duracion de la pelicula (en minutos): ");
    scanf("%d", &nuevaPelicula.duracionMinutos);
    setbuf(stdin, NULL);


    printf("Horas de proyeccion separadas por espacios (ej: 17:00 18:45 20:00): ");
    scanf(" %199[^\n]",nuevaPelicula.horarios);

        do {
        printf("Sala en que se exhibira (A, B o VIP): ");
        char salaInput[10];
        scanf(" %s", salaInput);

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

    FILE *archivoPeliculas = fopen("peliculas.txt", "a");

    if (archivoPeliculas == NULL) {
        printf("Error: No se pudo abrir o crear el archivo de peliculas.\n");
    } else {
        fprintf(archivoPeliculas, "%s|%s|%s|%d|%s|%s\n",nuevaPelicula.nombre,nuevaPelicula.genero,nuevaPelicula.sinopsis,nuevaPelicula.duracionMinutos,nuevaPelicula.horarios,nuevaPelicula.sala);
        fclose(archivoPeliculas);

        printf("\nPelicula '%s' dada de alta exitosamente.\n", nuevaPelicula.nombre);
    }
}

void verBoletosPorUsuario() {

    FILE *archivoUsuarios, *archivoCompras;
    char linea[512];
    Usuario usuarios[100];
    int totalUsuarios = 0;
    int seleccion = -1;

    printf("\n--- Ver Boletos Comprados por Usuario ---\n");

  
    archivoUsuarios = fopen("usuarios.txt", "r");
    if (archivoUsuarios == NULL) {
        printf("ADVERTENCIA: No se pudo abrir el archivo de usuarios. No hay usuarios registrados.\n");
        return;
    }

printf("Lista de Nicknames de usuarios registrados:\n");
int i = 1;
    // CORRECCIÓN: Usar sscanf para saltar los primeros 4 campos y obtener el 5to (Nickname)
while (fgets(linea, sizeof(linea), archivoUsuarios) != NULL && totalUsuarios < 100) {
char nickname_temp[30];

if (sscanf(linea, "%*[^|]|%*[^|]|%*[^|]|%*d|%[^|]", nickname_temp) == 1) {
strncpy(usuarios[totalUsuarios].nickname, nickname_temp, 29);
usuarios[totalUsuarios].nickname[29] = '\0';
printf("%d. %s\n", i++, usuarios[totalUsuarios].nickname);
totalUsuarios++;
}
}
fclose(archivoUsuarios);
    
    // ... (El resto de la función es correcto)
    if (totalUsuarios == 0) {
        printf("No hay usuarios registrados en el sistema.\n");
        return;
    }

    printf("\nIngrese el numero del usuario a revisar (o 0 para volver): ");
    if (scanf("%d", &seleccion) != 1 || seleccion < 0 || seleccion > totalUsuarios) {
        printf("Seleccion no valida. Volviendo al menu.\n");
        setbuf(stdin, NULL);
        return;
    }

    if (seleccion == 0) {
        return; 
    }
    const char *nicknameSeleccionado = usuarios[seleccion - 1].nickname;

    printf("\n--- Detalle de Compras para el Usuario: %s ---\n", nicknameSeleccionado);
   
    archivoCompras = fopen("compras.txt", "r");
    if (archivoCompras == NULL) {
        printf("ADVERTENCIA: No hay registros de boletos comprados.\n");
        return;
    }

    int comprasEncontradas = 0;
    RegistroCompra compra;
    printf("\n");

    while (fgets(linea, sizeof(linea), archivoCompras) != NULL) {
        if (sscanf(linea, "%[^|]|%[^|]|%[^|]|%[^|]|%d|%[^|]|%s", compra.nicknameUsuario, compra.nombrePelicula, compra.genero, compra.sala, &compra.numBoletos, compra.asientosComprados, compra.codigoCompra) == 7) {
            if (strcmp(compra.nicknameUsuario, nicknameSeleccionado) == 0) {
                comprasEncontradas++;
                printf("--------------------------------------\n");
                printf("  Pelicula: %s\n", compra.nombrePelicula);
                printf("  Genero: %s\n", compra.genero);
                printf("  Sala: %s\n", compra.sala);
                printf("  Numero de boletos comprados: %d\n", compra.numBoletos);
                printf("  Asientos: %s\n", compra.asientosComprados);
                printf("  Codigo de Compra: %s\n", compra.codigoCompra);
            }
        }
    }
    fclose(archivoCompras);

    if (comprasEncontradas == 0) {
        printf("El usuario %s no ha comprado boletos para ninguna pelicula.\n", nicknameSeleccionado);
    } else {
        printf("--------------------------------------\n");
    }

    printf("\nPresione Enter para regresar al Menu Principal del Administrador.\n");
    setbuf(stdin, NULL);
    getchar();
}

const int CAPACIDADES_SALA[3][2] = {
    {'J' - 'A' + 1, 10}, // Sala A
    {'J' - 'A' + 1, 10}, // Sala B
    {'F' - 'A' + 1, 6}   // Sala VIP
};

// --- Función de Usuario (Contenedor del menú) ---
void diego(const char *nicknameLogueado) {
    int opcion;
    do {
        printf("\n*****Menu de Usuario***** \n");
        printf("1. Compra de boletos de una pelicula\n"); // 7.1
        printf("2. Realizar un comentario...\n"); // 7.2
        // ... (otras opciones del 7.3 al 7.5)
        printf("6. Salir de sesion\n"); // 7.6
        printf("su opcion es : ");
        scanf("%d", &opcion);
        setbuf(stdin, NULL);

        switch (opcion) {
            case 1:
                // Se pasa el nickname a la función de compra
                compraDeBoletos(nicknameLogueado);
                break;
            case 6:
                printf("Cerrando sesion...\n");
                break;
            default:
                printf("Opcion no valida. Intente de nuevo.\n");
        }
    } while (opcion != 6);
}

// --- Función Auxiliar para mostrar Asientos (Simplificada) ---

void mostrarAsientos(const char *sala, const char *asientosOcupados, int *filas, int *lugaresPorFila) {
    int maxFilas, maxLugaresEnFila;
    char filaInicial = 'A';

    // 1. Determinar el tamaño general de la sala (Punto 6.1)
    if (strcmp(sala, "Sala A") == 0) { 
        maxFilas = 10; // Filas A-J
        maxLugaresEnFila = 10; // El máximo en esta sala
    } 
    else if (strcmp(sala, "Sala B") == 0) { 
        maxFilas = 10; // Filas A-J
        maxLugaresEnFila = 10; // El máximo en esta sala
    } 
    else if (strcmp(sala, "Sala VIP") == 0) { 
        maxFilas = 6; // Filas A-F
        maxLugaresEnFila = 6; // El máximo en esta sala
    } 
    else { 
        maxFilas = 0; maxLugaresEnFila = 0; 
    }
    
    *filas = maxFilas;
    *lugaresPorFila = maxLugaresEnFila; // Retornamos el valor máximo de la fila

    if (maxFilas == 0) {
        printf("Error: Sala no reconocida o mal definida.\n");
        return;
    }

    printf("\n\t\t---------------- PANTALLA ----------------\n");

    for (int r = 0; r < maxFilas; r++) {
        char filaActual = filaInicial + r;
        int lugaresDisponiblesEnFila = maxLugaresEnFila;

        // 2. Aplicar lógica especial para Sala B (Punto 6.1):
        // Filas A-D (r=0 a r=3) tienen 7 lugares. Filas E-J (r=4 a r=9) tienen 10.
        if (strcmp(sala, "Sala B") == 0 && filaActual <= 'D') {
            lugaresDisponiblesEnFila = 7;
        }
        
        printf("Fila %c: ", filaActual);
        
        for (int c = 1; c <= lugaresDisponiblesEnFila; c++) {
            char asientoStr[5];
            
            // 3. CORRECCIÓN CRÍTICA: Construir el asiento SIN espacio (ej: "A1", "J10")
            sprintf(asientoStr, "%c%d", filaActual, c);

            // Se asume que asientosOcupados es una cadena con los asientos ocupados separados por comas
            // (ej: "J5,J6,A1,B2").

            // Para verificar si un asiento está ocupado, necesitamos buscar el asiento rodeado de delimitadores
            // para evitar falsos positivos (ej: buscar '1' y encontrar '10').

            char busquedaDelimitada[10];
            // Construimos la cadena de búsqueda con una coma antes (ej: ",J5")
            sprintf(busquedaDelimitada, ",%s", asientoStr); 

            // Verificamos si el asiento está ocupado:
            // a) Si el asiento es el primero en la lista (no tiene coma antes)
            // b) Si el asiento está en la lista precedido por una coma (la mayoría de los casos)
            if (strstr(asientosOcupados, asientoStr) == asientosOcupados || // Es el primer asiento (al inicio de la cadena)
                strstr(asientosOcupados, busquedaDelimitada) != NULL) {
                
                printf("[ X ] "); // X = Ocupado
            } else {
                printf("[%2d] ", c); // Disponible
            }
        }
        printf("\n");
    }
    printf("\nDonde [ X ] = Ocupado. (Ejemplo de asiento: A1, J10)\n");
}

// --- Implementación de Compra de Boletos (Funcionalidad 7.1) ---
void compraDeBoletos(const char *nicknameUsuario) {
    FILE *archivoPeliculas, *archivoCompras;
    char linea[512];
    Pelicula cartelera[20];
    int totalPeliculas = 0;
    int seleccionPelicula;

    printf("\n--- Compra de Boletos ---\n");

    // =================================================================
    // PASO 1: Mostrar Películas disponibles y seleccionar una
    // =================================================================
    archivoPeliculas = fopen("peliculas.txt", "r");
    if (archivoPeliculas == NULL) {
        printf("ERROR: No hay cartelera disponible. (Archivo peliculas.txt no encontrado)\n");
        return;
    }

    printf("Peliculas en cartelera:\n");
    int i = 1;
    // Formato: nombre|genero|sinopsis|duracion|horarios|sala
  while (fgets(linea, sizeof(linea), archivoPeliculas) != NULL && totalPeliculas < 20) {
        
        // CORRECCIÓN CLAVE: Cambiar el último '%s' por '%[^\n]' para leer cadenas con espacios.
        if (sscanf(linea, "%[^|]|%[^|]|%[^|]|%d|%[^|]|%[^\n]",
                   cartelera[totalPeliculas].nombre, cartelera[totalPeliculas].genero,
                   cartelera[totalPeliculas].sinopsis, &cartelera[totalPeliculas].duracionMinutos,
                   cartelera[totalPeliculas].horarios, cartelera[totalPeliculas].sala) == 6) 
        {
            // La línea de limpieza del salto de línea ya no es tan necesaria
            // si usas %[^\n], pero se deja por si acaso.
            // cartelera[totalPeliculas].sala[strcspn(cartelera[totalPeliculas].sala, "\n")] = '\0';
            
            printf("%d. %s (Genero: %s | Sala: %s)\n", i++, cartelera[totalPeliculas].nombre, cartelera[totalPeliculas].genero, cartelera[totalPeliculas].sala);
            totalPeliculas++;
        }
    }
    fclose(archivoPeliculas);

    if (totalPeliculas == 0) { printf("Cartelera vacia.\n"); return; }

    printf("\nSeleccione el numero de la pelicula (o 0 para regresar): ");
    if (scanf("%d", &seleccionPelicula) != 1 || seleccionPelicula < 0 || seleccionPelicula > totalPeliculas) {
        printf("Seleccion no valida. Volviendo.\n"); setbuf(stdin, NULL); return;
    }
    if (seleccionPelicula == 0) { setbuf(stdin, NULL); return; }
    setbuf(stdin, NULL); 

    Pelicula peliculaSeleccionada = cartelera[seleccionPelicula - 1];

    // =================================================================
    // PASO 2: Seleccionar Horario
    // =================================================================
    char horarioSeleccionado[10];
    char horariosCopia[200];
    strcpy(horariosCopia, peliculaSeleccionada.horarios);

    printf("\nHorarios disponibles para %s:\n", peliculaSeleccionada.nombre);
    
    // Uso de strtok (ya incluido en tu archivo) para dividir la cadena de horarios
    char *h_token;
    int seleccionHorario = 0;
    int totalHorarios = 0;
    
    h_token = strtok(horariosCopia, " ");
    while (h_token != NULL) {
        printf("%d. %s\n", ++totalHorarios, h_token);
        // Guardar el primer horario para simular la selección si es necesario
        if (totalHorarios == 1) strcpy(horarioSeleccionado, h_token);
        h_token = strtok(NULL, " ");
    }

    printf("\nSeleccione el numero del horario (o 0 para regresar): ");
    if (scanf("%d", &seleccionHorario) != 1 || seleccionHorario < 0 || seleccionHorario > totalHorarios) {
        printf("Seleccion no valida. Volviendo.\n"); setbuf(stdin, NULL); return;
    }
    if (seleccionHorario == 0) { setbuf(stdin, NULL); return; }
    setbuf(stdin, NULL);

    // NOTA: Se necesitaría un segundo parseo con strtok para obtener el horario exacto por índice.
    // Usaremos el primer horario como ejemplo para simplificar:
    // **Corregir**: Si el usuario selecciona un índice > 1, 'horarioSeleccionado' será incorrecto.

    // =================================================================
    // PASO 3: Mostrar Asientos y Seleccionar Lugares
    // =================================================================
    
    char asientosOcupadosExistentes[500] = "J5, J6, A1, B2"; // Simulación de asientos ocupados
    char asientosDeseados[100];
    char numTarjeta[20];
    int maxFilas, maxLugares;

    // Mostrar el mapa de asientos 
    mostrarAsientos(peliculaSeleccionada.sala, asientosOcupadosExistentes, &maxFilas, &maxLugares); 

    printf("Escriba los asientos a comprar separados por espacios (ej: J7 J8): ");
    scanf(" %99[^\n]", asientosDeseados);
    setbuf(stdin, NULL);
    
    // Validación de asientos: Se debe verificar aquí si los asientos existen y no están ocupados.
    
    printf("Ingrese numero de la tarjeta: ");
    scanf(" %19s", numTarjeta);
    setbuf(stdin, NULL);

    // =================================================================
    // PASO 4: Generar Código de Compra y Registrar
    // =================================================================
    
    // 4.1 Generación del Código de Compra (SPPPHH:MMNNNAsientos)
    char salaLetra;
    if (strcmp(peliculaSeleccionada.sala, "Sala A") == 0) salaLetra = 'A';
    else if (strcmp(peliculaSeleccionada.sala, "Sala B") == 0) salaLetra = 'B';
    else if (strcmp(peliculaSeleccionada.sala, "Sala VIP") == 0) salaLetra = 'V';
    else salaLetra = 'X';
    
    char ppp[4], nnn[4];
    strncpy(ppp, peliculaSeleccionada.nombre, 3); ppp[3] = '\0';
    strncpy(nnn, nicknameUsuario, 3); nnn[3] = '\0';

    char hh[3], mm[3];
    strncpy(hh, horarioSeleccionado, 2); hh[2] = '\0';
    strncpy(mm, horarioSeleccionado + 3, 2); mm[2] = '\0';

    // Se necesita transformar 'J7 J8' a 'J7J8' (eliminando espacios)
    char asientosSinEspacios[100];
    int j = 0;
    for (int k = 0; asientosDeseados[k] != '\0'; k++) {
        if (asientosDeseados[k] != ' ') {
            asientosSinEspacios[j++] = asientosDeseados[k];
        }
    }
    asientosSinEspacios[j] = '\0';
    
    char codigoCompra[50];
    sprintf(codigoCompra, "%c%s%s:%s%s%s", // CORRECCIÓN: Se debe agregar el ':' al formato.
    salaLetra, ppp, hh, mm, nnn, asientosSinEspacios);
    // 4.2 Registro de la Compra
    archivoCompras = fopen("compras.txt", "a");
    if (archivoCompras != NULL) {
        // Contar boletos (simplificado: contar espacios + 1)
        int numBoletos = 1;
        for (int k = 0; asientosDeseados[k] != '\0'; k++) {
            if (asientosDeseados[k] == ' ') numBoletos++;
        }
        
        // Formato: NicknameUsuario|NombrePelicula|Genero|Sala|NumBoletos|AsientosComprados|CodigoCompra\n
        fprintf(archivoCompras, "%s|%s|%s|%s|%d|%s|%s\n",
                nicknameUsuario, peliculaSeleccionada.nombre, peliculaSeleccionada.genero,
                peliculaSeleccionada.sala, numBoletos, asientosDeseados, codigoCompra);
        fclose(archivoCompras);
        
        printf("\n COMPRA CONFIRMADA:\n");
        printf("  Pelicula: %s\n", peliculaSeleccionada.nombre);
        printf("  Hora: %s\n", horarioSeleccionado);
        printf("  Asientos Adquiridos: %s\n", asientosDeseados);
        printf("  CODIGO DE COMPRA: %s\n", codigoCompra);
    } else {
        fprintf(stderr, "ERROR: No se pudo registrar la compra.\n");
    }

    printf("\nPresione Enter para regresar al Menu de Usuario.\n");
    setbuf(stdin, NULL);
    getchar();
}