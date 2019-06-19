#!/bin/sh

cd "$(dirname "$0")"
rm -rf tmp
mkdir tmp
cd tmp

os=`uname -s`
if [[ $os = "Linux" ]]; then
    url="https://anaconda.org/shaktidb/shakti/2019.06.08/download/linux-64/shakti-2019.06.08-1176_g9aa9d4d.tar.bz2" 
else
    url="https://anaconda.org/shaktidb/shakti/2019.06.08/download/osx-64/shakti-2019.06.08-1176_g9aa9d4d.tar.bz2"
fi

echo "Downloading archive..."
curl -LGs $url | tar -jxf - "info/LICENSE.txt" "lib/k.so"
cat info/LICENSE.txt
echo ""

while true
do
    read -r -p "To continue, you must agree to the terms of this evaluation agreement [Y/n] " input
    case $input in
        [yY][eE][sS]|[yY])
    cp lib/k.so ..
    break
    ;;
        [nN][oO]|[nN])
    echo "Aborting installation..."
    break
    ;;
        *)
    echo "Please type \"yes\" or \"no\""
    ;;
    esac
done

cd ..
rm -r tmp
