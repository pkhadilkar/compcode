compcode
========
compile() {
        fullpath=`pwd`
        dir=`basename $fullpath`
        g++ -Wall -ggdb3 -o $dir "$dir".cpp
}

export compile
