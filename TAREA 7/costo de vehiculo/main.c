#include <stdio.h>
#include <string.h>

#define MAX_COMBUSTIBLES 20
#define MAX_VEHICULOS 20
#define MAX_NOMBRE 40

typedef struct {
    int id;
    char nombre[MAX_NOMBRE];
    double precio;
} Combustible;

typedef struct {
    int id;
    char nombre[MAX_NOMBRE];
    int idCombustible;
    double seguroAnual;
    double matriculaAnual;
    double precioCompra;
    double valorResidual;
    double vidaAnios;
    double limpiezaMes;
    double rendCiudad;
    double rendCarretera;
    double mantPorKm;
    double imprevistosAnual;
    double neumaticosPorKm;
    double mantPesadoCosto;
    double mantPesadoIntervalo;
    double kmAnual;
} Vehiculo;

Combustible combustibles[MAX_COMBUSTIBLES];
int numCombustibles = 0;
int siguienteIdCombustible = 1;

Vehiculo vehiculos[MAX_VEHICULOS];
int numVehiculos = 0;
int siguienteIdVehiculo = 1;

int leerEntero(const char *mensaje, int *valor)
{
    char linea[128];
    printf("%s", mensaje);
    if (fgets(linea, sizeof(linea), stdin) == NULL)
        return -1;
    if (sscanf(linea, "%d", valor) != 1)
        return 0;
    return 1;
}

int leerDouble(const char *mensaje, double *valor)
{
    char linea[128];
    printf("%s", mensaje);
    if (fgets(linea, sizeof(linea), stdin) == NULL)
        return -1;
    if (sscanf(linea, "%lf", valor) != 1)
        return 0;
    return 1;
}

void leerTexto(const char *mensaje, char *destino, int tam)
{
    char linea[256];
    printf("%s", mensaje);
    if (fgets(linea, sizeof(linea), stdin) == NULL) {
        destino[0] = '\0';
        return;
    }
    linea[strcspn(linea, "\r\n")] = '\0';
    strncpy(destino, linea, (size_t)(tam - 1));
    destino[tam - 1] = '\0';
}

int pedirPositivo(const char *campo, double *destino)
{
    double valor;
    char mensaje[128];
    snprintf(mensaje, sizeof(mensaje), "  %s: ", campo);
    if (leerDouble(mensaje, &valor) != 1) {
        printf("  Error: %s debe ser un numero.\n", campo);
        return 0;
    }
    if (valor <= 0) {
        printf("  Error: %s debe ser mayor que cero.\n", campo);
        return 0;
    }
    *destino = valor;
    return 1;
}

int pedirNoNegativo(const char *campo, double *destino)
{
    double valor;
    char mensaje[128];
    snprintf(mensaje, sizeof(mensaje), "  %s: ", campo);
    if (leerDouble(mensaje, &valor) != 1) {
        printf("  Error: %s debe ser un numero.\n", campo);
        return 0;
    }
    if (valor < 0) {
        printf("  Error: %s no puede ser negativo.\n", campo);
        return 0;
    }
    *destino = valor;
    return 1;
}

Combustible *buscarCombustiblePorId(int id)
{
    int i;
    for (i = 0; i < numCombustibles; i++) {
        if (combustibles[i].id == id)
            return &combustibles[i];
    }
    return NULL;
}

Vehiculo *buscarVehiculoPorId(int id)
{
    int i;
    for (i = 0; i < numVehiculos; i++) {
        if (vehiculos[i].id == id)
            return &vehiculos[i];
    }
    return NULL;
}

int existeNombreCombustible(const char *nombre, int idExcluir)
{
    int i;
    for (i = 0; i < numCombustibles; i++) {
        if (combustibles[i].id != idExcluir &&
            strcmp(combustibles[i].nombre, nombre) == 0)
            return 1;
    }
    return 0;
}

int existeNombreVehiculo(const char *nombre, int idExcluir)
{
    int i;
    for (i = 0; i < numVehiculos; i++) {
        if (vehiculos[i].id != idExcluir &&
            strcmp(vehiculos[i].nombre, nombre) == 0)
            return 1;
    }
    return 0;
}

int combustibleEnUso(int id)
{
    int i;
    for (i = 0; i < numVehiculos; i++) {
        if (vehiculos[i].idCombustible == id)
            return 1;
    }
    return 0;
}

void listarCombustibles(void)
{
    int i;
    if (numCombustibles == 0) {
        printf("No hay tipos de combustible registrados.\n");
        return;
    }
    printf("\n%-4s %-30s %10s\n", "ID", "Nombre", "Precio");
    for (i = 0; i < numCombustibles; i++) {
        printf("%-4d %-30s %10.2f\n", combustibles[i].id,
               combustibles[i].nombre, combustibles[i].precio);
    }
}

void listarVehiculos(void)
{
    int i;
    if (numVehiculos == 0) {
        printf("No hay vehiculos registrados.\n");
        return;
    }
    printf("\n%-4s %-25s %-20s\n", "ID", "Nombre", "Combustible");
    for (i = 0; i < numVehiculos; i++) {
        Combustible *c = buscarCombustiblePorId(vehiculos[i].idCombustible);
        const char *nombreComb = (c != NULL) ? c->nombre : "(desconocido)";
        printf("%-4d %-25s %-20s\n", vehiculos[i].id,
               vehiculos[i].nombre, nombreComb);
    }
}

void altaCombustible(void)
{
    char nombre[MAX_NOMBRE];
    double precio;

    if (numCombustibles >= MAX_COMBUSTIBLES) {
        printf("Error: se alcanzo la capacidad maxima de combustibles.\n");
        return;
    }
    leerTexto("Nombre del combustible: ", nombre, (int)sizeof(nombre));
    if (nombre[0] == '\0') {
        printf("Error: el nombre no puede estar vacio.\n");
        return;
    }
    if (existeNombreCombustible(nombre, -1)) {
        printf("Error: el nombre esta repetido.\n");
        return;
    }
    if (leerDouble("Precio por unidad: ", &precio) != 1) {
        printf("Error: precio invalido.\n");
        return;
    }
    if (precio <= 0) {
        printf("Error: el precio debe ser mayor que cero.\n");
        return;
    }
    combustibles[numCombustibles].id = siguienteIdCombustible++;
    strncpy(combustibles[numCombustibles].nombre, nombre, MAX_NOMBRE - 1);
    combustibles[numCombustibles].nombre[MAX_NOMBRE - 1] = '\0';
    combustibles[numCombustibles].precio = precio;
    numCombustibles++;
    printf("Combustible registrado con id %d.\n",
           combustibles[numCombustibles - 1].id);
}

void editarCombustible(void)
{
    int id;
    char nombre[MAX_NOMBRE];
    double precio;
    Combustible *c;

    if (numCombustibles == 0) {
        printf("No hay tipos de combustible registrados.\n");
        return;
    }
    listarCombustibles();
    if (leerEntero("Id del combustible a editar: ", &id) != 1) {
        printf("Entrada invalida.\n");
        return;
    }
    c = buscarCombustiblePorId(id);
    if (c == NULL) {
        printf("Error: el tipo no fue encontrado.\n");
        return;
    }
    leerTexto("Nuevo nombre: ", nombre, (int)sizeof(nombre));
    if (nombre[0] == '\0') {
        printf("Error: el nombre no puede estar vacio.\n");
        return;
    }
    if (existeNombreCombustible(nombre, id)) {
        printf("Error: el nombre esta repetido.\n");
        return;
    }
    if (leerDouble("Nuevo precio por unidad: ", &precio) != 1) {
        printf("Error: precio invalido.\n");
        return;
    }
    if (precio <= 0) {
        printf("Error: el precio debe ser mayor que cero.\n");
        return;
    }
    strncpy(c->nombre, nombre, MAX_NOMBRE - 1);
    c->nombre[MAX_NOMBRE - 1] = '\0';
    c->precio = precio;
    printf("Combustible actualizado.\n");
}

void borrarCombustible(void)
{
    int id;
    int i;
    Combustible *c;

    if (numCombustibles == 0) {
        printf("No hay tipos de combustible registrados.\n");
        return;
    }
    listarCombustibles();
    if (leerEntero("Id del combustible a borrar: ", &id) != 1) {
        printf("Entrada invalida.\n");
        return;
    }
    c = buscarCombustiblePorId(id);
    if (c == NULL) {
        printf("Error: el tipo no fue encontrado.\n");
        return;
    }
    if (combustibleEnUso(id)) {
        printf("Error: el combustible esta en uso por al menos un vehiculo.\n");
        return;
    }
    for (i = (int)(c - combustibles); i < numCombustibles - 1; i++)
        combustibles[i] = combustibles[i + 1];
    numCombustibles--;
    printf("Combustible eliminado.\n");
}

void menuCombustibles(void)
{
    int opcion;
    for (;;) {
        printf("\n--- Combustibles ---\n");
        printf("1. Alta\n");
        printf("2. Editar\n");
        printf("3. Borrar\n");
        printf("4. Listar\n");
        printf("0. Volver\n");
        int r = leerEntero("Opcion: ", &opcion);
        if (r < 0)
            return;
        if (r == 0) {
            printf("Entrada invalida.\n");
            continue;
        }
        switch (opcion) {
        case 1:
            altaCombustible();
            break;
        case 2:
            editarCombustible();
            break;
        case 3:
            borrarCombustible();
            break;
        case 4:
            listarCombustibles();
            break;
        case 0:
            return;
        default:
            printf("Opcion fuera de rango.\n");
            break;
        }
    }
}

int capturarDatosVehiculo(Vehiculo *v)
{
    int idc;

    listarCombustibles();
    if (leerEntero("Id del combustible: ", &idc) != 1) {
        printf("Entrada invalida.\n");
        return 0;
    }
    if (buscarCombustiblePorId(idc) == NULL) {
        printf("Error: el combustible no fue encontrado.\n");
        return 0;
    }
    v->idCombustible = idc;
    if (!pedirPositivo("Seguro anual", &v->seguroAnual))
        return 0;
    if (!pedirPositivo("Matricula e impuestos anual", &v->matriculaAnual))
        return 0;
    if (!pedirPositivo("Precio de compra", &v->precioCompra))
        return 0;
    if (!pedirNoNegativo("Valor residual", &v->valorResidual))
        return 0;
    if (!pedirPositivo("Vida util en anios", &v->vidaAnios))
        return 0;
    if (!pedirPositivo("Limpieza mensual", &v->limpiezaMes))
        return 0;
    if (!pedirPositivo("Rendimiento ciudad (km/unidad)", &v->rendCiudad))
        return 0;
    if (!pedirPositivo("Rendimiento carretera (km/unidad)", &v->rendCarretera))
        return 0;
    if (!pedirPositivo("Mantenimiento por km", &v->mantPorKm))
        return 0;
    if (!pedirPositivo("Imprevistos anuales", &v->imprevistosAnual))
        return 0;
    if (!pedirPositivo("Neumaticos por km", &v->neumaticosPorKm))
        return 0;
    if (!pedirPositivo("Costo mantenimiento pesado", &v->mantPesadoCosto))
        return 0;
    if (!pedirPositivo("Intervalo mantenimiento pesado (km)", &v->mantPesadoIntervalo))
        return 0;
    if (!pedirPositivo("Kilometros anuales estimados", &v->kmAnual))
        return 0;
    return 1;
}

void altaVehiculo(void)
{
    char nombre[MAX_NOMBRE];
    Vehiculo v;

    if (numVehiculos >= MAX_VEHICULOS) {
        printf("Error: se alcanzo la capacidad maxima de vehiculos.\n");
        return;
    }
    if (numCombustibles == 0) {
        printf("Error: registre primero un tipo de combustible.\n");
        return;
    }
    leerTexto("Nombre del vehiculo: ", nombre, (int)sizeof(nombre));
    if (nombre[0] == '\0') {
        printf("Error: el nombre no puede estar vacio.\n");
        return;
    }
    if (existeNombreVehiculo(nombre, -1)) {
        printf("Error: el nombre esta repetido.\n");
        return;
    }
    if (!capturarDatosVehiculo(&v)) {
        printf("Alta cancelada.\n");
        return;
    }
    v.id = siguienteIdVehiculo++;
    strncpy(v.nombre, nombre, MAX_NOMBRE - 1);
    v.nombre[MAX_NOMBRE - 1] = '\0';
    vehiculos[numVehiculos] = v;
    numVehiculos++;
    printf("Vehiculo registrado con id %d.\n", v.id);
}

void editarVehiculo(void)
{
    int id;
    char nombre[MAX_NOMBRE];
    Vehiculo *v;
    Vehiculo temp;

    if (numVehiculos == 0) {
        printf("No hay vehiculos registrados.\n");
        return;
    }
    listarVehiculos();
    if (leerEntero("Id del vehiculo a editar: ", &id) != 1) {
        printf("Entrada invalida.\n");
        return;
    }
    v = buscarVehiculoPorId(id);
    if (v == NULL) {
        printf("Error: el vehiculo no fue encontrado.\n");
        return;
    }
    leerTexto("Nuevo nombre: ", nombre, (int)sizeof(nombre));
    if (nombre[0] == '\0') {
        printf("Error: el nombre no puede estar vacio.\n");
        return;
    }
    if (existeNombreVehiculo(nombre, id)) {
        printf("Error: el nombre esta repetido.\n");
        return;
    }
    temp = *v;
    if (!capturarDatosVehiculo(&temp)) {
        printf("Edicion cancelada.\n");
        return;
    }
    strncpy(temp.nombre, nombre, MAX_NOMBRE - 1);
    temp.nombre[MAX_NOMBRE - 1] = '\0';
    *v = temp;
    printf("Vehiculo actualizado.\n");
}

void borrarVehiculo(void)
{
    int id;
    int i;
    Vehiculo *v;

    if (numVehiculos == 0) {
        printf("No hay vehiculos registrados.\n");
        return;
    }
    listarVehiculos();
    if (leerEntero("Id del vehiculo a borrar: ", &id) != 1) {
        printf("Entrada invalida.\n");
        return;
    }
    v = buscarVehiculoPorId(id);
    if (v == NULL) {
        printf("Error: el vehiculo no fue encontrado.\n");
        return;
    }
    for (i = (int)(v - vehiculos); i < numVehiculos - 1; i++)
        vehiculos[i] = vehiculos[i + 1];
    numVehiculos--;
    printf("Vehiculo eliminado.\n");
}

void menuVehiculos(void)
{
    int opcion;
    for (;;) {
        printf("\n--- Vehiculos ---\n");
        printf("1. Alta\n");
        printf("2. Editar\n");
        printf("3. Borrar\n");
        printf("4. Listar\n");
        printf("0. Volver\n");
        int r = leerEntero("Opcion: ", &opcion);
        if (r < 0)
            return;
        if (r == 0) {
            printf("Entrada invalida.\n");
            continue;
        }
        switch (opcion) {
        case 1:
            altaVehiculo();
            break;
        case 2:
            editarVehiculo();
            break;
        case 3:
            borrarVehiculo();
            break;
        case 4:
            listarVehiculos();
            break;
        case 0:
            return;
        default:
            printf("Opcion fuera de rango.\n");
            break;
        }
    }
}

void calcularViaje(void)
{
    int id;
    double km;
    double porcentaje;
    double depAnual;
    double fijoPorKm;
    double compartidoKm;
    double costoCiudadKm;
    double costoCarrKm;
    double kmCiudad;
    double kmCarretera;
    double costoTotal;
    double costoPorKm;
    Vehiculo *v;
    Combustible *c;

    if (numVehiculos == 0) {
        printf("No hay vehiculos registrados.\n");
        return;
    }
    listarVehiculos();
    if (leerEntero("Id del vehiculo: ", &id) != 1) {
        printf("Entrada invalida.\n");
        return;
    }
    v = buscarVehiculoPorId(id);
    if (v == NULL) {
        printf("Error: el vehiculo no fue encontrado.\n");
        return;
    }
    c = buscarCombustiblePorId(v->idCombustible);
    if (c == NULL) {
        printf("Error: el combustible del vehiculo no fue encontrado.\n");
        return;
    }
    if (leerDouble("Kilometros del viaje: ", &km) != 1) {
        printf("Entrada invalida.\n");
        return;
    }
    if (km <= 0) {
        printf("Error: los kilometros deben ser mayores que cero.\n");
        return;
    }
    if (leerDouble("Porcentaje en ciudad (0-100): ", &porcentaje) != 1) {
        printf("Entrada invalida.\n");
        return;
    }
    if (porcentaje < 0 || porcentaje > 100) {
        printf("Error: el porcentaje debe estar entre 0 y 100.\n");
        return;
    }
    depAnual = (v->precioCompra - v->valorResidual) / v->vidaAnios;
    fijoPorKm = (v->seguroAnual + v->matriculaAnual + v->imprevistosAnual +
                 12.0 * v->limpiezaMes + depAnual) / v->kmAnual;
    compartidoKm = v->mantPorKm + v->neumaticosPorKm +
                   v->mantPesadoCosto / v->mantPesadoIntervalo + fijoPorKm;
    costoCiudadKm = c->precio / v->rendCiudad + compartidoKm;
    costoCarrKm = c->precio / v->rendCarretera + compartidoKm;
    kmCiudad = km * porcentaje / 100.0;
    kmCarretera = km - kmCiudad;
    costoTotal = kmCiudad * costoCiudadKm + kmCarretera * costoCarrKm;
    costoPorKm = costoTotal / km;

    printf("\n--- Resultado del viaje ---\n");
    printf("Km ciudad: %.2f\n", kmCiudad);
    printf("Km carretera: %.2f\n", kmCarretera);
    printf("Costo fijo por km: %.2f\n", fijoPorKm);
    printf("Costo total: %.2f\n", costoTotal);
    printf("Costo por km: %.2f\n", costoPorKm);
}

int main(void)
{
    int opcion;
    for (;;) {
        printf("\n=== Costo de vehiculo por viaje ===\n");
        printf("1. Combustibles\n");
        printf("2. Vehiculos\n");
        printf("3. Calcular viaje\n");
        printf("4. Salir\n");
        int r = leerEntero("Opcion: ", &opcion);
        if (r < 0)
            break;
        if (r == 0) {
            printf("Entrada invalida.\n");
            continue;
        }
        switch (opcion) {
        case 1:
            menuCombustibles();
            break;
        case 2:
            menuVehiculos();
            break;
        case 3:
            calcularViaje();
            break;
        case 4:
            printf("Saliendo...\n");
            return 0;
        default:
            printf("Opcion fuera de rango.\n");
            break;
        }
    }
    return 0;
}
