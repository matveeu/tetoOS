#!/home/whoami/.nix-profile/bin/bash

rm -f tetos.iso 

if [ ! -f myos.bin ]; then
        echo "Error: myos.bin not found! Run 'make' first."
        exit 1
fi

cp myos.bin iso/boot/

nix-shell -p grub2 xorriso mtools --run "grub-mkrescue -o tetos.iso iso/"
