function green_printf {
    printf "\033[0;32m$1\033[0m" 
}

function red_printf {
    printf "\033[1;31m$1\033[0m"
}

function yellow_printf {
    printf "\033[0;33m$1\033[0m"
}
