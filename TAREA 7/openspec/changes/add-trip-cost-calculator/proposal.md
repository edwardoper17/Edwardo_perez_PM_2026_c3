# Proposal

## Why

La TAREA 7 requiere un programa en C que calcule el costo real de un viaje en vehículo y su costo por kilómetro, considerando combustible, desgaste, seguros, impuestos y depreciación. Sin una herramienta que concentre esos parámetros por vehículo, el estudiante tendría que recalcular todo a mano y no podría comparar vehículos ni conservar los datos entre ejecuciones.

## What Changes

- Se crea un programa de consola en C (Code::Blocks) con menú interactivo.
- Se agrega la gestión de vehículos: crear, listar, editar y borrar, con un identificador autoincremental.
- Se agrega el cálculo del costo de un viaje a partir de la distancia total y el porcentaje recorrido en carretera (el resto en ciudad).
- El costo del viaje se descompone en combustible, costos variables (neumáticos y mantenimiento), y costos fijos prorrateados (seguro, impuestos, limpieza y depreciación) usando los kilómetros anuales del vehículo.
- Se agrega un precio de combustible global (RD$/L) editable desde el menú.
- Los vehículos y la configuración se persisten en un archivo binario `vehiculos.dat` para conservarlos entre ejecuciones.
- Se validan entradas numéricas y porcentajes para evitar resultados inválidos.

## Capabilities

### New Capabilities
- `vehicle-management`: alta, listado, edición y borrado de vehículos con sus parámetros de costo, más persistencia en disco.
- `trip-cost-calculation`: cálculo del costo total del viaje y del costo por kilómetro a partir de la distancia y el reparto ciudad/carretera.

### Modified Capabilities
<!-- Ninguna: el proyecto no tiene specs existentes. -->

## Impact

- Nuevo código fuente en C dentro de `TAREA 7`, compilable con Code::Blocks (gcc/MinGW).
- Nuevo archivo de datos `vehiculos.dat` generado en tiempo de ejecución.
- No afecta otros proyectos ni tareas del repositorio.
- Moneda de trabajo: peso dominicano (RD$); unidades de distancia en km y consumo en km/L.
