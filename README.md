# DataSerialization
Data (De)Serialization

**Data Serialization** is a mechanism to transform the program's internal data structure into a form that could be sent to a remote machine over the network.
**Data (De)Serialization** helps in making data exchange between processes running on heterogeneous machines independent of underlying OS, Compiler, Programming Language, Hardware and the like.

>struct student_t {
  char name[30];
  int id;
  int no;
}

The memory layout for the above code is way more different in different architectures. So, without data (de)Serialization, it is impossible to have communication between heterogeneous machines.

Note that, Data (De)Serialization is one of the most important building block of various system programming concepts such as: RPC, State Synchronization, Check Pointing the application state.

Data Serialization deletes pads compiler adds in data structures. In the above code, the memory layout of the structure is somehow different with the its actual memory footprint. There are nested structures in some programs which contains pointer to the child's structure. In this case, when the data is serialized, the pointer is translated to 0xF...FF . This is called **Sentinel** value. During deserialization, when we encounter the Sentinel value in the serialized object, we know that this field was set to NULL in the original object.
Data Serialization is done in 3 condition:

1) Simple C structures

2) C structure with nested C sub-structure

3) C structure with pointer members

Data Serialization/deserialization is all about removing and adding padding bytes in the data structure memory footprint with the help of **Compiler**. So, it's important to know that the compiler involves in both processes and the programmer does not explicitly add the padding bytes.



| StructureName  |     Serialization Routine     |   Deserialization Routine   |
|----------------|-------------------------------|-----------------------------|
|  Person_t      |void serialize_person_t(person_t \*obj, ser_buff_t \*b);|person_t* de_serialize_person_t(ser_buff_t* b);|          |  Company_t     |void serialize_company_t(company_t \*obj, ser_buff_t \*b);|company_t* de_serialize_company_t(ser_buff_t* b);|
