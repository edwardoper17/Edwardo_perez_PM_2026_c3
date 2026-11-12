# Spec Delta

## Purpose

Calcula el costo total de un viaje en un vehículo y el costo por kilómetro, combinando combustible, desgaste y costos anuales prorrateados.

## ADDED Requirements

### Requirement: Configurar el precio del combustible
El sistema SHALL mantener un precio de combustible global en RD$ por litro, editable desde el menú y persistido entre ejecuciones.

#### Scenario: Precio inicial
- **WHEN** el programa inicia sin un precio de combustible guardado
- **THEN** el sistema usa un precio por defecto y permite cambiarlo

#### Scenario: Cambio de precio
- **WHEN** el usuario ingresa un precio de combustible mayor que cero
- **THEN** el sistema lo guarda y lo usa en los cálculos siguientes

#### Scenario: Precio inválido
- **WHEN** el usuario ingresa un precio de combustible menor o igual a cero o no numérico
- **THEN** el sistema rechaza el valor y conserva el precio anterior

### Requirement: Solicitar los datos del viaje
El sistema SHALL solicitar la distancia total en kilómetros y el porcentaje del recorrido en carretera, calculando el porcentaje en ciudad como el complemento.

#### Scenario: Entradas válidas
- **WHEN** el usuario ingresa una distancia mayor que cero y un porcentaje en carretera entre 0 y 100
- **THEN** el sistema calcula los kilómetros en carretera y en ciudad sobre la distancia total

#### Scenario: Distancia inválida
- **WHEN** el usuario ingresa una distancia menor o igual a cero
- **THEN** el sistema muestra un error y no calcula el viaje

#### Scenario: Porcentaje inválido
- **WHEN** el usuario ingresa un porcentaje menor que 0 o mayor que 100
- **THEN** el sistema muestra un error y no calcula el viaje

### Requirement: Calcular el costo de combustible
El sistema SHALL calcular el costo de combustible separando los kilómetros de ciudad y de carretera según el consumo correspondiente del vehículo y el precio global por litro.

#### Scenario: Viaje mixto
- **WHEN** el viaje tiene porcentaje en carretera mayor que cero y menor que 100
- **THEN** el costo de combustible es la suma del gasto en ciudad y en carretera a sus consumos respectivos

#### Scenario: Viaje solo en ciudad
- **WHEN** el porcentaje en carretera es 0
- **THEN** todo el combustible se calcula con el consumo en ciudad

#### Scenario: Viaje solo en carretera
- **WHEN** el porcentaje en carretera es 100
- **THEN** todo el combustible se calcula con el consumo en carretera

### Requirement: Calcular los costos variables
El sistema SHALL calcular los costos variables del viaje multiplicando la distancia total por la suma del costo de neumáticos por km y el costo de mantenimiento por km del vehículo.

#### Scenario: Costos variables del viaje
- **WHEN** el sistema calcula un viaje con un vehículo seleccionado
- **THEN** los costos variables equivalen a la distancia total por la suma de ambos costos por km

### Requirement: Prorratear los costos fijos anuales
El sistema SHALL calcular un costo fijo por kilómetro dividiendo la suma del seguro anual, impuestos anuales, limpieza anual y depreciación anual entre los kilómetros anuales del vehículo.

#### Scenario: Depreciación anual
- **WHEN** el sistema calcula los costos fijos de un vehículo
- **THEN** la depreciación anual equivale a la diferencia entre valor inicial y valor final dividida entre el tiempo de uso en años

#### Scenario: Costo fijo del viaje
- **WHEN** el sistema calcula un viaje
- **THEN** el costo fijo asignado equivale a la distancia total por el costo fijo por kilómetro

#### Scenario: Kilómetros anuales inválidos
- **WHEN** el vehículo tiene kilómetros anuales menores o iguales a cero
- **THEN** el sistema no calcula el viaje e indica que los datos del vehículo son inválidos

### Requirement: Mostrar el costo del viaje y el costo por kilómetro
El sistema SHALL mostrar el costo total del viaje, el costo por kilómetro y el desglose de combustible, costos variables y costos fijos, en RD$ con dos decimales.

#### Scenario: Resultado completo
- **WHEN** el cálculo del viaje termina con datos válidos
- **THEN** el sistema muestra el costo total, el costo por kilómetro y el desglose de los tres componentes

#### Scenario: Costo por kilómetro
- **WHEN** el sistema calcula un viaje con distancia mayor que cero
- **THEN** el costo por kilómetro equivale al costo total del viaje dividido entre la distancia total

#### Scenario: Vehículo inexistente
- **WHEN** el usuario selecciona un identificador de vehículo que no existe
- **THEN** el sistema muestra un error y no calcula el viaje
