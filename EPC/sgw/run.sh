echo "started"
sh ../sep.sh
cd ccpu/
sh ../../rad_clean_ccpu.sh
cd ../rad/
sh ../../rad_clean.sh
cd ../tril/
sh ../../tri_clean.sh
cd ..
ls
sh ../combine.sh
ls
echo "ended"
