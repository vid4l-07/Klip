<div align="center">

# Klip

Minimal terminal-based password manager.

<img src=".github/screenshot.gif" alt="descripcion"  width="700">

</div>

## Features

- Encrypted local database.
- Master password authentication system.
- Quick copy of username or password to the clipboard.
- Secure password generator.
- Fully offline operation.


## Installation

```bash
git clone https://github.com/vid4l-07/Klip.git
cd klip
mkdir build
cd build
cmake ..
make
```

## Usage

### Run the program

```bash
./klip <database_file>
```

- If no database file is provided, one will be requested through an interactive menu.
- If the file does not exist, it will be created automatically.


### First run

On the first launch:

1. The directory ```~/.config/klip/``` is created.

2. You will be prompted to create a master password.

This password is stored hashed in: ```~/.config/klip/password.txt```

### Menu navigation


| Key        | Action                    |
| -------    | ------------------------- |
| `j` / `DOWN` | move down               |
| `k` / `UP`   | move up                 |
| `Enter`      | select / copy           |
| `n`          | new credential          |
| `f`          | filter by site          |
| `e`          | edit credential         |
| `d`          | delete credential       |
| `g`          | generate secure password|
| `q`          | quit                    |


### Copy to clipboard

When a credential is selected:

- `Enter` on User copies the username.
- `Enter` on Pass copies the password.


## Encryption system

- The master password is converted into a hash.
- That hash is used as a PRNG seed.
- The pseudo-random number stream generates a key.
- Each character of the text is encrypted using that key:

```
cipher = char XOR key
```

- The result is encoded in hexadecimal so the parser can interpret it correctly.

With this method, the database cannot be accessed even if someone modifies the password.

---

## Contributions

Contributions are always welcome. If you find a bug or want to help with new features, you can:

- Open an issue in the repository.
- Fork the project.
- Open a pull request.
- Send me an email at <a href="mailto:h.vidal7@proton.me"> h.vidal7@proton.me </a>
