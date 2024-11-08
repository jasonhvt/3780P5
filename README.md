# **UDP Communication Program**

## **Overview**
This project demonstrates UDP communication between a sender and receiver using both IPv4 and IPv6.

- The **receiver** listens on a specified port, echoes received messages, and supports both IPv4 and IPv6.
- The **sender** sends messages to the receiver and waits for a reply.

## **Files**
- **`3-receiver.cc`**: Receiver program.
- **`2-send.cc`**: Sender program.
- **`Makefile`**: Automates compilation and execution.

## **Compilation**
Compile both programs with: make

## **Usage**

### **Run Receiver**
Start the receiver on port `3000`:
- IPv4: make run-receiver PROTOCOL=-4
- IPv6: make run-receiver PROTOCOL=-6

### **Run Sender**
Run the sender and send a message: make run-sender

### **Custom Receiver Address**
To send to a remote receiver: /sender <receiver_address> 3000

## **Testing**
1. **Local**: Run receiver and sender on the same machine in different terminals.
2. **Remote**: Run the receiver on `student0`: ssh student0.cs.uleth.ca ./receiver 3000 -4.
**Remote**: Then run the sender locally: ./sender student0.cs.uleth.ca 3000

## **Cleaning Up**
Remove executables: make clean













