# cp /boot/config-`uname -r` .config

make oldconfig
fakeroot make-kpkg --initrd kernel_image kernel_headers  -j3

sudo dpkg -i ../linux-image-*.deb
sudo dpkg -i ../linux-headers-*.deb

