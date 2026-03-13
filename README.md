<div align="center">

# Klip

Gestor de contraseñas minimista para terminal.

</div>

---

# Características

- Base de datos local cifrada.
- Sistema de autenticación con contraseña maestra.
- Copia rápida de usuario o contraseña al portapapeles.
- Generador de contraseñas seguras.
- Funcionamiento completamente offline.

---

# Instalación

```bash
git clone ...
cd klip
mkdir build
cd build
cmake ..
make
```
---

# Uso

## Ejecutar el programa

```bash
./klip <archivo_db>
```

- Si no se proporciona un archivo de base de datos, se solicitará uno mediante un menú interactivo.
- Si el archivo no existe se crea automaticamente

---

# Primera ejecución

En el primer inicio:

1. Se crea el directorio ```~/.config/klip/```

2. Se solicita crear una **contraseña maestra**.

Esta contraseña se almacena haseada en: ```~/.config/klip/password.txt```

---

# Navegación del menú

Controles principales:

| Tecla       | Acción                    |
| -------     | ------------------------- |
| `j` / `DOWN`| bajar                     |
| `k` / `UP`  | subir                     |
| `Enter`     | seleccionar / copiar      |
| `n`         | nueva credencial          |
| `f`         | filtrar por sitio         |
| `e`         | editar credencial         |
| `d`         | eliminar credencial       |
| `g`         | generar contraseña segura |
| `q`         | salir                     |

---

# Copiar al portapapeles

Cuando una credencial está seleccionada:

- `Enter` sobre **User** copia el usuario.
- `Enter` sobre **Pass** copia la contraseña.

---

# Generador de contraseñas

Klip incluye un generador de contraseñas que utiliza:

- letras mayúsculas
- letras minúsculas
- números
- símbolos

La longitud es configurable desde el menú.

---

# Sistema de cifrado

- La contraseña maestra se convierte en un **hash**.
- Ese hash se usa como **semilla de un PRNG**.
- El flujo de números pseudoaleatorios genera una clave.
- Cada carácter del texto se cifra usando esa clave:

```
cipher = char XOR key
```

- El resultado se codifica en **hexadecimal** para que el parser lo interprete correctamente.

Gracias a este método no se podrá tener acceso a la base de datos si se consigue cambiar la contraseña.

---

## Contribuciones

Las contribuciones siempre son bienvenidas. Si encuentras un error o quieres ayudar con alguna mejora puedes:
- Abrir un issue en el repositorio.
- Hacer un fork.
- Abrir una pull request.
- Mandarme un email a <a href="mailto:h.vidal7@proton.me"> h.vidal7@proton.me </a>
