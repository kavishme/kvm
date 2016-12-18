sudo insmod bonusmodule.ko REQUEST=2
sudo rmmod bonusmodule
dmesg | grep "Bonus2"