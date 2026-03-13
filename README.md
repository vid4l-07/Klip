# Klip

Gestor de contraseñas ligero para terminal escrito en **C++**.
Permite almacenar credenciales de forma cifrada en un archivo local y gestionarlas mediante una interfaz interactiva en la terminal.

El proyecto está diseñado para ser **minimalista, rápido y completamente offline**, sin dependencias externas ni servicios en la nube.

---

# Características

- Base de datos local cifrada.
- Sistema de autenticación con contraseña maestra.
- Copia rápida de usuario o contraseña al portapapeles.
- Generador de contraseñas seguras.
- Funcionamiento completamente offline.

---

# Capturas conceptuales

El flujo de uso de Klip sigue esta estructura:

1. Autenticación con contraseña maestra
2. Selección del archivo de base de datos
3. Gestión de credenciales mediante el menú interactivo

El menú principal permite navegar entre credenciales, visualizar usuario y contraseña, copiarlos al portapapeles o gestionar la base de datos.

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

# Base de datos

Las credenciales se almacenan en un archivo definido por el usuario.

Cada entrada contiene:

```
site
user
password
```

Antes de almacenarse, cada campo se **cifra** usando un PRNG derivado del hash de la contraseña maestra.

Formato interno del archivo:

```
encrypted_site;encrypted_user;encrypted_pass;|
```

---

# Navegación del menú

Controles principales:

| Tecla   | Acción                    |
| ------- | ------------------------- |
| `j`     | bajar                     |
| `k`     | subir                     |
| `Enter` | seleccionar / copiar      |
| `n`     | nueva credencial          |
| `f`     | filtrar por sitio         |
| `e`     | editar credencial         |
| `d`     | eliminar credencial       |
| `g`     | generar contraseña segura |
| `q`     | salir                     |

---

# Copiar al portapapeles

Cuando una credencial está seleccionada:

* `Enter` sobre **User** copia el usuario
* `Enter` sobre **Pass** copia la contraseña

El copiado se realiza usando la secuencia de escape:

```
OSC 52
```

lo que permite copiar directamente al portapapeles desde la terminal compatible.

---

# Generador de contraseñas

Klip incluye un generador de contraseñas que utiliza:

* letras mayúsculas
* letras minúsculas
* números
* símbolos

La longitud es configurable desde el menú.

---

# Sistema de cifrado

El cifrado funciona de la siguiente manera:

1. La contraseña maestra se convierte en un **hash**.
2. Ese hash se usa como **semilla de un PRNG (mt19937)**.
3. El flujo de números pseudoaleatorios genera una clave.
4. Cada carácter del texto se cifra usando esa clave:

```
cipher = char XOR key
```

5. El resultado se codifica en **hexadecimal** para que el parser lo interprete correctamente.

Gracias a esto no se podra tenter acceso a la base de datos si se consigue cambiar la contrasena.

---

# Seguridad

Características de seguridad:

* cifrado basado en XOR con PRNG
* datos almacenados localmente
* contraseña maestra protegida por hash

---

## Contribuciones

Las contribuciones siempre son bienvenidas. Si encuentras un error o quieres ayudar con alguna mejora puedes:
- Abrir un issue en el repositorio
- Hacer un fork
- Abrir una pull request
- Mandarme un email a <a href="mailto:h.vidal7@proton.me"> h.vidal7@proton.me </a>
