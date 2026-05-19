<div align="center">

# Klip

Minimal terminal-based password manager.

<img src=".github/screenshot.gif" alt="descripcion"  width="700">

</div>

## Features

- Encrypted local database.
- Secure encryption sistem using ```Argon2id``` for key derivation and autenticated encryption with ```libsodium```.
- Quick **copy** of username or password to the clipboard.
- Secure password generator.
- Fully **offline** operation.


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

- If no database file is provided, one will be requested through an interactive menu, where you can navigate recent databases by pressing ```TAB```.
- If the file does not exist, it will be created automatically.


### First run

On the first launch:

1. The directory ```~/.config/klip/``` is created used to store the **recent files** paths.

### Menu navigation


| Key        | Action                    |
| -------    | ------------------------- |
| ```j``` / ```DOWN``` | move down               |
| ```k``` / ```UP```   | move up                 |
| ```Enter```      | select / copy           |
| ```n```          | new credential          |
| ```f```          | filter by site          |
| ```e```          | edit credential         |
| ```d```          | delete credential       |
| ```g```          | generate secure password|
| ```q```          | quit                    |


### Copy to clipboard

When a credential is selected:

- ```Enter``` on User copies the username.
- ```Enter``` on Pass copies the password.


---

## Security

All encryption logic is located in ```src/Security.cpp```

### Key derivation

* When creating a database, a master password is requested.
* A cryptographic key is derived from the password and a unique ramdom salt using ```crypto_pwhash``` from **libsodium**, based on **Argon2id** in **INTERACTIVE** mode (adjustable cost parameters against brute-force attacks).

### Encryption

* The database is encrypted using ```crypto_secretbox_easy``` with the derived key and a random nonce.
* This algorithm provides tamper detection through a MAC.

### Storage format

* The encrypted file is stored in binary with the following format:

```
[salt][nonce][ciphertext]
```

### Decryption process

* The key is derived using the password provided by the user and the stored salt.
* The data is decrypted using ```crypto_secretbox_open_easy```.
* If the password is incorrect or the file has been modified, MAC verification fails and the operation is rejected.

---

## Contributions

Contributions are always welcome. If you find a bug or want to help with new features, you can:

- Open an issue in the repository.
- Fork the project.
- Open a pull request.
- Send me an email at <a href="mailto:h.vidal7@proton.me"> h.vidal7@proton.me </a>div align="center">
