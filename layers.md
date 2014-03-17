# Base networking layer (0)

## Open connection
*Client.*
How do we open a connection? We're gonna need a particular machine's IP:port pair and such.

## Send data
*Client.*
Load the file into memory and put it out via the UDP socket.

## Write received data
*Server.*
Grab data from UDP socket and write data to file.

## Send data transfer confirmation
*Server.*
Close file and send the client a confirmation of the transfer.

## Receive data transfer confirmation
*Client.*

Print receipt? And close.

## Other pieces
We also need a timer to figure out when we should consider the packet lost to time and just resend the packet.

# Header layer (1)
We'll need to design our headers. One bit needs to be the sequence number. In my opinion, this should be the first bit --
so we can just read it and determine whether or not our gremlin was successful. We also need a checksum and a section for
ACK/NAK.

## Check previous send's sequence number
*Client.*

If our last send was a 0 or didn't exist, make this one a 1. Otherwise, make it a 0.

## Create checksum
*Client.*

Add all the bits in the package for the checksum.

## Give each sent object a header
*Client.*

Self-explanatory. On send, just before sending, build a header from our gathered information and prepend it to the
package.

# Segmentation and reassembly layer (2)
## Break apart file
*Client.*

Separate file data to transmit into packets of size 128B (is it bytes or was it bits? grrr I'll correct this later). 

## Reassemble file
*Server.*

Take each packet and combine it back into one object.

# Gremlin layer and error correction layer (3)
*More to come.*


