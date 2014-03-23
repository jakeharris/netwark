We decided that we couldn't send something over the network without "serialization." We need to decide whether we
want to use serialization and pass our entire Packet objects through the sendto/recvfrom interface, or individually
and manually send each field, or even combine the fields into one field and then deconstruct on the other side.
(I think this last option is essentially serialization, but I'm uncertain.)

Check the client.cpp file, towards the bottom. 
