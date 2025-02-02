# Philosophers 🍽️

**Philosophers** es un proyecto en C que simula el problema de los filósofos comensales.
El objetivo es implementar un programa que modele a varios filósofos sentados en una mesa, cada uno con un tenedor a su izquierda y a su derecha, tratando de comer sin que haya bloqueos ni condiciones de carrera.

Este proyecto pone a prueba tu comprensión de los **hilos** (`threads`), **mutexes** y **sincronización** en programación concurrente. 💻

## Funcionalidades ✨

- **Simulación de filósofos comensales**: Los filósofos piensan, comen y alternan entre estos dos estados. Cada filósofo necesita dos tenedores para comer.
- **Control de hilos**: Cada filósofo es un hilo que interactúa con otros hilos para obtener los tenedores y comer.
- **Sincronización**: Se implementan mecanismos de sincronización para evitar problemas de condiciones de carrera y bloqueos (deadlock). 🔒
- **Parámetros de simulación**: El número de filósofos, el tiempo de vida y los tiempos de espera se pueden ajustar al inicio de la simulación. ⏱️

## Instalación y uso 🚀
```bash
make
```
Se usa de la siguiente forma:
```bash
./philosophers <num_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [optional: num_of_times_each_philosopher_must_eat]
```
Por ejemplo puedes escribir lo siguiente:
```bash
./philosophers 5 800 200 200 5
```
