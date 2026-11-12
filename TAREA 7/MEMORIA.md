# TAREA 7 - Costo de un viaje por vehiculo

Programa de consola en C que administra vehiculos y calcula el costo de un
viaje y el costo por kilometro.

## Como compilar y ejecutar

- Abrir `TAREA 7.cbp` en Code::Blocks y compilar (Build and run), o
- `gcc -Wall -Wextra -std=c11 -o "TAREA 7.exe" main.c` y ejecutar.

El programa crea `vehiculos.dat` en el directorio de trabajo para guardar los
vehiculos y el precio del combustible entre ejecuciones.

## Datos de cada vehiculo

| Campo | Unidad |
|---|---|
| Consumo en ciudad | km/L |
| Consumo en carretera | km/L |
| Seguro anual | RD$/anio |
| Impuestos anuales | RD$/anio |
| Limpieza anual | RD$/anio |
| Neumaticos | RD$/km |
| Mantenimiento | RD$/km |
| Valor inicial | RD$ |
| Valor final | RD$ |
| Tiempo de uso | anios |
| Kilometros anuales | km/anio |

## Formulas

```
dep_anual     = (valor_inicial - valor_final) / tiempo_uso
fijos_anual   = seguro + impuestos + limpieza + dep_anual
costo_fijo_km = fijos_anual / km_anuales

km_carretera  = distancia * pct_carretera / 100
km_ciudad     = distancia - km_carretera

combustible   = (km_ciudad / consumo_ciudad
                 + km_carretera / consumo_carretera) * precio_combustible
variables     = distancia * (neumaticos_km + mantenimiento_km)
fijos_viaje   = distancia * costo_fijo_km

costo_viaje   = combustible + variables + fijos_viaje
costo_km      = costo_viaje / distancia
```

## Supuesto de prorrateo

Los costos anuales (seguro, impuestos, limpieza y depreciacion) se reparten
entre los kilometros que el vehiculo recorre al anio (`km_anuales`). Por eso el
costo fijo asignado a un viaje es un promedio y no el costo marginal exacto de
ese recorrido. Este supuesto es el mismo documentado en `design.md`.

## Ejemplo verificado

Vehiculo: consumo 12.5 km/L ciudad y 18 km/L carretera, seguro RD$25,000,
impuestos RD$12,000, limpieza RD$6,000, neumaticos RD$1.50/km,
mantenimiento RD$0.80/km, valor inicial RD$900,000, valor final RD$300,000,
tiempo de uso 5 anios, km anuales 20,000; combustible RD$75/L.

Viaje de 100 km con 60 % en carretera:

```
dep_anual     = (900000 - 300000) / 5 = 120000
fijos_anual   = 25000 + 12000 + 6000 + 120000 = 163000
costo_fijo_km = 163000 / 20000 = 8.15
combustible   = (40/12.5 + 60/18) * 75 = 490.00
variables     = 100 * (1.5 + 0.8) = 230.00
fijos_viaje   = 100 * 8.15 = 815.00
costo_viaje   = 490.00 + 230.00 + 815.00 = 1535.00
costo_km      = 1535.00 / 100 = 15.35
```
