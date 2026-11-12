# Design

## Context

Proyecto nuevo y vacío salvo la configuración de OpenSpec. Ver `proposal.md` para la motivación. Restricciones que moldean el diseño: lenguaje C, compilador gcc/MinGW dentro de Code::Blocks en Windows, ejecución por consola, sin dependencias externas, y uso académico donde la claridad del código pesa más que la sofisticación.

## Goals / Non-Goals

**Goals:**
- Un ejecutable de consola con menú que cubra CRUD de vehículos, configuración del combustible y cálculo de viaje.
- Persistencia simple y confiable entre ejecuciones.
- Validación de entradas que evite divisiones entre cero y resultados inválidos.
- Código legible, en español, compilable sin flags especiales.

**Non-Goals:**
- Interfaz gráfica, base de datos, múltiples usuarios o concurrencia.
- Datos históricos de viajes, reportes o exportación a CSV.
- Precisión financiera con aritmética de punto fijo; se usa `double` con dos decimales al mostrar.
- Múltiples precios de combustible por tipo (gasolina/diésel).

## Decisions

### Programa de un solo archivo `main.c`
Todo el código vive en `main.c` con funciones estáticas auxiliares, más el archivo de datos generado en ejecución.

- **Por qué**: Code::Blocks crea un proyecto con un `main.c`; un solo archivo evita configurar enlaces y es fácil de entregar.
- **Alternativas**: módulos separados (`vehiculo.c`, `calculo.c`). Se descarta por tamaño manejable y para reducir fricción en la entrega; si el archivo crece demasiado, se puede dividir después sin cambiar el comportamiento.

### Estructura `Vehiculo` con arreglos de caracteres de tamaño fijo
```c
typedef struct {
    int    id;
    char   nombre[40];
    char   marca[30];
    char   modelo[30];
    int    anio;
    double consumo_ciudad;      /* km/L */
    double consumo_carretera;   /* km/L */
    double seguro_anual;        /* RD$/anio */
    double impuestos_anuales;   /* RD$/anio */
    double limpieza_anual;      /* RD$/anio */
    double neumaticos_km;       /* RD$/km */
    double mantenimiento_km;    /* RD$/km */
    double valor_inicial;       /* RD$ */
    double valor_final;         /* RD$ */
    double tiempo_uso;          /* anios */
    double km_anuales;          /* km/anio */
} Vehiculo;
```
- **Por qué**: evita `malloc`/`free` y los errores de memoria típicos en un curso introductorio.
- **Alternativas**: cadenas dinámicas. Se descartan por complejidad innecesaria.

### Arreglo fijo con capacidad máxima
`#define MAX_VEHICULOS 100` y un contador en memoria.
- **Por qué**: administración trivial y sin realloc.
- **Riesgo**: al llenarse se informa al usuario; suficiente para la tarea.

### Persistencia en un archivo binario `vehiculos.dat`
Un encabezado con magic, versión, precio de combustible, último id y cantidad de vehículos, seguido de los registros.
```c
typedef struct {
    char   magic[8];        /* "VEHICOST" o similar */
    int    version;         /* 1 */
    double precio_combustible;
    int    ultimo_id;
    int    cantidad;
} Cabecera;
```
- **Por qué**: `fread`/`fwrite` de estructuras es directo y no requiere parsear texto; el usuario no edita el archivo.
- **Alternativas**: CSV de texto. Se descarta porque exige parseo y manejo de errores de formato; se reconsidera si se pide inspeccionar los datos a mano.
- **Mitigación de corrupción**: si magic, versión o cantidad no son válidos, se ignora el contenido y se arranca vacío con aviso.

### Validación con `fgets` + `strtod`/`strtol`
Se leen líneas completas y se convierten; se acepta coma o punto decimal reemplazando la coma por punto antes de convertir.
- **Por qué**: `scanf("%lf")` deja basura en el buffer y rompe el menú; `fgets` es robusto.
- **Consecuencia**: entradas con separador decimal local funcionan sin depender de `setlocale`.

### Dinero en `double` y redondeo al mostrar
- **Por qué**: simplicidad; el resultado se presenta con `%.2f`.
- **Alternativa**: centavos como enteros. Se descarta por ruido en una tarea académica.

### Costos fijos prorrateados por kilómetros anuales
```
dep_anual   = (valor_inicial - valor_final) / tiempo_uso
fijos_anual = seguro + impuestos + limpieza + dep_anual
costo_fijo_km = fijos_anual / km_anuales
```
- **Por qué**: es la única forma coherente de convertir costos anuales en costo por km sin inventar la duración del viaje.
- **Consecuencia**: el costo fijo asignado es un promedio; se documenta en la memoria de la tarea.

### Flujo de cálculo
```
km_car = D * pct_car / 100
km_ciu = D - km_car
combustible = (km_ciu / cons_ciu + km_car / cons_car) * precio_L
variables   = D * (neumaticos_km + mantenimiento_km)
fijos       = D * costo_fijo_km
total       = combustible + variables + fijos
costo_km    = total / D
```

## Risks / Trade-offs

- [Archivo binario incompatible si cambia la estructura] → campo `version` en la cabecera; si no coincide, se descarta el archivo con aviso y se empieza vacío.
- [Alineación/padding del struct distinta entre compiladores] → se compila siempre con el mismo toolchain de Code::Blocks; aceptable para la entrega.
- [División entre cero] → validaciones en captura y en cálculo; `km_anuales`, consumos, `tiempo_uso` y distancia deben ser mayores que cero.
- [Precisión de `double`] → solo se muestran dos decimales; no se comparan montos por igualdad.
- [Capacidad fija de 100 vehículos] → mensaje claro al intentar crear más.
- [Entrada con coma decimal] → se normaliza antes de `strtod`; se documenta en la ayuda del menú.

## Migration Plan

Proyecto nuevo: no hay migración. Para revertir, se eliminan `main.c` y `vehiculos.dat`. El archivo de datos se crea en la primera ejecución con `precio_combustible` por defecto.

## Open Questions

Ninguna pendiente que afecte specs, enfoque o desglose de tareas.
