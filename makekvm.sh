# remove kvm module
sudo modprobe -vr kvm-intel
sudo modprobe -vr kvm

sudo rm -f /lib/modules/`(uname -r)`/kernel/arch/x86/kvm/kvm*

sudo make modules SUBDIRS=arch/x86/kvm
sudo make modules_install SUBDIRS=arch/x86/kvm INSTALL_MOD_DIR=kernel/arch/x86/kvm


sudo modprobe -v kvm
sudo modprobe -v kvm-intel
sudo modprobe -v kvm-amd