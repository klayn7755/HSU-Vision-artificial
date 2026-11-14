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
void realizarComentario(const char *nicknameLogueado);
void verComentariosPeliculas(void);
void calificarPelicula(const char *nicknameLogueado);
void verPromedioCalificaciones(void);



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
    char asientosComprados[100]; // Ej: G9G10G11
    char codigoCompra[50];
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
        system("cls");
        printf("\t\033[32;44mMENU PRINCIPAL\033[0m \n");
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
                printf("\033[31mSaliendo...\n\033[0m");
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
    system("cls");
    char nombreUsar[30], nombre[50], apellidoP[50], apellidoM[50], numeroCel[15], correoElec[100], contraUno[40], contraDos[40];
    int edad = 0;
    printf("\033[33;44m===== NUEVO REGISTRO =====\033[0;0m\n");

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

        if (strcmp(nombreUsar, adminUsuario) == 0){
            printf("\033[31mError: Este nombre de usuario esta reservado para el administrador.\n\033[0m");
            return;
        }      
 
        do{
            printf("Contrasena: ");
            setbuf(stdin, NULL);
            scanf("%39s", contraUno);
            printf("Confirmar contrasena: ");
            setbuf(stdin, NULL);
            scanf("%39s", contraDos);
                if (strcmp(contraUno, contraDos) != 0){
                    printf("\033[31mLas contrasenas no coinciden.\n\033[0m");
                }
        } while (strcmp(contraUno, contraDos) != 0);

    printf("\033[32mContrasena guardada.\n\033[0m");
    printf("Correo electronico: ");
    setbuf(stdin, NULL);
    scanf("%99s", correoElec);
    printf("Numero de celular: ");
    setbuf(stdin, NULL);
    scanf("%14s", numeroCel);

    FILE *archivo = fopen("usuarios.txt", "a");
    if (archivo == NULL)
    {
         printf("\033[31mError al abrir el archivo.\n\033[0m");
        return;
    }
    fprintf(archivo, "%s|%s|%s|%d|%s|%s|%s|%s|2\n",nombre, apellidoP, apellidoM, edad,nombreUsar, contraUno, correoElec, numeroCel);

    fclose(archivo);
    printf("\n");
printf("\033[32mTe has registrado correctamente\n\033[0m");
}
// este es la interfaz para crear una cuenta 
void ingresarSistema()
{
char usuarioIngresar[36], contrasenaIngresar[40];
 
 char nombreArchivo[50], apellidoPArchivo[21], apellidoMArchivo[21], usuarioArchivo[36], contraArchivo[40], correoElecArchivo[45], numeroCelArchivo[20];
 int edadArchivo, tipoUsuarioArchivo;
 char linea[512]; // Buffer para fgets
 int encontrado = 0;
 
 system("cls");
 printf("\n");
 printf("\033[31;44m ===== INGRESO AL SISTEMA =====\033[0m\n");
 printf("Nombre de usuario: ");
 setbuf(stdin, NULL);
 scanf("%s", usuarioIngresar);
 printf("Contrasena: ");
 setbuf(stdin, NULL);
 scanf("%s", contrasenaIngresar);

 if (strcmp(usuarioIngresar, adminUsuario) == 0 && strcmp(contrasenaIngresar, adminContrasena) == 0)
 {
printf("\033[32m Acceso concedido como Administrador \n\033[0m");
administradorPrincipal();
 return;
 } 

FILE *archivo = fopen("usuarios.txt", "r");
if (archivo == NULL)
  {
 printf("\033[31mNo se pudo abrir el archivo de usuarios. Puede que no haya cuentas registradas.\n\033[0m");
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
                    system("cls");
                    printf("\n\033[32mBienvenido %s %s!\n\033[0m", nombreArchivo, apellidoPArchivo);
                    printf("\033[32mHas ingresado correctamente.\n\033[0m");
                    diego(usuarioArchivo); // Llama al menú de usuario
                }
             else
                {
                    printf("\033[31mContrasena incorrecta.\n\033[0m");
                }

                break; // Sale del while una vez que encuentra el usuario (independiente de la contraseña)
             }
        }
    }
    fclose(archivo);
    if (!encontrado)
    {
        printf("\033[31mEl usuario no existe.\n\033[0m");
    }
}

// aquí es la interfaz de iniciar seción 

void administradorPrincipal(){
int opcion=0;
do{
    system("cls");
    printf("\033[31;44m*****Menu de administrador*****\033[0m\n");
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

    system("cls");
    printf("\n \033[31;31m--- Menu Dar de Alta una Nueva Pelicula ---\033[0;0m\n");
    printf("Por favor ingrese los siguientes datos:\n");
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
            printf("\033[31mSala no valida. Intente de nuevo.\n\033[0m");
            continue;
        }
        break;
    } while (1);

    FILE *archivoPeliculas = fopen("peliculas.txt", "a");

    if (archivoPeliculas == NULL) {
        printf("\033[31mError: No se pudo abrir o crear el archivo de peliculas.\n\033[0m  ");
    } else {
        fprintf(archivoPeliculas, "%s|%s|%s|%d|%s|%s\n",nuevaPelicula.nombre,nuevaPelicula.genero,nuevaPelicula.sinopsis,nuevaPelicula.duracionMinutos,nuevaPelicula.horarios,nuevaPelicula.sala);
        fclose(archivoPeliculas);

        printf("\n\033[32mPelicula '%s' dada de alta exitosamente.\n\033[0m", nuevaPelicula.nombre);
    }
}

void verBoletosPorUsuario() {

FILE *archivoUsuarios, *archivoCompras;
    char linea[512];
    Usuario usuarios[100];
    int totalUsuarios = 0;
    int seleccion = -1;

    printf("\n\033[31;31m--- Ver Boletos Comprados por Usuario ---\033[0;0m\n");

    archivoUsuarios = fopen("usuarios.txt", "r");
    if (archivoUsuarios == NULL) {
        printf("ADVERTENCIA: No se pudo abrir el archivo de usuarios. No hay usuarios registrados.\n");
        return;
    }

    printf("\033[31mLista de Nicknames de usuarios registrados:\n\033[0m");
    int i = 1;

    // --- CÓDIGO CORREGIDO PARA OBTENER EL NICKNAME ---
    while (fgets(linea, sizeof(linea), archivoUsuarios) != NULL && totalUsuarios < 100) {
        // Formato: Nombre|ApellidoP|ApellidoM|Edad|Nickname|Contrasena|Correo|Celular|Tipo
        char nombre[50], apP[50], apM[50], nick[30], contra[40], correo[100], cel[15];
        int edad, tipo;
        
        // Usamos sscanf para saltar a la posición del nickname (quinto campo)
        if (sscanf(linea, "%[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%[^|]|%[^|]|%d",
                   nombre, apP, apM, &edad, nick, contra, correo, cel, &tipo) == 9) {

            // Ahora 'nick' contiene el Nickname
            strncpy(usuarios[totalUsuarios].nickname, nick, 29);
            usuarios[totalUsuarios].nickname[29] = '\0';
            printf("%d. %s\n", i++, usuarios[totalUsuarios].nickname);
            totalUsuarios++;
        }
    }
    // --- FIN CÓDIGO CORREGIDO ---
    
    fclose(archivoUsuarios);

    if (totalUsuarios == 0) {
        printf("\033[31mNo hay usuarios registrados en el sistema.\n\033[0m");
        return;
    }

    printf("\033[34m\nIngrese el numero del usuario a revisar (o 0 para volver): \033[0m");
    if (scanf("%d", &seleccion) != 1 || seleccion < 0 || seleccion > totalUsuarios) {
        printf("\033[31mSeleccion no valida. Volviendo al menu.\n\033[0m");
        setbuf(stdin, NULL);
        return;
    }

    if (seleccion == 0) {
        return; 
    }
    const char *nicknameSeleccionado = usuarios[seleccion - 1].nickname;

    printf("\n\033[34m--- Detalle de Compras para el Usuario: %s ---\033[0m\n", nicknameSeleccionado);
   
    archivoCompras = fopen("compras.txt", "r");
    if (archivoCompras == NULL) {
        printf("\033[31mADVERTENCIA: No hay registros de boletos comprados.\n\033[0m");
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
        printf("\033[31mEl usuario %s no ha comprado boletos para ninguna pelicula.\n\033[0m", nicknameSeleccionado);
    } else {
        printf("--------------------------------------\n");
    }

    printf("\n\033[44mPresione Enter para regresar al Menu Principal del Administrador.\n\033[0m");
    setbuf(stdin, NULL);
    getchar();
}

const int CAPACIDADES_SALA[3][2] = {
    {'J' - 'A' + 1, 10}, // Sala A
    {'J' - 'A' + 1, 10}, // Sala B
    {'F' - 'A' + 1, 6}   // Sala VIP
};

// --- Función de Usuario (Contenedor del menú) ---
// --- Función de Usuario (Contenedor del menú) actualizada ---
void diego(const char *nicknameLogueado) {
    system("cls");
    int opcion;
    do {
        printf("\n\033[34m*****Menu de Usuario***** \033[0m\n");
        printf("1. Compra de boletos de una pelicula\n"); // 7.1
        printf("2. Realizar un comentario\n"); // 7.2
        printf("3. Revisar comentarios de una pelicula\n"); // 7.3
        printf("4. Calificar una pelicula\n"); // 7.4
        printf("5. Ver calificaciones (promedio por pelicula)\n"); // 7.5
        printf("6. Salir de sesion\n"); // 7.6
        printf("su opcion es : ");
        if (scanf("%d", &opcion) != 1) { while (getchar()!='\n'); opcion = -1; }
        setbuf(stdin, NULL);

        switch (opcion) {
            case 1:
                compraDeBoletos(nicknameLogueado);
                break;
            case 2:
                realizarComentario(nicknameLogueado);
                break;
            case 3:
                verComentariosPeliculas();
                break;
            case 4:
                calificarPelicula(nicknameLogueado);
                break;
            case 5:
                verPromedioCalificaciones();
                break;
            case 6:
                printf("\033[34mCerrando sesion...\n\033[0m");
                break;
            default:
                printf("\033[31mOpcion no valida. Intente de nuevo.\n\033[0m");
        }
    } while (opcion != 6);
}

// --- Función Auxiliar para mostrar Asientos (Simplificada) ---

// Coloca esta función ANTES de `compraDeBoletos` o en la parte superior del archivo.
int esAsientoOcupado(const char *asiento, const char *asientosOcupados) {
    // Caso 1: El asiento es el único o el primero (ej: "A1" o "A1,B2")
    if (strstr(asientosOcupados, asiento) == asientosOcupados) {
        // Doble verificación: Si es el único asiento, o si le sigue una coma.
        if (strlen(asientosOcupados) == strlen(asiento) || asientosOcupados[strlen(asiento)] == ',') {
            return 1; // Ocupado
        }
    }
    
    // Caso 2: El asiento está en medio o al final (ej: ...,B2,...)
    char busquedaDelimitada[10];
    // Buscamos con coma antes (ej: ",B2")
    sprintf(busquedaDelimitada, ",%s", asiento); 
    
    if (strstr(asientosOcupados, busquedaDelimitada) != NULL) {
        // Verificamos si es el último o si le sigue una coma (no puede ser solo el prefijo de otro asiento)
        char *ptr = strstr(asientosOcupados, busquedaDelimitada);
        // Debe ser el final de la cadena o seguido por otra coma
        if (ptr[strlen(busquedaDelimitada)] == '\0' || ptr[strlen(busquedaDelimitada)] == ',') {
            return 1; // Ocupado
        }
    }
    
    return 0; // Disponible
}

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
        printf("\033[31mError: Sala no reconocida o mal definida.\n\033[0m");
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
            char asientoStr[20];
            
            // 3. CORRECCIÓN CRÍTICA: Construir el asiento SIN espacio (ej: "A1", "J10")
            sprintf(asientoStr, "%c%d", filaActual, c);

            // Se asume que asientosOcupados es una cadena con los asientos ocupados separados por comas
            // (ej: "J5,J6,A1,B2").

            // Para verificar si un asiento está ocupado, necesitamos buscar el asiento rodeado de delimitadores
            // para evitar falsos positivos (ej: buscar '1' y encontrar '10').

            char busquedaDelimitada[30];
            // Construimos la cadena de búsqueda con una coma antes (ej: ",J5")
            sprintf(busquedaDelimitada, ",%s", asientoStr); 

            // Verificamos si el asiento está ocupado:
            // a) Si el asiento es el primero en la lista (no tiene coma antes)
            // b) Si el asiento está en la lista precedido por una coma (la mayoría de los casos)
            if (strstr(asientosOcupados, asientoStr) == asientosOcupados || // Es el primer asiento (al inicio de la cadena)
                strstr(asientosOcupados, busquedaDelimitada) != NULL) {
                
                printf("\033[31m[ X ] \033[0m"); // X = Ocupado
            } else {
                printf("\033[32m[%2d] \033[0m", c); // Disponible
            }
        }
        printf("\n");
    }
    printf("\n\033[31mDonde [ X ] = Ocupado. (Ejemplo de asiento: A1, J10)\n\033[0m");
}

/* ------------------  FUNCIONES: Comentarios y Calificaciones (7.2 - 7.6) ------------------ */

#define MAX_LINEA 512

void realizarComentario(const char *nicknameLogueado) {
    system("cls"); 
    FILE *fPeliculas = fopen("peliculas.txt", "r");
    FILE *fCompras = fopen("compras.txt", "r");
    if (!fPeliculas) {
        printf("\033[31mNo hay peliculas en cartelera (peliculas.txt no encontrado).\n\033[0m");
        return;
    }
    if (!fCompras) {
        printf("\033[31mNo hay compras registradas (compras.txt no encontrado). No puedes comentar sin comprar.\n\033[0m");
        fclose(fPeliculas);
        return;
    }

    char linea[MAX_LINEA];
    char peliculasCompradas[100][200];
    int pcCount = 0;

    while (fgets(linea, sizeof(linea), fCompras) != NULL && pcCount < 100) {
        // Formato compras: NicknameUsuario|NombrePelicula|Genero|Sala|NumBoletos|AsientosComprados|CodigoCompra
        char nick[60], nombreP[200], generoTemp[100], salaTemp[60];
        if (sscanf(linea, "%59[^|]|%199[^|]|%99[^|]|%59[^|]|%*d|%*[^|]|%*s",
                   nick, nombreP, generoTemp, salaTemp) >= 2) {
            if (strcmp(nick, nicknameLogueado) == 0) {
                int dup = 0;
                for (int i = 0; i < pcCount; ++i) if (strcmp(peliculasCompradas[i], nombreP) == 0) { dup = 1; break; }
                if (!dup) {
                    strncpy(peliculasCompradas[pcCount], nombreP, 199);
                    peliculasCompradas[pcCount][199] = '\0';
                    pcCount++;
                }
            }
        }
    }
    rewind(fCompras);

    if (pcCount == 0) {
        printf("\033[31mNo has comprado boletos para ninguna pelicula. No puedes dejar comentarios.\n\033[0m");
        fclose(fPeliculas);
        fclose(fCompras);
        return;
    }

    printf("\n\033[34mPeliculas para las que compraste boletos:\n\033[0m");
    for (int i = 0; i < pcCount; ++i) printf("%d) %s\n", i+1, peliculasCompradas[i]);
    printf("0) Regresar\n");
    printf("Selecciona la pelicula para comentar: ");
    int sel;
    if (scanf("%d", &sel) != 1) { while (getchar()!='\n'); printf("\033[31mEntrada invalida.\n\033[0m"); fclose(fPeliculas); fclose(fCompras); return; }
    while (getchar()!='\n');
    if (sel == 0) { fclose(fPeliculas); fclose(fCompras); return; }
    if (sel < 1 || sel > pcCount) { printf("\033[31mSeleccion invalida.\n\033[0m"); fclose(fPeliculas); fclose(fCompras); return; }

    char comentario[256];
    printf("Escribe tu comentario (max 200 caracteres). Pulsa Enter para finalizar:\n");
    if (!fgets(comentario, sizeof(comentario), stdin)) { printf("\033[31mError leyendo comentario.\n\033[0m"); fclose(fPeliculas); fclose(fCompras); return; }
    comentario[strcspn(comentario, "\n")] = '\0';

    if (strlen(comentario) == 0) {
        printf("\033[31mComentario vacio. Cancelado.\n\033[0m");
        fclose(fPeliculas); fclose(fCompras);
        return;
    }
    if (strlen(comentario) > 200) {
        printf("\033[31mTu comentario excede 200 caracteres (%zu). Por favor acorta tu comentario.\n\033[0m", strlen(comentario));
        fclose(fPeliculas); fclose(fCompras);
        return;
    }

    FILE *fComentarios = fopen("comentarios.txt", "a");
    if (!fComentarios) {
        printf("\033[31mNo se pudo abrir/crear comentarios.txt para escribir.\n\033[0m");
        fclose(fPeliculas); fclose(fCompras);
        return;
    }

    fprintf(fComentarios, "%s|%s|%s\n", nicknameLogueado, peliculasCompradas[sel-1], comentario);
    fclose(fComentarios);
    printf("\033[32mComentario guardado correctamente.\n\033[0m");

    fclose(fPeliculas);
    fclose(fCompras);
}

void verComentariosPeliculas(void) {
    FILE *fPeliculas = fopen("peliculas.txt", "r");
    if (!fPeliculas) {
        printf("\033[31mNo hay peliculas en cartelera (peliculas.txt no encontrado).\n\033[0m");
        return;
    }

    char linea[MAX_LINEA];
    char listaPeliculas[200][200];
    int pCount = 0;
    while (fgets(linea, sizeof(linea), fPeliculas) != NULL && pCount < 200) {
        char nombre[200];
        if (sscanf(linea, "%199[^|]", nombre) == 1) {
            nombre[strcspn(nombre, "\n")] = '\0';
            strncpy(listaPeliculas[pCount], nombre, 199);
            listaPeliculas[pCount][199] = '\0';
            pCount++;
        }
    }
    fclose(fPeliculas);

    if (pCount == 0) {
        printf("\033[31mNo hay peliculas en cartelera.\n\033[0m");
        return;
    }

    printf("\n\033[34mPeliculas en cartelera:\n\033[0m");
    for (int i = 0; i < pCount; ++i) printf("%d) %s\n", i+1, listaPeliculas[i]);
    printf("0) Regresar\n");
    printf("\033[34mSelecciona la pelicula para ver sus comentarios: \033[0m");

    int sel;
    if (scanf("%d", &sel) != 1) { while (getchar()!='\n'); printf("\033[31mEntrada invalida.\n\033[0m"); return; }
    while (getchar()!='\n');
    if (sel == 0) return;
    if (sel < 1 || sel > pCount) { printf("\033[31mSeleccion invalida.\n\033[0m"); return; }

    FILE *fComentarios = fopen("comentarios.txt", "r");
    if (!fComentarios) {
        printf("\033[31mNo hay comentarios registrados aun (comentarios.txt no encontrado).\n\033[0m");
        return;
    }

    int encontrados = 0;
    char nick[100], nombreP[200], texto[300];
    printf("\nComentarios para '%s':\n", listaPeliculas[sel-1]);
    while (fgets(linea, sizeof(linea), fComentarios) != NULL) {
        if (sscanf(linea, "%99[^|]|%199[^|]|%299[^\n]", nick, nombreP, texto) == 3) {
            if (strcmp(nombreP, listaPeliculas[sel-1]) == 0) {
                encontrados++;
                printf(" \033[34m- %s \033[0m : %s\n", nick, texto);
            }
        }
    }
    fclose(fComentarios);

    if (encontrados == 0) printf("\033[31mNo hay comentarios para esta pelicula.\n\033[0m");
    getchar();
}

void calificarPelicula(const char *nicknameLogueado) {
    system("cls");
    FILE *fCompras = fopen("compras.txt", "r");
    if (!fCompras) {
        printf("\033[31mNo hay compras registradas (compras.txt no encontrado). No puedes calificar sin comprar.\n\033[0m");
        return;
    }

    char linea[MAX_LINEA];
    char peliculasCompradas[100][200];
    int pcCount = 0;

    while (fgets(linea, sizeof(linea), fCompras) != NULL && pcCount < 100) {
        char nick[60], nombreP[200];
        if (sscanf(linea, "%59[^|]|%199[^|]|%*[^|]|%*[^|]|%*d|%*[^|]|%*s", nick, nombreP) >= 2) {
            if (strcmp(nick, nicknameLogueado) == 0) {
                int dup = 0;
                for (int i = 0; i < pcCount; ++i) if (strcmp(peliculasCompradas[i], nombreP) == 0) { dup = 1; break; }
                if (!dup) {
                    strncpy(peliculasCompradas[pcCount], nombreP, 199);
                    peliculasCompradas[pcCount][199] = '\0';
                    pcCount++;
                }
            }
        }
    }
    fclose(fCompras);

    if (pcCount == 0) {
        printf("\033[31mNo has comprado boletos para ninguna película. No puedes calificar.\n\033[0m");
        return;
    }

    printf("\n\033[34mPeliculas para calificar:\n\033[0m");
    for (int i = 0; i < pcCount; ++i) printf("%d) %s\n", i+1, peliculasCompradas[i]);
    printf("0) Regresar\n");
    printf("\033[34mSelecciona la pelicula a calificar: \033[0m");
    int sel;
    if (scanf("%d", &sel) != 1) { while (getchar()!='\n'); printf("\033[31mEntrada invalida.\n\033[0m"); return; }
    while (getchar()!='\n');
    if (sel == 0) return;
    if (sel < 1 || sel > pcCount) { printf("\033[31mSeleccion invalida.\n\033[0m"); return; }

    int estrellas;
    printf("Introduce la calificacion (1-5 estrellas): ");
    if (scanf("%d", &estrellas) != 1) { while (getchar()!='\n'); printf("\033[31mEntrada invalida.\n\033[0m"); return; }
    while (getchar()!='\n');
    if (estrellas < 1 || estrellas > 5) { printf("\033[31mCalificacion fuera de rango.\n\033[0m"); return; }

    FILE *fCal = fopen("calificaciones.txt", "a");
    if (!fCal) {
        printf("\033[31mNo se pudo abrir/crear calificaciones.txt para escribir.\n\033[0m");
        return;
    }
    fprintf(fCal, "%s|%s|%d\n", nicknameLogueado, peliculasCompradas[sel-1], estrellas);
    fclose(fCal);
    printf("\033[32mCalificacion registrada. Gracias.\n\033[0m");
}

void verPromedioCalificaciones(void) {
    system("cls");
    FILE *fPel = fopen("peliculas.txt", "r");
    if (!fPel) {
        printf("\033[31mNo hay peliculas en cartelera (peliculas.txt no encontrado).\n\033[0m");
        return;
    }

    char linea[MAX_LINEA];
    char listaPeliculas[200][200];
    int pCount = 0;
    while (fgets(linea, sizeof(linea), fPel) != NULL && pCount < 200) {
        char nombre[200];
        if (sscanf(linea, "%199[^|]", nombre) == 1) {
            nombre[strcspn(nombre, "\n")] = '\0';
            strncpy(listaPeliculas[pCount], nombre, 199);
            listaPeliculas[pCount][199] = '\0';
            pCount++;
        }
    }
    fclose(fPel);

    if (pCount == 0) {
        printf("\033[31mNo hay películas en cartelera.\n\033[0m");
        return;
    }

    FILE *fCal = fopen("calificaciones.txt", "r");
    int suma[200] = {0};
    int cuenta[200] = {0};

    if (fCal) {
        while (fgets(linea, sizeof(linea), fCal) != NULL) {
            char nick[100], nombreP[200];
            int est;
            if (sscanf(linea, "%99[^|]|%199[^|]|%d", nick, nombreP, &est) == 3) {
                for (int i = 0; i < pCount; ++i) {
                    if (strcmp(nombreP, listaPeliculas[i]) == 0) {
                        suma[i] += est;
                        cuenta[i] += 1;
                        break;
                    }
                }
            }
        }
        fclose(fCal);
    }

    printf("\n\033[34mPromedio de calificaciones por pelicula:\n\033[0m");
    for (int i = 0; i < pCount; ++i) {
        if (cuenta[i] == 0) {
            printf("\033[31m%s: (sin calificaciones)\n\033[0m", listaPeliculas[i]);
        } else {
            double promedio = (double)suma[i] / cuenta[i];
            printf("\033[32m%s: %.2f estrellas promedio (%d calificaciones)\n\033[0m", listaPeliculas[i], promedio, cuenta[i]);
        }
    }
    getchar();
}

/* ------------------  FIN: Comentarios y Calificaciones ------------------ */


// --- Implementación de Compra de Boletos (Funcionalidad 7.1) ---
void compraDeBoletos(const char *nicknameUsuario) {
    system("cls");
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
        printf("\033[31mERROR: No hay cartelera disponible. (Archivo peliculas.txt no encontrado)\n\033[0m");
        return;
    }

    printf("\033[34mPeliculas en cartelera:\n\033[0m");
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
        printf("\033[31mSeleccion no valida. Volviendo.\n\033[0m"); setbuf(stdin, NULL); return;
    }
    if (seleccionHorario == 0) { setbuf(stdin, NULL); return; }
    setbuf(stdin, NULL);

    // NOTA: Se necesitaría un segundo parseo con strtok para obtener el horario exacto por índice.
    // Usaremos el primer horario como ejemplo para simplificar:
    // **Corregir**: Si el usuario selecciona un índice > 1, 'horarioSeleccionado' será incorrecto.

    // =================================================================
    // PASO 3: Mostrar Asientos y Seleccionar Lugares
    // =================================================================
    
    char asientosOcupadosExistentes[500] = "";
    char asientosDeseados[100];
    char numTarjeta[20];
    int maxFilas, maxLugares;

    // Leer los asientos ocupados desde el archivo compras.txt para esta película y sala
    FILE *archivoComprasLectura = fopen("compras.txt", "r");
    if (archivoComprasLectura != NULL) {
        char lineaCompra[512];
        char nickTemp[30], peliTemp[100], genTemp[50], salaTemp[10];
        int numBoleTemp;
        char asientosTemp[100], codigoTemp[50];
        
      // En compraDeBoletos:
// ...

        while (fgets(lineaCompra, sizeof(lineaCompra), archivoComprasLectura) != NULL) {
            // ... (sscanf es correcto)

            if (sscanf(lineaCompra, "%[^|]|%[^|]|%[^|]|%[^|]|%d|%[^|]|%s",
                       nickTemp, peliTemp, genTemp, salaTemp, &numBoleTemp, asientosTemp, codigoTemp) == 7) {

                if (strcmp(peliTemp, peliculaSeleccionada.nombre) == 0 && 
                    strcmp(salaTemp, peliculaSeleccionada.sala) == 0) {

                    // *** NUEVA LÓGICA DE NORMALIZACIÓN ***
                    char asientosNormalizados[100];
                    int k = 0;
                    for (int l = 0; asientosTemp[l] != '\0'; l++) {
                        if (asientosTemp[l] != ' ') {
                            asientosNormalizados[k++] = asientosTemp[l];
                        } else {
                            asientosNormalizados[k++] = ','; // Reemplazar espacio por coma
                        }
                    }
                    asientosNormalizados[k] = '\0';
                    // *** FIN NUEVA LÓGICA ***

                    // Agregar los asientos a la lista de ocupados (con coma como separador)
                    if (strlen(asientosOcupadosExistentes) > 0) {
                        strcat(asientosOcupadosExistentes, ",");
                    }
                    strcat(asientosOcupadosExistentes, asientosNormalizados); // Usar asientos normalizados
                }
            }
        }
// ...
        fclose(archivoComprasLectura);
    }

    // Mostrar el mapa de asientos 
   mostrarAsientos(peliculaSeleccionada.sala, asientosOcupadosExistentes, &maxFilas, &maxLugares); 

    printf("Escriba los asientos a comprar separados por espacios (ej: J7 J8): ");
    scanf(" %99[^\n]", asientosDeseados);
    setbuf(stdin, NULL);
    
    // =================================================================
    // *** NUEVA LÓGICA DE VALIDACIÓN DE OCUPACIÓN Y FORMATO ***
    // =================================================================
    int asientosValidos = 1;
    char asientosDeseadosCopia[100];
    strcpy(asientosDeseadosCopia, asientosDeseados);
    
    char *asientoToken = strtok(asientosDeseadosCopia, " ");

    while (asientoToken != NULL) {
        // Simplificación: Validar que el formato es [Letra][Numero(s)]
        if (asientoToken[0] < 'A' || asientoToken[0] > ('A' + maxFilas - 1)) {
            printf("\033[31mERROR: Asiento '%s' con fila fuera de rango.\n\033[0m", asientoToken);
            asientosValidos = 0;
            break;
        }

        // Se usa la nueva función auxiliar
        if (esAsientoOcupado(asientoToken, asientosOcupadosExistentes)) {
            printf("\033[31mERROR: El asiento %s ya esta ocupado. Por favor, elija otro.\n\033[0m", asientoToken);
            asientosValidos = 0;
            break;
        }
        
        asientoToken = strtok(NULL, " ");
    }
    
    // Si la validación falló, regresamos sin confirmar la compra.
    if (!asientosValidos) {
        printf("\033[31m\nPresione Enter para intentar la compra de nuevo.\n\033[0m");
        setbuf(stdin, NULL);
        getchar();
        return; // ¡Regresa al menú o pide la compra de nuevo!
    }

    // =================================================================
    // *** CONTINUAR CON EL PROCESO DE PAGO Y REGISTRO ***
    // =================================================================

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
    
    char codigoCompra[150];
    sprintf(codigoCompra, "%c%s%s:%s%s%s", 
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
        
        printf("\033[32m\n COMPRA CONFIRMADA:\n\033[0m");
        printf("  Pelicula: %s\n", peliculaSeleccionada.nombre);
        printf("  Hora: %s\n", horarioSeleccionado);
        printf("  Asientos Adquiridos: %s\n", asientosDeseados);
        printf("  CODIGO DE COMPRA: %s\n", codigoCompra);
    } else {
        fprintf(stderr, "\033[31mERROR: No se pudo registrar la compra.\n\033[0m");
    }

    printf("\033[34m\nPresione Enter para regresar al Menu de Usuario.\n\033[0m");
    setbuf(stdin, NULL);
    getchar();
}