# Data formats and permissions

The program uses newline-delimited records with `#//#` between fields. Files are resolved relative to the working directory, so launch the app from the project root. There is no escaping mechanism: field values must not contain the separator or a newline.

## Client records

`data/Clients.txt`:

```text
FirstName#//#LastName#//#Email#//#Phone#//#AccountNumber#//#PinCode#//#Balance
```

Example:

```text
Alex#//#River#//#alex@example.com#//#5550101#//#A101#//#1234#//#1000.000000
```

The account number identifies the client. A save updates the matching record or appends a new one depending on the object's mode. PINs are stored as text, and balances are serialized from floating-point values.

## User records

`data/Users.txt`:

```text
FirstName#//#LastName#//#Email#//#Phone#//#Username#//#ShiftedPassword#//#Permissions
```

Passwords are encoded by shifting each character by five positions, then decoded during loading. This is a string manipulation exercise, not secure password storage. The included `admin` account uses password `learn123` and permissions `-1`.

| Permission | Value |
| --- | ---: |
| All features | -1 |
| List clients | 1 |
| Add client | 2 |
| Delete client | 4 |
| Update client | 8 |
| Find client | 16 |
| Transactions | 32 |
| Manage users | 64 |
| View login register | 128 |

Combine individual permissions with bitwise OR. For example, `1 | 16 | 32` equals `49`, granting list, find, and transaction access. A value of `0` grants none of these features.

## Login register

`data/LoginRegister.txt` is created when a successful login is recorded:

```text
DateTime#//#Username#//#Permissions
```

The record reflects the user's permissions at login time. Failed attempts are not recorded in this file.

## Transfer log

`data/TransfersLog.txt` is created when a transfer is recorded:

```text
DateTime#//#SenderAccount#//#ReceiverAccount#//#Amount#//#SenderBalance#//#ReceiverBalance#//#Username
```

Balances are recorded after the transfer. Date/time values come from the machine's local clock.

The parser currently uses `stoi` for amount and balance fields, so fractional values are lost when logs are read. Its `ReceiverAccountBalance` member holds the serialized sender balance, and its `SenderAccountBalance` member holds the receiver balance. Consult field positions when studying this code.

## Working with the dataset

- All supplied names, contact details, and credentials are fictional learning data.
- Client and user changes persist immediately and are not reset by rebuilding.
- Logs are generated locally and ignored by Git.
- Back up the two starter files before an exercise if you want to restore the same initial state later.
- Avoid editing files while the application is running. The app has no file locking or support for concurrent writers.
- Keep records complete and avoid blank lines; parsers assume the expected number of fields and valid numeric values.
