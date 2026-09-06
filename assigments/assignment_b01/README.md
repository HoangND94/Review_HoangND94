#

## 1. Description

This program creates a synthetic device status record from command line input.

The record contains:

* ID
* State
* Flags
* Payload

There are 3 valid states:

* `INIT`
* `ACTIVE`
* `FAULT`

There are 2 payload types:

* `temp`
* `rpm`

## 2. Data Types

`uint32_t` is used for the ID because the ID is non-negative and needs a fixed 32-bit type.

`uint8_t` is used for flags because flags are stored as one unsigned byte, with values from 0 to 255.

`DeviceState` is an enum used to define the three valid states.

`PayloadKind` is an enum used to identify whether the payload is temperature or RPM.

`PayloadValue` is a union because only one payload value is needed at a time.

`DeviceStatus` is a struct that contains all fields of the status record.

## 3. Input Validation

Numbers are parsed using `strtoimax()`.

The program checks the range before converting the value to a smaller type:

* ID: `0 .. UINT32_MAX`
* Flags: `0 .. UINT8_MAX`
* Temperature: `INT32_MIN .. INT32_MAX`
* RPM: `0 .. UINT32_MAX`

If a value is invalid, the program prints an error and returns `2`.

State must be `INIT`, `ACTIVE`, or `FAULT`.

Payload type must be `temp` or `rpm`.

## 4. Union and Lifetime

`PayloadValue` contains two members: `temperature_c` and `rpm`.

The program uses `payload_kind` to decide which union member should be read. It does not read the other member.

The fields are stored directly inside the `DeviceStatus` structure. No pointer is used for the payload. The record is created in `main` and exists during the program execution.

## 5. Build and Run

Build command:

```text
gcc -std=c17 -Wall -Wextra -Wpedantic -Werror main.c -o device_status
```

Example with temperature:

```text
./device_status 100 ACTIVE 5 temp 25
```

Example with RPM:

```text
./device_status 101 INIT 255 rpm 3200
```

Invalid examples:

```text
./device_status 100 RUNNING 5 temp 25
./device_status 100 ACTIVE 256 temp 25
./device_status 100 ACTIVE 5 voltage 12
```

Invalid input is rejected and does not produce a successful record output.

## 6. Test Evidence

The test results are recorded in `evidence.txt`.

The tests include:

* 2 valid payload cases
* 3 invalid input cases
* Strict compiler flags
