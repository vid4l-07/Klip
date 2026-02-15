# Klip - Gestor de Contraseñas en C++

Klip es un gestor de contraseñas simple desarrollado en **C++**, diseñado como proyecto de aprendizaje. Permite almacenar, ver, generar, editar y eliminar credenciales de forma local, con una interfaz de línea de comandos interactiva.

---

## Características

- **Gestión de contraseña maestra:** Solo puedes acceder a tus credenciales con la contraseña principal.  
- **Almacenamiento de credenciales:** Guarda sitios, usuarios y contraseñas de manera local.  
- **Generador de contraseñas aleatorias:** Puedes generar contraseñas seguras con longitud personalizada.  
- **Interfaz interactiva:** Menú con opciones para ver, filtrar, editar y eliminar credenciales.  
- **Protección básica:** Contraseñas y datos se guardan cifrados (cifrado simple tipo César).

---

## Estructura del Proyecto

- `Auth.h / Auth.cpp` → Manejo de la contraseña maestra.  
- `Database.h / Database.cpp` → Gestión de la base de datos de credenciales.  
- `Creds.h` → Representación de una entrada de credenciales.  
- `Security.h / Security.cpp` → Funciones de cifrado y generación de contraseñas.  
- `Ui.h / Ui.cpp` → Interfaz de usuario y menús interactivos.  
- `main.cpp` → Punto de entrada del programa.

---

## Instalación

1. Clonar o descargar el repositorio:

```bash
git clone https://github.com/vid4l-07/Klip.git
cd klip
```

2. Compilar

```bash
make clean
make
```

3. Ejecutar

```bash
./klip
```
---

## Uso

1. Al ejecutar por primera vez, se solicitará crear una contraseña maestra.

2. Una vez dentro, el menú principal permite:

- Ver todas las contraseñas guardadas.

- Añadir nuevas credenciales.

- Generar contraseñas aleatorias.

- Editar o eliminar entradas existentes.

3. La contraseña maestra se solicita cada vez que se inicia el programa (hasta 3 intentos).

---

## Advertencias de Seguridad

- El cifrado actual es básico y no seguro (tipo César). No usar para contraseñas reales importantes.

- Las credenciales se almacenan en archivos de texto local (~/.config/klip/db.txt).

- Este proyecto está pensado como ejercicio de programación y no reemplaza gestores de contraseñas profesionales.
