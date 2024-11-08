# **UDP Communication Program**

## **Overview**
This project demonstrates UDP communication between a sender and a receiver using both IPv4 and IPv6.

- The **receiver** listens for messages on a specified port and echoes the received message back to the sender.
- The **sender** sends a message to the receiver and waits for a reply.

## **Files**
1. **`3-receiver.cc`**: The receiver program.
2. **`2-send.cc`**: The sender program.
3. **`Makefile`**: Automates compilation and execution.

## **Features**
- Supports both **IPv4** and **IPv6** communication.
- The sender infers the IP version based on the receiver’s address.
- The receiver specifies the IP version (`-4` for IPv4, `-6` for IPv6) via command-line arguments.

## **Compilation**
To compile both the sender and receiver programs, run:
