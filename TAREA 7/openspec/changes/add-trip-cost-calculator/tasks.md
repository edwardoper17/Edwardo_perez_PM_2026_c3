# Tasks

## 1. Base del programa

- [x] 1.1 Crear el proyecto de Code::Blocks con `main.c`, las estructuras `Vehiculo` y `Cabecera`, y la constante `MAX_VEHICULOS`; verificar que compila y ejecuta sin errores.
- [x] 1.2 Implementar el menú principal con las opciones crear, listar, editar, borrar, calcular viaje, editar precio de combustible y salir; verificar que cada opción responde y que `0` termina el programa.

## 2. Entrada de datos y persistencia

- [x] 2.1 Implementar los auxiliares de lectura con `fgets` y `strtod`/`strtol`, aceptando coma o punto decimal; verificar que el texto inválido se rechaza y que `12,5` se interpreta como `12.5`.
- [x] 2.2 Implementar carga y guardado binario en `vehiculos.dat` con cabecera (magic, versión, precio, último id, cantidad); verificar que los datos sobreviven a un reinicio, que sin archivo arranca vacío y que un archivo corrupto se descarta con aviso.
- [x] 2.3 Implementar la validación de campos del vehículo (consumos > 0, km anuales > 0, tiempo de uso > 0, valor final <= inicial, año razonable); verificar que cada valor fuera de rango se rechaza indicando el campo.

## 3. Gestión de vehículos

- [x] 3.1 Implementar la creación de vehículos con identificador autoincremental; verificar que dos altas seguidas reciben ids distintos y que el registro aparece en el listado.
- [x] 3.2 Implementar el listado de vehículos; verificar que con catálogo vacío informa que no hay registros y que con datos muestra id y parámetros.
- [x] 3.3 Implementar la edición por identificador; verificar que conserva el id, actualiza solo los campos elegidos y que un id inexistente muestra error sin cambios.
- [x] 3.4 Implementar el borrado con confirmación; verificar que el vehículo desaparece del listado y sigue ausente tras reiniciar.

## 4. Precio del combustible y cálculo del viaje

- [x] 4.1 Implementar el precio de combustible global con valor por defecto, edición y persistencia; verificar que un valor inválido se rechaza y que el nuevo precio se usa en el cálculo siguiente.
- [x] 4.2 Implementar las funciones de cálculo (depreciación anual, costo fijo por km, combustible, costos variables, total y costo por km) según `design.md`; verificar con un ejemplo numérico calculado a mano.
- [x] 4.3 Implementar la pantalla de cálculo que pide id del vehículo, distancia y porcentaje en carretera; verificar que valida distancia > 0, porcentaje 0-100 y vehículo existente, y que muestra el desglose y el costo por km con dos decimales.
- [x] 4.4 Documentar en el código y en la memoria las fórmulas y el supuesto de prorrateo por kilómetros anuales; verificar que coinciden con `design.md`.

## 5. Integración y entrega

- [x] 5.1 Ejecutar un escenario completo (crear dos vehículos, calcular viaje mixto, solo ciudad y solo carretera, editar y borrar uno, reiniciar); verificar que los resultados y la persistencia coinciden con lo esperado.
- [x] 5.2 Compilar en Code::Blocks con advertencias visibles; verificar que no hay advertencias ni errores y que se informa al alcanzar el máximo de vehículos.

## Workflow follow-up

- Archivar el cambio cuando la tarea esté entregada y revisada.
- Verificar el resultado archivado y que `openspec/specs/` contiene las dos capacidades.
