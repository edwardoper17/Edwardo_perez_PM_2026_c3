# Spec Delta

## Purpose

Administra el catálogo de vehículos y sus parámetros de costo, conservándolos entre ejecuciones del programa.

## ADDED Requirements

### Requirement: Crear un vehículo
El sistema SHALL permitir registrar un vehículo nuevo con nombre, marca, modelo, año, consumo de combustible en ciudad y carretera, costo anual de seguro, costo anual de impuestos, costo anual de limpieza, costo de neumáticos por km, costo de mantenimiento por km, valor inicial, valor final, tiempo de uso en años y kilómetros anuales.

#### Scenario: Registro exitoso
- **WHEN** el usuario elige crear un vehículo e ingresa todos los campos con valores válidos
- **THEN** el sistema guarda el vehículo y muestra el identificador asignado

#### Scenario: Identificador único
- **WHEN** el usuario crea un vehículo después de que ya existen otros vehículos
- **THEN** el sistema asigna un identificador entero autoincremental distinto a todos los existentes

### Requirement: Listar vehículos
El sistema SHALL mostrar todos los vehículos almacenados con su identificador y sus parámetros de costo.

#### Scenario: Catálogo vacío
- **WHEN** el usuario solicita listar vehículos y no hay ninguno registrado
- **THEN** el sistema informa que no hay vehículos

#### Scenario: Catálogo con vehículos
- **WHEN** el usuario solicita listar vehículos y existen registros
- **THEN** el sistema muestra cada vehículo con su identificador y parámetros

### Requirement: Editar un vehículo
El sistema SHALL permitir modificar los campos de un vehículo existente identificado por su identificador.

#### Scenario: Edición exitosa
- **WHEN** el usuario selecciona un vehículo existente y proporciona valores válidos para uno o más campos
- **THEN** el sistema actualiza el vehículo y conserva su identificador

#### Scenario: Vehículo inexistente
- **WHEN** el usuario intenta editar un identificador que no existe
- **THEN** el sistema muestra un mensaje de error y no modifica datos

### Requirement: Borrar un vehículo
El sistema SHALL permitir eliminar un vehículo identificado por su identificador.

#### Scenario: Borrado exitoso
- **WHEN** el usuario confirma el borrado de un vehículo existente
- **THEN** el sistema elimina el vehículo y lo excluye de listados y cálculos posteriores

#### Scenario: Vehículo inexistente
- **WHEN** el usuario intenta borrar un identificador que no existe
- **THEN** el sistema muestra un mensaje de error y no altera el catálogo

### Requirement: Validar los datos del vehículo
El sistema SHALL rechazar valores no numéricos o fuera de rango al crear o editar un vehículo, sin guardar el registro.

#### Scenario: Valor no numérico
- **WHEN** el usuario ingresa texto donde se espera un número
- **THEN** el sistema muestra un mensaje de error y vuelve a solicitar el dato

#### Scenario: Valores fuera de rango
- **WHEN** el usuario ingresa consumo menor o igual a cero, kilómetros anuales menores o iguales a cero, tiempo de uso menor o igual a cero, o valor final mayor que el valor inicial
- **THEN** el sistema rechaza el registro e indica el campo inválido

### Requirement: Persistir los vehículos
El sistema SHALL cargar los vehículos al iniciar y guardar los cambios en un archivo de datos local, de modo que se conserven entre ejecuciones.

#### Scenario: Carga al iniciar
- **WHEN** el programa inicia y el archivo de datos existe con vehículos guardados
- **THEN** el sistema los carga y los muestra en el listado

#### Scenario: Archivo inexistente
- **WHEN** el programa inicia y el archivo de datos no existe
- **THEN** el sistema comienza con el catálogo vacío y crea el archivo al guardar

#### Scenario: Persistencia tras cambios
- **WHEN** el usuario crea, edita o borra un vehículo y luego reinicia el programa
- **THEN** el catálogo conserva exactamente esos cambios
