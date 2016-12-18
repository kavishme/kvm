sudo insmod bonusmodule.ko REQUEST=4
sudo rmmod bonusmodule
dmesg | grep "Bonus4"