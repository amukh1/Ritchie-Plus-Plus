<!-- [![npm version](https://badge.fury.io/js/ritchie.svg)](https://www.npmjs.com/package/ritchie) -->
[![GitHub version](https://badge.fury.io/gh/amukh1%2FRitchie-Plus-Plus.svg)](https://badge.fury.io/gh/amukh1%2FRitchie-Plus-Plus)

# Ritchie ++

> A Non- Statically-Typed *compiled* programming language that compiles to x86.

<br>

> Contact me for help, because I *will* respond. Discord: amukh1#9613

# Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

# Installation
<br>

**BEFORE YOU INSTALL:** please read the [prerequisites](#prerequisites)

<br>

## To install and set up the library, run:

From Github:

```sh
$ git clone https://github.com/amukh1/Ritchie-Plus-Plus
$ cd Ritchie-Plus-Plus
$ g++ *.cpp -o rpp
$ sudo cp ./rpp /usr/bin
```

From APT:
    
```sh
$ sudo apt install rpp
```

<!-- ## There is also a vscode extension:
**[Extension Link](https://marketplace.visualstudio.com/items?itemName=amukh1.ritchie)**

**Or  just search up "Ritchie++" in the extensions section**

![img](./rvsco.png) -->


# Usage

<br>

## For x86 (Intel Linux):
```sh
$ rpp ./name.rpp -o name
$ nasm -f elf64 name.asm
$ ld -m elf_i386 -o -s name.o -o name
$ ./name
```
## For C (Depreca ted):
```sh
$ rpp ./name.rpp -c name
$ gcc name.c -o name
$ ./name
```

## ASM compiles to bytecode with NASM on Linux (if your on Windows/OSX use an online [assembler](https://www.jdoodle.com/compile-assembler-nasm-online/)).
<!-- ## [Web Assembler](https://www.jdoodle.com/compile-assembler-nasm-online/) -->

## Alternatively, if you are not on an Intel Machine, you can use *QEMU* to emulate an x86 machine.

## Install QEMU:
```sh
$ sudo apt install qemu
```

## Run QEMU:
```sh
$ rpp ./name.rpp -o name
$ nasm -f elf64 name.asm
$ ld -m elf_i386 -o -s name.o -o name
$ qemu-i386 ./name
```

## Example program:
<br>

```c
import "stdio"; /* Imports the standard input/output library */
import "stdlib"; /* Imports the standard library */

func main(argc, argv) {
   println("Hello World!", 12); /* Prints "Hello World!" */
   var v = 0; /* Declares a variable */
   var v = "hi"; /* Re-Declares a variable */
   println(v, 2); /* Prints the value of v */
   var& a = v; /* Declares a reference to v */
   var* b = a; /* De-Reference a */
   println(b, 2); /* Prints the value of b */

   return 0; /* Returns 0 */
};
```

```
Hello World!
hi
hi
```
<!-- ## Wanna learn more? check out the docs: [Visit docs](https://ritchie.js.org/docs) -->

<!-- <style>
.docs {
    transition: all 0.5s ease;
    position: relative;
    top: 0px;
    background-color:#0f38f0; 
    border-radius:25px; 
    color: white; 
    padding:25px;
    border: none;
}

.docs:Hover {
    top: -10px;
    background-color: #0009a8;
        /* color: white;  */
}

.a {
      text-decoration: none;
    color: white;
    font-size: 2rem;
}

</style> -->

<!-- <button class="docs" href="/handbook/toc/" style="" onClick="()=>{alert('Missed the link?')}">
<a class="a" href="https://ritchie.js.org/docs/">Visit Docs</a>
</button> -->


<br>

## Contributing

You can contribute to the project by making a pull request on [GitHub](https://github.com/amukh1/Ritchie-Plus-Plus).

## Credits

### Amukh1.

## Built With

* [C++](https://cplusplus.com/)
* [Assembly](http://x86asm.net/)
* [Love](https://amukh1.dev)

## Authors

* **Amukh1** - [Github](https://github.com/amukh1) / amukh1#9613

See also the list of [contributors](https://github.com/amukh1/Ritchie-Plus-Plus/contributors) who participated in this project.

## License

[MIT License](https://mit-license.org/2022) © Amukh1
