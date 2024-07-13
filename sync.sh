cd res
rm -rf rdpwrap.ini
wget https://raw.githubusercontent.com/sebaxakerhtc/rdpwrap.ini/master/rdpwrap.ini
cd ..
git commit res/rdpwrap.ini -m sync
git push -f origin master