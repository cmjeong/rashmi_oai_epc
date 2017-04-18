echo "started"
sh ../sep.sh
cd ccpu/
sh ../../ccpu_clean.sh
cd ../rad/
sh ../../rad_clean.sh
cd ../tril/
sh ../../tri_clean.sh
cd ..
ls
sh ../combine.sh
ls
echo "ended"
