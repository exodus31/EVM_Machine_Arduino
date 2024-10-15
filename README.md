# Electronic Voting Machine (EVM) Using Arduino UNO

## Overview
This project is an Electronic Voting Machine (EVM) built using an Arduino UNO, designed for secure and reliable voting. The machine uses a unique identification code to ensure one vote per person and includes multiple features to streamline the voting process.

## Features
- **Unique Identification Code**: Each voter is required to input a unique identification code to cast a vote, ensuring that only one vote can be cast per person.
- **4x4 Keypad Input**: The system uses a 4x4 keypad for voters to input their unique identification code and select the party they want to vote.
- **Sleep Mode**: After a vote is cast, the machine goes into a 2-minute sleep mode to prevent immediate consecutive voting.
- **Edge Case Handling**: The code is designed to handle various edge cases, such as:
  - Invalid inputs
  - Multiple vote casting attempts
  - Ensuring a hassle-free voting process
- **3D-Printed Structure**: The machine's components, including the Arduino board and keypad, are securely housed in a custom 3D-printed structure for durability and stability.

## Hardware
- **Arduino UNO**: The core of the voting machine.
- **4x4 Keypad**: Used to take input from the user.
- **3D-Printed Structure**: A custom-built frame to hold the Arduino, keypad, and other components.

## How It Works
1. The voter enters their unique identification code using the 4x4 keypad.
2. After the vote is registered, the system enters a 2-minute sleep mode to prevent multiple votes in quick succession.
3. The system is equipped with error handling to manage invalid input and ensure voting security.
