#!/bin/sh

# /var/static промонтированный volume со всей статикой
# /var/www/public/storage первый симлинк для лары
# /var/www/storage/app/public второй симлинк для вояджера
LINK_PATH=/var/static

TEST_ONE=/var/www/public/storage
TEST_TWO=/var/www/storage/app/public

fix_symlink () {
    if [ -L $1 ] ; then
        if [ -e $1 ] ; then
            echo "Good link"
        else
            echo "Link is broken! Trying to fix them"
            rm $1
            ln -s $LINK_PATH $1
        fi
    elif [ -e $1 ] ; then
        echo "It is not a link, it is folder! Trying to fix them"
        rm -rf $1
        ln -s $LINK_PATH $1
    else
        echo "Missing link! Trying to fix them"
        ln -s $LINK_PATH $1
    fi
    chown 1000:985 $1 -R
    chmod -R 777 $1
}

fix_symlink $TEST_ONE
fix_symlink $TEST_TWO